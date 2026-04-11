@echo off
REM Set up Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

REM Build Detours
cd /d D:\SuperBattleGolfModLoader\Detours
nmake

echo Build complete. Detours library should be in lib.X64

REM Copy lib files to parent directory
if exist lib.X64 (
    copy lib.X64\detours.lib ..\detours.lib
    echo Copied detours.lib to SuperBattleGolfModLoader
)
