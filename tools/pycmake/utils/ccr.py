import json

from utils.log import Logger

SYSV_INFO_FILE = "c:/Users/i52235/z/pws/benchmarking/scripts/_test/testData/size/dist/default/production/sysv-info.txt"
SYSV_INFO_TITLES = ["Name", "Value", "Class", "Type", "Size", "Line", "Section"]
CCR_JSON_FILE = "c:/Users/i52235/z/pws/benchmarking/scripts/_test/testData/size/dist/default/production/ccr.json"
DIAG_CCR_JSON_FILE = "c:/Users/i52235/z/pws/benchmarking/scripts/_test/testData/size/dist/default/production/ccr-diag.json"
TEXT_SECTION_VALUES = [".text", ".const", ".dinit"]
RAM_SECTION_VALUES = [".nbss", ".ndata", ".bss"]
DIAG_MODULES_NAMES = ["_DIAG_", "_FAULTINJ_"]


class Ccr:
    def __init__(self, cfg = None):
        self._cfg = cfg
        self.L = Logger()
        self.ccrData = list()
        self.infoFile = SYSV_INFO_FILE
        self.outFile = CCR_JSON_FILE
        self.outDiagFile = DIAG_CCR_JSON_FILE
        self.textSections = list()
        self.bssSections = list()
        self.nbssSections = list()
        self.diagModules = list()
        self.diagTextModules = list()
        self.diagDataModules = list()
        if cfg is not None:
            if cfg.ccrFile is not None:
                self.infoFile = cfg.ccrFile
                self.L.i("Using CCR file - {}".format(self.infoFile))
            if cfg.ccrOutFile is not None:
                self.outFile = cfg.ccrOutFile
                self.L.i("Using CCR output file - {}".format(self.outFile))
        pass

    def createInfo(self):
        with open(self.infoFile, "r") as inf:
            lines = inf.readlines()
            for line in lines:
                line = line.replace("\n", "")
                entries = str(line).split("|")
                if len(entries) == len(SYSV_INFO_TITLES):
                    data = dict()
                    i = 0
                    for entry in entries:
                        e = entry.replace(" ", "")
                        if (SYSV_INFO_TITLES[i] == "Value") or (SYSV_INFO_TITLES[i] == "Size"):
                            data[SYSV_INFO_TITLES[i]+"_str"] = e
                            if e != "":
                                data[SYSV_INFO_TITLES[i]+"_int"] = int(e, 16)
                            else:
                                data[SYSV_INFO_TITLES[i]+"_int"] = 0
                        else:
                            data[SYSV_INFO_TITLES[i]] = e
                        i += 1
                    # self.L.i("Entry -> {}".format(data))
                    self.ccrData.append(data)
        pass

    def writeInfo(self):
        with open(self.outFile, "w") as of:
            json.dump(self.ccrData, of)
        pass

    def getTextSections(self):
        with open(self.outFile, "r") as inf:
            self.textSections = list()
            jsondata = json.load(inf)
            for entry in jsondata:
                if entry["Section"] in TEXT_SECTION_VALUES:
                    self.textSections.append(entry)
                    self.L.i("Text section Entry -> {}".format(entry))

            size = 0
            constSize = 0
            textSize = 0
            miscSize = 0
            for entry in self.textSections:
                size += entry["Size_int"]
                if entry["Section"] == ".const":
                    constSize += entry["Size_int"]
                elif entry["Section"] == ".text":
                    textSize += entry["Size_int"]
                else:
                    miscSize += entry["Size_int"]

            self.L.i("Total Text section size = {}".format(size))
            self.L.i("text section size = {}".format(textSize))
            self.L.i("const section size = {}".format(constSize))
            self.L.i("other section size = {}".format(miscSize))

            diagSize = 0
            self.diagModules = list()
            for entry in self.textSections:
                if (str(entry["Name"]).startswith("_DIAG_")) or (str(entry["Name"]).startswith("_FAULTINJ_")):
                    diagSize += entry["Size_int"]
                    self.diagModules.append(entry)
                    self.L.i("Diag module -> {}".format(entry))
            self.L.i("Diag module size = {}".format(diagSize))
        pass

    def getDiagSections(self):
        self.diagTextModules = list()
        self.diagDataModules = list()
        with open(self.outFile, "r") as inf:
            self.textSections = list()
            jsondata = json.load(inf)
            for entry in jsondata:
                if entry["Section"] in TEXT_SECTION_VALUES:
                    for name in DIAG_MODULES_NAMES:
                        if str(entry["Name"]).startswith(name):
                            self.diagTextModules.append(entry)
                            break
                if entry["Section"] in RAM_SECTION_VALUES:
                    for name in DIAG_MODULES_NAMES:
                        if str(entry["Name"]).startswith(name):
                            self.diagDataModules.append(entry)
                            break
        with open(self.outDiagFile, "w") as of:
            jsonData = dict()
            jsonData["program"] = self.diagTextModules
            jsonData["data"] = self.diagDataModules
            json.dump(jsonData, of)
        pass
    