# Super Battle Golf Mod Loader

A native C++ mod loader for Super Battle Golf, enabling custom modifications through a simple DLL-based plugin system.

## ✨ Features

- ✅ **Native C++ Architecture** - No .NET dependencies, works directly with Unity IL2CPP
- ✅ **DLL Injection System** - Clean injection using Windows CreateRemoteThread
- ✅ **Update-Proof** - Survives game updates (tested: v1.1.0 → v1.1.1)
- ✅ **Mod Discovery** - Automatically loads mods from `Mods/` directory
- ✅ **Simple SDK** - Easy-to-use interface for mod developers
- ✅ **Comprehensive Logging** - Full debug logs in `%APPDATA%\sbg-mod-loader\`

## 🚀 Quick Start

### For Players

1. Download the latest release
2. Extract `GameLauncher.exe` and `ModLoaderCore.dll` to your Super Battle Golf directory
3. Place mod DLLs in the `Mods/` folder
4. Run `GameLauncher.exe` to start the game with mods loaded

### For Developers

1. Clone this repository
2. Open the Visual Studio solution or use the provided build scripts
3. Create a new mod by implementing the `IModModule` interface from ModSDK
4. Compile your mod and place the DLL in the `Mods/` folder

## 📁 Project Structure

```
SuperBattleGolfModLoader/
├── GameLauncher/          # DLL injection tool
│   └── main.cpp           # Injects ModLoaderCore.dll into game process
├── ModLoaderCore/         # Core mod loader framework
│   ├── src/
│   │   ├── dllmain.cpp    # DLL entry point
│   │   ├── Hooks.cpp      # Game integration & initialization
│   │   ├── ModManager.cpp # Mod discovery & lifecycle management
│   │   ├── Overlay.cpp    # Window title modification for verification
│   │   └── Log.cpp        # Logging system
│   └── include/           # Header files
├── ModSDK/                # SDK for mod developers
│   └── include/
│       └── IModModule.h   # Interface all mods must implement
├── VersionDisplayMod/     # Example mod
│   └── VersionDisplayMod.cpp
├── Detours/               # Microsoft Detours library (for hooking)
└── compile.bat            # Build script
```

## 🛠️ Building from Source

### Prerequisites

- Visual Studio 2026 (or 2022)
- Windows SDK
- C++17 support

### Build Steps

```batch
# Build Detours library (one-time)
cd Detours\src
nmake

# Build mod loader
cd ..\..
compile.bat

# Build game launcher
cd GameLauncher
compile-launcher.bat
```

## 🔌 Creating Mods

### Basic Mod Template

```cpp
#include "IModModule.h"
#include <string>

class MyMod : public ModSDK::IModModule {
public:
    const char* GetModName() override { 
        return "MyMod"; 
    }
    
    const char* GetModVersion() override { 
        return "1.0.0"; 
    }
    
    bool OnLoad() override {
        // Initialize your mod here
        return true;
    }
    
    void OnUnload() override {
        // Cleanup
    }
    
    void OnUpdate(float deltaTime) override {
        // Called every frame
    }
};

// Export the mod creation function
extern "C" __declspec(dllexport) ModSDK::IModModule* CreateMod() {
    return new MyMod();
}
```

### IModModule Interface

Mods implement these callbacks:

- `GetModName()` - Return your mod's name
- `GetModVersion()` - Return version string
- `OnLoad()` - Called when mod is loaded (return false to prevent loading)
- `OnUnload()` - Called when game exits or mod is unloaded
- `OnUpdate(float deltaTime)` - Called every frame
- `OnLateUpdate(float deltaTime)` - Called after all updates
- `OnSceneLoaded(const char* sceneName)` - Called when a new scene loads

## 🏗️ Architecture

### How It Works

1. **GameLauncher.exe** - Starts the game and injects `ModLoaderCore.dll`
2. **ModLoaderCore.dll** - Loads once game window is detected
3. **ModManager** - Scans `Mods/` folder for DLLs
4. **Mod Loading** - Calls `CreateMod()` function in each DLL
5. **Lifecycle** - Calls appropriate callbacks (OnLoad, OnUpdate, etc.)

### Why Native C++?

We tried .NET/EasyHook initially, but Unity's IL2CPP compilation creates a native binary that doesn't use the .NET runtime. This caused complete CLR isolation, making .NET-based injection impossible. Native C++ works directly with the game's memory space.

### Why Not Hook Game Methods?

The initial plan was to use Detours to hook IL2CPP methods, but:
- Decompiled code RVAs pointed to non-executable memory
- IL2CPP reorganizes code differently than the decompiled version
- Game updates would break hardcoded addresses

Instead, we use window detection and title modification for verification, with the framework ready to add proper hooks when correct addresses are available.

## 📝 Logs

Logs are saved to: `%APPDATA%\sbg-mod-loader\mod-loader.log`

Contains:
- DLL injection status
- Mod discovery and loading
- Game window detection
- Error messages and warnings

## 🤝 Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Code Style

- Use descriptive variable names
- Comment complex logic
- Keep functions focused and single-purpose
- Follow existing code formatting

## 📜 License

This project is open source. See LICENSE file for details.

## ⚠️ Disclaimer

This mod loader is for educational and community enhancement purposes. Always respect the game developers and do not use mods to cheat in online play or circumvent game protections.

## 🙏 Acknowledgments

- **Microsoft Detours** - For the hooking library
- **Super Battle Golf Devs** - For creating an awesome game
- **Community** - For testing and contributions

## 📧 Support

- **Issues**: Report bugs via GitHub Issues
- **Discussions**: Use GitHub Discussions for questions and ideas

---

**Status**: ✅ Fully Operational (Tested on Super Battle Golf v1.1.1)
