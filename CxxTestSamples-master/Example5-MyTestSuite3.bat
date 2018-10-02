@echo off

title MyTestSuite3
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner5.cpp MyTestSuite3.h

echo.
echo.Compiling...
g++ -o runner5 -I..\CxxTest\cxxtest-4.0.3\ runner5.cpp

echo.
echo.Executing...
runner5.exe

echo.
echo.Done
pause
:End