@echo off

title MyTestSuite7
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner15.cpp MyTestSuite7.h

echo.
echo.Compiling...
g++ -o runner15 -I..\CxxTest\cxxtest-4.0.3\ runner15.cpp

echo.
echo.Executing...
runner15.exe

echo.
echo.Done
pause
:End