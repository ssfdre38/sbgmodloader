@echo off
cd /d D:\SuperBattleGolfModLoader

REM Set up Visual Studio environment
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

REM Compile ModLoaderCore.dll
set CL_COMPILER="C:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.35717\bin\Hostx64\x64\cl.exe"

%CL_COMPILER% ^
  /D_WINDOWS /D_USRDLL /D_WINDLL ^
  /EHsc /W3 /O2 /std:c++17 ^
  /I"ModSDK\include" /I"ThirdParty\include" /I"ModLoaderCore\include" ^
  ModLoaderCore\src\dllmain.cpp ^
  ModLoaderCore\src\Hooks.cpp ^
  ModLoaderCore\src\Overlay.cpp ^
  ModLoaderCore\src\ModManager.cpp ^
  ModLoaderCore\src\Log.cpp ^
  /link /DLL /OUT:"x64\Release\ModLoaderCore.dll" ^
  /SUBSYSTEM:WINDOWS /MACHINE:X64 ^
  detours.lib user32.lib kernel32.lib shell32.lib gdi32.lib

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ===== COMPILATION SUCCESSFUL =====
    echo DLL: D:\SuperBattleGolfModLoader\x64\Release\ModLoaderCore.dll
    echo.
    
    REM Copy to game directories
    copy "x64\Release\ModLoaderCore.dll" "C:\Windows\System32\" /Y
    copy "x64\Release\ModLoaderCore.dll" "C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf\x64\Release\" /Y
    
    echo DLL deployed to game directories
) else (
    echo.
    echo ===== COMPILATION FAILED =====
    echo Error code: %ERRORLEVEL%
)
