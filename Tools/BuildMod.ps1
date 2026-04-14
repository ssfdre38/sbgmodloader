# Super Battle Golf - Mod Builder
# Automates Unity asset bundle building and mod packaging

param(
    [Parameter(Mandatory=$true)]
    [ValidateSet('Map', 'Character', 'Item')]
    [string]$ModType,
    
    [Parameter(Mandatory=$true)]
    [string]$ModName,
    
    [Parameter(Mandatory=$true)]
    [string]$UnityProjectPath,
    
    [Parameter(Mandatory=$true)]
    [string]$OutputPath
)

$ErrorActionPreference = "Stop"

Write-Host "=== Super Battle Golf Mod Builder ===" -ForegroundColor Cyan
Write-Host ""

# Validate Unity project
if (!(Test-Path "$UnityProjectPath\Assets")) {
    Write-Host "❌ Invalid Unity project path" -ForegroundColor Red
    exit 1
}

# Check for Addressables
$addressablesPath = "$UnityProjectPath\Assets\AddressableAssetsData"
if (!(Test-Path $addressablesPath)) {
    Write-Host "❌ Addressables not configured in project" -ForegroundColor Red
    Write-Host "   Run: Window → Asset Management → Addressables → Groups" -ForegroundColor Yellow
    exit 1
}

Write-Host "✅ Unity project validated" -ForegroundColor Green

# Build asset bundles (requires Unity Editor to be installed)
$unityPath = "C:\Program Files\Unity\Hub\Editor\6000.3.10f1\Editor\Unity.exe"
if (!(Test-Path $unityPath)) {
    Write-Host "⚠️  Unity 6000.3.10f1 not found at default location" -ForegroundColor Yellow
    Write-Host "   Please build asset bundles manually:" -ForegroundColor Yellow
    Write-Host "   Window → Asset Management → Addressables → Build → New Build → Default Build Script" -ForegroundColor Yellow
    $skipBuild = $true
} else {
    Write-Host "🔨 Building asset bundles..." -ForegroundColor Cyan
    
    $buildArgs = @(
        "-quit",
        "-batchmode",
        "-projectPath", "`"$UnityProjectPath`"",
        "-executeMethod", "UnityEditor.AddressableAssets.Build.DataBuilders.BuildScriptPackedMode.BuildContent"
    )
    
    & $unityPath $buildArgs
    
    if ($LASTEXITCODE -ne 0) {
        Write-Host "❌ Asset bundle build failed" -ForegroundColor Red
        exit 1
    }
    
    Write-Host "✅ Asset bundles built" -ForegroundColor Green
}

# Create mod folder structure
$modFolder = Join-Path $OutputPath $ModName
New-Item -ItemType Directory -Path $modFolder -Force | Out-Null

Write-Host "📁 Created mod folder: $modFolder" -ForegroundColor Cyan

# Copy asset bundles
$bundleSource = "$UnityProjectPath\Assets\AddressableAssetsData\Windows"
if (Test-Path $bundleSource) {
    Copy-Item "$bundleSource\*" -Destination $modFolder -Recurse -Force
    Write-Host "✅ Copied asset bundles" -ForegroundColor Green
} else {
    Write-Host "⚠️  No asset bundles found - build manually if needed" -ForegroundColor Yellow
}

# Generate mod.json template
$modJsonPath = Join-Path $modFolder "mod.json"

$template = switch ($ModType) {
    'Map' {
        @"
{
  "id": "$($ModName.ToLower() -replace ' ', '-')",
  "name": "$ModName",
  "author": "YourName",
  "version": "1.0.0",
  "description": "TODO: Add description",
  "type": "map",
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  },
  "meta": {
    "difficulty": "medium",
    "holes": 3,
    "environment": "custom",
    "tags": ["custom"]
  }
}
"@
    }
    'Character' {
        @"
{
  "id": "$($ModName.ToLower() -replace ' ', '-')",
  "name": "$ModName",
  "author": "YourName",
  "version": "1.0.0",
  "description": "TODO: Add description",
  "type": "character",
  "character": {
    "cosmetics": [
      {
        "id": "cosmetic-1",
        "name": "TODO: Cosmetic Name",
        "type": "skin",
        "addressable": "CustomCosmeticYourName",
        "rarity": "rare",
        "description": "TODO: Description"
      }
    ]
  },
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  },
  "meta": {
    "tags": ["skin"]
  }
}
"@
    }
    'Item' {
        @"
{
  "id": "$($ModName.ToLower() -replace ' ', '-')",
  "name": "$ModName",
  "author": "YourName",
  "version": "1.0.0",
  "description": "TODO: Add description",
  "type": "item",
  "items": [
    {
      "id": "item-1",
      "name": "TODO: Item Name",
      "type": "weapon",
      "addressable": "CustomItemYourName",
      "description": "TODO: Description",
      "stats": {
        "damage": 50.0,
        "explosionRadius": 5.0,
        "cooldown": 3.0,
        "ammo": 5
      }
    }
  ],
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  },
  "meta": {
    "tags": ["weapon"]
  }
}
"@
    }
}

$template | Out-File -FilePath $modJsonPath -Encoding UTF8
Write-Host "✅ Generated mod.json template" -ForegroundColor Green

# Create README
$readmePath = Join-Path $modFolder "README.md"
$readme = @"
# $ModName

TODO: Add mod description

## Installation

1. Copy this folder to: `[Game]\Mods\$($ModType)s\$ModName\`
2. Launch game with mod loader
3. Enjoy!

## Credits

Author: YourName
Version: 1.0.0

---

Created with Super Battle Golf Mod Loader SDK
"@

$readme | Out-File -FilePath $readmePath -Encoding UTF8
Write-Host "✅ Generated README.md" -ForegroundColor Green

Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan
Write-Host "✅ Mod build complete!" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Yellow
Write-Host "1. Edit mod.json (fill in TODOs)" -ForegroundColor White
Write-Host "2. Test: Copy to [Game]\Mods\$($ModType)s\$ModName\" -ForegroundColor White
Write-Host "3. Distribute: Zip folder and share!" -ForegroundColor White
Write-Host ""
Write-Host "Output: $modFolder" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan
