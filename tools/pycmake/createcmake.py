import argparse
from pathlib import Path

from cmaker.cmakeConfig import CmakeConfig
from utils.log import Logger

L = Logger()


def createCmake(g_Config, g_RootPath):
    cfg = CmakeConfig(rootPath=g_RootPath, settingsFile=g_Config)
    cfg.createCmakeFile()
    cfg.show()
    pass


if __name__ == '__main__':
    g_Parser = argparse.ArgumentParser(description="Create Cmake files")
    g_Parser.add_argument('config_file', help="the settings file")
    g_Parser.add_argument('root_path', help="Root directory path")

    g_args = g_Parser.parse_args()
    g_Config = Path(g_args.config_file).absolute()
    g_RootPath = Path(g_args.root_path).absolute()

    createCmake(g_Config, g_RootPath)

    pass
