@ECHO OFF
SETLOCAL
ECHO.

ECHO [[ Looking for Visual C++ 2019... ]]

SET VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% set VCVARSALL_BAT="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat"
IF NOT EXIST %VCVARSALL_BAT% GOTO NoBuildTools

CALL :RunGenerate
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunBuild
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :RunInstall
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

ECHO [[ Success ]]
EXIT /b 0



REM ############################
REM ##
REM ##  CMake generate
REM ##
REM ############################

:RunGenerate
CALL :RunGeneratePlatform x86
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

CALL :RunGeneratePlatform x64
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

EXIT /b 0


:RunGeneratePlatform
SETLOCAL
ECHO.
ECHO [[ Preparing the environment with %1 build tools ]]
ECHO.
SET VSCMD_ARG_TGT_ARCH=not-set
CALL %VCVARSALL_BAT% %1
IF NOT "%VSCMD_ARG_TGT_ARCH%"=="%1" GOTO VCVarsError

CALL :Generate Debug
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Generate Release
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:Generate
ECHO.
ECHO [[ Generate :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake -B build\%1\%VSCMD_ARG_TGT_ARCH% -S . -G Ninja -DCMAKE_BUILD_TYPE=%1 -DCMAKE_TOOLCHAIN_FILE=CMake\toolchain.windows.cmake
EXIT /b %ERRORLEVEL%



REM ############################
REM ##
REM ##  CMake build
REM ##
REM ############################

:RunBuild
CALL :RunBuildPlatform x86
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

CALL :RunBuildPlatform x64
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

EXIT /b 0


:RunBuildPlatform
CALL :Build Debug
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Build Release
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0


:Build
ECHO.
ECHO [[ Build :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake --build build\%1\%VSCMD_ARG_TGT_ARCH%
EXIT /b %ERRORLEVEL%



REM ############################
REM ##
REM ##  CMake install
REM ##
REM ############################

:RunInstall
CALL :RunInstallPlatform x86
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

CALL :RunInstallPlatform x64
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%
ECHO.

EXIT /b 0


:RunInstallPlatform
CALL :Install Debug
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

CALL :Install Release
SET EL=%ERRORLEVEL%
IF NOT "%EL%"=="0" EXIT /b %EL%

EXIT /b 0

:Install
ECHO.
ECHO [[ Install :: %1 :: %VSCMD_ARG_TGT_ARCH% ]]
ECHO.
CALL cmake --install build\%1\%VSCMD_ARG_TGT_ARCH% --prefix dist --component dist
EXIT /b %ERRORLEVEL%


:NoBuildTools
ECHO [[ ERROR ]] Failed to find Visual C++ 2019 in any of the standard locations
EXIT /b 1

:VCVarsError
ECHO [[ ERROR ]] Failed while trying to configure the environment for a Visual C++ build
EXIT /b 2
