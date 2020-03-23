@ECHO OFF
SETLOCAL

CALL :RunTestsConfigurations
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

ECHO [[ Success ]]
EXIT /b 0


:RunTestsConfigurations
CALL :RunTestsPlatforms Debug
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunTestsPlatforms Release
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:RunTestsPlatforms
CALL :RunTests %1 x86
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunTests %1 x64
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:RunTests
ECHO.
ECHO [[ Testing :: %1 :: %2 ]]
ECHO.
CALL dist\%1\%2\ManifestTests.exe
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0
