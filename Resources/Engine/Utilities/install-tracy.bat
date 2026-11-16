@echo off
setlocal

set "URL=https://github.com/SpaRcle-Studio/tracy/releases/download/v0.15.0/windows.zip"
set "ARCHIVE=%~dp0windows.zip"
set "DEST=%~dp0tracy"

echo Downloading Tracy...

curl.exe -fL --retry 3 -o "%ARCHIVE%" "%URL%"
if errorlevel 1 (
    echo ERROR: Download failed!
    exit /b 1
)

echo Extracting Tracy...

if not exist "%DEST%" mkdir "%DEST%"

tar.exe -xf "%ARCHIVE%" -C "%DEST%"
if errorlevel 1 (
    echo ERROR: Extraction failed!
    exit /b 1
)

del /q "%ARCHIVE%"

echo Tracy installed successfully!
exit /b 0