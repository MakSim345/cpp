@echo off

REM call "C:\[2] dev\set_visual_studio.bat"
REM call "D:\dev\start_vs_path.bat"
call rm *.obj

nmake -f makefile.win

