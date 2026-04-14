# Repository Branch Guide

This repository uses separate branches to organize different components of the Super Battle Golf modding ecosystem.

## Branch Structure

### 🔧 `master` - Core Mod Loader
**Purpose:** C++ DLL mod loader  
**Size:** ~100 files, ~2MB  
**Language:** C++17  

**Contains:**
- `ModLoaderCore/` - Source code (15 managers/helpers)
- `compile.bat` - Build script
- `docs/` - Development documentation
- `Mods/` - Example test mods
- Test reports and architecture docs

**For:** Core developers, contributors

**Build:**
```bash
git checkout master
compile.bat
```

---

### 📦 `sdk-package` - Mod Developer SDK
**Purpose:** Templates, examples, tools for mod creation  
**Size:** 18 files, ~43KB  
**Language:** JSON, PowerShell  

**Contains:**
- `SDK/Templates/` - 4 mod type templates (Map, GameMode, Character, Item)
- `SDK/Examples/` - 4 complete example mods with READMEs
- `SDK/Tools/` - BuildMod.ps1, ValidateMod.ps1
- `SDK/README.md`, `QUICKSTART.md`, `CHANGELOG.md`

**For:** Mod developers who want to create content

**Use:**
```bash
git checkout sdk-package
cd SDK
# Follow QUICKSTART.md
```

---

### 🗺️ `mapmaker-tool` - Unity Map Maker
**Purpose:** No-code Unity editor for creating custom golf courses  
**Size:** 13 files, ~40KB code  
**Language:** C# (Unity)  

**Contains:**
- `MapMaker/Assets/Scripts/` - 6 C# scripts (editor tools + components)
- `MapMaker/Packages/` - Unity package dependencies
- `MapMaker/ProjectSettings/` - Unity 6000.3.10f1 configuration
- `MapMaker/README.md`, `QUICKSTART.md`, `CHANGELOG.md`

**For:** Map creators (no coding required!)

**Use:**
```bash
git checkout mapmaker-tool
# Install Unity 6000.3.10f1
# Open MapMaker/ in Unity
# Follow QUICKSTART.md
```

---

## Which Branch Do I Need?

### I want to...

**...play with mods:**
→ Download release from `master` branch

**...create a custom map:**
→ Use `mapmaker-tool` branch
→ Requires: Unity 6000.3.10f1
→ Time: 5-15 minutes per map
→ Coding: None!

**...create a custom game mode, character, or item:**
→ Use `sdk-package` branch
→ Requires: Text editor, basic JSON knowledge
→ Time: 10-30 minutes per mod
→ Coding: Minimal (just JSON)

**...contribute to the mod loader:**
→ Use `master` branch
→ Requires: Visual Studio 2022, C++ knowledge
→ Time: Varies
→ Coding: C++

---

## Branch Relationships

```
master (core mod loader)
  ├─ Loads all mod types
  ├─ Tested with examples from sdk-package
  └─ Loads maps exported from mapmaker-tool

sdk-package (mod creation)
  ├─ Templates match mod loader expectations
  ├─ Examples tested with master
  └─ Tools generate mod loader-compatible output

mapmaker-tool (map creation)
  ├─ Exports map mods for master
  ├─ Generates mod.json matching sdk-package format
  └─ Creates asset bundles master can load
```

**All branches are compatible and work together!**

---

## Clone Instructions

### Get Everything
```bash
git clone https://github.com/ssfdre38/sbgmodloader.git
cd sbgmodloader

# All branches downloaded automatically
git branch -a
```

### Switch Branches
```bash
# To mod loader
git checkout master

# To SDK
git checkout sdk-package

# To Map Maker
git checkout mapmaker-tool
```

### Work on Multiple Components
```bash
# Clone into separate folders
git clone -b master https://github.com/ssfdre38/sbgmodloader.git modloader
git clone -b sdk-package https://github.com/ssfdre38/sbgmodloader.git sdk
git clone -b mapmaker-tool https://github.com/ssfdre38/sbgmodloader.git mapmaker
```

---

## File Organization

### master Branch
```
sbgmodloader/
├── ModLoaderCore/        (C++ source)
│   ├── include/          (Headers)
│   ├── src/              (Implementations)
│   └── libs/             (Dependencies)
├── compile.bat           (Build script)
├── docs/                 (Documentation)
├── Mods/                 (Test mods)
└── README.md
```

### sdk-package Branch
```
sbgmodloader/
├── SDK/
│   ├── Templates/        (mod.json templates)
│   ├── Examples/         (Complete example mods)
│   ├── Tools/            (Build/validation scripts)
│   ├── README.md
│   ├── QUICKSTART.md
│   └── CHANGELOG.md
└── [Also has master files]
```

### mapmaker-tool Branch
```
sbgmodloader/
├── MapMaker/
│   ├── Assets/
│   │   └── Scripts/      (C# editor tools)
│   ├── Packages/         (Unity packages)
│   ├── ProjectSettings/  (Unity config)
│   ├── README.md
│   ├── QUICKSTART.md
│   └── CHANGELOG.md
└── [Also has master files]
```

**Note:** `sdk-package` and `mapmaker-tool` branches **include all master files** plus their additional content.

---

## Development Workflow

### Working on Core Mod Loader
```bash
git checkout master
# Make changes to ModLoaderCore/
compile.bat
# Test
git add .
git commit -m "feat: your changes"
git push origin master
```

### Working on SDK
```bash
git checkout sdk-package
# Make changes to SDK/
# Test templates/examples
git add SDK/
git commit -m "docs: update SDK"
git push origin sdk-package
```

### Working on Map Maker
```bash
git checkout mapmaker-tool
# Make changes to MapMaker/
# Test in Unity
git add MapMaker/
git commit -m "feat: improve map maker"
git push origin mapmaker-tool
```

---

## Branch Synchronization

When master is updated, SDK and Map Maker branches should be synced:

```bash
# Update SDK branch with master changes
git checkout sdk-package
git merge master
git push origin sdk-package

# Update Map Maker branch with master changes
git checkout mapmaker-tool
git merge master
git push origin mapmaker-tool
```

**Sync frequency:** After major master updates

---

## Quick Reference

| Branch | Size | Language | Build Time | For |
|--------|------|----------|------------|-----|
| `master` | ~2MB | C++ | 5-10 min | Core devs |
| `sdk-package` | ~43KB | JSON | N/A | Mod creators |
| `mapmaker-tool` | ~40KB | C# | 1-2 min | Map creators |

**Current Status:** 24/26 complete (92.3%)

---

## Questions?

- **Core mod loader issues** → master branch
- **SDK problems** → sdk-package branch  
- **Map Maker bugs** → mapmaker-tool branch

**GitHub Issues:** https://github.com/ssfdre38/sbgmodloader/issues

---

**Happy Modding!** 🎮⛳
