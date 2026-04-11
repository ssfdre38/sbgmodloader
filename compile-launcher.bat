@echo off
cd /d D:\SuperBattleGolfModLoader

REM Set up Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if %ERRORLEVEL% NEQ 0 (
    echo Failed to initialize Visual Studio 2022 build environment
    exit /b %ERRORLEVEL%
)

if not exist "x64\Release" mkdir "x64\Release"

cl.exe ^
  /EHsc /W3 /O2 /std:c++17 ^
  GameLauncher\src\main.cpp ^
  /link /OUT:"x64\Release\GameLauncher.exe" ^
  /SUBSYSTEM:CONSOLE /MACHINE:X64

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ===== LAUNCHER COMPILATION SUCCESSFUL =====
    echo EXE: D:\SuperBattleGolfModLoader\x64\Release\GameLauncher.exe
    echo.
    copy "x64\Release\GameLauncher.exe" "C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf\" /Y
    echo GameLauncher.exe deployed to game directory
) else (
    echo.
    echo ===== LAUNCHER COMPILATION FAILED =====
    echo Error code: %ERRORLEVEL%
)
