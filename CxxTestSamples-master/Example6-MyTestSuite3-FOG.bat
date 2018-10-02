@echo off

title MyTestSuite3 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner6.cpp MyTestSuite3.h

echo.
echo.Compiling...
g++ -o runner6 -I..\CxxTest\cxxtest-4.0.3\ runner6.cpp

echo.
echo.Executing...
runner6.exe

echo.
echo.Done
pause
:End