@echo off
cls

set ARCH=%1

echo Packing resources...
call pack_resources.bat assembleRelease
call build_no_resources.bat %ARCH%