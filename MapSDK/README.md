# Super Battle Golf Map SDK

## Overview

The Map SDK allows developers to create custom golf courses for Super Battle Golf. Maps are distributed as DLLs that implement the `IMapModule` interface and include Unity asset bundles containing the 3D environment.

## Quick Start

### 1. Include the SDK Header

```cpp
#include "IMapModule.h"
using namespace MapSDK;
```

### 2. Implement IMapModule

```cpp
class MyCustomMap : public IMapModule {
public:
    const char* GetMapName() override {
        return "My Awesome Course";
    }
    
    const char* GetMapDescription() override {
        return "A challenging tropical course with water hazards";
    }
    
    // ... implement other required methods
};
```

### 3. Export CreateMap Function

```cpp
extern "C" __declspec(dllexport) IMapModule* CreateMap() {
    return new MyCustomMap();
}
```

### 4. Build the DLL

Use the provided build script or your own build system:

```batch
cl /LD /MD /std:c++17 /I..\MapSDK\include MyMap.cpp
```

### 5. Create Unity Asset Bundle

In Unity:
1. Create your golf course scene
2. Mark it as Addressable
3. Build the asset bundle for Windows Standalone
4. Place bundle in `Maps/MyMap/` folder

### 6. Deploy

Place in the game's mod folder:
```
Super Battle Golf/
└── Mods/
    └── Maps/
        └── MyMap/
            ├── MyMap.dll
            └── mycourse.bundle
```

## Map Structure

### Required Components

Every custom map must have:

1. **Spawn Points** - Where players start
   - At least 1 spawn point
   - Support for up to 16 players recommended
   - Position and rotation defined

2. **Goal** - Where players finish
   - Single hole/goal per course
   - Trigger radius for detection
   - Par value for scoring

3. **Bounds** - Play area definition
   - Min/max XYZ coordinates
   - "Kill Z" for instant respawn below certain height
   - Out-of-bounds detection

4. **Collision Mesh** - Ground and obstacles
   - Physics-enabled geometry
   - Walk-able surfaces
   - Wall colliders

### Optional Components

- **Item Spawners** - Power-up locations
- **Mobility Spawners** - Golf cart spawn points
- **Water Hazards** - Special respawn zones
- **Jump Pads** - Launch players upward
- **Moving Platforms** - Dynamic obstacles
- **Custom Game Rules** - JSON configuration

## IMapModule Interface Reference

### Identity Methods

```cpp
const char* GetMapName()           // Display name (required)
const char* GetMapDescription()    // Brief description (required)
const char* GetAuthor()            // Creator name (required)
const char* GetVersion()           // Version string (required)
```

### Property Methods

```cpp
MapDifficulty GetDifficulty()     // Easy, Medium, Hard, Expert
MapTheme GetTheme()                // Tropical, Desert, Snow, etc.
int GetMinPlayers()                // Minimum recommended players
int GetMaxPlayers()                // Maximum supported players
int GetEstimatedTime()             // Completion time in minutes
```

### Asset Bundle Methods

```cpp
const char* GetAssetBundlePath()   // Path to .bundle file
const char* GetSceneName()         // Unity scene address key
```

### Geometry Methods

```cpp
SpawnPoint* GetSpawnPoints(int& outCount)  // Array of spawn positions
GoalInfo* GetGoalInfo()                    // Goal/hole information
MapBounds* GetBounds()                     // Play area bounds
```

### Lifecycle Callbacks

```cpp
void OnRegister()                  // Map registered with loader
void OnBeforeLoad()                // Before scene loads
void OnLoaded()                    // After scene loads
void OnPlayerSpawn(void*)          // Player spawned
void OnPlayerGoal(void*, float)    // Player reached goal
void OnUnload()                    // Map unloading
```

### Optional Overrides

```cpp
const char* GetCustomRules()       // JSON game rules
const char* GetPreviewImagePath()  // Preview thumbnail
bool SupportsMultiplayer()         // Multiplayer support
const char* GetRequirements()      // Required DLC/mods
```

## Data Structures

### SpawnPoint

```cpp
struct SpawnPoint {
    float x, y, z;          // World position
    float rotationY;        // Y-axis rotation in degrees
    int maxPlayers;         // Max players for this spawn
    const char* name;       // Optional label
};
```

### GoalInfo

```cpp
struct GoalInfo {
    float x, y, z;          // World position
    float radius;           // Trigger radius
    int par;                // Par for this hole
    const char* name;       // Hole name
};
```

### MapBounds

