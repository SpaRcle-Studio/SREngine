@echo off
setlocal enabledelayedexpansion

set "APK_FOLDER=app/build/outputs/apk/release"
set "PLATFORM_TOOLS=platform-tools"
set "KEYSTORE=key.keystore"
set "KEY_ALIAS=android"
set "KEY_PASS=123456"

REM Создаём keystore если не существует
IF NOT EXIST "%KEYSTORE%" (
    echo Creating keystore...
    "%PLATFORM_TOOLS%/keytool.exe" -noprompt -genkey -v -keystore "%KEYSTORE%" -alias "%KEY_ALIAS%" -keyalg RSA -keysize 2048 -validity 20000 -storepass %KEY_PASS% -keypass %KEY_PASS%
)

REM Проходим по всем APK в папке
for %%F in ("%APK_FOLDER%\*-unsigned.apk") do (
    set "APK_UNSIGNED=%%F"
    set "APK_BASE=%%~nF"
    set "APK_SIGNED=%APK_FOLDER%\!APK_BASE:-unsigned=!.apk"

    echo Signing !APK_UNSIGNED! ...

    REM Zipalign
    "%PLATFORM_TOOLS%/zipalign.exe" -v 4 "!APK_UNSIGNED!" "!APK_SIGNED!"

    REM Подписываем через apksigner
    java -jar "%PLATFORM_TOOLS%/apksigner.jar" sign --ks "%KEYSTORE%" --ks-pass pass:%KEY_PASS% --key-pass pass:%KEY_PASS% --ks-key-alias "%KEY_ALIAS%" "!APK_SIGNED!"

    echo Done: !APK_SIGNED!
)

echo All APKs signed.