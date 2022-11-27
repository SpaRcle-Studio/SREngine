echo off

echo Build application...
./build.bat

echo Run application...
./run_application.bat

goto LABEL_SUCCESS

:LABEL_FAIL
	echo BUILD FAILED
	goto LABEL_EXIT

:LABEL_SUCCESS
	echo BUILD SUCCESSFUL
	goto LABEL_EXIT

:LABEL_EXIT
	pause
