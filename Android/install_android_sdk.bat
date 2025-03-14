@echo off
setlocal enabledelayedexpansion

:: Указываем локальную папку для SDK
set "SDK_DIR=%CD%\android-sdk"
set "CMDLINE_TOOLS_URL=https://dl.google.com/android/repository/commandlinetools-win-10406996_latest.zip"
set "CMDLINE_TOOLS_ZIP=%CD%\cmdline-tools.zip"
set "CMDLINE_TOOLS_DIR=%SDK_DIR%\cmdline-tools"

:: Создаем нужные папки
mkdir "%CMDLINE_TOOLS_DIR%" 2>nul

:: Скачиваем Android SDK командные утилиты
echo Downloading command-line tools...
curl -o "%CMDLINE_TOOLS_ZIP%" "%CMDLINE_TOOLS_URL%" --silent --show-error
if %errorlevel% neq 0 (
    echo Failed to download command-line tools.
    exit /b 1
)

:: Распаковываем архив
echo Extracting command-line tools...
tar -xf "%CMDLINE_TOOLS_ZIP%" -C "%CMDLINE_TOOLS_DIR%"
del "%CMDLINE_TOOLS_ZIP%"
move "%CMDLINE_TOOLS_DIR%\cmdline-tools" "%CMDLINE_TOOLS_DIR%\latest"

:: Устанавливаем переменные среды для текущей сессии
set "ANDROID_HOME=%SDK_DIR%"
set "ANDROID_SDK_ROOT=%ANDROID_HOME%"
set "PATH=%ANDROID_HOME%\cmdline-tools\latest\bin;%ANDROID_HOME%\platform-tools;%PATH%"

:: Создаем папку лицензий и автоматически принимаем их
mkdir "%ANDROID_HOME%\licenses" 2>nul
(
echo 8933bad161af4178b1185d1a37fbf41ea5269c55
echo d56f5187479451eabf01fb78af6dfcb131a6481e
echo 24333f8a63b6825ea9c5514f83c2829b004d1fee
) > "%ANDROID_HOME%\licenses\android-sdk-license"

:: Создаем папку лицензий и автоматически принимаем их
mkdir "%ANDROID_HOME%\licenses" 2>nul
(
echo 84831b9409646a918e30573bab4c9c91346d8abd
) > "%ANDROID_HOME%\licenses\android-sdk-preview-license"

echo SDK licenses accepted.

echo Check available versions...
sdkmanager --list | findstr /C:"ndk;"

:: Скачиваем необходимые компоненты
echo Installing SDK components...
:: sdkmanager --install "platform-tools" "platforms;android-34" "build-tools;34.0.0" "ndk;25.2.9519653" "cmake;3.22.1"
:: sdkmanager --install "platform-tools" "platforms;android-34" "build-tools;34.0.0" "ndk;26.1.10909125" "cmake;3.22.1"
sdkmanager --install "platform-tools" "platforms;android-34" "build-tools;34.0.0" "ndk;29.0.13113456" "cmake;3.22.1"

echo Android SDK setup completed!
:: exit /b 0

pause
