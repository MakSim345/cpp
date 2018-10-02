@echo off

title MockGeneric
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner21.cpp MockGeneric.h

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner21 -I..\CxxTest\cxxtest-4.0.3\ runner21.cpp generic_mock.cpp generic_example.cpp generic.cpp

echo.
echo.Executing...
runner21.exe

echo.
echo.Done
pause
:End