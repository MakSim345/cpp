@echo off

REM call Visual studio compiler:

REM cl -EHsc -o my_test.exe my_test.cpp 

cl -EHsc -I"C:\cxxtest-4.3" -o my_test.exe my_test.cpp 

REM cl.exe -GX -W3 -WX -I. -I -o my_test.exe my_test.cpp 