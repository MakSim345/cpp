@echo off

title MyTestSuite11
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner18.cpp MyTestSuite11.h

echo.
echo.Compiling...
g++ -o runner18 -I..\CxxTest\cxxtest-4.0.3\ runner18.cpp

echo.
echo.Executing...
runner18.exe

echo.
echo.Done
pause
:End