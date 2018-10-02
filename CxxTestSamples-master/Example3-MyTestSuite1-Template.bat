@echo off

title MyTestSuite1 Template
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen -o runner3.cpp --template MyTestSuite1.tpl MyTestSuite1.h

echo.
echo.Compiling...
g++ -o runner3 -I..\CxxTest\cxxtest-4.0.3\ runner3.cpp

echo.
echo.Executing...
runner3.exe

echo.
echo.Done
pause
:End