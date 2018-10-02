@echo off

REM call "C:\[2] dev\set_visual_studio.bat"
call rm *.obj

nmake -f makefile.win

REM nmake -f makefile.win.lt

