@echo off

title BadTestSuite1 FOG
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --fog --error-printer -o runner10.cpp BadTestSuite1.h

echo.
echo.Compiling...
g++ -o runner10 -I..\CxxTest\cxxtest-4.0.3\ runner10.cpp

echo.
echo.Executing...
runner10.exe

echo.
echo.Done
pause
:End