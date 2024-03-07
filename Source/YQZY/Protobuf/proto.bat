echo.
for %%i in (./*.proto) do (call:gen_protobuf_code %%i)
pause
exit

rem 

:gen_protobuf_code
@echo off
echo generating %1
protoc.exe --proto_path=. --cpp_out=. %1
IF %ERRORLEVEL% NEQ 0 (
    echo FAIL FAIL FAIL
	echo.
	timeout /T -1 /NOBREAK
) ELSE (
	echo SUCC SUCC SUCC
	echo.
)

goto:eof

