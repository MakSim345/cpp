@echo off

title MyTestSuite2
echo.Setting Scope...
cd "%~dp0"

echo.
echo.Generating...
python ..\CxxTest\cxxtest-4.0.3\bin\cxxtestgen --runner=XmlPrinter -o runner2.cpp MyTestSuite2.h

echo.
echo.Compiling...
g++ -o runner2 -I..\CxxTest\cxxtest-4.0.3\ runner2.cpp

echo.
echo.Executing...
runner2.exe > runner2.xml

echo.
echo.Done
pause
:End