@echo off

REM call "C:\[2] dev\set_visual_studio.bat"
call "D:\dev\set_visual_studio.bat"
call cls

nmake -f makefile.win

REM nmake -f makefile.win.lt

