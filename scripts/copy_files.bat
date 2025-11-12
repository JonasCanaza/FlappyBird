@echo off

set "src=%~1"
set "out=%~2"

if "%src%"=="" (
    goto :eof
)
if "%out%"=="" (
    goto :eof
)

echo Using source folder: %src%
echo Using output folder: %out%

if not exist "%out%" mkdir "%out%"

cd /d "%src%"

echo "%src%\lib\sigil-vc2015-win64\lib\"
xcopy "%src%\lib\sigil-vc2015-win64\lib\*.dll" "%out%\" /y /i

echo "%src%\res\"
xcopy "%src%\res\*" "%out%\res\" /y /s /i

xcopy "%src%\config\*" "%out%\config\" /y /s /i
xcopy "%src%\data\*" "%out%\data\" /y /s /i

pause