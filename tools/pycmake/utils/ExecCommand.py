from utils import log
import subprocess

LOG_FILE = "terminal.log"
ERR_LOG_FILE = "err.log"


class ShellCommand:
    def __init__(self, cfg=None):
        self._cmd = list()
        self.errorCode = -1
        if cfg is None:
            self.logFile = LOG_FILE
            self.errLogFile = ERR_LOG_FILE
            self.L = log.Logger(None)
        else:
            self.logFile = cfg.logFile
            self.errLogFile = cfg.errLogFile
            self.L = log.Logger(cfg.logFile)
        pass

    def startCmdMinimized(self, paramList):
        self._cmd = list()
        self._cmd.append('start')
        self._cmd.append('/wait')
        self._cmd.append('/min')
        for param in paramList:
            self._cmd.append(param)
        self.L.i("Starting Command : {}".format(self._cmd))
        self._execSubProcessCallWithLogging()
        pass

    def execCmd(self, paramList):
        self._cmd = list()
        for param in paramList:
            self._cmd.append(param)
        self.L.i("Executing Command : {}".format(self._cmd))
        self._execSubProcessCallWithLogging()
        pass

    def execBatchFile(self, paramList):
        self.execCmd(paramList)

    def _execSubProcessCallWithLogging(self):
        self.errorCode = -1
        with open(self.logFile, "a", encoding='utf-8') as hlog:
            with open(self.errLogFile, "a", encoding='utf-8') as herr:
                retcode = subprocess.call(self._cmd, shell=True, stdout=hlog, stderr=herr)
                self.errorCode = retcode
                self.L.i("Return code is : {}".format(retcode))
        pass

    def getExecutionResult(self):
        if self.errorCode != 0:
            self.L.i("ExecCommand - Execution Result - {}".format(self.errorCode))
        return self.errorCode
    pass
