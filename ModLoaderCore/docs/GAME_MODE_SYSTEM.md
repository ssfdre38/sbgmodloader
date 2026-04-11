# Game Mode System Analysis

## Overview
Super Battle Golf's game mode system is controlled by several key classes that handle match setup, rules, and gameplay flow. Through deep inspection using Mono reflection, we've mapped out the complete architecture.

## Core Classes (Fully Inspected)

### MatchSetupRules (74 methods) ✅
**Purpose:** Manages game rules and presets for match configuration

**Key Methods Discovered:**
- `get_CurrentPreset` - Gets the active rule preset
- `IsCheatsEnabled` - Detects if cheats are active
- `Initialize` - Setup/initialization method
- `add_UpdateItemSpawnersLoc` / `remove_UpdateItemSpawnersLoc` - Item spawner events
- `add_RulesPopulated` / `remove_RulesPopulated` - Rules configuration events
- `GetPoolLocString` - Gets localized string for item pools
- `UpdateTooltips` - Updates UI tooltips for rules
- `DistanceUnitChanged` - Handles distance unit switching
- `UpdateCurrentItemPool` - **Controls which items spawn**
- `SpawnChanceUpdated` - Called when spawn chances change
- `UpdateSliderGreyedOut` / `UpdateDropdownGreyedOut` - UI state management
- `UpdateTotalWeightForPool` - Calculates total spawn weight
- `ServerUpdateSpawnChanceValue` - **Network sync for item spawn chances**

**What This Controls:**
- Rule presets (Classic, Battle Royale, etc.)
- Item spawner configuration and spawn rates
- Rule validation and population
- Network synchronization of rule changes

### MatchSettings (67 methods) ✅
**Purpose:** Contains all match configuration parameters and timing

**Key Methods Discovered:**
- `get/set_HoleOverviewInitialBlankDuration` - Blank screen before hole overview
- `get/set_HoleOverviewHoleNameDuration` - How long hole name displays
- `get/set_HoleOverviewFinalBlankDuration` - Blank screen after hole overview
- `get/set_HoleOverviewCameraSlowdownDuration` - Camera slowdown timing
- `get/set_HoleOverviewFlyOverToTeeCurve` - Camera animation curve
- `get/set_TeeOffCountdownDuration` - **Countdown before tee-off**
- `get/set_MatchEndCountdownDuration` - **Countdown at match end**
- `get/set_OvertimeDuration` - **Overtime period length (Battle Royale!)**
- `get/set_StartNextMatchDelay` - Delay before next match starts
- `get/set_FinishCourseDelay` - Delay before course ends

**What This Controls:**
- All timing parameters for match flow
- Camera animation settings
- Countdown durations
- Overtime support (important for Battle Royale mode!)

### MatchState (enum) ✅
**Purpose:** Represents current state of the match

**Status:** 0 methods (pure enum, no methods)

**Possible States:** (Inferred from usage)
- PreMatch
- InProgress
- HoleComplete
- MatchEnd
- Overtime (based on OvertimeDuration setting)

### Rule (enum) ❌
**Status:** Not found as standalone class (likely nested enum inside MatchSetupRules)

### RuleCategory (enum) ❌
**Status:** Not found as standalone class (likely nested enum inside MatchSetupRules)

### Preset (enum) ❌
**Status:** Not found as standalone class (likely nested enum inside MatchSetupRules)

**Note:** These enums are likely nested types within MatchSetupRules. To access them, we need to inspect the nested types of MatchSetupRules.

## Match Setup & UI Classes

### MatchSetupMenu (88 methods) ✅
**Purpose:** UI for configuring matches before they start

