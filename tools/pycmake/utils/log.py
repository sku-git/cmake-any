LOG_FILE = "terminal-python.log"


def e(err):
    t = "\n[ERROR ] {}".format(err)
    print(t)
    with open(LOG_FILE, "a") as hlog:
        hlog.write(t)
    pass


def i(info):
    t = "\n[INFO ] {}".format(info)
    print(t)
    with open(LOG_FILE, "a") as hlog:
        hlog.write(t)
    pass


def w(warn):
    t = "\n[WARNING ] {}".format(warn)
    print(t)
    with open(LOG_FILE, "a") as hlog:
        hlog.write(t)
    pass


class Logger:
    def __init__(self, logFile=None):
        self.logFile = logFile
        if logFile is None:
            self.logFile = LOG_FILE
        pass

    def setLogFile(self, logFile):
        self.logFile = logFile
        pass

    def i(self, info):
        t = "\n[INFO ] {}".format(info)
        self._logText(t)

    def e(self, err):
        t = "\n[ERROR ] {}".format(err)
        self._logText(t)

    def w(self, warn):
        t = "\n[WARNING ] {}".format(warn)
        self._logText(t)

    def _logText(self, t):
        print(t)
        if self.logFile is None:
            return
        with open(self.logFile, "a", encoding='utf-8') as hlog:
            hlog.write(t)
        pass
    pass
