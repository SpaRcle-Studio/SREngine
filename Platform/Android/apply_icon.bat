@echo off
setlocal

REM Определяем директорию скрипта
set SCRIPT_DIR=%~dp0
echo Script dir: %SCRIPT_DIR%

REM Путь к исходной иконке
set SRC_ICON=%SCRIPT_DIR%..\..\Resources\Engine\Textures\logo-mobile.png
if not exist "%SRC_ICON%" (
    echo ERROR: Source icon not found: %SRC_ICON%
    pause
    exit /b 1
)

REM Путь к папке ресурсов Android
set RES_DIR=%SCRIPT_DIR%\app\src\main\res
if not exist "%RES_DIR%" (
    echo ERROR: Android res folder not found: %RES_DIR%
    pause
    exit /b 1
)

REM Папки mipmap
set MIPMAPS=mdpi hdpi xhdpi xxhdpi xxxhdpi

setlocal enabledelayedexpansion

for %%m in (%MIPMAPS%) do (
    set "DEST_DIR=%RES_DIR%\mipmap-%%m"
    if not exist "!DEST_DIR!" mkdir "!DEST_DIR!"
    copy /y "%SRC_ICON%" "!DEST_DIR!\ic_launcher.png"
	copy /y "%SRC_ICON%" "!DEST_DIR!\ic_launcher_round.png"
)

REM mipmap-anydpi-v26 для adaptive icon
if not exist "%RES_DIR%\mipmap-anydpi-v26" mkdir "%RES_DIR%\mipmap-anydpi-v26"

REM Создаем drawable для foreground и background
rem if not exist "%RES_DIR%\drawable" mkdir "%RES_DIR%\drawable"
rem copy /y "%SRC_ICON%" "%RES_DIR%\drawable\ic_launcher_background.png"

REM Создаем drawable для foreground и background
if not exist "%RES_DIR%\drawable" mkdir "%RES_DIR%\drawable"
copy /y "%SRC_ICON%" "%RES_DIR%\drawable-v24\ic_launcher_foreground.png"

REM Файл background.xml
(
echo ^<?xml version="1.0" encoding="utf-8"?^>
echo ^<layer-list xmlns:android="http://schemas.android.com/apk/res/android"^>
echo     ^<item android:drawable="@android:color/black" /^>
echo ^</layer-list^>
) > "%RES_DIR%\drawable\ic_launcher_background.xml"

REM Adaptive icon XML
(
echo ^<?xml version="1.0" encoding="utf-8"?^>
echo ^<adaptive-icon xmlns:android="http://schemas.android.com/apk/res/android"^>
echo     ^<background android:drawable="@drawable/ic_launcher_background" /^>
echo     ^<foreground android:drawable="@drawable/ic_launcher_foreground" /^>
echo ^</adaptive-icon^>
) > "%RES_DIR%\mipmap-anydpi-v26\ic_launcher.xml"

echo Icon applied successfully.

