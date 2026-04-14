# Super Battle Golf - Modding Guide

This guide teaches you how to create mods for Super Battle Golf using the custom mod loader.

## Table of Contents

1. [Getting Started](#getting-started)
2. [Mod Structure](#mod-structure)
3. [Creating Custom Maps](#creating-custom-maps)
4. [Creating Custom Game Modes](#creating-custom-game-modes)
5. [Creating Custom Characters](#creating-custom-characters)
6. [Creating Custom Items](#creating-custom-items)
7. [Advanced Topics](#advanced-topics)

---

## Getting Started

### Prerequisites

- Super Battle Golf (installed via Steam)
- Mod Loader installed (see main README.md)
- Basic understanding of JSON files

For **map creation**:
- Unity 6000.3.10f1
- Unity Addressables 2.8.1

### Your First Mod

Let's create a simple mod that adds a custom game mode.

1. Create folder: `[Game]/Mods/GameModes/MyFirstMode/`
2. Create `mod.json`:

```json
{
  "id": "my-first-mode",
  "name": "My First Mode",
  "author": "YourName",
  "version": "1.0.0",
  "description": "A test game mode",
  "type": "gamemode",
  "gamemode": {
    "holes": [
      "CourseSelectionDesert01",
      "CourseSelectionDesert02",
      "CourseSelectionDesert03"
    ],
    "rules": {
      "overtimeDuration": 60.0,
      "itemSpawnChance": 0.5,
      "allowCustomItems": true
    }
  }
}
```

3. Launch the game with mod loader
4. Your mode will appear in custom modes!

---

## Mod Structure

### mod.json Format

Every mod needs a `mod.json` file:

```json
{
  "id": "unique-mod-id",           // Required: lowercase-with-dashes
  "name": "Display Name",           // Required
  "author": "Your Name",            // Required
  "version": "1.0.0",               // Required: semantic versioning
  "description": "What it does",    // Required
  "type": "map|gamemode|character|item",  // Required
  "dependencies": ["other-mod-id"], // Optional
  
  // Type-specific fields below
}
```

### Mod Types

| Type | Folder | Purpose |
|------|--------|---------|
| `map` | `Mods/Maps/` | Golf courses |
| `gamemode` | `Mods/GameModes/` | Custom rules/matches |
| `character` | `Mods/Characters/` | Skins/cosmetics |
| `item` | `Mods/Items/` | Weapons/power-ups |

---

## Creating Custom Maps

Custom maps require Unity and asset bundles.

### Step 1: Setup Unity Project

1. Install Unity Hub
2. Install Unity **6000.3.10f1** (exact version required!)
3. Create new **3D (URP)** project
4. Install Addressables:
   - Window → Package Manager
   - Unity Registry → Addressables → Install 2.8.1

### Step 2: Create Your Course

1. Create scene: `Assets/Scenes/MyCustomCourse.unity`
2. Build your golf course (terrain, holes, obstacles)
3. Add required components:
   - **CourseData** - Course metadata
   - **HoleData** - Per-hole info
   - Colliders and physics
4. Test in Unity play mode

### Step 3: Configure Addressables

1. Window → Asset Management → Addressables → Groups
2. Create new group: "MyCustomCourse"
3. Drag your scene into the group
4. Set Address: `"CustomCourseMyMap"` (must start with "CustomCourse")

### Step 4: Build Asset Bundle

1. Window → Asset Management → Addressables → Build
2. Build → New Build → Default Build Script
3. Find output: `Assets/AddressableAssetsData/Windows/`
4. Copy files to your mod folder

### Step 5: Create mod.json

```json
{
  "id": "my-custom-map",
  "name": "My Custom Golf Course",
  "author": "YourName",
  "version": "1.0.0",
  "description": "A fun new course with obstacles!",
  "type": "map",
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  }
}
```

### Final Structure

```
Mods/Maps/MyCustomMap/
├── mod.json
├── catalog.bin
├── catalog.json
└── *.bundle files
```

---

## Creating Custom Game Modes

Game modes don't require Unity - just JSON!

### Full Example

```json
{
  "id": "battle-royale-extreme",
  "name": "Battle Royale Extreme",
  "author": "ModMaster",
  "version": "1.0.0",
  "description": "18-hole chaos with max items",
  "type": "gamemode",
  "gamemode": {
    "holes": [
      "CourseSelectionDesert01",
      "CourseSelectionDesert02",
      "CourseSelectionDesert03",
      "CourseSelectionForest01",
      "CourseSelectionForest02",
      "CourseSelectionForest03",
      "CourseSelectionSnow01",
      "CourseSelectionSnow02",
      "CourseSelectionSnow03"
    ],
    "rules": {
      "overtimeDuration": 180.0,
      "itemSpawnChance": 1.0,
      "allowCustomItems": true,
      "maxPlayers": 8,
      "teamMode": false
    }
  }
}
```

### Available Holes

Use any hole ID from the base game:
- `CourseSelectionDesert01` through `CourseSelectionDesert05`
- `CourseSelectionForest01` through `CourseSelectionForest05`
- `CourseSelectionSnow01` through `CourseSelectionSnow05`
- `CourseSelectionSpace01` through `CourseSelectionSpace05`

Or reference custom maps:
- `CustomCourseMyMap` (from your custom map's Addressable address)

### Rules Options

| Field | Type | Description |
|-------|------|-------------|
| `overtimeDuration` | float | Overtime seconds (default: 60.0) |
| `itemSpawnChance` | float | 0.0-1.0 spawn chance (default: 0.5) |
| `allowCustomItems` | bool | Enable modded items (default: true) |
| `maxPlayers` | int | Max players (default: 4) |
| `teamMode` | bool | Team vs team (default: false) |

---

## Creating Custom Characters

Character mods add skins, cosmetics, and appearances.

### Step 1: Create Assets in Unity

1. Import character model (FBX/OBJ)
2. Setup materials and textures
3. Add to Addressables group
4. Set Address: `"CustomCosmeticSkinName"`
5. Build asset bundle

### Step 2: Create mod.json

```json
{
  "id": "cool-skin-pack",
  "name": "Cool Skin Pack",
  "author": "ArtistName",
  "version": "1.0.0",
  "description": "Awesome new skins",
  "type": "character",
  "character": {
    "cosmetics": [
      {
        "id": "neon-golfer",
        "name": "Neon Golfer",
        "type": "skin",
        "addressable": "CustomCosmeticNeonGolfer",
        "rarity": "epic"
      },
      {
        "id": "space-suit",
        "name": "Space Suit",
        "type": "outfit",
        "addressable": "CustomCosmeticSpaceSuit",
        "rarity": "legendary"
      }
    ]
  },
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  }
}
```

### Cosmetic Types

- `skin` - Full character skin
- `outfit` - Clothing/costume
- `hat` - Headwear
- `accessory` - Misc items
- `emote` - Victory animations
- `trail` - Ball trails

### Rarity Levels

- `common` - Gray
- `uncommon` - Green
- `rare` - Blue
- `epic` - Purple
- `legendary` - Gold

---

## Creating Custom Items

Add weapons, power-ups, and consumables.

### mod.json Example

```json
{
  "id": "ultimate-weapons",
  "name": "Ultimate Weapons Pack",
  "author": "WeaponSmith",
  "version": "1.0.0",
  "description": "OP weapons for chaos",
  "type": "item",
  "items": [
    {
      "id": "mega-rocket",
      "name": "Mega Rocket",
      "type": "weapon",
      "addressable": "CustomItemMegaRocket",
      "stats": {
        "damage": 100.0,
        "explosionRadius": 10.0,
        "cooldown": 5.0,
        "ammo": 3
      }
    },
    {
      "id": "speed-boost-ultra",
      "name": "Speed Boost Ultra",
      "type": "powerup",
      "addressable": "CustomItemSpeedBoostUltra",
      "stats": {
        "duration": 10.0,
        "speedMultiplier": 2.5
      }
    }
  ],
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  }
}
```

### Item Types

- `weapon` - Throwable/shootable
- `powerup` - Temporary buff
- `consumable` - One-time use
- `trap` - Placeable hazard

---

## Advanced Topics

### Dependencies

Mods can depend on other mods:

```json
{
  "id": "my-expansion",
  "dependencies": ["base-mod-pack", "another-mod"]
}
```

The loader ensures dependencies load first.

### Debugging

Check the log file:
```
%APPDATA%\Roaming\sbg-mod-loader\mod-loader.log
```

Common issues:
- ❌ **Mod not loading** → Check mod.json syntax
- ❌ **Assets not found** → Verify Addressable addresses match
- ❌ **Crash on load** → Check Unity version matches exactly

### Asset Bundle Best Practices

1. **Match Unity Version** - Must use 6000.3.10f1
2. **Use Addressables 2.8.1** - Exact version required
3. **Small Bundles** - Split large assets across bundles
4. **Compression** - Enable LZ4 compression for faster loads
5. **Test Locally** - Always test before distributing

### Performance Tips

- Keep poly counts reasonable (< 50k tris per model)
- Use texture atlases (combine small textures)
- Optimize materials (PBR Standard)
- Use LODs for distant objects
- Avoid excessive particle effects

---

## Getting Help

- GitHub Issues: [sbgmodloader/issues](https://github.com/ssfdre38/sbgmodloader/issues)
- Discord: [Link TBD]
- Wiki: [Link TBD]

---

**Happy Modding!** 🏌️⛳
