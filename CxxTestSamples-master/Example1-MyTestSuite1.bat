@echo off

set MAIN_OBJ=runner1

title MyTestSuite1
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
call cxxtestgen.py --error-printer -o %MAIN_OBJ%.cpp MyTestSuite1.h

if exist %MAIN_OBJ%.exe del %MAIN_OBJ%.exe

echo.
echo.Compiling...
::g++ -o runner1 -I..\CxxTest\cxxtest-4.0.3\ runner1.cpp
call cl -EHsc -I"C:\cxxtest-4.3" -o %MAIN_OBJ%.exe %MAIN_OBJ%.cpp

echo.
echo.Executing...
call %MAIN_OBJ%.exe
::runner1.exe

echo.
echo.Done
::pause
:End
