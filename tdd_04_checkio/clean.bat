@echo off

if exist *.exe goto EXE_EXIST
goto CHECK_OBJ

:EXE_EXIST
echo Delete all EXE files from curent directory:
call ll *.exe
rm *.exe

:CHECK_OBJ
if exist *.obj goto OBJ_EXIST

goto NO_FILES_TO_ERASE

:OBJ_EXIST
echo Delete all OBJ files from curent directory:
call ll *.obj
rm *.obj
goto END

:NO_FILES_TO_ERASE
echo No files to clean.

:END
echo Complete.

