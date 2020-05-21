#!/usr/bin/env python
# coding: utf-8

import os
import sys

import numpy as np
import matplotlib.pyplot as plt


img = plt.imread(sys.argv[1])
print("Reading from %s" % sys.argv[1])

if os.path.splitext(sys.argv[1])[1] == '.png':
    print("Rescaling PNG")
    img = img * 255

filename = os.path.splitext(sys.argv[1])[0]
print("Writing to %s" % (filename + '.h'))
print("Image %d x %d" % (img.shape[1], img.shape[0]))

with open(filename + '.h', 'w+') as f:
    f.write("#ifndef __%s_H__\n" % (filename.upper()))
    f.write("#define __%s_H__\n" % (filename.upper()))
    f.write("\n")

    f.write("const uint8_t %s_w = %d;\n" % (filename, img.shape[1]) )
    f.write("const uint8_t %s_h = %d;\n" % (filename, img.shape[0]) )
    f.write("\n")

    f.write("uint8_t %s[] = {" % filename)

    for w in range(img.shape[0]):
        for h in range(img.shape[1]):
            f.write("0x%x," % (int(img[w ,h, 0])))
        f.write("\n")

    for w in range(img.shape[0]):
        for h in range(img.shape[1]):
            f.write("0x%x," % (int(img[w, h, 1])))
        f.write("\n")

    for w in range(img.shape[0]):
        for h in range(img.shape[1]):
            f.write("0x%x," % (int(img[w, h, 2])))
        f.write("\n")

    f.write("};\n")

    f.write("\n")
    f.write("#endif\n")
