# Build Release Package Script
# Creates a portable ZIP release (no installer needed)

param(
    [string]$Version = "1.0.0"
)

$ErrorActionPreference = "Stop"

Write-Host "Building Super Battle Golf Mod Loader v$Version" -ForegroundColor Green
Write-Host ""

# Paths
$RootDir = Split-Path -Parent $PSScriptRoot
$ReleaseDir = Join-Path $RootDir "Releases"
$TempDir = Join-Path $ReleaseDir "temp"
$OutputZip = Join-Path $ReleaseDir "SBGModLoader-v$Version-Portable.zip"

# Clean up
Write-Host "Cleaning up old releases..." -ForegroundColor Yellow
if (Test-Path $TempDir) { Remove-Item $TempDir -Recurse -Force }
New-Item -ItemType Directory -Path $TempDir -Force | Out-Null
New-Item -ItemType Directory -Path $ReleaseDir -Force | Out-Null

# Build C++ Mod Loader
Write-Host "Building ModLoaderCore.dll..." -ForegroundColor Cyan
Push-Location (Join-Path $RootDir "ModLoaderCore")
& compile.bat
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: C++ build failed!" -ForegroundColor Red
    exit 1
}
Pop-Location

# Build .NET GUI Launcher
Write-Host "Building GUI Launcher..." -ForegroundColor Cyan
Push-Location (Join-Path $RootDir "GUILauncher")
dotnet publish -c Release -r win-x64 --self-contained false
if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: .NET build failed!" -ForegroundColor Red
    exit 1
}
Pop-Location

# Copy files to temp directory
Write-Host "Packaging files..." -ForegroundColor Cyan

# Core mod loader
Copy-Item (Join-Path $RootDir "ModLoaderCore\Release\ModLoaderCore.dll") $TempDir

# GUI Launcher
$GuiBuildDir = Join-Path $RootDir "GUILauncher\bin\Release\net8.0-windows\win-x64\publish"
Copy-Item "$GuiBuildDir\*" $TempDir -Recurse

# PowerShell launcher
Copy-Item (Join-Path $RootDir "LaunchGameWithMods.ps1") $TempDir

# Documentation
Copy-Item (Join-Path $RootDir "README.md") $TempDir
Copy-Item (Join-Path $RootDir "BRANCHES.md") $TempDir
Copy-Item (Join-Path $RootDir "docs") $TempDir -Recurse

# Create Mods folder structure
$ModsFolders = @("Maps", "GameModes", "Characters", "Items", "Audio", "UI", "Scripts", "Core")
foreach ($folder in $ModsFolders) {
    $path = Join-Path $TempDir "Mods\$folder"
    New-Item -ItemType Directory -Path $path -Force | Out-Null
    
    # Add README in each folder
    $readmeContent = @"
# $folder Mods

Place your $folder mods in this folder.

Each mod should be in its own subfolder with a mod.json file:

``````
Mods/$folder/
├── YourModName/
│   ├── mod.json
│   └── [mod files]
``````

To disable a mod, rename its folder to start with `.disabled_`
Example: `.disabled_YourModName`

For more information, see the documentation in the docs folder.
"@
    Set-Content -Path (Join-Path $path "README.txt") -Value $readmeContent
}

# Create installation guide
$InstallGuide = @"
# Super Battle Golf Mod Loader - Installation Guide

## Quick Start (5 minutes)

### Step 1: Extract Files
Extract this ZIP to any location (e.g., C:\SBGModLoader or D:\Games\SBGModLoader)

### Step 2: Run the Launcher
Double-click **SBGModLauncher.exe**

### Step 3: Set Game Path
- The launcher will try to auto-detect your game installation
- If it doesn't find it, click "Browse" and select your game folder
- The game folder contains "Super Battle Golf.exe"

### Step 4: Install Mods
- Click "Open Mods Folder" or browse to the Mods folder
- Place mods in the appropriate subfolder (Maps, GameModes, etc.)
- Click "Refresh Mods" to reload the list

### Step 5: Launch!
- Click "Launch with Mods" to start the game with mods enabled
- Or click "Launch Vanilla" to play without mods

## Folder Structure

``````
SBGModLoader/
├── SBGModLauncher.exe     (Main launcher - start here!)
├── ModLoaderCore.dll       (Core mod loader)
├── LaunchGameWithMods.ps1  (PowerShell script)
├── Mods/                   (Your mods go here)
│   ├── Maps/
│   ├── GameModes/
│   ├── Characters/
│   ├── Items/
│   └── [other types]/
└── docs/                   (Documentation)
``````

## Windows SmartScreen Warning

**This is NORMAL for unsigned software!**

When you first run the launcher, Windows may show:
> "Windows protected your PC"

This happens because the software isn't code-signed (signing costs $400/year).

**To run anyway:**
1. Click "More info"
2. Click "Run anyway"

The software is safe - it's open source: https://github.com/ssfdre38/sbgmodloader

## Finding Mods

- Check out the mod browser: Click "Browse Mods" in the launcher
- Visit the GitHub repository for examples
- Join the community Discord (link in README.md)

## Troubleshooting

**Game not found?**
- Make sure you selected the folder containing "Super Battle Golf.exe"
- Try common locations:
  - C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf
  - D:\SteamLibrary\steamapps\common\Super Battle Golf

**Mods not loading?**
- Check mod.json is valid
- Make sure folder isn't disabled (.disabled_ prefix)
- Check logs: %APPDATA%\sbg-mod-loader\mod-loader.log

**Need help?**
- Read docs/MOD_DISTRIBUTION_SYSTEM.md
- Check GitHub Issues
- Ask in Discord

## Uninstallation

Simply delete the folder - no registry entries or system changes!

## Version

Super Battle Golf Mod Loader v$Version
Built: $(Get-Date -Format 'yyyy-MM-dd')
"@

Set-Content -Path (Join-Path $TempDir "INSTALL.txt") -Value $InstallGuide

# Create ZIP
Write-Host "Creating ZIP archive..." -ForegroundColor Cyan
if (Test-Path $OutputZip) { Remove-Item $OutputZip -Force }
Compress-Archive -Path "$TempDir\*" -DestinationPath $OutputZip -CompressionLevel Optimal

# Clean up
Remove-Item $TempDir -Recurse -Force

Write-Host ""
Write-Host "SUCCESS! Release package created:" -ForegroundColor Green
Write-Host "  $OutputZip" -ForegroundColor White
Write-Host ""
Write-Host "File size: $([math]::Round((Get-Item $OutputZip).Length / 1MB, 2)) MB" -ForegroundColor Cyan
Write-Host ""
Write-Host "Ready to distribute!" -ForegroundColor Green
