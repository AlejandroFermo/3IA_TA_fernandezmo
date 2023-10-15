#!/bin/sh

# Example script to build a program with the ESAT graphic library for 
# linux 64bit systems.
#
# This script compiles all .cc files found at the ../src/ directory and links 
# them with the libESAT library and all its dependencies (e.g: asound, pthread,
# OpenGL, etc...).
#
# Standard ESAT C++ project structure with standard directory names is 
# assumed (src, include, deps . . .)

rm -f test *.o

g++ -g -Wall -m64 -std=c++0x -I../include -I../deps/ESAT/include/ -c ../src/*.cc 
g++ -g -Wall -m64 -std=c++0x -L../deps/esat/bin/linux64 -lESAT -lasound -ldl -lpthread -lX11 -lGL -lGLU *.o -o test

