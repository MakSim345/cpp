@ECHO OFF
REM
REM To setup VS cl.exe, run follow:
REM "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"
REM

set PRODUCT_NAME=MimsSensor
set SUPPORTED_TARGETS=SensorEK SensorR1

:RUN_CMAKE
@ECHO ON

cmake -G "Ninja" -DCMAKE_C_COMPILER=cl.exe -DCMAKE_CXX_COMPILER=cl.exe  ..

@ECHO OFF

goto END
:END
