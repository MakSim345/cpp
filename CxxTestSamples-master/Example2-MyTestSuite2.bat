@echo off

title MyTestSuite2
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner2.cpp MyTestSuite2.h

echo.
echo.Compiling...
g++ -o runner2 -I..\CxxTest\cxxtest-4.0.3\ runner2.cpp

echo.
echo.Executing...
runner2.exe

echo.
echo.Done
pause
:End