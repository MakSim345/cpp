@echo off

title MyTestSuite8
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner14.cpp MyTestSuite8.h

echo.
echo.Compiling...
g++ -o runner14 -I..\CxxTest\cxxtest-4.0.3\ runner14.cpp

echo.
echo.Executing...
runner14.exe

echo.
echo.Done
pause
:End