echo off

echo Delete old signed apk

set APK_UNSIGNED_FILE="app/build/outputs/apk/release/app-release-unsigned.apk"

del %APK_UNSIGNED_FILE%

echo Build application

rem --------------------------------------------------------------------------------------------------------
if exist "C:\Program Files\Java\jdk-11.0.6\bin\javaw.exe" (
  set JAVA_HOME="C:\Program Files\Java\jdk-11.0.6"
) 
echo Java home is: %JAVA_HOME%
rem --------------------------------------------------------------------------------------------------------

"cmd /c gradlew.bat assembleRelease"

if not exist %APK_UNSIGNED_FILE% (
	goto LABEL_FAIL
)

IF NOT EXIST "key.keystore" (
	"platform-tools/keytool.exe" -noprompt -genkey -v -keystore key.keystore -alias android -keyalg RSA -keysize 2048 -validity 20000
) 

"platform-tools/jarsigner.exe" -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore key.keystore app/build/outputs/apk/release/app-release-unsigned.apk android
"platform-tools/jarsigner.exe" -verify app/build/outputs/apk/release/app-release-unsigned.apk

echo Delete old signed apk...
del "app/build/outputs/apk/release/app-release-signed.apk"

echo Zip align apk...

"platform-tools/zipalign.exe" -v 4 app/build/outputs/apk/release/app-release-unsigned.apk app/build/outputs/apk/release/app-release-signed.apk

echo Apk signing...
"java.exe" -jar platform-tools/apksigner.jar sign --ks key.keystore --ks-key-alias android app/build/outputs/apk/release/app-release-signed.apk

echo Uninstall application...
"platform-tools/adb.exe" uninstall "com.monika.sparcle"

echo Install application...
"platform-tools/adb.exe" install -r app/build/outputs/apk/release/app-release-signed.apk

echo Run application...
./run_application.bat

goto LABEL_SUCCESS

:LABEL_FAIL
	echo BUILD FAILED
	goto LABEL_EXIT

:LABEL_SUCCESS
	echo BUILD SUCCESSFUL
	goto LABEL_EXIT

:LABEL_EXIT
	pause
