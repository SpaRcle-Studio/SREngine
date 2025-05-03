@echo off
chcp 65001

echo Build application...
cmd /c build.bat assembleRelease
if errorlevel 1 goto LABEL_FAIL

echo Install apk...
cmd /c install_app.bat
if errorlevel 1 goto LABEL_FAIL

echo Run application...
cmd /c run_application.bat assembleRelease
if errorlevel 1 goto LABEL_FAIL

goto LABEL_SUCCESS

:LABEL_FAIL
    echo BUILD FAILED
    exit /b 1

:LABEL_SUCCESS
    echo BUILD SUCCESSFUL
    exit /b 0