@echo off

title MyTestSuite1 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner4.cpp MyTestSuite1.h

echo.
echo.Compiling...
g++ -o runner4 -I..\CxxTest\cxxtest-4.0.3\ runner4.cpp

echo.
echo.Executing...
runner4.exe

echo.
echo.Done
pause
:End