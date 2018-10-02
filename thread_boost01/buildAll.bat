@echo off
REM============================================================
REM
REM File:           buildAll.bat
REM
REM============================================================
REM Description:
REM CMD batch to build/rebuild/clean target SW
REM
REM Syntax: build.bat <configuration> <command>
REM
REM Default is Debug configuration and build. Other commands
REM are rebuild and clean.
REM============================================================

:INIT
echo off
rem Default is Debug configuration
set CONFIG=Debug
rem By changing the command we can do rebuild / clean / etc.
set DEVCMD=build
set FAILEDBUILDS=
set VS_SOLUTION=Thread14.sln

set VCVARSPATH="C:\Program Files\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"

if "%1"=="help" goto HELP
rem NOTE that parameter checking is omitted!
if not "%1"=="" set CONFIG="%1"
if not "%2"=="" set DEVCMD="%2"

echo ----------------------------------------------------------
echo MY SW %DEVCMD% run, %DATE% %TIME%
echo ----------------------------------------------------------
echo Variables:
echo CONFIG=%CONFIG%
echo DEVCMD=%DEVCMD%
echo.

:BUILD
echo Setup VC environment
@echo on
call %VCVARSPATH% x86
@echo off

:GENIE
set CURSUBSYS=%VS_SOLUTION%
echo ==========
echo %CURSUBSYS%
devenv %VS_SOLUTION% /%DEVCMD% %CONFIG%
if not %ERRORLEVEL%==0 set FAILEDBUILDS=%CURSUBSYS%
echo.

:BUILDEND
if "%FAILEDBUILDS%"=="" goto SUCCESS
goto FAILURE

:SUCCESS
echo Build ended, SW built successfully!
goto END

:FAILURE
echo Build ended, the following subsystems had errors:
echo %FAILEDBUILDS%
goto END

:USAGE
:HELP
echo Syntax: buildAll.bat <configuration> <command>
echo.
echo Default is Debug configuration and build.

:END
pause
REM EOF

