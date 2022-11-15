echo off

echo Delete old signed apk
del "app/build/outputs/apk/release/app-release-unsigned.apk"

echo Build application

"cmd /c gradlew.bat assembleRelease"

IF NOT EXIST "key.keystore" (
	"platform-tools/keytool.exe" -noprompt -genkey -v -keystore key.keystore -alias android -keyalg RSA -keysize 2048 -validity 20000
) 

"platform-tools/jarsigner.exe" -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore key.keystore app/build/outputs/apk/release/app-release-unsigned.apk android
"platform-tools/jarsigner.exe" -verify app/build/outputs/apk/release/app-release-unsigned.apk

echo Delete old signed apk
del "app/build/outputs/apk/release/app-release-signed.apk"

"platform-tools/zipalign.exe" -v 4 app/build/outputs/apk/release/app-release-unsigned.apk app/build/outputs/apk/release/app-release-signed.apk

java.exe -jar platform-tools/apksigner.jar sign --ks key.keystore --ks-key-alias android app/build/outputs/apk/release/app-release-signed.apk

echo Uninstall application
"platform-tools/adb.exe" uninstall "com.monika.sparcle"

echo Install application
"platform-tools/adb.exe" install -r app/build/outputs/apk/release/app-release-signed.apk

echo Run application
./run_application.bat

pause