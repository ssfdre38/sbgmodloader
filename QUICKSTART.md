# SDK Quick Start

Get up and running with mod development in 5 minutes!

## Prerequisites

- Windows 10/11
- Unity Hub installed
- Super Battle Golf (with mod loader installed)

## Step 1: Install Unity (5 minutes)

1. Download [Unity Hub](https://unity.com/download)
2. Open Unity Hub
3. Click "Installs" → "Install Editor"
4. Select version **6000.3.10f1** (exact version!)
5. Install with default modules

## Step 2: Install Addressables (2 minutes)

1. Create new Unity project (3D URP template)
2. Window → Package Manager
3. Select "Unity Registry"
4. Find "Addressables" → Install version **2.8.1**

## Step 3: Import SDK (1 minute)

Copy SDK files to your project or import via Package Manager.

## Step 4: Choose Your Path

### Path A: Game Mode (Easiest - No Unity!)

Perfect for beginners - just edit JSON!

1. Copy `SDK/Templates/GameModeTemplate/`
2. Edit `mod.json`:
   - Change `id`, `name`, `author`
   - Customize holes and rules
3. Copy to `[Game]/Mods/GameModes/YourMod/`
4. Test in-game!

**Time:** 10 minutes  
**Difficulty:** ⭐☆☆☆☆

---

### Path B: Custom Map (Intermediate - Unity Required)

Create golf courses!

1. Open Unity project
2. Create new scene
3. Build terrain, holes, obstacles
4. Add to Addressables (address: `CustomCourseYourMap`)
5. Build asset bundles
6. Create mod.json
7. Test in-game!

**Time:** 1-4 hours  
**Difficulty:** ⭐⭐⭐☆☆

See: `SDK/Examples/ExampleMap/`

---

### Path C: Character Skin (Advanced - 3D Modeling)

Custom character appearance!

1. Create/import character model
2. Setup materials in Unity
3. Add to Addressables (address: `CustomCosmeticYourSkin`)
4. Build asset bundles
5. Create mod.json with cosmetics array
6. Test in-game!

**Time:** 2-8 hours  
**Difficulty:** ⭐⭐⭐⭐☆

See: `SDK/Examples/ExampleCharacter/`

---

### Path D: Custom Item (Expert - Programming)

Weapons and power-ups!

1. Create item prefab in Unity
2. Write C# behavior script
3. Add visual/audio effects
4. Add to Addressables (address: `CustomItemYourItem`)
5. Build asset bundles
6. Create mod.json with item stats
7. Test and balance!

**Time:** 4-12 hours  
**Difficulty:** ⭐⭐⭐⭐⭐

See: `SDK/Examples/ExampleItem/`

---

## Building Your Mod

### Option 1: Automated Build (Recommended)

```powershell
.\SDK\Tools\BuildMod.ps1 `
    -ModType "Map" `
    -ModName "My Awesome Course" `
    -UnityProjectPath "C:\MyUnityProject" `
    -OutputPath "C:\Mods"
```

### Option 2: Manual Build

1. Unity: Window → Asset Management → Addressables → Build
2. Copy output from `Assets/AddressableAssetsData/Windows/`
3. Create mod.json manually
4. Copy to game's Mods folder

## Testing Your Mod

1. Copy mod folder to:
   ```
   [Game]\Mods\[Type]\[YourMod]\
   ```
   
   Examples:
   - Maps: `C:\...\Super Battle Golf\Mods\Maps\MyMap\`
   - GameModes: `C:\...\Super Battle Golf\Mods\GameModes\MyMode\`

2. Launch game with mod loader

3. Check log file for errors:
   ```
   %APPDATA%\sbg-mod-loader\mod-loader.log
   ```

4. Test your content in-game!

## Validating Before Publishing

```powershell
.\SDK\Tools\ValidateMod.ps1 -ModPath "C:\Mods\MyMod"
```

Checks:
- ✅ mod.json syntax and required fields
- ✅ Addressable address prefixes
- ✅ File structure
- ✅ Asset bundles present

## Publishing Your Mod

1. **Test thoroughly** - Make sure it works!
2. **Validate** - Run ValidateMod.ps1
3. **Document** - Create README.md with installation instructions
4. **Package** - Zip your mod folder
5. **Upload** - Share on GitHub, Nexus Mods, etc.

## Common Issues

### "Asset bundle won't load"
- ✅ Check Unity version (must be 6000.3.10f1 exactly)
- ✅ Check Addressables version (must be 2.8.1 exactly)
- ✅ Verify address prefix (CustomCourse, CustomCosmetic, CustomItem)

### "Mod not appearing in-game"
- ✅ Check mod.json syntax (use JSON validator)
- ✅ Verify folder location (correct Mods subfolder)
- ✅ Check log file for errors
- ✅ Ensure mod loader is installed

### "Compilation errors in Unity"
- ✅ Import Addressables package first
- ✅ Use URP project template
- ✅ Check Unity version

## Next Steps

- 📖 Read full [Modding Guide](../docs/MODDING_GUIDE.md)
- 🔧 Explore [Examples](Examples/)
- 📋 Use [Templates](Templates/)
- 💬 Get help on Discord [TBD]

---

**Ready? Pick a path above and start creating!** 🎉