**Key Methods Discovered:**
- `get/set_CustomCourseData` - **CRITICAL: Custom course selection!**
- `get/set_RandomCourseData` - Random course generation
- `get_IsActive` - Is menu currently active
- `get_ServerName` - Gets the server name
- `OnDestroy` / `Start` - Unity lifecycle
- `OnInputDeviceChange` - Input handling
- `InitializeStatics` - Static initialization
- `SetEnabled` - Enable/disable menu
- `OnMenuExit` - Called when exiting menu
- `UpdateCourseTooltips` - Updates course tooltips
- `InitializeCourses` - **Initializes course list**
- `OnHoleOrderUpdate` - Called when hole order changes
- `GetRandomMaxHolesSliderDefaultValue` - Default value for random mode
- `UpdateRandomMaxHolesSlider` - Updates random mode slider
- `SetCourse` - **Sets the active course**
- `OnRandomEnabledChanged` - Random mode toggle
- `GetCurrentCourseData` - **Gets currently selected course**

**What This Controls:**
- Course selection (normal and custom)
- Random course generation
- UI state and tooltips
- Server name display

**CRITICAL DISCOVERY:** `CustomCourseData` property is how custom courses are injected! We can hook this to add our own game modes.

### MatchEndCountdown (27 methods)
**Purpose:** Handles countdown and transition at match end

**Key Methods:**
- `get_DisplayedTime` - Time shown on countdown
- `Awake` - Unity lifecycle
- `Show` - Shows countdown UI

### NextMatchCountdown (28 methods)
**Purpose:** Handles countdown between matches in a series

**Key Methods:**
- `get_NextMatchCountdownMessage` - Message for next match
- `get_CourseEndedCountdownMessage` - Message when course ends
- `Awake` - Unity lifecycle

## Gameplay Classes

### GolfHole (46 methods) ✅
**Purpose:** Represents a single golf hole in the course

**Key Methods Discovered:**
- `get_IsMainHole` - Checks if this is the primary hole
- `get_Settings` - Gets hole-specific settings
- `TriggerHoleScoreBlast` - Visual effect when scoring
- `Start` / `OnWillBeDestroyed` - Unity lifecycle
- `OnStartServer` / `OnStartClient` - Mirror networking
- `ServerInformFellIn` - Server: ball fell in hole
- `ServerSetAreAnyPlayersOnGreen` - Server: tracks players on green
- `ServerSetAreAnyPlayersInGreenTrigger` - Server: tracks green trigger
- `ServerUpdateIsFlagRaised` - Server: flag state
- `IsPointInGreenTrigger` - Check if point is in green area
- `MoveFlagRoutine` - Coroutine for flag animation
- `ServerOnBallScored` - **Server: called when ball scores**
- `RpcPlayBallInHoleSound` - Network: play scoring sound
- `PlayBallInHoleSoundInternal` - Local sound playback
- `RpcPlayFallingInHoleSound` - Network: play falling sound
- `PlayFallingInHoleSoundInternal` - Local falling sound
- `HideWorldspaceIcon` / `UpdateWorldspaceIcon` - Hole icon management

**What This Controls:**
- Hole state and settings
- Scoring detection and effects
- Network synchronization of hole events
- Audio/visual feedback

### GolfHoleManager (12 methods)
**Purpose:** Manages all holes in the current course

**Key Methods:**
- `get_MainHole` - Gets the main hole reference
- `get_HasMaxReferenceDistance` / `get_MaxReferenceDistance` - Distance tracking

### HoleData (20 methods) ✅
**Purpose:** Data structure representing a hole configuration

**Key Methods Discovered:**
- `get/set_LocalizedName` - Hole name (localized)
- `get/set_Scene` - **Unity scene reference for the hole**
- `get/set_Par` - Par for this hole
- `get/set_Difficulty` - Difficulty rating
- `get/set_ScreenshotsThumbnail` - Thumbnail image
- `get/set_MusicEvent` - FMOD music event
- `get/set_ParentCourse` - Reference to parent course
- `get/set_ParentCourseIndex` - Index within parent course
- `get/set_GlobalIndex` - Global hole index
- `RuntimeInitialize` - Runtime initialization
- `.ctor` - Constructor

