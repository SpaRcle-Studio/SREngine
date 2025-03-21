@echo off
set INPUT_DIR=C:\Work\SREngine\Resources\Engine\Net\10.0-android-arm64
set OUTPUT_DIR=C:\Work\SREngine\Resources\Engine\Net\10.0-android-arm64-so
set ANDROID_NDK=C:\Work\SREngine\Android\android-sdk\ndk\29.0.13113456

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

for %%f in ("%INPUT_DIR%\*.dll") do (
    echo Processing %%~nxf...
    C:\Work\SREngine\.venv\MonoBuildTool\bin\mono.exe --aot=full,asmonly,static,outfile="%OUTPUT_DIR%\%%~nxf.s" "%%f"
    "%ANDROID_NDK%\toolchains\llvm\prebuilt\windows-x86_64\bin\aarch64-linux-android21-clang" -shared -o "%OUTPUT_DIR%\%%~nxf.so" "%OUTPUT_DIR%\%%~nxf.s"
)