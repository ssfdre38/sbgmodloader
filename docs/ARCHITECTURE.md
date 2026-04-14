# Architecture Documentation

This document describes the technical architecture of the Super Battle Golf Mod Loader.

## Table of Contents

1. [System Overview](#system-overview)
2. [Component Architecture](#component-architecture)
3. [Initialization Flow](#initialization-flow)
4. [Mod Loading Pipeline](#mod-loading-pipeline)
5. [Scene Change Detection](#scene-change-detection)
6. [Content Injection](#content-injection)
7. [Threading Model](#threading-model)
8. [Memory Management](#memory-management)

---

## System Overview

The mod loader is a **native C++ DLL** injected into Super Battle Golf at startup. It interfaces with Unity's Mono runtime to:

- Discover and load mods from the filesystem
- Hook into Unity's scene management
- Inject custom content (maps, game modes, characters, items)
- Extend Unity's Addressables system

### Key Design Principles

1. **Native First** - C++ with direct Mono API access (no managed code injection)
2. **Non-Invasive** - No IL patching or game code modification
3. **Survives Updates** - Uses Unity's public APIs, not internal structures
4. **Minimal Overhead** - Lazy initialization, cached lookups, background threads
5. **Safe Defaults** - Graceful degradation on errors, never crashes the game

---

## Component Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                     DLL Main Entry Point                     │
│                      (dllmain.cpp)                           │
└──────────────────┬──────────────────────────────────────────┘
                   │
                   ├─→ MonoHelper (Mono Runtime Wrapper)
                   │   ├─ GetDomain()
                   │   ├─ GetImage()
                   │   ├─ GetClassFromName()
                   │   ├─ InvokeMethod()
                   │   └─ CreateInstance()
                   │
                   ├─→ ModManager (Mod Discovery & Loading)
                   │   ├─ DiscoverMods()
                   │   ├─ ParseManifest()
                   │   ├─ ResolveDependencies()
                   │   └─ LoadMods()
                   │
                   ├─→ SceneHooks (Scene Change Detection)
                   │   ├─ Background polling thread
                   │   ├─ GetActiveSceneName()
                   │   └─ NotifyCallbacks()
                   │
                   ├─→ GameModeManager (Custom Game Modes)
                   │   ├─ LoadGameModes()
                   │   ├─ ParseGameModeConfig()
                   │   ├─ BuildCourseData()
                   │   └─ InjectCustomGameMode()
                   │
                   ├─→ CharacterManager (Custom Cosmetics)
                   │   ├─ LoadCharacterMods()
                   │   ├─ RegisterCosmetic()
                   │   └─ HookCosmeticsSystem()
                   │
                   └─→ ItemManager (Custom Items)
                       ├─ LoadItemMods()
                       ├─ RegisterItem()
                       └─ HookItemPool()
```

---

## Initialization Flow

### 1. DLL Injection (DLL_PROCESS_ATTACH)

```cpp
// dllmain.cpp:DllMain()
BOOL APIENTRY DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        CreateThread(nullptr, 0, InitializeModLoader, hModule, 0, nullptr);
    }
}
```

**Why a separate thread?**
- DllMain has strict restrictions (can't wait on other threads)
- Game may not be fully initialized yet
- Avoids deadlocks with loader lock

---

### 2. Delayed Initialization

```cpp
// dllmain.cpp:InitializeModLoader()
DWORD WINAPI InitializeModLoader(LPVOID lpParam) {
    Sleep(5000);  // Wait for game startup
    
    // 1. Initialize logging
    Logger::Initialize();
    
    // 2. Find Mono runtime
    HMODULE hMono = GetModuleHandleA("mono-2.0-bdwgc.dll");
    
    // 3. Initialize MonoHelper
    MonoHelper::Initialize(hMono);
    
    // 4. Discover mods
    ModManager::Initialize("C:\\..\\Mods");
    ModManager::DiscoverMods();
    
    // 5. Initialize content managers
    GameModeManager::Initialize();
    CharacterManager::Initialize();
    ItemManager::Initialize();
    
    // 6. Start scene detection
    SceneHooks::Initialize();
    
    // 7. Load mods
    ModManager::LoadMods();
}
```

**Why 5 second delay?**
- Unity runtime must be fully initialized
- Mono domain must be created
- Assemblies must be loaded
- Too early = crash, too late = miss initialization hooks

---

### 3. Component Initialization Order

**Critical ordering:**
1. **Logger first** - All other components need logging
2. **MonoHelper second** - Everything depends on Mono access
3. **Managers third** - Find and cache Unity classes
4. **SceneHooks fourth** - Start background detection
5. **ModManager last** - Load mods after everything is ready

---

## Mod Loading Pipeline

### Phase 1: Discovery

```
Mods/
├── Maps/
│   └── CustomTestMap/
│       └── mod.json  ← Found
├── GameModes/
│   └── TestMode/
│       └── mod.json  ← Found
└── Items/
    └── MegaWeapons/
        └── mod.json  ← Found
```

**Process:**
1. Scan 8 category folders (Maps, GameModes, Characters, Items, etc.)
2. Find all `mod.json` files
3. Parse JSON into `ModInfo` structs
4. Validate required fields (id, name, version, type)

---

### Phase 2: Dependency Resolution

```cpp
std::vector<ModInfo> ModManager::ResolveDependencies(std::vector<ModInfo>& mods) {
    // Topological sort
    // Ensures dependencies load before dependents
    return sortedMods;
}
```

**Example:**
```
Mod A (depends on: B, C)
Mod B (depends on: C)
Mod C (no dependencies)

Load order: C → B → A
```

---

### Phase 3: Loading by Type

```cpp
void ModManager::LoadMods() {
    auto maps = FilterByType(mods, "map");
    auto gamemodes = FilterByType(mods, "gamemode");
    auto characters = FilterByType(mods, "character");
    auto items = FilterByType(mods, "item");
    
    LoadMaps(maps);
    GameModeManager::LoadGameModes(gamemodes);
    CharacterManager::LoadCharacterMods(characters);
    ItemManager::LoadItemMods(items);
}
```

---

### Phase 4: Content-Type Specific Loading

#### Maps (Addressables)
```cpp
void LoadMap(const ModInfo& mod) {
    std::string catalogPath = mod.path + "/catalog.bin";
    
    MonoMethod* loadMethod = GetMethod("LoadContentCatalogAsync");
    MonoString* pathStr = CreateString(catalogPath.c_str());
    void* params[2] = { pathStr, nullptr };
    
    InvokeMethod(loadMethod, nullptr, params);
}
```

#### Game Modes (JSON → Mono Objects)
```cpp
void GameModeManager::LoadGameMode(const ModInfo& mod) {
    // Parse JSON
    json config = ParseJSON(mod.path + "/mod.json");
    
    // Create CourseData object
    MonoObject* courseData = CreateInstance(courseDataClass);
    
    // Build HoleData array
    for (auto& holeId : config["gamemode"]["holes"]) {
        MonoObject* hole = CreateHoleData(holeId);
        holes.push_back(hole);
    }
    
    // Store for later injection
    customGameModes[mod.id] = courseData;
}
```

---

## Scene Change Detection

### Background Polling Thread

```cpp
void SceneHooks::Update() {
    while (isRunning) {
        __try {
            std::string currentScene = GetActiveSceneName();
            
            if (currentScene != lastScene) {
                NotifyCallbacks(currentScene);
                lastScene = currentScene;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            // Ignore exceptions
        }
        
        Sleep(500);  // Poll every 500ms
    }
}
```

**Why polling instead of hooks?**
- Unity's SceneManager events are C# delegates (hard to hook from C++)
- Polling is simpler and more reliable
- 500ms interval is fast enough for UX

**SEH Exception Handling:**
- Mono API calls from background threads can throw Windows SEH exceptions
- `__try/__except` prevents crashes
- Better to miss a scene change than crash the game

---

### Scene-Based Content Injection

```cpp
void GameModeManager::OnSceneChanged(const std::string& sceneName) {
    if (sceneName == "MapSelection") {
        InjectCustomGameModes();
    }
}
```

**Key scenes:**
- `MainMenu` - UI modifications, version display
- `MapSelection` - Inject custom maps and game modes
- `CharacterSelection` - Inject custom cosmetics
- `Gameplay` - Inject custom items into spawn pools

---

## Content Injection

### Example: Game Mode Injection

```cpp
void GameModeManager::InjectCustomGameMode(MonoObject* courseData) {
    // Find MatchSetupMenu instance
    MonoClass* menuClass = GetClassFromName("MatchSetupMenu");
    MonoObject* menuInstance = FindObjectOfType(menuClass);
    
    // Get CustomCourseData property
    MonoProperty* prop = GetProperty(menuClass, "CustomCourseData");
    MonoMethod* setter = GetPropertySetter(prop);
    
    // Invoke setter
    void* params[1] = { courseData };
    InvokeMethod(setter, menuInstance, params);
    
    Logger::Info("Injected custom game mode!");
}
```

**Injection Points:**
- `MatchSetupMenu.CustomCourseData` - Custom game modes
- `PlayerCosmetics.LoadedCosmetics` - Custom skins
- `ItemSettings.ItemPool` - Custom weapons
- `Addressables.Catalogs` - Custom asset bundles

---

## Threading Model

### Threads

1. **Main Thread** (Unity)
   - Game logic, rendering, physics
   - **All Mono API calls should happen here**
   
2. **Initialization Thread** (Mod Loader)
   - Created in DllMain
   - Initializes components
   - Terminates after loading mods
   
3. **Scene Detection Thread** (SceneHooks)
   - Polls GetActiveSceneName() every 500ms
   - Runs entire game lifetime
   - **Uses SEH protection** - can throw exceptions

### Thread Safety

**Mono is NOT thread-safe!**
- Mono methods should only be called from the main thread
- SceneHooks thread uses SEH protection
- Callbacks from SceneHooks execute on background thread (dangerous!)

**Current Limitation:**
Scene callbacks cannot directly invoke Mono methods. Solutions:
1. Use a deferred queue (callbacks add tasks, main thread processes)
2. Hook Unity's Update loop
3. Use Mono's `mono_thread_attach()` (untested)

---

## Memory Management

### Mono Objects (GC Managed)

```cpp
MonoObject* obj = CreateInstance(klass);
// obj is managed by Mono GC
// DO NOT delete or free!
```

**Lifetime:**
- Created with `mono_object_new()`
- Managed by Mono's garbage collector
- Will be collected when no references exist
- **Never manually free Mono objects**

### Strings

```cpp
MonoString* str = CreateString("Hello");
// Managed by Mono GC
```

### Native Memory

```cpp
std::string path = "...";  // C++ heap
std::vector<ModInfo> mods;  // C++ heap
// Clean up with destructors
```

### Handles & Pinning

**Not currently used**, but for reference:
```cpp
uint32_t handle = MonoHelper::GCHandleNew(obj, true);  // Pin
// obj won't be collected or moved
MonoHelper::GCHandleFree(handle);  // Unpin
```

---

## Error Handling

### Mono Exceptions

```cpp
MonoObject* exc = nullptr;
MonoObject* result = mono_runtime_invoke(method, obj, params, &exc);

if (exc) {
    MonoString* msg = mono_object_to_string(exc, nullptr);
    Logger::Error("Exception: {}", MonoStringToUTF8(msg));
}
```

**MonoHelper::InvokeMethod() handles this automatically.**

---

### Windows SEH Exceptions

```cpp
__try {
    // Code that might throw SEH exception
    MonoObject* scene = GetActiveScene();
}
__except (EXCEPTION_EXECUTE_HANDLER) {
    Logger::Error("SEH exception caught");
}
```

**Used in:**
- SceneHooks background thread
- Any call that returns structs (not objects)

---

### Graceful Degradation

**Philosophy:** Never crash the game.

```cpp
MonoClass* klass = GetClassFromName(...);
if (!klass) {
    Logger::Error("Class not found - feature disabled");
    return;  // Continue without feature
}
```

**Examples:**
- Scene detection fails → UI injection still works
- Game mode injection fails → Game still playable
- Custom cosmetics fail → Base game cosmetics work

---

## Performance Considerations

### Caching

```cpp
// BAD: Lookup every frame
for (int i = 0; i < 1000; i++) {
    MonoClass* klass = GetClassFromName(...);  // Slow!
}

// GOOD: Cache once
static MonoClass* klass = GetClassFromName(...);
for (int i = 0; i < 1000; i++) {
    // Use cached klass
}
```

**Cached at initialization:**
- MonoClass* pointers
- MonoMethod* pointers
- MonoImage* pointers

---

### Lazy Initialization

```cpp
MonoClass* GetCourseDataClass() {
    static MonoClass* klass = nullptr;
    if (!klass) {
        klass = GetClassFromName(...);
    }
    return klass;
}
```

Only lookup when first needed.

---

### Minimal Polling

Scene detection polls every **500ms**, not every frame.
- Frame rate: 60 FPS = 16ms per frame
- Polling: 500ms = 30 frames between polls
- Overhead: negligible

---

## Security & Stability

### No IL Patching

BepInEx uses **Harmony** to patch IL bytecode at runtime. We don't.

**Advantages:**
- No risk of breaking game logic
- Survives game updates
- No compatibility issues with anti-cheat

**Tradeoff:**
- Can't modify existing game behavior
- Can only extend via public APIs

---

### Manifest Validation

```cpp
bool ValidateManifest(const ModInfo& mod) {
    if (mod.id.empty()) return false;
    if (mod.name.empty()) return false;
    if (mod.version.empty()) return false;
    if (mod.type.empty()) return false;
    return true;
}
```

Prevents malformed mods from loading.

---

### Exception Safety

**All public APIs catch exceptions:**
```cpp
void PublicAPI() {
    try {
        // Implementation
    }
    catch (const std::exception& e) {
        Logger::Error("Exception: {}", e.what());
    }
}
```

---

## Debugging Tips

### Enable Detailed Logging

```cpp
Logger::SetLevel(LogLevel::Debug);
```

### Check Log File

```
%APPDATA%\Roaming\sbg-mod-loader\mod-loader.log
```

### Common Issues

| Symptom | Cause | Solution |
|---------|-------|----------|
| DLL not loading | Missing dependencies | Check detours.lib |
| Mono functions fail | Too early | Increase init delay |
| Scene detection crashes | SEH exception | Already protected |
| Content not appearing | Wrong scene | Check scene name |

---

## Future Improvements

1. **Main Thread Execution** - Move Mono calls from background thread to Unity Update hook
2. **GC Handle Management** - Pin objects to prevent GC collection during use
3. **Hot Reload** - Reload mods without restarting game
4. **Mod Conflicts** - Detect and warn about incompatible mods
5. **Performance Profiling** - Measure overhead of mod system

---

**See also:**
- [API_REFERENCE.md](API_REFERENCE.md) - C++ API documentation
- [MODDING_GUIDE.md](MODDING_GUIDE.md) - User-facing guide
