import csv
import json

from utils.log import Logger


class JsonToCsv:
    def __init__(self, csvOutFile, jsonData=None, jsonFile=None):
        self.jsonFile = jsonFile
        self.jsonData = jsonData
        self.csvFile = csvOutFile
        self.L = Logger()
        pass

    def convert(self, wa="w"):
        self.L.i("Converting JSON - {} to CSV - {}".format(self.jsonFile, self.csvFile))
        if self.jsonFile is not None:
            with open(self.jsonFile, "r") as inf:
                self.L.i("JSON file opened successfully")
                self.jsonData = json.load(inf)

        with open(self.csvFile, wa, newline="") as of:
            jsonEntry = self.jsonData[0]
            csvWriter = csv.writer(of)
            header = jsonEntry.keys()
            csvWriter.writerow(header)
            for jd in self.jsonData:
                csvWriter.writerow(jd.values())

        with open(self.csvFile, "a", newline="") as of:
            of.write("\r\n")

        pass

    def append(self):
        self.convert(wa="a")
        pass
