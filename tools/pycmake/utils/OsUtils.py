import os
import shutil
import subprocess
from utils import log as L
from distutils.dir_util import copy_tree
from pathlib import Path


def delete_folder_contents(path_to_folder):
    if not Path(path_to_folder).exists():
        return

    folder = path_to_folder
    for the_file in os.listdir(folder):
        file_path = os.path.join(folder, the_file)
        try:
            if os.path.isfile(file_path):
                os.unlink(file_path)
            elif os.path.isdir(file_path): shutil.rmtree(file_path)
        except Exception as e:
            print(e)
    pass


def create_folders(path_to_file):
    os.makedirs(path_to_file, exist_ok=True)
    pass


def copy_folders(src_folder, dst_folder):
    copy_tree(src_folder, dst_folder)
    pass


def copy_file(src, dest):
    shutil.copy(src, dest)
    pass
