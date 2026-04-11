# Super Battle Golf - Public API Reference

## Overview

Through Mono reflection inspection, we've discovered the **complete public API** of Super Battle Golf's game systems. This reference documents all callable methods, properties, and integration points available for mod development.

**This is NOT reverse engineering** - we're simply enumerating the public C# API that's already exposed by the game's managed assemblies. Every method listed here is publicly callable.

## Game Mode API

### MatchSetupRules Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 74 total

**Properties (get/set):**
- `CurrentPreset` - Get/set active rule preset

**Events:**
- `UpdateItemSpawnersLoc` - Event when item spawners update (add/remove)
- `RulesPopulated` - Event when rules are populated (add/remove)

**Methods - Configuration:**
- `IsCheatsEnabled()` - Check if cheats are active
- `Initialize()` - Initialize the rules system
- `UpdateTooltips()` - Update UI tooltips
- `DistanceUnitChanged()` - Handle distance unit change

**Methods - Item Management:**
- `GetPoolLocString()` - Get localized string for item pool
- `UpdateCurrentItemPool()` - **Update which items can spawn**
- `SpawnChanceUpdated()` - Handle spawn chance changes
- `UpdateTotalWeightForPool()` - Recalculate total spawn weight
- `ServerUpdateSpawnChanceValue()` - **Network: sync spawn chance changes**

**Methods - UI State:**
- `UpdateSliderGreyedOut()` - Update slider enabled/disabled state
- `UpdateDropdownGreyedOut()` - Update dropdown enabled/disabled state

**Mod Integration Points:**
```cpp
// Get current preset
MonoMethod* getCurrentPreset = mono_class_get_method_from_name(
    matchSetupRulesClass, "get_CurrentPreset", 0);

// Update item pool (for custom spawn rates)
MonoMethod* updateItemPool = mono_class_get_method_from_name(
    matchSetupRulesClass, "UpdateCurrentItemPool", 0);
mono_runtime_invoke(updateItemPool, instance, nullptr, nullptr);

// Network sync item changes
MonoMethod* serverUpdateSpawn = mono_class_get_method_from_name(
    matchSetupRulesClass, "ServerUpdateSpawnChanceValue", 0);
```

---

### MatchSettings Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 67 total

**Properties - Hole Overview Timing:**
- `HoleOverviewInitialBlankDuration` (get/set) - Blank screen before overview
- `HoleOverviewHoleNameDuration` (get/set) - Hole name display duration
- `HoleOverviewFinalBlankDuration` (get/set) - Blank screen after overview
- `HoleOverviewCameraSlowdownDuration` (get/set) - Camera slowdown time
- `HoleOverviewFlyOverToTeeCurve` (get/set) - Camera animation curve

**Properties - Match Timing:**
- `TeeOffCountdownDuration` (get/set) - **Countdown before tee-off**
- `MatchEndCountdownDuration` (get/set) - **Countdown at match end**
- `OvertimeDuration` (get/set) - **Overtime period length**
- `StartNextMatchDelay` (get/set) - Delay before next match
- `FinishCourseDelay` (get/set) - Delay before course ends

**Mod Integration Points:**
```cpp
// Modify overtime duration
MonoClass* settingsClass = MonoHelper::FindClass("GameAssembly", "", "MatchSettings");
MonoProperty* overtimeProp = mono_class_get_property_from_name(settingsClass, "OvertimeDuration");
MonoMethod* setter = mono_property_get_set_method(overtimeProp);

// Set to 30 seconds
float newDuration = 30.0f;
void* args[] = { &newDuration };
mono_runtime_invoke(setter, settingsInstance, args, nullptr);
```

---

### MatchSetupMenu Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 88 total

**Properties - Course Selection:**
- `CustomCourseData` (get/set) - **CRITICAL: Custom course injection point!**
- `RandomCourseData` (get/set) - Random course data
- `IsActive` (get) - Is menu currently active
- `ServerName` (get) - Current server name

**Methods - Lifecycle:**
- `Start()` - Unity Start lifecycle
- `OnDestroy()` - Unity OnDestroy lifecycle
- `OnInputDeviceChange()` - Input device changed

