@echo off
cls

echo Packing resources...
call pack_resources.bat assembleRelease
call build_no_resources.bat