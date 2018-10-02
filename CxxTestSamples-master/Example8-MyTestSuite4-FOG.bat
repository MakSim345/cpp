@echo off

title MyTestSuite4 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner8.cpp MyTestSuite4.h

echo.
echo.Compiling...
g++ -o runner8 -I..\CxxTest\cxxtest-4.0.3\ runner8.cpp

echo.
echo.Executing...
runner8.exe

echo.
echo.Done
pause
:End