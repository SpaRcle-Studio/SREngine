set APK_FOLDER=app/build/outputs/apk/release
set APK_SIGNED_FILE=%APK_FOLDER%/app-release-signed.apk
set PLATFORM_TOOLS=platform-tools
set APP_NAME=com.monika.sparcle

echo Uninstall application...
"%PLATFORM_TOOLS%/adb.exe" uninstall "%APP_NAME%"

echo Install debug application...
"%PLATFORM_TOOLS%/adb.exe" install -t "%APK_SIGNED_FILE%"

echo Install release application...
"%PLATFORM_TOOLS%/adb.exe" install -r "%APK_SIGNED_FILE%"
