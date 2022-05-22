from utils.log import Logger
import xml.etree.ElementTree as ET


class XmlUtils:
    def __init__(self, xmlfile):
        self.xmlfile = xmlfile
        self.L = Logger()
        self.root = ET.parse(self.xmlfile).getroot()
        pass

    def getXmlItem(self, pathlist):
        item = self.root
        for element in pathlist:
            item = item.find(element)
        return item

    def getXmlAllItems(self, pathlist):
        item = self.root
        for i in range(len(pathlist)-1):
            item = item.find(pathlist[i])

        return item.findall(pathlist[-1])

    def getXmlItemText(self, pathlist):
        item = self.getXmlItem(pathlist)
        return item.text

    def getConfigProperty(self, pathlist, keyName):
        # works with entries like
        # <property key="optimization-level" value="2"/>
        items = self.getXmlAllItems(pathlist)
        self.L.i("All items : {}".format(items))
        for item in items:
            value = item.get("key")
            if value == keyName:
                return item.get("value")
        return None
