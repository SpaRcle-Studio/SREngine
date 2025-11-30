echo off
cls

REM Получить путь до текущего скрипта
set "SCRIPT_DIR=%~dp0"

"../.venv/python/python.exe" ninjatracing.py ../cmake-build-debug/.ninja_log > trace.json