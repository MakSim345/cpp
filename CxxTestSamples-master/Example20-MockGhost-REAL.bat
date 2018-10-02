@echo off

title MockGhost Real
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Compiling...
:: Note that all of the cpp files being used must be included.
g++ -o runner20r -I..\CxxTest\cxxtest-4.0.3\ ghost_main.cpp ghost_example.cpp ghost.cpp

echo.
echo.Executing...
runner20r.exe

echo.
echo.Done
pause
:End