@echo off

set SOURCE_LIB_FOLDER=lib\release
set DESTINATION_LIB_FOLDER=app\src\main\jniLibs

:: Создаём папку, если её нет
mkdir "%DESTINATION_LIB_FOLDER%" 2>nul

echo Destination libs folder: "%DESTINATION_LIB_FOLDER%"
echo Source libs folder: "%SOURCE_LIB_FOLDER%"

:: Полностью удаляем папку с либами, если она есть
rmdir /s /q "%DESTINATION_LIB_FOLDER%"

:: Создаём папку заново
mkdir "%DESTINATION_LIB_FOLDER%" 2>nul

:: Копируем ресурсы
xcopy /s /e /y "%SOURCE_LIB_FOLDER%" "%DESTINATION_LIB_FOLDER%"

echo Libraries copied successfully!