**What This Controls:**
- Hole metadata (name, par, difficulty)
- Unity scene reference (for loading)
- Course organization (parent, indices)
- Visual assets (thumbnails)
- Audio (music events)

**CRITICAL DISCOVERY:** Each hole has a `Scene` property that references the Unity scene. Custom holes = custom scenes loaded via Addressables!

### PlayerMatchResolution (enum)
**Purpose:** How a player's match ended

**Status:** 0 methods (pure enum)

**Possible Values:** (To be discovered through enum value inspection)
- Won
- Eliminated  
- Quit
- Disconnected
- etc.

## Custom Game Mode Strategy

### Phase 1: Understand Existing Modes ✅ COMPLETE
1. ✅ Identify key classes
2. ✅ Inspect class methods using Mono reflection
3. ✅ Map critical properties and methods
4. ⏳ Understand rule application flow (next step)

**Key Discoveries:**
- Custom courses use `MatchSetupMenu.CustomCourseData`
- Holes are Unity scenes referenced by `HoleData.Scene`
- Item spawning controlled by `MatchSetupRules.UpdateCurrentItemPool`
- Network sync via `ServerUpdateSpawnChanceValue`
- Overtime support exists (`MatchSettings.OvertimeDuration`)

### Phase 2: Hook System Design

**Approach 1: Custom Course Injection (RECOMMENDED)**
Hook `MatchSetupMenu.CustomCourseData` property to inject custom game modes as "courses" with modified rules.

**Steps:**
1. Create `GameModeHook` class in mod loader
2. Hook `MatchSetupMenu.get_CustomCourseData()` using Mono runtime
3. Inject custom `CourseData` objects with modified rule presets
4. Custom "courses" contain rule modifications (item spawn rates, overtime settings, etc.)

**Approach 2: Direct Rule Manipulation**
Hook `MatchSetupRules.CurrentPreset` and `Initialize()` to inject custom rule sets.

**Steps:**
1. Hook `MatchSetupRules.get_CurrentPreset()`
2. Return custom preset enum values
3. Hook `MatchSetupRules.Initialize()` to configure custom rules
4. Network sync via existing `ServerUpdateSpawnChanceValue()`

**Approach 3: Scene-Based Game Modes**
Since each hole is a Unity scene (`HoleData.Scene`), create custom scenes with modified gameplay scripts.

**Steps:**
1. Export custom Unity scene via Addressables
2. Create `HoleData` referencing custom scene
3. Inject into course via `MatchSetupMenu.SetCourse()`
4. Custom scene contains modified game rules/scripts

### Phase 3: Mod Format

**gamemode Mod Type:**
```json
{
  "id": "battle-royale-plus",
  "name": "Battle Royale Plus",
  "type": "gamemode",
  "description": "Battle Royale with double items and faster overtime",
  "version": "1.0.0",
  "author": "ModAuthor",
  
  "gamemode": {
    "baseMode": "BattleRoyale",
    "displayName": "Battle Royale+",
    
    "rules": {
      "itemSpawnMultiplier": 2.0,
      "enableCheats": false
    },
    
    "settings": {
      "overtimeDuration": 30.0,
      "matchEndCountdownDuration": 5.0,
      "teeOffCountdownDuration": 3.0
    },
    
    "customCourse": {
      "name": "BR+ Arena",
      "holes": [
        {
          "scene": "CustomArena1",
          "par": 3,
          "difficulty": 2,
          "catalogPath": "arenas/arena1_catalog.bin"
        }
      ]
    }
  }
}
```

**Map with Custom Rules:**
```json
{
  "id": "crazy-castle",
  "name": "Crazy Castle",
  "type": "map",
  "description": "A wild castle course with modified physics",
  
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  },
  
  "gameRules": {
    "itemSpawnMultiplier": 1.5,
    "overtimeDuration": 60.0
  }
}
```

### Phase 4: Implementation Plan

