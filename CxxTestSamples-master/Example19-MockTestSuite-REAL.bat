@echo off

title MockTestSuite
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner19r -I..\CxxTest\cxxtest-4.0.3\ rand_main.cpp rand_example.cpp time_real.cpp

echo.
echo.Executing...
runner19r.exe

echo.
echo.Done
pause
:End