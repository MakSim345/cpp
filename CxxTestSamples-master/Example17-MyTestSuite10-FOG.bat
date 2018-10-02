@echo off

title MyTestSuite10 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner17.cpp MyTestSuite10.h

echo.
echo.Compiling...
g++ -o runner17 -I..\CxxTest\cxxtest-4.0.3\ runner17.cpp

echo.
echo.Executing...
runner17.exe

echo.
echo.Done
pause
:End