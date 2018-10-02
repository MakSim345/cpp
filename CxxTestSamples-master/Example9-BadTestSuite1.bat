@echo off

title BadTestSuite1
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner9.cpp BadTestSuite1.h

echo.
echo.Compiling...
g++ -o runner9 -I..\CxxTest\cxxtest-4.0.3\ runner9.cpp

echo.
echo.Executing...
runner9.exe

echo.
echo.Done
pause
:End