#!/bin/bash

# This bash script compiles and executes the given C file.
# It takes one commandline argument which is the C file.
# Usage: ./run.sh main.c

gcc -o output ${1}

if [[ 0 == ${?} ]] then
	./output
fi