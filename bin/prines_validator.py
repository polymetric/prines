#!/usr/bin/env python 
import sys
import re

# argv[1] and argv[2] contain the file we want to check
path_1 = sys.argv[1]
path_2 = sys.argv[2]

file_1 = open(path_1).read()
file_2 = open(path_2).read()

# Remove duplicates (checkpoints can cause these) and sort the lists
file_1 = sorted(list(set(file_1)))
file_2 = sorted(list(set(file_2)))

# Exit correctly
if file_1 == file_2:
    sys.exit(0)
else:
    sys.exit(1)
