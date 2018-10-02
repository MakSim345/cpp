@echo off

:INIT 
set MAIN_OBJ=catch_main

if exist %MAIN_OBJ%.exe del %MAIN_OBJ%.exe

REM autogenerate cpp file for unit test:
::call cxxtestgen.py --error-print -o %MAIN_OBJ%.cpp %MAIN_OBJ%.h

g++ -I"C:\cxxtest-4.3" -o %MAIN_OBJ%.exe %MAIN_OBJ%.cpp patient.cpp

if exist %MAIN_OBJ%.exe goto TARGET_EXIST
goto ERROR_NO_EXE_FILE

:TARGET_EXIST
call %MAIN_OBJ%.exe -a
goto END

:ERROR_NO_EXE_FILE
echo ERROR: file '%MAIN_OBJ%.exe' not exist!
goto END

:END
echo Complete.
