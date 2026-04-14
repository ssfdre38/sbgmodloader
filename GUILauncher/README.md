# Super Battle Golf - GUI Mod Launcher

A modern WPF application for managing and launching Super Battle Golf with mods.

## Features

### 🎮 Game Launching
- **Launch with Mods** - Start game with mod loader injected
- **Launch Vanilla** - Start game without any mods
- Auto-detect game installation
- Game version display

### 📦 Mod Management
- **View All Mods** - See all installed mods at a glance
- **Enable/Disable** - Toggle individual mods with checkboxes
- **Bulk Operations** - Enable/disable all mods with one click
- **Organized by Type** - Separate tabs for Maps, Game Modes, Characters, Items
- **Mod Details** - View name, author, version, description

### 🔍 Advanced Features
- **Conflict Detection** - Warns about duplicate mod IDs
- **Dependency Tracking** - Shows mod dependencies (future)
- **Auto-Save States** - Remembers which mods are enabled
- **Quick Refresh** - Instant mod list updates
- **Open Mods Folder** - Direct access to mod directory

### 📊 Statistics
- Total mod count
- Enabled mod count
- Real-time updates

## Quick Start

### For Users

1. **Build the launcher:**
   ```bash
   cd GUILauncher
   dotnet build
   ```

2. **Run:**
   ```bash
   dotnet run
   ```

3. **Or build release:**
   ```bash
   dotnet publish -c Release -r win-x64 --self-contained
   ```

4. **First Launch:**
   - Click "Browse..." to select your Super Battle Golf installation folder
   - Launcher will scan for mods automatically
   - Use checkboxes to enable/disable mods
   - Click "Launch with Mods" to play!

### For Players (Standalone)

Just run `SBGModLauncher.exe` - no installation needed!

## How It Works

### Mod Discovery

The launcher scans:
```
[Game]\Mods\
├── Maps\
├── GameModes\
├── Characters\
└── Items\
```

Each mod folder must contain `mod.json`:
```json
{
  "id": "my-mod",
  "name": "My Mod",
  "author": "YourName",
  "version": "1.0.0",
  "description": "A cool mod",
  "type": "map"
}
```

### Enable/Disable System

**Enabled:** `Mods/Maps/MyMap/`  
**Disabled:** `Mods/Maps/.disabled_MyMap/`

The launcher renames folders with `.disabled_` prefix to disable mods.
The mod loader skips folders starting with `.disabled_`.

**Benefits:**
- No file modification
- Instant toggle
- Preserves mod data
- Works with all mod types

### Settings Storage

Mod states saved to:
```
%APPDATA%\sbg-mod-loader\launcher-config.json
```

Format:
```json
{
  "my-map-id": true,
  "another-mod": false
}
```

## Architecture

### MVVM Pattern

**Models:**
- `ModInfo` - Represents a mod with metadata

**ViewModels:**
- `MainViewModel` - Main window logic and state

**Views:**
- `MainWindow.xaml` - UI layout

**Services:**
- `ModService` - Mod discovery and management
- `GameLauncherService` - Game launching logic

### Technologies

- **.NET 8.0** - Latest framework
- **WPF** - Modern Windows UI
- **MVVM Toolkit** - Clean architecture
- **Newtonsoft.Json** - JSON parsing

## UI Overview

### Header
- Game version display
- Browse button for game path

### Sidebar (Quick Actions)
- Launch with Mods (green)
- Launch Vanilla (gray)
- Refresh Mods
- Enable All
- Disable All
- Open Mods Folder
- Statistics panel

### Main Area (Tabs)
- **All Mods** - Every mod with type indicator
- **Maps** - Map mods with holes/difficulty
- **Game Modes** - Game mode mods
- **Characters** - Character/cosmetic mods
- **Items** - Item/weapon mods

### Details Panel
- Selected mod information
- Name, description, author, version

### Status Bar
- Current operation status
- Launcher version

## Building

### Requirements
- .NET 8.0 SDK
- Visual Studio 2022 or VS Code

### Build Commands

**Debug:**
```bash
dotnet build
```

**Release:**
```bash
dotnet publish -c Release -r win-x64 --self-contained
```

**Output:** `bin/Release/net8.0-windows/win-x64/publish/`

### Distribution

Package contents:
```
SBGModLauncher/
├── SBGModLauncher.exe
├── SBGModLauncher.dll
├── Newtonsoft.Json.dll
├── CommunityToolkit.Mvvm.dll
└── [Other .NET runtime DLLs]
```

**Size:** ~60MB (self-contained)  
**No .NET installation required!**

## Customization

### Colors

Edit `MainWindow.xaml` resources:
```xml
<SolidColorBrush x:Key="PrimaryBrush" Color="#2196F3"/>
<SolidColorBrush x:Key="AccentBrush" Color="#FF9800"/>
<SolidColorBrush x:Key="SuccessBrush" Color="#4CAF50"/>
```

### Game Path Detection

Edit `MainViewModel.AutoDetectGamePath()`:
```csharp
var possiblePaths = new[]
{
    @"C:\Your\Custom\Path",
    // Add more paths
};
```

## Troubleshooting

### "Game not found"
- Click "Browse..." and manually select game folder
- Folder must contain `Super Battle Golf.exe`

### "Mods not appearing"
- Check `Mods/` folder exists in game directory
- Verify `mod.json` files are valid JSON
- Click "Refresh Mods" button

### "Launch failed"
- Verify `ModLoader.dll` exists in game folder
- Check `LaunchGameWithMods.ps1` script exists
- Run as administrator if needed

### "Checkboxes don't work"
- Ensure you have write permissions to Mods folder
- Check if mods are in use (game running)

## Advanced Usage

### Command Line

```bash
# Specify game path
SBGModLauncher.exe --game-path "C:\Games\SBG"

# Launch immediately with mods
SBGModLauncher.exe --launch-modded

# Launch vanilla
SBGModLauncher.exe --launch-vanilla
```

### Integration

```csharp
// Use ModService in your own app
var modService = new ModService(@"C:\Games\SBG");
var mods = modService.DiscoverMods();

foreach (var mod in mods)
{
    Console.WriteLine($"{mod.Name} - {mod.IsEnabled}");
}
```

## Future Enhancements

### Planned Features
- ✅ Mod search/filter
- ✅ Sort by name, type, author
- ✅ Mod update checking
- ✅ One-click mod install
- ✅ Mod profiles (load sets of mods)
- ✅ Backup/restore configurations
- ✅ Workshop browser integration
- ✅ Mod screenshots/previews

### Contribution Ideas
- Dark theme
- Localization
- Mod load order customization
- Performance monitoring
- Cloud sync for mod configs

## License

MIT License - See main repository LICENSE file

## Credits

- **Framework:** .NET 8.0, WPF
- **Libraries:** Newtonsoft.Json, MVVM Toolkit
- **Icons:** Emoji (cross-platform compatible)
- **Design:** Material Design inspired

## Support

- **Issues:** https://github.com/ssfdre38/sbgmodloader/issues
- **Discord:** [TBD]
- **Logs:** `%APPDATA%\sbg-mod-loader\mod-loader.log`

---

**Version:** 1.0.0  
**Last Updated:** 2026-04-14
