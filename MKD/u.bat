@echo off
@echo Files updating routine starts.

REM   Description: 
REM    The script looks for che.zip file in the local directory and trying 
REM    to unzip it. If zip-file was corrupted or else, this file will be 
REM    removed and all process starts from zero.
REM    
REM    How to realize that file was corrupted? In this case no "che.exe"
REM    appears in the directory. I've tryed to check "if errorlevel" but
REM    it doesn't work
REM 
REM    
REM    This bat file must start before CHE.EXE run! 
REM 
REM 
REM    by Yuriy Senishch,  2005.
REM                       INFORMATION
REM **********************************************************************************
REM
REM **********************************************************************************
REM 
REM **********************************************************************************
REM 
REM **********************************************************************************
REM 
REM **********************************************************************************

IF EXIST CHE.ZIP goto FILE_EXIST
goto EXIST_FAIL

:EXIST_FAIL
@echo ZIP-file does not exist!
goto GOOD_END

:FILE_EXIST
REM calling an utility zpcheck.exe:
zpcheck.exe COMPARE che.zip info.inf
if errorlevel 1 goto UNZIP_IT
if errorlevel 0 goto USUAL_END
goto END

:UNZIP_IT
@echo New file 'che.zip' found. Unzip it...
REM First - save a working copy of *.exe file to *.zor:
if EXIST che.zor del che.zor
if EXIST che.exe ren che.exe che.zor
REM Unzipping as it:
unzip32 che.zip
REM Check how succesful unzipping was:
if EXIST che.exe goto SUCCESS
goto UNZIP_FAIL

:UNZIP_FAIL
@echo Error occures! ZIP-files corrupted!
REM @echo The "che.zip" must be erased! Check it.
IF EXIST che.zip del che.zip
IF EXIST info.inf del info.inf
REM restore original che.exe
@echo Restore original "che.exe".
IF EXIST che.zor ren che.zor che.exe
goto BAD_END

:SUCCESS
REM ************************************************************
REM The timestamp of this zip file we have to write to info file
REM to prevent unnecessary unzipping next time.
REM ************************************************************
zpcheck.exe WRITE che.zip info.inf
@echo ZIP-file timestamp information was store in the file info.inf.
goto GOOD_END

:USUAL_END
@echo No new files for updating were found.
goto END

:GOOD_END
@echo File updating successfull.
goto END

:BAD_END
@echo Zip file must be re-sended!!
goto END

:END
@echo Complete.