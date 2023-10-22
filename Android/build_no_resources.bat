echo off

cls

set APK_FOLDER=app/build/outputs/apk/release
set APK_UNSIGNED_FILE=%APK_FOLDER%/app-release-unsigned.apk
set APK_SIGNED_FILE=%APK_FOLDER%/app-release-signed.apk
set PLATFORM_TOOLS=platform-tools
set GRADLEW=gradlew.bat
set APP_NAME=com.monika.sparcle

echo Delete old signed and unsigned apk...
del /s /q "%APK_FOLDER%"

rem --------------------------------------------------------------------------------------------------------
if exist "C:\Program Files\Java\jdk-11.0.6\bin\javaw.exe" (
  set JAVA_HOME="C:\Program Files\Java\jdk-11.0.6"
  echo | set /p ANDROID_SDK_ROOT = "C:\Program Files\Java\jdk-11.0.6"
) 
echo Java home is: %JAVA_HOME%
rem --------------------------------------------------------------------------------------------------------

"cmd /c accept_licenses.bat"

echo Build application

"cmd /c %GRADLEW% assembleRelease"

if not exist %APK_UNSIGNED_FILE% (
	goto LABEL_FAIL
)

"cmd /c sign_apk.bat"

"cmd /c install_app.bat"

goto LABEL_SUCCESS

:LABEL_FAIL
	echo BUILD FAILED
	goto LABEL_EXIT

:LABEL_SUCCESS
	echo BUILD SUCCESSFUL
	goto LABEL_EXIT

:LABEL_EXIT
