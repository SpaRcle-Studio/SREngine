@echo off
setlocal

set "SOURCE_RESOURCES_FOLDER=..\..\Resources"
set "DESTINATION_RESOURCES_FOLDER=app\src\main\assets"

:: удаляем папку assets целиком
if exist "%DESTINATION_RESOURCES_FOLDER%" rmdir /s /q "%DESTINATION_RESOURCES_FOLDER%"

:: пересоздаём
mkdir "%DESTINATION_RESOURCES_FOLDER%"

:: копируем подпапки
xcopy "%SOURCE_RESOURCES_FOLDER%\Engine"    "%DESTINATION_RESOURCES_FOLDER%\Engine"    /E /I /Y
xcopy "%SOURCE_RESOURCES_FOLDER%\Editor"    "%DESTINATION_RESOURCES_FOLDER%\Editor"    /E /I /Y
xcopy "%SOURCE_RESOURCES_FOLDER%\Launcher"  "%DESTINATION_RESOURCES_FOLDER%\Launcher"  /E /I /Y

pause