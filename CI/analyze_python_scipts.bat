echo off
cls

REM Получить путь до текущего скрипта
set "SCRIPT_DIR=%~dp0"

"../.venv/python/python.exe" scripts/pylint_code_analyzer.py %SCRIPT_DIR%/scripts