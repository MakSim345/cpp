@echo off

title MyTestSuite4
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner7.cpp MyTestSuite4.h

echo.
echo.Compiling...
g++ -o runner7 -I..\CxxTest\cxxtest-4.0.3\ runner7.cpp

echo.
echo.Executing...
runner7.exe

echo.
echo.Done
pause
:End