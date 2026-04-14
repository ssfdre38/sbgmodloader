# Super Battle Golf Mod Loader SDK

Official development kit for creating Super Battle Golf mods.

## What's Included

- **Unity Package** - Import into Unity 6000.3.10f1
- **Templates** - Pre-configured mod structures
- **Examples** - Working reference mods
- **Build Tools** - Automated asset bundle building
- **Documentation** - Quick start guides

## Quick Start

### 1. Install Unity

Download and install **Unity 6000.3.10f1** (exact version required)

### 2. Create New Project

1. Open Unity Hub
2. Click "New Project"
3. Select **3D (URP)** template
4. Name: "MySuperbattleGolfMods"
5. Click "Create Project"

### 3. Install Addressables

1. Window → Package Manager
2. Select "Unity Registry"
3. Find "Addressables"
4. Install version **2.8.1**

### 4. Import SDK

**Method A: Package Manager (Recommended)**
1. Window → Package Manager
2. Click "+" → "Add package from git URL"
3. Enter: `https://github.com/ssfdre38/sbgmodloader.git?path=/SDK/UnityPackage`

**Method B: Local Install**
1. Download this repository
2. Copy `SDK/UnityPackage` to your project's `Packages` folder
3. Rename to `com.superbattlegolf.modloader-sdk`

### 5. Import Examples

1. Window → Package Manager
2. Find "Super Battle Golf Mod Loader SDK"
3. Expand "Samples"
4. Import the examples you want

## Creating Your First Mod

### Option 1: Custom Map

See `Examples/ExampleMap/` for complete working example.

**Quick Steps:**
1. Create new scene
2. Build your golf course (terrain, holes, obstacles)
3. Add to Addressables group (address must start with "CustomCourse")
4. Build asset bundles (Tools → Build Addressables)
5. Copy output to `[Game]/Mods/Maps/YourMod/`
6. Create `mod.json` (see template)

### Option 2: Custom Game Mode

See `Examples/ExampleGameMode/` for complete working example.

**Quick Steps:**
1. Copy template from `Templates/GameMode/`
2. Edit `mod.json` (no Unity required!)
3. Set holes, rules, settings
4. Copy to `[Game]/Mods/GameModes/YourMod/`

### Option 3: Custom Character

See `Examples/ExampleCharacter/` for complete working example.

**Quick Steps:**
1. Import character model (FBX/OBJ)
2. Setup materials and textures
3. Add to Addressables (address must start with "CustomCosmetic")
4. Build asset bundles
5. Create `mod.json` with cosmetic definitions
6. Copy to `[Game]/Mods/Characters/YourMod/`

### Option 4: Custom Item

See `Examples/ExampleItem/` for complete working example.

**Quick Steps:**
1. Create prefab with item scripts
2. Add to Addressables (address must start with "CustomItem")
3. Build asset bundles
4. Create `mod.json` with item stats
5. Copy to `[Game]/Mods/Items/YourMod/`

## Build Tools

### Asset Bundle Builder

Automates Addressables build and export:

1. Window → Super Battle Golf → Build Mod
2. Select mod type
3. Choose output folder
4. Click "Build"

Automatically:
- Builds asset bundles
- Copies catalog files
- Creates folder structure
- Generates mod.json template

### Mod Validator

Checks your mod before publishing:

1. Window → Super Battle Golf → Validate Mod
2. Select mod folder
3. Click "Validate"

Checks:
- mod.json syntax and required fields
- Addressable addresses (correct prefixes)
- Unity version compatibility
- Asset bundle integrity
- File size limits

## Templates

Pre-configured mod structures in `Templates/`:

- **MapTemplate/** - Empty course with basic setup
- **GameModeTemplate/** - JSON config template
- **CharacterTemplate/** - Cosmetic mod structure
- **ItemTemplate/** - Weapon/item mod structure

Copy and customize for your mod.

## Examples

Complete working mods in `Examples/`:

### ExampleMap - "Red Cube Arena"
- Simple test course with red cube
- Demonstrates scene setup
- Addressables configuration
- mod.json for maps

### ExampleGameMode - "Test Battle Royale"
- 3-hole game mode
- Custom rules configuration
- Demonstrates JSON structure

### ExampleCharacter - "Neon Golfer Skin"
- Custom character skin
- Material/texture setup
- Cosmetic metadata

### ExampleItem - "Mega Rocket Launcher"
- Custom weapon prefab
- Item stats configuration
- Asset bundle workflow

## Documentation

- **[Quick Start Guide](../docs/MODDING_GUIDE.md)** - Full tutorial
- **[API Reference](../docs/API_REFERENCE.md)** - C++ API (advanced)
- **[Architecture](../docs/ARCHITECTURE.md)** - System design (advanced)

## Troubleshooting

### Unity Version Mismatch
**Error:** Asset bundles won't load in game  
**Solution:** Must use Unity 6000.3.10f1 exactly

### Addressables Version Wrong
**Error:** Catalog loading fails  
**Solution:** Must use Addressables 2.8.1 exactly

### Address Prefix Missing
**Error:** Content doesn't appear in game  
**Solution:** Addresses must start with:
- Maps: `CustomCourse...`
- Characters: `CustomCosmetic...`
- Items: `CustomItem...`

### Asset Bundle Not Found
**Error:** Mod folder missing files  
**Solution:** Build Addressables (Window → Asset Management → Addressables → Build)

## Publishing Your Mod

1. **Test locally** - Copy to game's Mods folder and test
2. **Validate** - Use SDK Mod Validator tool
3. **Package** - Zip your mod folder
4. **Upload** - Share on GitHub, Nexus Mods, etc.
5. **Document** - Include README with installation instructions

## Support

- **Issues:** [GitHub Issues](https://github.com/ssfdre38/sbgmodloader/issues)
- **Discord:** [TBD]
- **Wiki:** [TBD]

## Version History

**v0.1.0** (2026-04-14)
- Initial SDK release
- Map, GameMode, Character, Item templates
- Example mods
- Build tools

---

**Happy Modding!** 🏌️⛳
