@echo off
setlocal
set "ANALYZER_PYTHON=%~dp0..\.venv\python\python.exe"
if exist "%ANALYZER_PYTHON%" goto run
set "ANALYZER_PYTHON=%~dp0..\.venv\Scripts\python.exe"
if exist "%ANALYZER_PYTHON%" goto run
set "ANALYZER_PYTHON=python"
:run
"%ANALYZER_PYTHON%" "%~dp0scripts\analyze_binary_size.py" %*
set "ANALYZER_RESULT=%ERRORLEVEL%"
if "%~1"=="" pause
exit /b %ANALYZER_RESULT%