**Methods - Initialization:**
- `InitializeStatics()` - Initialize static data
- `InitializeCourses()` - **Initialize course list**
- `SetEnabled()` - Enable/disable menu

**Methods - Course Management:**
- `UpdateCourseTooltips()` - Update course tooltips
- `OnHoleOrderUpdate()` - Hole order changed
- `GetRandomMaxHolesSliderDefaultValue()` - Get default max holes
- `UpdateRandomMaxHolesSlider()` - Update slider value
- `SetCourse()` - **Set active course**
- `OnRandomEnabledChanged()` - Random mode toggled
- `GetCurrentCourseData()` - **Get currently selected course**

**Methods - Menu Navigation:**
- `OnMenuExit()` - Called when exiting menu

**Mod Integration Points:**
```cpp
// CRITICAL: Inject custom course
MonoClass* menuClass = MonoHelper::FindClass("GameAssembly", "", "MatchSetupMenu");
MonoProperty* customCourseProp = mono_class_get_property_from_name(menuClass, "CustomCourseData");
MonoMethod* setter = mono_property_get_set_method(customCourseProp);

// Set our custom course data
void* args[] = { customCourseObject };
mono_runtime_invoke(setter, menuInstance, args, nullptr);
```

---

### HoleData Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 20 total

**Properties - Metadata:**
- `LocalizedName` (get/set) - Hole name (localized)
- `Scene` (get/set) - **Unity scene reference**
- `Par` (get/set) - Par for this hole
- `Difficulty` (get/set) - Difficulty rating (1-5)
- `ScreenshotsThumbnail` (get/set) - Thumbnail image
- `MusicEvent` (get/set) - FMOD music event

**Properties - Organization:**
- `ParentCourse` (get/set) - Reference to parent course
- `ParentCourseIndex` (get/set) - Index within parent course
- `GlobalIndex` (get/set) - Global hole index

**Methods:**
- `RuntimeInitialize()` - Runtime initialization
- `.ctor()` - Constructor

**Mod Integration Points:**
```cpp
// Create custom hole data
MonoClass* holeDataClass = MonoHelper::FindClass("GameAssembly", "", "HoleData");
MonoObject* holeData = mono_object_new(MonoHelper::GetDomain(), holeDataClass);
mono_runtime_object_init(holeData);

// Set scene reference (from Addressables)
MonoProperty* sceneProp = mono_class_get_property_from_name(holeDataClass, "Scene");
MonoMethod* sceneSetter = mono_property_get_set_method(sceneProp);
void* args[] = { sceneReference };
mono_runtime_invoke(sceneSetter, holeData, args, nullptr);

// Set par
MonoProperty* parProp = mono_class_get_property_from_name(holeDataClass, "Par");
MonoMethod* parSetter = mono_property_get_set_method(parProp);
int par = 3;
void* parArgs[] = { &par };
mono_runtime_invoke(parSetter, holeData, parArgs, nullptr);
```

---

### GolfHole Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 46 total

**Properties:**
- `IsMainHole` (get) - Check if this is the main hole
- `Settings` (get) - Get hole-specific settings

**Methods - Lifecycle:**
- `Start()` - Unity Start
- `OnWillBeDestroyed()` - Before destruction
- `OnStartServer()` - Mirror: server started
- `OnStartClient()` - Mirror: client connected

**Methods - Gameplay (Server):**
- `ServerInformFellIn()` - Ball fell in hole
- `ServerSetAreAnyPlayersOnGreen()` - Track players on green
- `ServerSetAreAnyPlayersInGreenTrigger()` - Track green trigger
- `ServerUpdateIsFlagRaised()` - Update flag state
- `ServerOnBallScored()` - **Called when ball scores**

**Methods - Gameplay (Client):**
- `IsPointInGreenTrigger()` - Check if point is in green
- `MoveFlagRoutine()` - Coroutine for flag animation

