echo off

cls

echo Packing resources...
"cmd /c pack_resources.bat assembleRelease"

"cmd /c build_no_resources.bat"
