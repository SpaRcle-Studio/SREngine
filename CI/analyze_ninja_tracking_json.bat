echo off
cls

REM Получить путь до текущего скрипта
set "SCRIPT_DIR=%~dp0"

"../.venv/python/python.exe" scripts/analyze_ninja_tracking_json.py %*