**Step 1: Create GameModeManager** (C++)
- Singleton manager for custom game modes
- Loads gamemode mods from `Mods/GameModes/`
- Registers custom modes with game

**Step 2: Implement Hooks**
```cpp
// Hook MatchSetupMenu.CustomCourseData getter
MonoMethod* getCustomCourseMethod = mono_class_get_method_from_name(
    matchSetupMenuClass, "get_CustomCourseData", 0);
// Use mono_method_get_unmanaged_thunk or detours to hook

// Hook MatchSetupRules.UpdateCurrentItemPool
MonoMethod* updateItemPoolMethod = mono_class_get_method_from_name(
    matchSetupRulesClass, "UpdateCurrentItemPool", 0);
// Inject custom item spawn multipliers
```

**Step 3: Create CourseData Builder**
```cpp
class CustomCourseBuilder {
public:
    static MonoObject* CreateCustomCourse(
        const char* name,
        const std::vector<HoleConfig>& holes,
        const GameModeSettings& settings);
    
    static MonoObject* CreateHoleData(
        const char* sceneName,
        int par,
        int difficulty);
};
```

**Step 4: Network Synchronization**
- Use existing `ServerUpdateSpawnChanceValue()` for item changes
- Custom modes must sync via Mirror networking
- Send mode config as JSON string over network
- All clients validate they have the same mode installed

**Step 5: Testing**
1. Create simple test mode (e.g., "Double Items Classic")
2. Verify it appears in match setup menu
3. Test multiplayer sync
4. Verify custom settings apply correctly

### Phase 5: Advanced Features

**Dynamic Rule Modification:**
- Allow mods to change rules mid-match
- Hook `MatchSettings` setters to inject real-time changes

**Custom Scoring Systems:**
- Hook `GolfHole.ServerOnBallScored()` to modify scoring logic
- Support point multipliers, bonus scoring, etc.

**Custom Win Conditions:**
- Hook match end logic to implement new win conditions
- First to X points, survival modes, team-based scoring

## Next Steps

1. **Inspect MatchSetupRules fields** - See what fields/properties control rules
2. **Find existing preset definitions** - Discover how Classic/BR are defined
3. **Trace rule application** - Follow how rules are applied during match setup
4. **Design hook points** - Plan where to intercept and extend
5. **Implement GameModeHook** - Create the hooking system
6. **Test custom mode** - Create a simple test mode and verify it works

## Technical Challenges & Solutions

### Challenge 1: Enum Extension
**Problem:** Enums in C# are fixed at compile time (Rule, RuleCategory, Preset)

**Solution:** Don't extend enums directly. Instead:
- Hook methods that read enum values
- Return our own "virtual" enum values
- Or use existing enum values with modified behavior

**Alternative:** These enums may be nested inside MatchSetupRules. Inspect nested types to find them.

### Challenge 2: Network Sync
**Problem:** Custom modes need to sync across all clients

**Solution:**
- Leverage existing network messages (e.g., `StartMatchMessage`)
- Send custom mode config as JSON string via Mirror RPC
- All clients must have the same mod installed
- Hash the mod config and validate on connect

**Implementation:**
```cpp
// When starting match, inject custom data into StartMatchMessage
// Clients receive and validate they have matching mod
```

### Challenge 3: Rule Validation
**Problem:** Game may validate rules against known presets

**Solution:**
- Hook validation methods in MatchSetupRules
- Inject custom rule acceptance logic
- Bypass or extend validation for custom rules

### Challenge 4: UI Integration
**Problem:** Custom modes need to appear in match setup menu

**Solution:**
- Hook `MatchSetupMenu.InitializeCourses()` to add custom entries
- Create UI elements dynamically using Unity UI system
- Or: Inject into existing UI as "custom" category

### Challenge 5: Addressables Integration
**Problem:** Custom scenes need to load via Addressables

**Solution:** ✅ ALREADY SOLVED!
- We already have Addressables catalog loading working
- Use same approach: load custom catalog, reference scenes
- `HoleData.Scene` accepts Unity scene references from catalogs

