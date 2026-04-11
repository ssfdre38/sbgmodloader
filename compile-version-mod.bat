@echo off
cd /d D:\SuperBattleGolfModLoader

REM Set up Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

REM Compile VersionDisplayMod.dll
set CL_COMPILER="C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.35717\bin\Hostx64\x64\cl.exe"

%CL_COMPILER% ^
  /D_WINDOWS /D_USRDLL /D_WINDLL ^
  /EHsc /W3 /O2 /std:c++17 ^
  /I"ModSDK\include" /I"ThirdParty\include" ^
  VersionDisplayMod\VersionDisplayMod.cpp ^
  /link /DLL /OUT:"x64\Release\VersionDisplayMod.dll" ^
  /SUBSYSTEM:WINDOWS /MACHINE:X64 ^
  user32.lib kernel32.lib

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ===== VersionDisplayMod COMPILATION SUCCESSFUL =====
    echo DLL: D:\SuperBattleGolfModLoader\x64\Release\VersionDisplayMod.dll
    echo.
    
    REM Copy to mods directory
    if not exist "Mods" mkdir Mods
    copy "x64\Release\VersionDisplayMod.dll" "Mods\VersionDisplayMod.dll" /Y
    
    echo DLL deployed to Mods directory
) else (
    echo.
    echo ===== VersionDisplayMod COMPILATION FAILED =====
    echo Error code: %ERRORLEVEL%
)
