@ECHO OFF
SETLOCAL
ECHO.

ECHO [[ Looking for Visual C++ 2017... ]]

SET VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% GOTO NoBuildTools

CALL :RunArch x86
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunArch x64
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

ECHO.
ECHO [[ Success ]]
EXIT /b 0


REM ############################
REM ##
REM ##  Toolchain architecture
REM ##
REM ############################

:RunArch
SETLOCAL
ECHO.
ECHO [[ Preparing the environment with %1 build tools ]]
ECHO.
SET VSCMD_ARG_TGT_ARCH=not-set
CALL %VCVARSALL_BAT% %1
IF NOT "%VSCMD_ARG_TGT_ARCH%"=="%1" GOTO VCVarsError

IF %WindowsSDKVersion:~-1%==\ SET WindowsSDKVersion=%WindowsSDKVersion:~0,-1%

CALL :RunGenerate %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunBuild %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunInstall %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0



REM ############################
REM ##
REM ##  CMake generate
REM ##
REM ############################

:RunGenerate
CALL :Generate Debug %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Generate Release %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:Generate
ECHO.
ECHO [[ Generate :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake -B build\%1\Win32\%VSCMD_ARG_TGT_ARCH% -S . -G Ninja -DCMAKE_BUILD_TYPE=%1 -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_SYSTEM_VERSION=%WindowsSDKVersion%
EXIT /b %ERRORLEVEL%



REM ############################
REM ##
REM ##  CMake build
REM ##
REM ############################

:RunBuild
CALL :Build Debug %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Build Release %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:Build
ECHO.
ECHO [[ Build :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake --build build\%1\Win32\%VSCMD_ARG_TGT_ARCH%
EXIT /b %ERRORLEVEL%



REM ############################
REM ##
REM ##  CMake install
REM ##
REM ############################

:RunInstall
CALL :Install Debug %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Install Release %1
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0

:Install
ECHO.
ECHO [[ Install :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake --install build\%1\Win32\%VSCMD_ARG_TGT_ARCH% --prefix dist --component dist
EXIT /b %ERRORLEVEL%


:NoBuildTools
ECHO [[ ERROR ]] Failed to find Visual C++ 2017 in any of the standard locations
EXIT /b 1

:VCVarsError
ECHO [[ ERROR ]] Failed while trying to configure the environment for a Visual C++ build
EXIT /b 2
