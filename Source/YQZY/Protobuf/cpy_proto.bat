cd %~dp0
set sourceDir=%cd%

cd D:\UEEditors\Server_A\Server\Server\Shared\protobuf

set tarDir=%cd%
xcopy /y %sourceDir%\*.proto   %tarDir%  /s/e 

pause
exit