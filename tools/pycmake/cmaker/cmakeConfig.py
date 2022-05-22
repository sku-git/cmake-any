import json
import os
from pathlib import Path
from typing import List

from utils.OsUtils import create_folders, delete_folder_contents
from utils.log import Logger

L = Logger()


class ProjectConfig:
    def __init__(self, jsonData):
        self.projPath = jsonData["projPath"]
        self.cmakeOutpath = jsonData["cmakeOutpath"]
        self.excludeFolders = jsonData["excludeFolders"]
        self.fileExtnList = jsonData["fileExtnList"]

        self.projPathAbs = None
        self.cmakeOutPathAbs = None

    def show(self):
        L.i(f"projPath : {self.projPath}")
        L.i(f"cmakeOutpath : {self.cmakeOutpath}")
        L.i(f"excludeFolders : {self.excludeFolders}")
        L.i(f"fileExtnList : {self.fileExtnList}")
        L.i(f"projPathAbs : {self.projPathAbs}")
        L.i(f"cmakeOutPathAbs : {self.cmakeOutPathAbs}")

    pass


class CmakeConfig:
    def __init__(self, rootPath, settingsFile):
        self.toolRootDir = Path(rootPath).absolute()
        self.settings = Path(settingsFile).absolute()
        self.count = 1

        self.guestRoot = None
        self.guestRootFromBuildDir = None
        self.hostRoot = None
        self.hostCmakeFilesPath = None
        self.guestProjects: List[ProjectConfig] = []

        self._processSettings()

        pass

    def _processSettings(self):
        with open(self.settings, "r") as inf:
            jsonData = json.load(inf)
            self.guestRoot = Path(jsonData["tool"]["guestRoot"]).absolute()
            self.guestRootFromBuildDir = jsonData["tool"]["guestRootFromBuildDir"]
            self.hostRoot = Path(jsonData["cmakeGen"]["hostProject"]).absolute()
            self.hostCmakeFilesPath = Path(jsonData["cmakeGen"]["hostCmakeFilesPath"]).absolute()

            create_folders(self.hostCmakeFilesPath)
            projLists = jsonData["cmakeGen"]["projects"]
            for proj in projLists:
                projCfg = ProjectConfig(jsonData=proj)
                self.guestProjects.append(projCfg)
        pass

    def show(self):
        for proj in self.guestProjects:
            proj.show()
        pass

    def createCmakeFile(self):
        for proj in self.guestProjects:
            self._updateCurrentProjConfig(proj)
            self._createCmakeFiles(proj)
        self._createGuestCmake()
        pass

    def _updateCurrentProjConfig(self, proj: ProjectConfig):
        proj.projPathAbs = self.guestRoot.joinpath(proj.projPath).absolute()
        proj.cmakeOutPathAbs = self.hostCmakeFilesPath.joinpath(proj.cmakeOutpath).absolute()
        pass

    def _createCmakeFiles(self, proj: ProjectConfig):
        outdir = proj.cmakeOutPathAbs
        projdir = proj.projPathAbs
        create_folders(outdir)
        delete_folder_contents(outdir)
        cmekEntries = []
        for root, dirs, files in os.walk(projdir):
            dirs[:] = [d for d in dirs if d not in proj.excludeFolders]
            subdirfile = self._processDir(root, files, proj)
            cmekEntries.append(subdirfile)

        cmakefile = outdir.joinpath("CMakeLists.txt").absolute()
        with open(cmakefile, "w") as of:

            of.write(f"set(GUEST_SOURCE_ROOT ${{CMAKE_SOURCE_DIR}}/{self.guestRootFromBuildDir}/{proj.projPath})\n\n")
            for e in cmekEntries:
                of.write(f"include({e})\n")
            of.write("\n\n#Include path for the library\n")
            of.write("add_inc_folders(${GUEST_SOURCE_ROOT})\n")
        pass

    def _processDir(self, root, files, proj:ProjectConfig):
        outdir = proj.cmakeOutPathAbs
        extnList = proj.fileExtnList
        projdir = proj.projPathAbs
        dir_name = os.path.basename(root)
        filename = f"lib-{dir_name}-{self.count}.cmake"
        self.count += 1
        filepath = outdir.joinpath(filename).absolute()
        with open(filepath, "w") as of:
            for f in files:
                if Path(f).suffix in extnList:
                    relpath = Path(root).joinpath(f).relative_to(projdir)
                    of.write("add_src_files(${GUEST_SOURCE_ROOT}/" + relpath.as_posix() + ")\n")
        return filename

    def _createGuestCmake(self):
        outdir = self.hostCmakeFilesPath
        cmakefile = outdir.joinpath("CMakeLists.txt").absolute()
        with open(cmakefile, "w") as of:
            for proj in self.guestProjects:
                of.write(f"add_subdirectory({proj.cmakeOutpath})\n")
        pass
