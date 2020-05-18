CALL "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" %BUILDARCH% %BUILDWINDOWSSDK%
SET CC=%VCToolsInstallDir%\bin\Host%VSCMD_ARG_TGT_ARCH%\%VSCMD_ARG_TGT_ARCH%\cl.exe
SET CXX=%VCToolsInstallDir%\bin\Host%VSCMD_ARG_TGT_ARCH%\%VSCMD_ARG_TGT_ARCH%\cl.exe
ECHO CC=%CC%
ECHO CXX=%CXX%
