# Super Battle Golf Mod Folder Structure

## Overview
Mods are organized by type in dedicated subfolders for easy management and discovery.

## Directory Structure

```
📁 [Game Root]/Mods/
├── 📁 Maps/              ← Custom golf courses and arenas
├── 📁 GameModes/         ← Custom game rules and modes
├── 📁 Weapons/           ← Custom weapons and projectiles
├── 📁 Characters/        ← Custom characters, skins, and cosmetics
├── 📁 Audio/             ← Custom music, sound effects, and voice packs
├── 📁 UI/                ← UI modifications and themes
├── 📁 Scripts/           ← Behavior mods (C# DLL plugins)
└── 📁 Core/              ← Core utilities, libraries, and frameworks
```

## Mod Package Format

### Standard Mod Layout
Each mod lives in its own subfolder within the appropriate category:

```
📁 Maps/DesertArena/
├── mod.json              ← Mod metadata (REQUIRED)
├── catalog.bin           ← Addressables catalog (for asset mods)
├── catalog.hash          ← Catalog validation
├── *.bundle              ← Asset bundles
├── preview.png           ← Mod thumbnail (512x512 recommended)
└── README.md             ← Optional mod documentation
```

### mod.json Schema

```json
{
  "id": "desert-arena-v1",
  "name": "Desert Arena",
  "author": "YourName",
  "version": "1.0.0",
  "description": "A challenging desert-themed golf course with sandtraps and cacti",
  "type": "map",
  "gameVersion": "1.0+",
  "dependencies": [],
  "tags": ["desert", "competitive", "18-hole"],
  "url": "https://github.com/yourname/desert-arena",
  
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin",
    "primaryAsset": "DesertArena",
    "assetType": "scene"
  }
}
```

## Mod Types

### 1. Maps (`Maps/`)
**Purpose:** Custom golf courses, arenas, and environments

**Required Files:**
- `mod.json` - Metadata
- `catalog.bin` - Addressables catalog
- `*.bundle` - Scene asset bundles

**Example:**
```
Maps/LavaIsland/
├── mod.json
├── catalog.bin
├── catalog.hash
├── lavaisland_scenes_*.bundle
└── preview.png
```

### 2. Game Modes (`GameModes/`)
**Purpose:** Custom game rules, scoring systems, special modes

**Content:** Usually C# DLLs or JSON rule definitions

**Example:**
```
GameModes/KingOfTheHill/
├── mod.json
├── KingOfTheHill.dll
└── rules.json
```

### 3. Weapons (`Weapons/`)
**Purpose:** Custom golf clubs, projectiles, power-ups

**Required Files:**
- `mod.json` - Metadata
- Asset bundles with weapon models/effects

**Example:**
```
Weapons/LaserPutter/
├── mod.json
├── catalog.bin
├── laserputter_*.bundle
└── preview.png
```

### 4. Characters (`Characters/`)
**Purpose:** Custom player models, skins, cosmetics

**Content:** Character models, textures, animations

### 5. Audio (`Audio/`)
**Purpose:** Custom music, sound effects, announcers

**Content:** Audio asset bundles, music tracks

### 6. UI (`UI/`)
**Purpose:** UI modifications, HUD changes, menus

**Content:** UI prefabs, textures, layouts

### 7. Scripts (`Scripts/`)
**Purpose:** Code-based mods that modify game behavior

**Content:** C# DLLs, behavior scripts

**Security Note:** Scripts have full game access - only load from trusted sources!

### 8. Core (`Core/`)
**Purpose:** Shared libraries, utility frameworks, mod dependencies

**Content:** Reusable code libraries, frameworks

**Example:**
```
Core/ModFramework/
├── mod.json
├── ModFramework.dll
└── docs/
```

## Loading Order

1. **Core/** - Load shared libraries first
2. **Scripts/** - Load behavior mods
3. **Audio/, UI/** - Load presentation mods
4. **Weapons/, Characters/** - Load gameplay assets
5. **GameModes/** - Load game rule modifications
6. **Maps/** - Load after everything else (maps may depend on other mods)

## Mod Dependencies

Mods can declare dependencies in `mod.json`:

```json
{
  "dependencies": [
    {
      "id": "mod-framework",
      "version": ">=1.0.0"
    },
    {
      "id": "custom-weapons-api",
      "version": "^2.1.0"
    }
  ]
}
```

The mod loader will:
1. Resolve dependency tree
2. Load dependencies before dependents
3. Warn about missing/incompatible dependencies

## Mod Discovery

The mod loader scans all category folders on startup:

```
[INFO] Scanning for mods...
[INFO] Found 3 mods in Maps/
[INFO] Found 1 mod in Weapons/
[INFO] Found 2 mods in Scripts/
[INFO] Total: 6 mods discovered
```

## Best Practices

### For Mod Creators:
- Always include `mod.json` with complete metadata
- Use semantic versioning (major.minor.patch)
- Include `preview.png` for mod browsers
- Document dependencies clearly
- Test with only your mod enabled (no conflicts)

### For Mod Users:
- Keep mods organized in correct category folders
- Check mod compatibility before enabling
- Read mod documentation
- Report issues to mod authors

### For Mod Loader:
- Validate `mod.json` schema before loading
- Gracefully handle missing/corrupt mods
- Log all loading errors with helpful messages
- Allow mods to be enabled/disabled without file deletion

## Example: Installing a Map Mod

1. Download `DesertArena.zip`
2. Extract to `Mods/Maps/DesertArena/`
3. Verify structure:
   ```
   Mods/Maps/DesertArena/
   ├── mod.json          ✅
   ├── catalog.bin       ✅
   └── *.bundle          ✅
   ```
4. Launch game - mod auto-detected!

## Future: Mod Manager UI

Planned features:
- Browse installed mods by category
- Enable/disable individual mods
- View mod details (description, author, version)
- Check for updates
- One-click installation from URLs
- Conflict detection and resolution

## Technical Notes

### Addressables Catalogs
- Each mod can have its own catalog
- Catalogs are loaded additively (won't replace game's catalog)
- Asset addresses must be unique across all mods

### Asset Bundle Compatibility
- Must match game's Unity version
- Use same platform (StandaloneWindows64)
- Respect game's texture/mesh import settings

### Script Mods Security
- Scripts have full game access (powerful but dangerous)
- Consider sandboxing in future versions
- Warn users about untrusted script mods

---

**Version:** 1.0  
**Last Updated:** 2026-04-11  
**Status:** Specification (Implementation Pending)
