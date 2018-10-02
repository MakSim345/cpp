@echo off

title MockTestSuite
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner19.cpp MockTestSuite.h

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner19 -I..\CxxTest\cxxtest-4.0.3\ runner19.cpp rand_example.cpp time_mock.cpp

echo.
echo.Executing...
runner19.exe

echo.
echo.Done
pause
:End