# API Reference

This document describes the C++ API for advanced mod development.

## Table of Contents

1. [MonoHelper](#monohelper) - Mono runtime integration
2. [ModManager](#modmanager) - Mod discovery and loading
3. [GameModeManager](#gamemodemanager) - Custom game modes
4. [CharacterManager](#charactermanager) - Custom cosmetics
5. [ItemManager](#itemmanager) - Custom items
6. [SceneHooks](#scenehooks) - Scene change callbacks

---

## MonoHelper

**Purpose:** Wrapper for Unity Mono embedding API.

**Location:** `ModLoaderCore/include/MonoHelper.h`

### Initialization

```cpp
bool MonoHelper::Initialize(HMODULE hMono)
```

Initialize the Mono helper with a handle to `mono-2.0-bdwgc.dll`.

**Parameters:**
- `hMono` - Module handle from `GetModuleHandleA("mono-2.0-bdwgc.dll")`

**Returns:** `true` if all function pointers loaded successfully

**Example:**
```cpp
HMODULE hMono = GetModuleHandleA("mono-2.0-bdwgc.dll");
if (!MonoHelper::Initialize(hMono)) {
    Logger::Error("Failed to initialize MonoHelper");
    return false;
}
```

---

### Domain & Assembly Functions

#### GetDomain()
```cpp
MonoDomain* MonoHelper::GetDomain()
```

Get the root Mono domain (the Unity runtime context).

**Returns:** Pointer to MonoDomain

---

#### GetImage()
```cpp
MonoImage* MonoHelper::GetImage(const char* assemblyName)
```

Get a loaded assembly image by name.

**Parameters:**
- `assemblyName` - Assembly name (e.g., "GameAssembly", "UnityEngine.CoreModule")

**Returns:** MonoImage* or nullptr if not found

**Example:**
```cpp
MonoImage* gameImage = MonoHelper::GetImage("GameAssembly");
MonoImage* coreImage = MonoHelper::GetImage("UnityEngine.CoreModule");
```

---

### Class Discovery

#### GetClassFromName()
```cpp
MonoClass* MonoHelper::GetClassFromName(MonoImage* image, const char* namespaceName, const char* className)
```

Find a class by namespace and name.

**Parameters:**
- `image` - Assembly image
- `namespaceName` - Namespace (empty string "" for global namespace)
- `className` - Class name

**Returns:** MonoClass* or nullptr if not found

**Example:**
```cpp
MonoImage* gameImage = MonoHelper::GetImage("GameAssembly");
MonoClass* courseDataClass = MonoHelper::GetClassFromName(gameImage, "", "CourseData");
```

---

#### EnumerateClasses()
```cpp
void MonoHelper::EnumerateClasses(MonoImage* image, std::function<void(MonoClass*)> callback)
```

Enumerate all classes in an assembly.

**Parameters:**
- `image` - Assembly image
- `callback` - Function called for each class

**Example:**
```cpp
MonoHelper::EnumerateClasses(gameImage, [](MonoClass* klass) {
    const char* className = MonoHelper::GetClassName(klass);
    Logger::Info("Found class: {}", className);
});
```

---

### Method Discovery

#### GetMethodFromName()
```cpp
MonoMethod* MonoHelper::GetMethodFromName(MonoClass* klass, const char* methodName, int paramCount)
```

Find a method by name and parameter count.

**Parameters:**
- `klass` - Class to search
- `methodName` - Method name
- `paramCount` - Number of parameters (-1 for any)

**Returns:** MonoMethod* or nullptr if not found

**Example:**
```cpp
MonoMethod* loadMethod = MonoHelper::GetMethodFromName(
    addressablesClass, 
    "LoadContentCatalogAsync", 
    2
);
```

---

#### EnumerateMethods()
```cpp
void MonoHelper::EnumerateMethods(MonoClass* klass, std::function<void(MonoMethod*)> callback)
```

Enumerate all methods in a class.

**Example:**
```cpp
MonoHelper::EnumerateMethods(courseDataClass, [](MonoMethod* method) {
    const char* name = MonoHelper::GetMethodName(method);
    int paramCount = MonoHelper::GetMethodParamCount(method);
    Logger::Info("Method: {} ({} params)", name, paramCount);
});
```

---

### Method Invocation

#### InvokeMethod()
```cpp
MonoObject* MonoHelper::InvokeMethod(MonoMethod* method, MonoObject* instance, void** params)
```

Invoke a Mono method with exception handling.

**Parameters:**
- `method` - Method to invoke
- `instance` - Object instance (nullptr for static methods)
- `params` - Array of parameter pointers

**Returns:** MonoObject* result or nullptr

**Example:**
```cpp
MonoString* pathStr = MonoHelper::CreateString("catalog.bin");
void* params[2] = { pathStr, nullptr };

MonoObject* result = MonoHelper::InvokeMethod(loadMethod, nullptr, params);
if (result) {
    Logger::Info("Method succeeded!");
}
```

---

### Object Creation

#### CreateInstance()
```cpp
MonoObject* MonoHelper::CreateInstance(MonoClass* klass)
```

Create a new instance of a class.

**Parameters:**
- `klass` - Class to instantiate

**Returns:** MonoObject* instance or nullptr

**Example:**
```cpp
MonoObject* courseData = MonoHelper::CreateInstance(courseDataClass);
```

---

### Property Access

#### GetProperty()
```cpp
MonoProperty* MonoHelper::GetProperty(MonoClass* klass, const char* propertyName)
```

Find a property by name.

**Example:**
```cpp
MonoProperty* customDataProp = MonoHelper::GetProperty(menuClass, "CustomCourseData");
```

---

#### SetPropertyValue()
```cpp
void MonoHelper::SetPropertyValue(MonoObject* obj, MonoProperty* prop, void* value)
```

Set a property value on an object.

**Example:**
```cpp
MonoHelper::SetPropertyValue(menuInstance, customDataProp, &courseDataInstance);
```

---

#### GetPropertyValue()
```cpp
MonoObject* MonoHelper::GetPropertyValue(MonoObject* obj, MonoProperty* prop)
```

Get a property value from an object.

---

### String Utilities

#### CreateString()
```cpp
MonoString* MonoHelper::CreateString(const char* str)
```

Create a managed string.

---

#### MonoStringToUTF8()
```cpp
std::string MonoHelper::MonoStringToUTF8(MonoString* monoStr)
```

Convert managed string to C++ string.

---

### Boxing/Unboxing

#### Box()
```cpp
MonoObject* MonoHelper::Box(MonoClass* klass, void* value)
```

Box a value type (int, float, etc.) into a MonoObject.

**Example:**
```cpp
float duration = 120.0f;
MonoClass* floatClass = MonoHelper::GetClassFromName(coreImage, "System", "Single");
MonoObject* boxedDuration = MonoHelper::Box(floatClass, &duration);
```

---

## ModManager

**Purpose:** Discover, load, and manage mods.

**Location:** `ModLoaderCore/include/ModManager.h`

### Initialization

```cpp
void ModManager::Initialize(const std::string& modsPath)
```

Initialize the mod manager with the mods directory path.

**Parameters:**
- `modsPath` - Path to Mods folder (e.g., `C:\Games\SuperBattleGolf\Mods`)

---

### Mod Discovery

```cpp
void ModManager::DiscoverMods()
```

Scan all category folders for mod.json files and parse metadata.

---

### Mod Loading

```cpp
void ModManager::LoadMods()
```

Load all discovered mods in dependency order.

---

## GameModeManager

**Purpose:** Load and manage custom game modes.

**Location:** `ModLoaderCore/include/GameModeManager.h`

### Initialization

```cpp
void GameModeManager::Initialize()
```

Find required Unity classes (CourseData, HoleData, MatchSetupMenu, etc.).

---

### Loading Game Modes

```cpp
void GameModeManager::LoadGameModes(const std::vector<ModInfo>& mods)
```

Load all game mode mods from the mod list.

**Parameters:**
- `mods` - List of mods (filtered to type="gamemode")

---

### Scene Callbacks

```cpp
void GameModeManager::OnSceneChanged(const std::string& sceneName)
```

Called when scene changes (registered with SceneHooks).

Injects custom game modes when entering MapSelection scene.

---

## CharacterManager

**Purpose:** Load and manage custom character cosmetics.

**Location:** `ModLoaderCore/include/CharacterManager.h`

### Initialization

```cpp
void CharacterManager::Initialize()
```

Find PlayerCosmetics, CosmeticsSwitcher, and related classes.

---

### Loading Characters

```cpp
void CharacterManager::LoadCharacterMods(const std::vector<ModInfo>& mods)
```

Load all character mods.

---

### API

```cpp
void CharacterManager::RegisterCosmetic(const std::string& id, const std::string& name, const std::string& type)
```

Register a custom cosmetic item.

**Parameters:**
- `id` - Unique cosmetic ID
- `name` - Display name
- `type` - Cosmetic type (skin, hat, outfit, etc.)

---

## ItemManager

**Purpose:** Load and manage custom items/weapons.

**Location:** `ModLoaderCore/include/ItemManager.h`

### Initialization

```cpp
void ItemManager::Initialize()
```

Find ItemSettings and item pool classes.

---

### Loading Items

```cpp
void ItemManager::LoadItemMods(const std::vector<ModInfo>& mods)
```

Load all item mods.

---

### API

```cpp
void ItemManager::RegisterItem(const std::string& id, const std::string& name, const std::string& type)
```

Register a custom item.

**Parameters:**
- `id` - Unique item ID
- `name` - Display name
- `type` - Item type (weapon, powerup, consumable, trap)

---

## SceneHooks

**Purpose:** Detect scene changes and notify content managers.

**Location:** `ModLoaderCore/include/SceneHooks.h`

### Initialization

```cpp
void SceneHooks::Initialize()
```

Find SceneManager and setup scene detection.

---

### Callbacks

```cpp
void SceneHooks::RegisterCallback(std::function<void(const std::string&)> callback)
```

Register a callback for scene changes.

**Example:**
```cpp
SceneHooks::RegisterCallback([](const std::string& sceneName) {
    if (sceneName == "MainMenu") {
        Logger::Info("Main menu loaded!");
    }
});
```

---

## Logger

**Purpose:** Thread-safe logging to file.

**Location:** `ModLoaderCore/include/Logger.h`

### Methods

```cpp
Logger::Info(const char* format, ...)
Logger::Error(const char* format, ...)
Logger::Debug(const char* format, ...)
```

**Example:**
```cpp
Logger::Info("Loading mod: {}", modName);
Logger::Error("Failed to load class: {}", className);
Logger::Debug("Method count: {}", methodCount);
```

---

## Complete Example: Custom Game Mode Injection

```cpp
#include "MonoHelper.h"
#include "Logger.h"

void InjectCustomGameMode() {
    // Get Unity assemblies
    MonoImage* gameImage = MonoHelper::GetImage("GameAssembly");
    MonoImage* coreImage = MonoHelper::GetImage("UnityEngine.CoreModule");
    
    // Find required classes
    MonoClass* courseDataClass = MonoHelper::GetClassFromName(gameImage, "", "CourseData");
    MonoClass* holeDataClass = MonoHelper::GetClassFromName(gameImage, "", "HoleData");
    MonoClass* menuClass = MonoHelper::GetClassFromName(gameImage, "", "MatchSetupMenu");
    
    // Create CourseData instance
    MonoObject* courseData = MonoHelper::CreateInstance(courseDataClass);
    
    // Create HoleData instances
    std::vector<MonoObject*> holes;
    for (int i = 0; i < 3; i++) {
        MonoObject* hole = MonoHelper::CreateInstance(holeDataClass);
        
        // Set hole properties
        MonoProperty* sceneProp = MonoHelper::GetProperty(holeDataClass, "Scene");
        MonoString* sceneStr = MonoHelper::CreateString("CourseSelectionDesert01");
        MonoHelper::SetPropertyValue(hole, sceneProp, &sceneStr);
        
        holes.push_back(hole);
    }
    
    // Set CourseData.Holes array
    MonoProperty* holesProp = MonoHelper::GetProperty(courseDataClass, "Holes");
    // TODO: Create MonoArray and set holes
    
    // Find MatchSetupMenu instance
    MonoObject* menuInstance = FindMatchSetupMenuInstance();
    
    // Set CustomCourseData property
    MonoProperty* customProp = MonoHelper::GetProperty(menuClass, "CustomCourseData");
    MonoHelper::SetPropertyValue(menuInstance, customProp, &courseData);
    
    Logger::Info("Custom game mode injected!");
}
```

---

## Error Handling

All API functions handle exceptions internally and log errors. Check return values:

```cpp
MonoClass* klass = MonoHelper::GetClassFromName(image, "MyNamespace", "MyClass");
if (!klass) {
    Logger::Error("Class not found!");
    return;
}
```

---

## Threading

**CRITICAL:** Mono API calls must be made from the main thread!

SceneHooks runs on a background thread but callbacks execute on the background thread. For Mono operations, use a deferred queue or hook Unity's Update loop.

---

## Performance

- **Cache MonoClass* pointers** - Class lookup is expensive
- **Cache MonoMethod* pointers** - Method lookup is expensive
- **Batch operations** - Don't invoke methods in tight loops
- **Use native callbacks** - Avoid managed → native → managed roundtrips

---

**See also:**
- [MODDING_GUIDE.md](MODDING_GUIDE.md) - User-facing mod creation guide
- [ARCHITECTURE.md](ARCHITECTURE.md) - System architecture details
