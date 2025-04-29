@echo off

REM call "C:\[2] dev\set_visual_studio.bat"
REM call cls

REM nmake -f makefile.win

REM nmake -f makefile.win.lt
REM

rm build -rf
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..
ninja
