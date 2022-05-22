import random
from typing import List

from utils.log import Logger

L = Logger()

def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]


def convToByteArray(num: int) -> List[int]:
    if num == 0:
        return [0]
    bitLen = num.bit_length()
    # print(f"{num}, {bitLen}, {bitLen % 8}")
    bitLen = bitLen % 8
    hxStr = f"{hex(num)}".replace("0x", "")
    if (bitLen < 4) and (bitLen != 0):
        hxStr = "0" + hxStr
    else:
        hxStr = hxStr
    # print(f"hxStr : {hxStr}")
    b = bytearray.fromhex(hxStr)
    return [h for h in b]


def parseDateFromX509Format(x509Date: str):
    """ Splits the format : 2020-03-06 11:56:00 -> 2020, 03, 06, 11, 56, 00"""
    dateInfo = x509Date.split(" ")[0]
    y = dateInfo.split('-')[0]
    m = dateInfo.split('-')[1]
    d = dateInfo.split('-')[2]

    timeInfo = x509Date.split(" ")[1]
    hh = timeInfo.split(':')[0]
    mm = timeInfo.split(':')[1]
    ss = timeInfo.split(':')[2]

    return int(y), int(m), int(d), int(hh), int(mm), int(ss)


def convertToHexList(byteList):
    return [hex(d) for d in byteList]


def getRandom(min=0, max=1):
    rand = random.random()
    prob = (max+min) / ((max - min) + 1)
    if prob < 0:
        prob *= -1
    # L.i(f"r, p : {rand}, {prob}")
    randNo = min
    for i in range(max+1):
        if (prob * (i + 1)) >= rand:
            # L.i(f"{(prob * i)}, {rand}")
            randNo = i
            break
    return randNo

