@echo off
cls

set ARCH=%1

if "%ARCH%"=="" (
    echo No architecture specified. Using default: arm64-v8a, x86_64
    set ARCH=arm64-v8a,x86_64
)

echo Selected architecture: %ARCH%

set APK_FOLDER=app/build/outputs/apk/release
set PLATFORM_TOOLS=platform-tools
set GRADLEW=gradlew.bat
set APP_NAME=com.monika.sparcle

echo Delete old signed and unsigned apk...
del /s /q "%APK_FOLDER%"

rem --------------------------------------------------------------------------------------------------------
if exist "C:\Program Files\Java\jdk-11.0.6\bin\javaw.exe" (
  set JAVA_HOME=C:\Program Files\Java\jdk-11.0.6
  echo | set /p ANDROID_SDK_ROOT = C:\Program Files\Java\jdk-11.0.6
) 
echo Java home is: %JAVA_HOME%
rem --------------------------------------------------------------------------------------------------------

call accept_licenses.bat
if errorlevel 1 goto LABEL_FAIL

echo Build application
call %GRADLEW% assembleRelease -Parchs=%ARCH%
if errorlevel 1 goto LABEL_FAIL

echo Sign apk...
call sign_apk.bat
if errorlevel 1 goto LABEL_FAIL

goto LABEL_SUCCESS

:LABEL_FAIL
    echo BUILD FAILED
    exit /b 1

:LABEL_SUCCESS
    echo BUILD SUCCESSFUL
    exit /b 0
