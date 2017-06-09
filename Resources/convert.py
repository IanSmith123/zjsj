#! /usr/bin/env python3
#######################################################################
#     File Name           :     convert.py
#     Created By          :     Les1ie
#     Email               :     iansmith@qq.com
#     Creation Date       :     [2017-06-05 14:41]
#     Last Modified       :     [2017-06-05 15:19]
#     Description         :      convert
#######################################################################

import sys
from PIL import Image

filename = sys.argv[1]
size = sys.argv[2]

def convert(filename, size):
    old = Image.open(filename)
    new_size = int(size), int(size)
    old.thumbnail(new_size)
    old.save("new-" + filename)
string = '''

使用方法: python convert.py file.png 64
前面是文件名，后面是尺寸 64表示 64*64

'''
print(string)
convert(filename, size)
