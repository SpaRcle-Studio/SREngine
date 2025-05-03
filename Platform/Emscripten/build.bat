@echo off
setlocal

rem === Настройки ===
set EMSDK_DIR=%~dp0emsdk
set SR_ENGINE_DIR=%~dp0..\..  
set BUILD_DIR==%~dp0\build
set CONFIG=Release
set PLATFORM=Emscripten

if not exist "%EMSDK_DIR%" (
	echo emsdk not exists. Clone it...
	git clone https://github.com/emscripten-core/emsdk.git
	echo Activate emsdk...
	cd emsdk
	call .\emsdk install latest
	call .\emsdk activate latest
	cd ../
)

echo Activate emsdk environment...

rem === Вход в окружение Emscripten ===
call "%EMSDK_DIR%\emsdk_env.bat"
if errorlevel 1 goto :error

rem === Создание директории сборки ===
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

rem === Генерация сборки через emcmake ===
echo.
echo Генерация CMake сборки для Emscripten...
emcmake cmake -S "%SRENGINE_DIR%" -B "%BUILD_DIR%" -DCMAKE_BUILD_TYPE=%CONFIG% -DSR_PLATFORM=%PLATFORM%
if errorlevel 1 goto :error

rem === Сборка проекта ===
echo.
echo Сборка проекта...
emmake cmake --build "%BUILD_DIR%" --config %CONFIG%
if errorlevel 1 goto :error

echo.
echo ✅ Сборка под Emscripten завершена успешно!
exit /b 0

:error
	echo.
	echo ❌ Ошибка во время сборки.
	exit /b 1