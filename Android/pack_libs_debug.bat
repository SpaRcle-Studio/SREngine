@echo off

set SOURCE_LIB_FOLDER=lib\debug
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

set SOURCE_PDB_FOLDER=lib/dbg
set DESTINATION_PDB_FOLDER=app\src\main\obj\local

:: Создаём папку, если её нет
mkdir "%DESTINATION_PDB_FOLDER%" 2>nul

echo Destination pdb folder: "%DESTINATION_PDB_FOLDER%"
echo Source pdb folder: "%SOURCE_PDB_FOLDER%"

:: Полностью удаляем папку с отладочныыми символами, если она есть
rmdir /s /q "%DESTINATION_PDB_FOLDER%"

:: Создаём папку заново
mkdir "%DESTINATION_PDB_FOLDER%" 2>nul

:: Копируем ресурсы
xcopy /s /e /y "%SOURCE_PDB_FOLDER%" "%DESTINATION_PDB_FOLDER%"

echo Dbg files copied successfully!