@echo off

title MockGeneric
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner21r -I..\CxxTest\cxxtest-4.0.3\ generic_main.cpp generic_example.cpp generic_real.cpp generic.cpp

echo.
echo.Executing...
runner21r.exe

echo.
echo.Done
pause
:End