**Methods - Audio/Visual:**
- `TriggerHoleScoreBlast()` - **Visual effect when scoring**
- `RpcPlayBallInHoleSound()` - Network: play scoring sound
- `PlayBallInHoleSoundInternal()` - Local sound playback
- `RpcPlayFallingInHoleSound()` - Network: falling sound
- `PlayFallingInHoleSoundInternal()` - Local falling sound
- `HideWorldspaceIcon()` - Hide hole icon
- `UpdateWorldspaceIcon()` - Update hole icon

**Mod Integration Points:**
```cpp
// Hook scoring to modify behavior
MonoMethod* onBallScored = mono_class_get_method_from_name(
    golfHoleClass, "ServerOnBallScored", -1); // -1 = any param count

// Custom scoring logic, point multipliers, etc.
```

---

## Item System API

### ItemSettings Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 470 total (!)

**This is the COMPLETE item/weapon framework.** With 470 methods, this class handles:
- Item spawning
- Item behavior
- Item effects
- Item networking
- Item visuals/audio

**Mod Integration:** Full documentation pending (too many methods to list here)

---

## Player API

### PlayerInfo Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 323 total

**Manages all player state and data.** Key areas:
- Player stats
- Inventory
- Cosmetics
- Network identity
- Match participation

### PlayerGolfer Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 228 total

**Player controller and movement.** Key areas:
- Golf swing mechanics
- Movement
- Ball interaction
- Physics

### PlayerCosmetics Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 75 total

**Character customization.** Key areas:
- Skin loading
- Model switching
- Cosmetic effects

---

## Network API

### BNetworkManager Class

**Namespace:** `(root)`  
**Assembly:** GameAssembly  
**Methods:** 148 total

**Multiplayer/lobby system.** Key areas:
- Lobby creation
- Player joining
- Network synchronization
- Steam integration

---

## Using This API

### Basic Pattern

```cpp
// 1. Find the class
MonoClass* klass = MonoHelper::FindClass("GameAssembly", "", "ClassName");

// 2. Find the method
MonoMethod* method = mono_class_get_method_from_name(klass, "MethodName", paramCount);

// 3. Get an instance (or use static method with nullptr)
MonoObject* instance = GetInstanceSomehow();

// 4. Call the method
void* args[] = { arg1, arg2 };
MonoObject* result = mono_runtime_invoke(method, instance, args, nullptr);
```

### Property Access

```cpp
// Get property
MonoProperty* prop = mono_class_get_property_from_name(klass, "PropertyName");

// Get getter/setter
MonoMethod* getter = mono_property_get_get_method(prop);
MonoMethod* setter = mono_property_get_set_method(prop);

// Read property
MonoObject* value = mono_runtime_invoke(getter, instance, nullptr, nullptr);

// Write property
void* args[] = { newValue };
mono_runtime_invoke(setter, instance, args, nullptr);
```

### Finding Instances

```cpp
// Option 1: Find via static property/method
MonoMethod* getInstance = mono_class_get_method_from_name(klass, "get_Instance", 0);
MonoObject* instance = mono_runtime_invoke(getInstance, nullptr, nullptr, nullptr);

// Option 2: Search Unity objects
MonoClass* objectClass = mono_class_from_name(mono_get_corlib(), "UnityEngine", "Object");
MonoMethod* findMethod = mono_class_get_method_from_name(objectClass, "FindObjectOfType", 1);
// ... call with type parameter

// Option 3: Hook a method and cache the 'this' pointer
```

---

## Mod Developer SDK

All of these APIs will be wrapped in a C++ SDK for mod developers:

```cpp
// Proposed SDK usage
ModSDK::GameMode::SetOvertimeDuration(30.0f);
ModSDK::GameMode::SetItemSpawnMultiplier(2.0f);
ModSDK::GameMode::RegisterCustomCourse(courseData);

ModSDK::Player::GetLocalPlayer();
ModSDK::Player::ModifyScore(playerId, points);

ModSDK::Network::SendCustomMessage("ModEvent", jsonData);
```

---

**Document Status:** Living document - API surface discovered via Mono reflection  
**Last Updated:** 2026-04-11  
**Total Classes Documented:** 10 core classes  
**Total Methods Mapped:** 1,000+ across all classes
