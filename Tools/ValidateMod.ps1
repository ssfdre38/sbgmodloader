# Super Battle Golf - Mod Validator
# Validates mod structure and configuration before publishing

param(
    [Parameter(Mandatory=$true)]
    [string]$ModPath
)

$ErrorActionPreference = "Stop"
$validationErrors = @()
$validationWarnings = @()

Write-Host "=== Super Battle Golf Mod Validator ===" -ForegroundColor Cyan
Write-Host ""
Write-Host "Validating: $ModPath" -ForegroundColor White
Write-Host ""

# Check mod folder exists
if (!(Test-Path $ModPath)) {
    Write-Host "❌ Mod folder not found: $ModPath" -ForegroundColor Red
    exit 1
}

# Check mod.json exists
$modJsonPath = Join-Path $ModPath "mod.json"
if (!(Test-Path $modJsonPath)) {
    $validationErrors += "mod.json not found"
} else {
    Write-Host "✅ mod.json exists" -ForegroundColor Green
    
    # Parse JSON
    try {
        $modJson = Get-Content $modJsonPath -Raw | ConvertFrom-Json
        Write-Host "✅ mod.json is valid JSON" -ForegroundColor Green
        
        # Validate required fields
        $requiredFields = @('id', 'name', 'author', 'version', 'description', 'type')
        foreach ($field in $requiredFields) {
            if (!$modJson.$field) {
                $validationErrors += "Missing required field: $field"
            }
        }
        
        if ($validationErrors.Count -eq 0) {
            Write-Host "✅ All required fields present" -ForegroundColor Green
        }
        
        # Validate ID format (lowercase-with-dashes)
        if ($modJson.id -and $modJson.id -cnotmatch '^[a-z0-9-]+$') {
            $validationErrors += "ID must be lowercase-with-dashes (got: $($modJson.id))"
        } else {
            Write-Host "✅ ID format valid: $($modJson.id)" -ForegroundColor Green
        }
        
        # Validate version format (semantic versioning)
        if ($modJson.version -and $modJson.version -notmatch '^\d+\.\d+\.\d+') {
            $validationWarnings += "Version should use semantic versioning (e.g., 1.0.0)"
        } else {
            Write-Host "✅ Version format valid: $($modJson.version)" -ForegroundColor Green
        }
        
        # Validate type
        $validTypes = @('map', 'gamemode', 'character', 'item')
        if ($modJson.type -and $modJson.type -notin $validTypes) {
            $validationErrors += "Invalid type: $($modJson.type) (must be: $($validTypes -join ', '))"
        } else {
            Write-Host "✅ Type valid: $($modJson.type)" -ForegroundColor Green
        }
        
        # Type-specific validation
        switch ($modJson.type) {
            'map' {
                # Check for asset bundles
                if ($modJson.content.addressables) {
                    $catalogPath = Join-Path $ModPath $modJson.content.catalogPath
                    if (!(Test-Path $catalogPath)) {
                        $validationErrors += "Catalog file not found: $($modJson.content.catalogPath)"
                    } else {
                        Write-Host "✅ Catalog file found" -ForegroundColor Green
                    }
                    
                    # Check for bundle files
                    $bundles = Get-ChildItem -Path $ModPath -Filter "*.bundle" -ErrorAction SilentlyContinue
                    if ($bundles.Count -eq 0) {
                        $validationWarnings += "No .bundle files found - did you build asset bundles?"
                    } else {
                        Write-Host "✅ Found $($bundles.Count) asset bundle(s)" -ForegroundColor Green
                    }
                }
            }
            'gamemode' {
                # Validate gamemode section
                if (!$modJson.gamemode) {
                    $validationErrors += "Missing 'gamemode' section"
                } else {
                    if (!$modJson.gamemode.holes -or $modJson.gamemode.holes.Count -eq 0) {
                        $validationErrors += "gamemode.holes must have at least one hole"
                    } else {
                        Write-Host "✅ Game mode has $($modJson.gamemode.holes.Count) hole(s)" -ForegroundColor Green
                    }
                }
            }
            'character' {
                # Validate character section
                if (!$modJson.character) {
                    $validationErrors += "Missing 'character' section"
                } else {
                    if (!$modJson.character.cosmetics -or $modJson.character.cosmetics.Count -eq 0) {
                        $validationErrors += "character.cosmetics must have at least one cosmetic"
                    } else {
                        Write-Host "✅ Character mod has $($modJson.character.cosmetics.Count) cosmetic(s)" -ForegroundColor Green
                        
                        # Validate cosmetic addressables
                        foreach ($cosmetic in $modJson.character.cosmetics) {
                            if ($cosmetic.addressable -and $cosmetic.addressable -notmatch '^CustomCosmetic') {
                                $validationErrors += "Cosmetic addressable must start with 'CustomCosmetic': $($cosmetic.addressable)"
                            }
                        }
                    }
                    
                    # Check for asset bundles
                    if ($modJson.content.addressables) {
                        $catalogPath = Join-Path $ModPath $modJson.content.catalogPath
                        if (!(Test-Path $catalogPath)) {
                            $validationErrors += "Catalog file not found: $($modJson.content.catalogPath)"
                        } else {
                            Write-Host "✅ Catalog file found" -ForegroundColor Green
                        }
                    }
                }
            }
            'item' {
                # Validate items section
                if (!$modJson.items -or $modJson.items.Count -eq 0) {
                    $validationErrors += "items array must have at least one item"
                } else {
                    Write-Host "✅ Item mod has $($modJson.items.Count) item(s)" -ForegroundColor Green
                    
                    # Validate item addressables
                    foreach ($item in $modJson.items) {
                        if ($item.addressable -and $item.addressable -notmatch '^CustomItem') {
                            $validationErrors += "Item addressable must start with 'CustomItem': $($item.addressable)"
                        }
                    }
                }
                
                # Check for asset bundles
                if ($modJson.content.addressables) {
                    $catalogPath = Join-Path $ModPath $modJson.content.catalogPath
                    if (!(Test-Path $catalogPath)) {
                        $validationErrors += "Catalog file not found: $($modJson.content.catalogPath)"
                    } else {
                        Write-Host "✅ Catalog file found" -ForegroundColor Green
                    }
                }
            }
        }
        
    } catch {
        $validationErrors += "Failed to parse mod.json: $($_.Exception.Message)"
    }
}

