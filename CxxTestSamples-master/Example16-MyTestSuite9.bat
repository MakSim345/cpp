@echo off

title MyTestSuite9
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner16.cpp MyTestSuite9.h

echo.
echo.Compiling...
g++ -o runner16 -I..\CxxTest\cxxtest-4.0.3\ runner16.cpp

echo.
echo.Executing...
runner16.exe

echo.
echo.Done
pause
:End