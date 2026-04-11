# Super Battle Golf - Maps Research

## Overview
Super Battle Golf uses **Unity Addressables** for asset management, which is a modern Unity system for loading/unloading content dynamically.

## Key Findings

### Unity Addressables Architecture
- **Location:** `Super Battle Golf_Data/StreamingAssets/aa/StandaloneWindows64/`
- **System:** Unity Addressables 2.8.1
- **Catalog:** `catalog.bin` (204 KB) - binary catalog of all addressable assets
- **Settings:** `settings.json` - addressables configuration

### Asset Bundles Structure

| Bundle | Size | Likely Contents |
|--------|------|----------------|
| `managers_assets_all_...bundle` | 51.18 MB | **Main target** - Game managers, courses, levels, prefabs |
| `ui_assets_all_...bundle` | 53.91 MB | UI elements, menus, HUD |
| `fonts_assets_all_...bundle` | 47.11 MB | Font data |
| `defaultlocalgroup_assets_all_...bundle` | 21.95 MB | Default local content |
| `vfx_assets_all_...bundle` | 10.17 MB | Visual effects |
| `cosmeticscharacter_assets_all_...bundle` | 9.27 MB | Character cosmetics |

### Unity Scene System
- Game uses `Eflatun.SceneReference` package for scene management
- Scenes are loaded via GUIDs, not hardcoded paths
- Scene initialization happens via `GameManager::InitializeBeforeSceneLoad` and `GameManager::InitializeAfterSceneLoad`

### Asset References Found in Catalog
From scanning `catalog.bin`, discovered asset references including:
- **Cosmetics:** Golf clubs (Axe, Baseball bat, Bee, Hammer, etc.), Golf balls (Billiard, Disco, Eyeball, etc.)
- **VFX:** Explosions, water impacts, checkpoints, player spawns, orbital laser, mines, etc.
- **Game Objects:** Coffee dispensers, electromagnets, freeze bombs, golf carts, jump pads, rockets
- **Shaders:** Toon shader, droplet shader, speck shader

## What This Means for Custom Maps

### Good News ✅
1. **Addressables are moddable** - We can add our own addressables catalog alongside the game's
2. **No hardcoded paths** - Game loads assets by keys/labels, not file paths
3. **Asset bundles are standard Unity format** - We can create our own
4. **Scene references use GUIDs** - We can register custom scenes

### Challenges ⚠️
1. **Binary catalog format** - Need to understand Unity's catalog serialization
2. **Scene registration** - Must integrate with Eflatun.SceneReference system
3. **Asset dependencies** - Custom maps need correct references to game materials/shaders
4. **Network sync** - Multiplayer maps need to load on all clients

## Next Steps

### Phase 3A: Extract & Analyze (Current)
- [ ] Use AssetRipper to extract `managers_assets_all` bundle
- [ ] Identify map/course prefab structure
- [ ] Document required components for a valid course
- [ ] Find scene references and loading mechanism

### Phase 3B: Create Test Map
- [ ] Build simple test map in Unity with ProBuilder
- [ ] Export as addressable asset bundle
- [ ] Create custom addressables catalog
- [ ] Hook game to load additional catalogs at startup

### Phase 3C: Map Loading API
- [ ] Add IL2CPP hooks for scene loading (needs Phase 2 RVAs)
- [ ] Create mod API: `IModModule::RegisterCustomMap(string name, string bundlePath, string sceneAddress)`
- [ ] Handle map discovery from `Mods/Maps/` folder
- [ ] Inject custom maps into game's map selection UI

## Tools Needed

### Extraction & Analysis
- **AssetRipper** ✅ Installed at `C:\Users\admin\AssetRipper\`
  - Extracts Unity asset bundles to readable formats
  - Can export scenes, prefabs, materials, textures

### Unity Development
- **Unity Hub** - Install Unity 2023.x (match game's version)
- **Addressables Package** - Unity's addressables system
- **ProBuilder** - For map building (game uses this)

### Debugging
- **Unity AssetBundle Browser** - View bundle contents
- **dnSpy** - For analyzing GameAssembly.dll scene loading code

## Research Questions

1. **How does the game populate the map selection menu?**
   - Look for methods reading addressables catalog
   - Find UI manager that displays available courses

2. **What components are required for a valid course?**
   - Spawn points
   - Holes/goals
   - Collision geometry  
   - Bounds/out-of-bounds areas
   - Game rules/modifiers?

3. **How are networked maps synchronized?**
   - Does host send map data to clients?
   - Or do all clients load same addressable key?
   - Mirror networking implications

4. **Can we inject addressables catalogs at runtime?**
   - Unity's `Addressables.LoadContentCatalogAsync()` API
   - Need to call from C++ via IL2CPP

## Development Strategy

### Option A: Addressables Injection (Preferred)
**Pros:**
- Clean integration with game's asset system
- Proper dependency management
- Network sync automatically handled
- Maps can use game's materials/shaders

**Cons:**
- Complex - requires Unity project setup
- Need to match game's Unity version
- Learning curve for Unity Addressables

**Implementation:**
1. Create Unity project with same version as game
2. Import game's shared assets (materials, shaders)
3. Build custom maps as addressable assets
4. Export asset bundles
5. Create catalog pointing to custom bundles
6. Hook game to load additional catalogs at startup

### Option B: Direct Scene Loading (Simpler)
**Pros:**
- Don't need Unity project
- Maps can be standalone Unity scenes
- Easier for modders

**Cons:**
- Missing asset dependencies
- No integration with game's asset management
- Network sync challenges
- Maps might not have correct materials/shaders

**Implementation:**
1. Create standalone Unity scenes
2. Export as asset bundles
3. Load directly via `SceneManager.LoadSceneAsync()`
4. Handle missing dependencies

## Recommendation

Start with **Option A (Addressables Injection)** because:
- It's how the game is designed to work
- Better long-term maintainability
- Maps will look/behave correctly
- Community can build sophisticated custom content

The initial setup is more complex, but the payoff is a professional-grade modding system.

## Action Items

**Immediate (Tonight):**
- [x] Download and install AssetRipper
- [ ] Extract managers bundle and document structure
- [ ] Find example course prefab structure
- [ ] Screenshot key components

**Short Term (This Week):**
- [ ] Install Unity Hub and appropriate Unity version
- [ ] Set up test Unity project with Addressables
- [ ] Create simple "Hello World" test map
- [ ] Build and export as addressable bundle

**Medium Term (Next 2 Weeks):**
- [ ] Hook IL2CPP to inject custom catalogs
- [ ] Test loading custom map in-game
- [ ] Create ModAPI functions for map registration
- [ ] Document map creation workflow

**Long Term (Phase 3):**
- [ ] Build map maker tool (Unity editor extension?)
- [ ] Create sample maps
- [ ] Write map creation tutorials
- [ ] Establish map distribution system

---

**Updated:** 2026-04-11  
**Status:** Research phase - discovered Addressables system  
**Blocker:** Need to extract and analyze managers bundle to understand map structure