## Code Examples

### Hooking get_CustomCourseData

```cpp
// Get the MatchSetupMenu class
MonoClass* menuClass = MonoHelper::FindClass("GameAssembly", "", "MatchSetupMenu");

// Get the get_CustomCourseData method
MonoMethod* getterMethod = mono_class_get_method_from_name(menuClass, "get_CustomCourseData", 0);

// Hook it (using MinHook, Detours, or Mono's thunk system)
// When called, inject our custom CourseData object
```

### Creating Custom HoleData

```cpp
// Create a HoleData instance
MonoClass* holeDataClass = MonoHelper::FindClass("GameAssembly", "", "HoleData");
MonoObject* holeData = mono_object_new(MonoHelper::GetDomain(), holeDataClass);

// Set properties
MonoProperty* sceneProperty = mono_class_get_property_from_name(holeDataClass, "Scene");
MonoMethod* sceneSetter = mono_property_get_set_method(sceneProperty);

// Create scene reference (from Addressables)
MonoObject* sceneReference = CreateAddressableSceneReference("CustomScene");

// Set the scene
void* args[] = { sceneReference };
mono_runtime_invoke(sceneSetter, holeData, args, nullptr);
```

### Modifying Item Spawn Rates

```cpp
// Hook MatchSetupRules.UpdateCurrentItemPool
// When called, multiply spawn chances by mod's multiplier

void Hook_UpdateCurrentItemPool(MonoObject* this_ptr) {
    // Call original
    Original_UpdateCurrentItemPool(this_ptr);
    
    // Get item spawn multiplier from active mod
    float multiplier = GameModeManager::GetActiveMultiplier();
    
    // Modify spawn weights
    // ... access internal fields and multiply
}
```

## Related Classes to Investigate

- **StartMatchMessage** - Network message to begin match
- **EliminationReason** - Why players get eliminated (for BR mode)
- **ItemSpawner** / **ItemSettings** - How items spawn in different modes
- **CourseData** - Parent class for course configuration
- **BNetworkManager** - Network synchronization for multiplayer

## Summary & Next Steps

### What We Know ✅

1. **Custom Course System Exists:**
   - `MatchSetupMenu.CustomCourseData` property for custom courses
   - `HoleData.Scene` references Unity scenes
   - Works with Addressables (already proven working!)

2. **Game Mode Configuration:**
   - `MatchSetupRules` manages rules and presets
   - `MatchSettings` contains all timing parameters
   - Overtime support exists (Battle Royale mode)

3. **Item System:**
   - `UpdateCurrentItemPool` controls item spawning
   - Spawn chances can be modified via network sync
   - Server-authoritative via `ServerUpdateSpawnChanceValue`

4. **Network Architecture:**
   - Mirror networking framework
   - Server-authoritative for game state
   - Existing RPC methods for syncing

### Implementation Priority

**Immediate Next Steps:**
1. ✅ Document findings (DONE)
2. ⏳ Create GameModeManager class
3. ⏳ Hook MatchSetupMenu.CustomCourseData
4. ⏳ Build CourseData injector
5. ⏳ Test custom mode loads

**Future Features:**
- Custom rule presets
- Item spawn modification
- Custom win conditions
- Dynamic rule changes mid-match

### Why This Will Work

1. **Addressables Already Works** - We've proven custom catalogs load
2. **Scenes = Holes** - Each hole is just a Unity scene
3. **Custom Course Support** - Game already has CustomCourseData property
4. **Network Sync Exists** - Leverage existing Mirror RPCs

**The path forward is clear: Hook CustomCourseData, inject our courses, and let the game's existing systems handle the rest!**

---

**Document Status:** Complete architecture analysis based on Mono reflection inspection  
**Last Updated:** 2026-04-11  
**Classes Inspected:** 10 (6 successfully, 4 not found as standalone)
