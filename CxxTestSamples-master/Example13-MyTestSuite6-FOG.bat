@echo off

title MyTestSuite6 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner13.cpp MyTestSuite6.h

echo.
echo.Compiling...
g++ -o runner13 -I..\CxxTest\cxxtest-4.0.3\ runner13.cpp

echo.
echo.Executing...
runner13.exe

echo.
echo.Done
pause
:End