@echo off
setlocal
cd /d "%~dp0"
cls

rem === Настройки ===
set EMSDK_DIR=%~dp0emsdk
set EMSDK_VERSION=5.0.2
for %%I in ("%~dp0..\..") do set SR_ENGINE_DIR=%%~fI
set BUILD_DIR=%~dp0build
set CONFIG=Release
set PLATFORM=Emscripten
set NINJA_URL=https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip
set NINJA_ZIP=%~dp0ninja-win.zip
set NINJA_EXE=%~dp0ninja.exe

echo === Environment Variables ===

echo SR_ENGINE_DIR = %SR_ENGINE_DIR%
echo BUILD_DIR = %BUILD_DIR%
echo CONFIG = %CONFIG%
echo PLATFORM = %PLATFORM%
echo NINJA_URL = %NINJA_URL%
echo NINJA_ZIP = %NINJA_ZIP%
echo NINJA_EXE = %NINJA_EXE%
echo EMSDK_DIR = %EMSDK_DIR%

echo:
echo === Setup emscripten environment ===

rem === Проверка наличия Ninja ===
if not exist "%NINJA_EXE%" (
    echo Ninja not exists. Downloading...
    powershell -Command "Invoke-WebRequest -Uri '%NINJA_URL%' -OutFile '%NINJA_ZIP%'"
    if errorlevel 1 goto :error

    echo Unzipping Ninja...
    powershell -Command "Expand-Archive -Path '%NINJA_ZIP%' -DestinationPath '%~dp0' -Force"
    if errorlevel 1 goto :error

    del "%NINJA_ZIP%"
    echo Ninja downloaded and unzipped.
)
set "PATH=%~dp0;%PATH%"

echo Ninja version:
ninja --version

rem === Проверка наличия Emscripten ===
if not exist "%EMSDK_DIR%" (
	echo emsdk not exists. Clone it...
	git clone https://github.com/SpaRcle-Studio/emsdk
    if errorlevel 1 goto :error
)

echo Activate emsdk...
cd emsdk
call .\emsdk install %EMSDK_VERSION%
if errorlevel 1 goto :error
call .\emsdk activate %EMSDK_VERSION%
if errorlevel 1 goto :error
cd ../

set EMSDK_DIR=%~dp0emsdk

echo:
echo Activate emsdk environment...

rem === Вход в окружение Emscripten ===
call "%EMSDK_DIR%\emsdk_env.bat"
if errorlevel 1 goto :error

pause
exit /b 0

:error
exit /b 1
