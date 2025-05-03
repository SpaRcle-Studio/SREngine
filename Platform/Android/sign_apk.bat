set APK_FOLDER=app/build/outputs/apk/release
set APK_UNSIGNED_FILE=%APK_FOLDER%/app-release-unsigned.apk
set APK_SIGNED_FILE=%APK_FOLDER%/app-release-signed.apk
set PLATFORM_TOOLS=platform-tools

IF NOT EXIST "key.keystore" (
	echo Create key.keystore
	"%PLATFORM_TOOLS%/keytool.exe" -noprompt -genkey -v -keystore key.keystore -alias android -keyalg RSA -keysize 2048 -validity 20000
) 

echo Build application

"%PLATFORM_TOOLS%/jarsigner.exe" -storepass 123456 -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore key.keystore "%APK_UNSIGNED_FILE%" android
"%PLATFORM_TOOLS%/jarsigner.exe" -verify "%APK_UNSIGNED_FILE%"

echo Zip align apk...

"%PLATFORM_TOOLS%/zipalign.exe" -v 4 "%APK_UNSIGNED_FILE%" "%APK_SIGNED_FILE%"

echo Apk signing...

echo 123456|"java.exe" -jar "%PLATFORM_TOOLS%/apksigner.jar" sign --ks key.keystore --ks-key-alias android "%APK_SIGNED_FILE%"