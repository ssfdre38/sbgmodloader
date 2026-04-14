# Super Battle Golf Mod Loader

A native C++ mod loader for Super Battle Golf, built from scratch without frameworks. Injects directly into Unity and enables custom maps, game modes, characters, and items.

## ✅ Features

- **Custom Maps** - Load golf courses via Unity Addressables
- **Custom Game Modes** - Custom rules, holes, match types
- **Custom Characters** - Skins, cosmetics, appearances
- **Custom Items** - Weapons, power-ups, consumables
- **UI Injection** - Modify game UI
- **Mod Management** - Auto-discovery, loading, dependencies

## 🚀 Quick Start

### Players
1. Download release
2. Extract to game directory
3. Run `LaunchGameWithMods.ps1`
4. Add mods to `Mods/` folder

### Mod Creators

**For creating mods:**
1. Clone this repository: `git clone https://github.com/ssfdre38/sbgmodloader.git`
2. Check out the SDK: `git checkout sdk-package`
3. Follow `SDK/QUICKSTART.md`

**For creating maps:**
1. Check out Map Maker: `git checkout mapmaker-tool`
2. Install Unity 6000.3.10f1
3. Open MapMaker project
4. Follow `MapMaker/QUICKSTART.md`

## 📦 Mod Structure

```
Mods/
├── Maps/YourMap/
│   ├── mod.json
│   └── *.bundle
├── GameModes/YourMode/
│   └── mod.json
├── Characters/YourCharacter/
│   ├── mod.json
│   └── *.bundle
└── Items/YourItem/
    ├── mod.json
    └── *.bundle
```

## 🛠️ Development

### Build Requirements
- Visual Studio 2022
- C++17
- Windows SDK
- Microsoft Detours

### Build
```bash
compile.bat
```

## 🔍 Debugging

Log file: `%APPDATA%\sbg-mod-loader\mod-loader.log`

## 🏗️ Architecture

- **MonoHelper** - Unity/Mono integration
- **ModManager** - Mod discovery & loading
- **GameModeManager** - Custom game modes
- **CharacterManager** - Custom cosmetics
- **ItemManager** - Custom items
- **SceneHooks** - Scene detection

## 📊 Status

**24/26 features complete (92.3%)!**

✅ Core injection, Mono integration, maps, game modes, characters, items, UI injection, network sync, SDK, map maker

⏳ GUI launcher, mod distribution

## 📂 Repository Branches

This repository is organized into separate branches for different components:

- **`master`** - Core mod loader (C++ DLL, this branch)
- **`sdk-package`** - SDK for mod developers (templates, examples, tools)
- **`mapmaker-tool`** - Unity project for creating custom maps (no-code map editor)

### Getting the SDK
```bash
git checkout sdk-package
```

### Getting the Map Maker
```bash
git checkout mapmaker-tool
```

## 🎯 Game Info

- **Unity Version:** 6000.3.10f1
- **Addressables:** 2.8.1
- **Backend:** Mono (not IL2CPP)

## 🙏 Credits

Built from scratch - no BepInEx, no frameworks, just C++ and determination.

---

**Version:** 0.1.0-beta
