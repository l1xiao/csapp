#!/usr/bin/env python
# encoding: utf-8

file = open("test.txt", "r")
file1 = open("test1.txt", "w")
for line in file.readlines():
    if line.startswith('I'):
        continue
    file1.write(line)
file.close()
file1.close()
