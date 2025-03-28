@echo off

::nmake -f makefile.win

:: c:\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin\g++.exe -std=c++11 main.cpp
::
::mkdir build && cd build && cmake -G Ninja ..

echo Create BUILD folder and run cl.exe compiler:
mkdir build && cd build && cmake -G "Ninja" -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ..
