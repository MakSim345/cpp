@echo off

title MyTestSuite5
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner12.cpp MyTestSuite5.h

echo.
echo.Compiling...
g++ -o runner12 -I..\CxxTest\cxxtest-4.0.3\ runner12.cpp

echo.
echo.Executing...
runner12.exe

echo.
echo.Done
pause
:End