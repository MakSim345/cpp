@echo off

title MyTestSuite 1+2+4
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen -f --error-printer -o runner11.cpp MyTestSuite1.h MyTestSuite2.h MyTestSuite4.h

echo.
echo.Compiling...
g++ -o runner11 -I..\CxxTest\cxxtest-4.0.3\ runner11.cpp

echo.
echo.Executing...
runner11.exe > runner11.txt
runner11.exe --help >> runner11.txt
runner11.exe --help-tests >> runner11.txt
runner11.exe MyTestSuite2 >> runner11.txt
runner11.exe MyTestSuite2 testMultiplication >> runner11.txt
runner11.exe -v MyTestSuite2 testMultiplication >> runner11.txt

echo.
echo.Done
pause
:End