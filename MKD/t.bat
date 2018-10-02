@echo off

if -%1==- goto NoParam

if -%1==-MON goto MON
if -%1==-TUE goto TUE
if -%1==-WED goto WED
if -%1==-THU goto THU
if -%1==-FRI goto FRI

REM    
REM    application mkd.exe using for write or add information to a file.
REM    How to use mkd.exe:
REM       mkd.exe <WRITE/ADD> <filename> <message_to_file>
REM 

:MON
REM @echo Jarmo's computer is not avaliable
REM goto END
mkd.exe WRITE run.bat ONLABSER
call run.bat
goto END

:TUE
@echo This computer is not avaliable
goto END

:WED
REM @echo Timo's computer is not avaliable
REM goto END
mkd.exe WRITE run.bat Timo
call run.bat
goto END

:THU
@echo This computer is not avaliable
goto END

:FRI
REM @echo Yuri's computer is not avaliable
REM goto END
mkd.exe WRITE run.bat Yuriysen
call run.bat
goto END 


:NoParam
@echo t.bat error:
@echo There is no any parameter.
@echo You have to try "t.bat <DAY>" Where DAY == {TUE, WED, THU}
@echo Good luck!
@echo .
REM mkd.exe ADD backup.log "Error occures during copyng file. Program has been called without parameters!"

:END