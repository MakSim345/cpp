@echo off

title MockGhost
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --error-printer -o runner20.cpp MockGhost.h

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner20 -I..\CxxTest\cxxtest-4.0.3\ runner20.cpp ghost_example.cpp ghost_mock.cpp

echo.
echo.Executing...
runner20.exe

echo.
echo.Done
pause
:End