```cpp
struct MapBounds {
    float minX, minY, minZ; // Minimum bounds
    float maxX, maxY, maxZ; // Maximum bounds
    float killZ;            // Instant respawn height
};
```

## Building in Unity

### Project Setup

1. Install Unity 6000.3.10f1 (game's version)
2. Create new 3D project
3. Install Addressables package
4. Import game's shared assets (materials, shaders)

### Scene Requirements

Your golf course scene must include:

#### GameObjects
- Terrain or ground mesh
- Collision geometry
- Visual meshes
- Lighting

#### Scripts (from game)
- Course Manager component
- Spawn Point markers
- Goal trigger zone
- Bounds markers

### Addressables Setup

1. Open **Window > Asset Management > Addressables > Groups**
2. Create new group: "MyMap"
3. Add your scene to the group
4. Set address key (e.g., "Assets/Scenes/MyCourse.unity")
5. Build addressables for Windows Standalone

### Building Asset Bundles

```
Build Settings > Addressables > Build > New Build > Default Build Script
```

Output location: `Assets/AddressableAssets/StandaloneWindows64/`

## Custom Game Rules

You can override game rules with JSON:

```cpp
const char* GetCustomRules() override {
    return R"({
        "allowItems": true,
        "allowGolfCart": false,
        "timeLimit": 600,
        "respawnOnOutOfBounds": true,
        "gravity": 1.0,
        "windSpeed": 0.5,
        "parMultiplier": 1.0
    })";
}
```

### Available Rules

| Rule | Type | Default | Description |
|------|------|---------|-------------|
| `allowItems` | bool | true | Enable power-ups |
| `allowGolfCart` | bool | true | Enable golf carts |
| `timeLimit` | int | 0 | Time limit in seconds (0 = none) |
| `respawnOnOutOfBounds` | bool | true | Auto-respawn when out of bounds |
| `gravity` | float | 1.0 | Gravity multiplier |
| `windSpeed` | float | 0.0 | Wind effect strength |
| `parMultiplier` | float | 1.0 | Score multiplier |

## Testing Your Map

### Local Testing

1. Build your map DLL
2. Copy DLL and bundle to `Mods/Maps/YourMap/`
3. Launch game
4. Check mod loader log for errors
5. Your map should appear in course selection

### Debug Logging

Add logging to your map code:

```cpp
#include "../ModLoaderCore/src/Log.h"

void OnLoaded() override {
    Log::Info("[MyMap] Map loaded successfully!");
}
```

## Best Practices

### Performance

- Keep vertex count under 100k for main geometry
- Use LODs for distant objects
- Bake lighting where possible
- Optimize texture sizes (2K max recommended)

### Gameplay

- Test with minimum and maximum player counts
- Provide multiple routes/strategies
- Balance difficulty with fun
- Include visual guides (arrows, signs)

### Compatibility

- Test with and without items enabled
- Verify multiplayer synchronization
- Handle edge cases (players getting stuck)
- Provide clear out-of-bounds indicators

## Example Maps

See `ExampleMap/` folder for a complete implementation demonstrating:
- Basic map structure
- Spawn point configuration
- Goal setup
- Bounds definition
- Custom rules

## Troubleshooting

### Map Not Loading

- Check DLL is in correct folder
- Verify asset bundle path matches GetAssetBundlePath()
- Check mod loader log for errors
- Ensure DLL exports CreateMap() function

### Asset Bundle Not Found

- Verify bundle is in Maps/YourMap/ folder
- Check GetAssetBundlePath() returns correct relative path
- Ensure bundle was built for Windows Standalone platform

### Players Falling Through Floor

- Add collision meshes to ground geometry
- Ensure mesh colliders are enabled
- Check physics material settings
- Verify spawn points are above ground

### Multiplayer Issues

- Test with 2+ clients
- Verify all assets are in bundle (no scene-only references)
- Check network synchronization
- Ensure spawn points support enough players

## Distribution

### Packaging

Create a ZIP with:
```
MyMap/
├── MyMap.dll
├── mycourse.bundle
├── preview.png (optional)
└── README.txt
```

### Installation Instructions

Tell users to:
1. Extract ZIP to `Super Battle Golf/Mods/Maps/`
2. Launch game
3. Select your map in course menu

## Support

For questions and issues:
- GitHub: https://github.com/ssfdre38/sbgmodloader
- Discord: (TBD)
- Documentation: See ROADMAP.md for development plans

---

**Map SDK Version:** 0.1.0-beta  
**Compatible with:** Super Battle Golf v1.1.1+  
**Mod Loader:** v0.1.0-beta+
