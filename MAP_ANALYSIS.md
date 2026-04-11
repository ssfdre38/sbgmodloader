# Super Battle Golf - Map Structure Analysis

## 🎯 Key Findings

### Scenes Extracted
**Location:** `D:\sbg-assets\ExportedProject\Assets\Scenes\Holes\`

**Total Maps:** 46 golf courses

**Map Names:**
- Atoll (246.02 MB)
- Big Rock (207.34 MB)
- Blast Off (256.89 MB)
- Bullseye (238.36 MB)
- Catwalk (244.69 MB)
- Chasm (205.7 MB)
- Cove (256.14 MB)
- Donut (256.13 MB)
- Downhill (258.21 MB)
- Gauntlet (239.88 MB)
- Hidden Lagoon (251.3 MB)
- Hilltops (253.87 MB)
- Jungle (253.43 MB)
- Lone Island (248.37 MB)
- Long Beach (252.48 MB)
- Oasis (206.96 MB)
- Overgrown (264.35 MB)
- Overlook (260.57 MB)
- Patches (211.72 MB)
- Rolling Hills (253.63 MB)
- Roundabout (89.69 MB)
- Sand Traps (202.83 MB)
- Sandbanks (244.11 MB)
- Seaside Cliff (243.03 MB)
- Serpent Trail (206.95 MB)
- Shallows (244.03 MB)
- Showdown (207.59 MB)
- Snow 1 (206.59 MB)
- Snow 2 (208.37 MB)
- Snow 3 (203.34 MB)
- Snow 4 (204.59 MB)
- Snow 5 (203.64 MB)
- Snow 6 (204.02 MB)
- Snow 7 (204.06 MB)
- Snow 8 (204.8 MB)
- Snow 9 (205.13 MB)
- SNOW TEST (202.93 MB)
- Spiral (73.6 MB)
- Terraces (247.26 MB)
- Treasure Island (246.61 MB)
- Twin Beach (242.85 MB)
- Twin Path (244.89 MB)
- Underpass (205.19 MB)
- Upward (254.68 MB)
- Vertigo (207.42 MB)
- Woodland Bay (86.57 MB)


### Scene File Format
- Unity YAML format (.unity files)
- Contains references to assets by GUID
- Each scene is 73-264 MB

### Key Components Found in Scenes
Based on analysis of Spiral.unity:

**Rendering & Environment:**
- RenderSettings (fog, skybox, lighting)
- LightmapSettings (baked lighting data)
- NavMeshSettings (AI pathfinding)

**Gameplay Objects:**
- Item spawners
- Mobility spawners
- Player spawn points
- Hole/goal objects
- Bounds/out-of-bounds markers

**UI Elements:**
- Hole info display
- Player info panels
- Score tracking
- Minimap/overview camera

### Asset Structure

**Main Folders:**
```
D:\sbg-assets\ExportedProject\Assets\
├── Scenes\
│   ├── Holes\ (46 courses)
│   ├── Main menu.unity
│   └── Driving range.unity
├── Prefabs\
│   ├── Cosmetics\
│   ├── Managers\
│   ├── UI\
│   └── VFX\
├── Materials\
├── Meshes\
├── Textures\
└── Scripts (MonoBehaviour)\
```

**Critical Prefabs:**
- Game manager.prefab - Core game controller
- Dev console.prefab - Debug tools

## 🎮 How Maps Work

### Loading System
Maps use Unity's scene system with:
1. Scene GUID references (from Eflatun.SceneReference)
2. Addressables for dynamic loading
3. Asset bundles for packaging

### Required Components (Estimated)
Based on object names found:
- **Course Manager** - Controls game rules
- **Spawn Points** - Where players start
- **Goal/Hole** - Win condition
- **Bounds System** - Out-of-bounds detection
- **Item Spawners** - Power-ups/items
- **Lighting** - Baked lightmaps
- **Collision Mesh** - Ground/walls
- **Visual Mesh** - 3D models
- **Materials/Textures** - Appearance

## 📋 SDK/GDK Requirements

### For Custom Map Support

**Phase 1: Asset Extraction (✅ DONE)**
- Extracted all 46 original courses
- Identified scene structure
- Found prefab dependencies

**Phase 2: Unity Project Setup**
Need to:
1. Install Unity (same version as game)
2. Import extracted assets as reference
3. Create template project for modders
4. Document required components

**Phase 3: Mod Loader Integration**
Implement in ModLoaderCore:
```cpp
// Map Loading API
class IMapModule {
    virtual const char* GetMapName() = 0;
    virtual const char* GetMapDescription() = 0;
    virtual const char* GetAssetBundlePath() = 0;
    virtual const char* GetSceneAddress() = 0; // Addressables key
};
```

Hook IL2CPP to:
- Inject custom addressables catalogs
- Register custom maps with game
- Add to map selection UI

**Phase 4: Map Maker Tool**
Unity Editor extension:
- Template scene with required objects
- Component validation
- Asset bundle build automation
- Testing tools

## 🚧 Blockers

**Current Blockers:**
1. ❌ Don't have Unity version used by game
2. ❌ Can't build asset bundles without Unity
3. ❌ Don't know exact script GUIDs
4. ❌ Missing IL2CPP hooks (need Phase 2 RVAs)

**What We CAN Do Now:**
1. ✅ Study existing map structure
2. ✅ Document component requirements
3. ✅ Plan SDK architecture
4. ✅ Create map loading API design

## 🎯 Next Steps

**Immediate:**
1. Find game's Unity version
2. Install Unity Hub + matching version
3. Create test Unity project
4. Import one course as reference

**Short Term:**
1. Build simple test map
2. Export as asset bundle
3. Test loading via mod loader
4. Document process

**Long Term:**
1. Create map maker template
2. Write modding guide
3. Build example custom maps
4. Release SDK v1.0

## 💡 Key Insights

**Good News:**
- All maps successfully extracted ✅
- Scene format is readable YAML ✅
- Game uses standard Unity systems ✅
- No obfuscation or encryption ✅

**Challenges:**
- Maps are HUGE (200+ MB each)
- Complex component dependencies
- Need exact Unity version
- Requires IL2CPP hooking for injection

**Recommendation:**
Focus on Unity project setup next. We have all the data we need, now we need the tools to work with it.

---
**Generated:** 2026-04-10 22:11:58
**Analyst:** AI + Daniel 🍺
