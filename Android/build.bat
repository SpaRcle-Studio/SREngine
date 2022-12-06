echo off

cls

set APK_UNSIGNED_FILE="app/build/outputs/apk/release/app-release-unsigned.apk"
set APK_SIGNED_FILE="app/build/outputs/apk/release/app-release-signed.apk"
set PLATFORM_TOOLS=platform-tools
set GRADLEW=gradlew.bat
set APP_NAME=com.monika.sparcle

echo Delete old signed apk

del %APK_UNSIGNED_FILE%

rem --------------------------------------------------------------------------------------------------------
if exist "C:\Program Files\Java\jdk-11.0.6\bin\javaw.exe" (
  set JAVA_HOME="C:\Program Files\Java\jdk-11.0.6"
) 
echo Java home is: %JAVA_HOME%
rem --------------------------------------------------------------------------------------------------------

echo Packing resources...
"cmd /c pack_resources.bat assembleRelease"

echo Build application

"cmd /c %GRADLEW% assembleRelease"

if not exist %APK_UNSIGNED_FILE% (
	goto LABEL_FAIL
)

IF NOT EXIST "key.keystore" (
	echo Create key.keystore
	"%PLATFORM_TOOLS%/keytool.exe" -noprompt -genkey -v -keystore key.keystore -alias android -keyalg RSA -keysize 2048 -validity 20000
) 

echo Build application

"%PLATFORM_TOOLS%/jarsigner.exe" -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore key.keystore %APK_UNSIGNED_FILE% android
"%PLATFORM_TOOLS%/jarsigner.exe" -verify %APK_UNSIGNED_FILE%

echo Delete old signed apk...
del %APK_SIGNED_FILE%

echo Zip align apk...

"%PLATFORM_TOOLS%/zipalign.exe" -v 4 %APK_UNSIGNED_FILE% %APK_SIGNED_FILE%

echo Apk signing...
"java.exe" -jar "%PLATFORM_TOOLS%/apksigner.jar" sign --ks key.keystore --ks-key-alias android %APK_SIGNED_FILE%

echo Uninstall application...
"%PLATFORM_TOOLS%/adb.exe" uninstall "%APP_NAME%"

echo Install application...
"%PLATFORM_TOOLS%/adb.exe" install -r %APK_SIGNED_FILE%

goto LABEL_SUCCESS

:LABEL_FAIL
	echo BUILD FAILED
	goto LABEL_EXIT

:LABEL_SUCCESS
	echo BUILD SUCCESSFUL
	goto LABEL_EXIT

:LABEL_EXIT
	pause
