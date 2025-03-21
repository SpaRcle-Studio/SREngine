@echo off

set SOURCE_RESOURCES_FOLDER=..\Resources
set DESTINATION_RESOURCES_FOLDER=app\src\main\assets

:: Создаём папку, если её нет
mkdir "%DESTINATION_RESOURCES_FOLDER%" 2>nul

echo Destination resources folder: "%DESTINATION_RESOURCES_FOLDER%"
echo Source resources folder: "%SOURCE_RESOURCES_FOLDER%"

:: Полностью удаляем папку с ресурсами, если она есть
rmdir /s /q "%DESTINATION_RESOURCES_FOLDER%"

:: Создаём папку заново
mkdir "%DESTINATION_RESOURCES_FOLDER%" 2>nul

:: Копируем ресурсы
xcopy /s /e /y "%SOURCE_RESOURCES_FOLDER%\Engine" "%DESTINATION_RESOURCES_FOLDER%\Engine\"
xcopy /s /e /y "%SOURCE_RESOURCES_FOLDER%\Editor" "%DESTINATION_RESOURCES_FOLDER%\Editor\"
xcopy /s /e /y "%SOURCE_RESOURCES_FOLDER%\Libraries" "%DESTINATION_RESOURCES_FOLDER%\Libraries\"
xcopy /s /e /y "%SOURCE_RESOURCES_FOLDER%\Launcher" "%DESTINATION_RESOURCES_FOLDER%\Launcher\"

echo Resources copied successfully!
