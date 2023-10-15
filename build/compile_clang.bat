@ECHO OFF

del *.obj *.pdb
REM clang++ -g -m32 -O0 -std=c++0x -I ..\include -I ..\deps\esat\include -c ..\src\*.cc
REM clang++ -g -m32 -O0 -std=c++0x -L ..\deps\esat\bin -lESAT_d -lopengl32 -lgdi32 -user32 -lshell32 -o test.exe *.o

clang-cl /nologo /Zi /GR- /EHs /MDd -m32 -I..\include -I..\deps\esat\include /c ..\src\*.cc
clang-cl /nologo /Zi /MDd /Fetest.exe -m32 *.obj ..\deps\esat\bin\ESAT_d.lib opengl32.lib user32.lib gdi32.lib shell32.lib

