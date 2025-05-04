@echo off
setlocal enabledelayedexpansion

rem Переход в корень репозитория (предполагается, что скрипт лежит в CI\)
cd /d %~dp0..
if not exist .git (
    echo [ERROR] .git не найден в текущей папке.
    exit /b 1
)

echo Поиск index.lock-файлов в .git...

for /R ".git" %%F in (index.lock) do (
    echo Удаляю: %%F
    del /f /q "%%F" >nul 2>&1
)

echo Все index.lock-файлы удалены.
endlocal
pause