import serial
from utils.log import Logger
import time


def getProtocolType():
    return 2


class uartIntf:
    def __init__(self, cfg=None, port=None, baud=None):
        self._cfg = cfg
        self.L = Logger()
        self.port = port
        self.baudrate = baud
        self.timeout = 10
        self.rx = None
        self.tx = None
        self.ser = None

        if cfg is not None:
            self.port = cfg.serPort
            self.baudrate = cfg.serBaudrate
            self.timeout = cfg.serTimeout

        if getProtocolType() == 2:
            self.timeout = self.timeout * 1
        # self.L.i("UART Settings - port - {}, baudrate - {} timeoout -{}".format(self.port, self.baudrate, self.timeout))
        pass

    def open(self):
        self.ser = serial.Serial(port=self.port, baudrate=self.baudrate, timeout=self.timeout)
        self.ser.flushInput()
        self.ser.flushOutput()
        self.L.i("Opening Serial port {}".format(self.ser.name))

    def receiveLine(self):
        data = bytes(self.ser.readline())
        # self.L.i("UART Received data  - {}".format(data))
        self.rx = data.replace(b' ', b'').replace(b'\x00', b'').replace(b'\n', b'').split(b',')
        # self.L.i("UART Processed data - {}".format(self.rx))
        return self.rx

    def receiveLines(self, len=1):
        lines = list()
        for i in range(len):
            lines.append(self.receiveLine())
        return lines

    def receiveLineAscii(self):
        data = bytes(self.ser.readline())
        # self.L.i("UART Received bytes  - {}".format(data.hex()))
        return data

    def ignoreLine(self):
        data = bytes(self.ser.readline())
        return data

    def receiveBytes(self, len):
        data = bytes(self.ser.read(size=len))
        # self.L.i("UART Received bytes  - {}".format(data.hex()))
        self.rx = bytearray()
        for b in data:
            self.rx.append(b)
        return self.rx

    def sendBytes(self, data):
        time.sleep(0.1)
        self.tx = bytearray()
        for b in data:
            self.tx.append(b)
        self.ser.write(self.tx)
        # self.L.i("UART Transmit bytes  - {}".format(self.tx.hex()))
        pass

    def sendBytesAscii(self, data):
        time.sleep(0.1)
        self.tx = data
        self.ser.write(self.tx)
        # self.L.i("UART Transmit bytes  - {}".format(self.tx.hex()))
        pass
