echo off
chcp 65001

echo Build application...
"cmd /c build.bat assembleRelease"

echo Install apk...
"cmd /c install_app.bat"

echo Run application...
"cmd /c run_application.bat assembleRelease"

goto LABEL_SUCCESS

:LABEL_FAIL
	echo BUILD FAILED
	goto LABEL_EXIT

:LABEL_SUCCESS
	echo BUILD SUCCESSFUL
	goto LABEL_EXIT

:LABEL_EXIT
	pause
