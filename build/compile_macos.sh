#!/bin/sh

clang++ -g -m32 -std=c++0x -I../include -I../deps/ESAT/include/ -c ../src/main.cc 
clang++ -g -m32 -std=c++0x -L../deps/ESAT/bin -lESAT_d -framework OpenGL -framework Cocoa -framework Corevideo -framework IOKit main.o -o main

#clang++ -m32 -std=c++0x -I../include -I../deps/ESAT/include/ -c ../src/main.cc 
#clang++ -m32 -std=c++0x -L../deps/ESAT/bin -l ESAT -framework OpenGL -framework Cocoa -framework Corevideo -framework IOKit main.o -o main