# Check for README (optional but recommended)
$readmePath = Join-Path $ModPath "README.md"
if (!(Test-Path $readmePath)) {
    $validationWarnings += "No README.md found (recommended for documentation)"
} else {
    Write-Host "✅ README.md found" -ForegroundColor Green
}

# File size check
$totalSize = (Get-ChildItem -Path $ModPath -Recurse | Measure-Object -Property Length -Sum).Sum
$sizeMB = [math]::Round($totalSize / 1MB, 2)
Write-Host "📦 Total mod size: $sizeMB MB" -ForegroundColor Cyan

if ($sizeMB -gt 500) {
    $validationWarnings += "Mod size is large ($sizeMB MB) - consider optimizing assets"
}

# Summary
Write-Host ""
Write-Host "========================================" -ForegroundColor Cyan

if ($validationErrors.Count -eq 0 -and $validationWarnings.Count -eq 0) {
    Write-Host "✅ VALIDATION PASSED!" -ForegroundColor Green
    Write-Host ""
    Write-Host "Your mod is ready to publish!" -ForegroundColor White
    exit 0
} else {
    if ($validationErrors.Count -gt 0) {
        Write-Host "❌ VALIDATION FAILED" -ForegroundColor Red
        Write-Host ""
        Write-Host "Errors ($($validationErrors.Count)):" -ForegroundColor Red
        foreach ($error in $validationErrors) {
            Write-Host "  • $error" -ForegroundColor Red
        }
    }
    
    if ($validationWarnings.Count -gt 0) {
        Write-Host ""
        Write-Host "⚠️  Warnings ($($validationWarnings.Count)):" -ForegroundColor Yellow
        foreach ($warning in $validationWarnings) {
            Write-Host "  • $warning" -ForegroundColor Yellow
        }
    }
    
    Write-Host ""
    if ($validationErrors.Count -gt 0) {
        Write-Host "Please fix errors before publishing." -ForegroundColor Red
        exit 1
    } else {
        Write-Host "Warnings are optional but recommended to fix." -ForegroundColor Yellow
        exit 0
    }
}
