rem Bat file Control by LVI aka SC0x1
@echo off
cls
:main_menu
title Logger Menu
echo  .                                        .
echo  . ~~~~~ Select the level of detail ~~~~~ .
echo  .                                        .
echo  .   1 - DEBUG_3                          .
echo  .   2 - DEBUG_2                          .
echo  .   3 - DEBUG_1                          .
echo  .   4 - DEBUG                            .
echo  .                                        .
echo  .   5 - INFO                             .
echo  .   6 - WARNING                          .
echo  .   7 - ERROR                            .
echo  .                                        .
echo  .   9 - Cls                              .
echo  .   0 - Exit                             .
echo  .                                        .
echo   ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~

set SelectItem=x
set /p SelectItem=" Input: "
cls

cd .\build\

if /i %SelectItem%==1 goto logDEBUG_3
if /i %SelectItem%==2 goto logDEBUG_2
if /i %SelectItem%==3 goto logDEBUG_1
if /i %SelectItem%==4 goto logDEBUG
if /i %SelectItem%==5 goto logINFO
if /i %SelectItem%==6 goto logWARNING
if /i %SelectItem%==7 goto logERROR

if /i %SelectItem%==9 goto Cls
if /i %SelectItem%==0 goto End
goto main_menu
rem ...Item Menu
:logERROR
if exist Logger.exe Logger.exe ERROR
pause
cls
goto mein_menu
rem ...Item Menu
:logWARNING
if exist Logger.exe Logger.exe WARNING
pause
cls
goto main_menu
rem ...Item Menu
:logINFO
if exist Logger.exe Logger.exe INFO
pause
cls
goto main_menu
rem ...Item Menu
:logDEBUG
if exist Logger.exe Logger.exe DEBUG
pause
cls
goto main_menu
rem ...Item Menu
:logDEBUG_1
if exist Logger.exe Logger.exe DEBUG1
pause
cls
goto main_menu
rem ...Item Menu
:logDEBUG_2
if exist Logger.exe Logger.exe DEBUG2
pause
cls
goto main_menu
rem ...Item Menu
:logDEBUG_3
if exist Logger.exe Logger.exe DEBUG3
pause
cls
goto main_menu
rem ...Item Menu
:Cls
@echo off
cls
goto main_menu
rem ...Item Menu Exit...
:End
exit