import os
from pathlib import Path
from zipfile import ZipFile
from datetime import datetime
import uuid

from utils.log import Logger


class Zipper:
    def __init__(self, name, path):
        self.L = Logger()
        self.name = name
        self.path = path
        self.zipFile = Path(self.path).joinpath(name)
        self.extn = self._getUniqueName()
        pass

    def addDir(self, dir, archiveName=""):
        if not Path(dir).exists():
            self.L.w("The directory does not exists : {}".format(Path(dir).as_posix()))
        for root, dirs, files in os.walk(dir):
            for f in files:
                self.L.i("Adding file {} to archive".format(f))
                self._addToArchive(dir, root, f, archiveName)
        pass

    def _addToArchive(self, root, dir, fname, archName):
        # self.L.i("Root : {}, Directory  : {},  File : {}, Arch Name : {}".format(root, dir, fname, archName))
        archRoot = Path(dir).relative_to(Path(root))
        filename = Path(dir).joinpath(fname).absolute()
        archPath = "{}{}/{}/{}".format(archName, self.extn, archRoot, fname)
        # self.L.i("archRoot : {}, filename  : {},  archPath : {}".format(archRoot, filename, archPath))

        with ZipFile(file=self.zipFile, mode="a") as zof:
            # self.L.i("Member List : {}".format(zof.namelist()))
            zof.write(filename, arcname=archPath)
        pass

    def _getUniqueName(self):
        timeInfo = datetime.now().strftime("%y%m%d-%H%M%S")
        uid = uuid.uuid4()
        return "{}_{}".format(timeInfo, str(uid)[0:4])
