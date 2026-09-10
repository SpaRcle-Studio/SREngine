@echo off
setlocal

set "SOURCE_RESOURCES_FOLDER=..\..\Resources"
set "DESTINATION_ASSETS_FOLDER=app\src\main\assets"

:: ресурсы кладутся в assets вместе с папкой "Resources", чтобы пути внутри apk
:: совпадали с виртуальными путями движка на остальных платформах
set "DESTINATION_RESOURCES_FOLDER=%DESTINATION_ASSETS_FOLDER%\Resources"

:: удаляем папку assets целиком
if exist "%DESTINATION_ASSETS_FOLDER%" rmdir /s /q "%DESTINATION_ASSETS_FOLDER%"

:: пересоздаём
mkdir "%DESTINATION_RESOURCES_FOLDER%"

:: копируем подпапки
xcopy "%SOURCE_RESOURCES_FOLDER%\Engine"    "%DESTINATION_RESOURCES_FOLDER%\Engine"    /E /I /Y
xcopy "%SOURCE_RESOURCES_FOLDER%\Editor"    "%DESTINATION_RESOURCES_FOLDER%\Editor"    /E /I /Y
xcopy "%SOURCE_RESOURCES_FOLDER%\Launcher"  "%DESTINATION_RESOURCES_FOLDER%\Launcher"  /E /I /Y
