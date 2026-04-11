# Detours & IL2CPP Setup Complete

**Date**: 2026-04-10  
**Status**: ✅ Infrastructure ready for game hooking and mod development

## What Was Set Up

### 1. Microsoft Detours Library
**Location**: `ThirdParty\Detours\`

Detours is Microsoft's industry-standard library for API hooking. It allows us to:
- Intercept function calls
- Replace function implementations
- Chain hooks (call original after our version)
- Works with native C++ and IL2CPP compiled code

**Key files**:
- `include\detours.h` - Main hooking API
- Includes: `DetourTransactionBegin()`, `DetourAttach()`, `DetourDetach()`

### 2. IL2CPP Runtime API Wrapper
**Location**: `ThirdParty\include\il2cpp-api.h`

Custom header file declaring all IL2CPP runtime functions needed for mod development:

```cpp
// Domain access
il2cpp_domain_get()  // Get game runtime domain
il2cpp_domain_get_assemblies()  // List all loaded assemblies

// Class lookup
il2cpp_class_from_name(image, namespace, className)  // Find a class
il2cpp_class_get_name(klass)  // Get class name

// Object creation
il2cpp_object_new(klass)  // Create instance of a class
il2cpp_runtime_invoke(method, obj, params, exc)  // Call a method

// String/Array creation
il2cpp_string_new(str)  // Create IL2CPP string
il2cpp_array_new(elementType, length)  // Create array

// Field access
il2cpp_field_get_value(obj, field)  // Read field
il2cpp_field_set_value(obj, field, value)  // Write field
```

### 3. IL2CPP API Implementation
**Location**: `ThirdParty\include\il2cpp-api.cpp`

Implementation file that:
- Dynamically resolves function pointers from `il2cpp.dll` or `GameAssembly.dll`
- Provides `il2cpp_api_init()` to initialize all pointers at startup
- Handles errors gracefully if functions not found

## How Hooks Work in Our System

### Current Architecture

```
Game.exe launches
    ↓
GameLauncher.exe injects ModLoaderCore.dll
    ↓
ModLoaderCore DllMain() runs
    ↓
Hooks::Initialize() sets up Detours hooks
    ↓
Hooks::HookGameManagerAwake() intercepts game init
    ↓
Game's GameManager::Awake() called
    ↓
Our Hooked_GameManager_Awake() called first
    ↓
Call original GameManager::Awake()
    ↓
Hooks::OnGameInitialized() triggers
    ↓
ModManager discovers and loads all mods
    ↓
Each mod's OnLoad() called when game ready
```

### The Detours Hook Pattern

```cpp
// 1. Define original function pointer
typedef void(*OriginalFunc)(void* thisPtr);
OriginalFunc original_function = nullptr;

// 2. Create hooked replacement
void Hooked_Function(void* thisPtr) {
    printf("Before original function\n");
    
    // Call original
    original_function(thisPtr);
    
    printf("After original function\n");
}

// 3. Attach the hook
DetourTransactionBegin();
DetourUpdateThread(GetCurrentThread());
DetourAttach(&(PVOID&)original_function, Hooked_Function);
DetourTransactionCommit();

// 4. Later, detach if needed
DetourTransactionBegin();
DetourDetach(&(PVOID&)original_function, Hooked_Function);
DetourTransactionCommit();
```

## Finding the Hook Target

To actually hook the game, we need the **method address** of `GameManager::Awake()` in GameAssembly.dll.

### Option 1: IDA Pro (Professional)
1. Open `GameAssembly.dll` in IDA Pro
2. Use "Search" → "Text" to find "GameManager::Awake"
3. Note the **RVA** (Relative Virtual Address)
4. Convert to absolute address: `BaseAddress + RVA`

### Option 2: Il2CppInspector (Free)
1. Download from: https://github.com/djkaty/Il2CppInspector
2. Open `GameAssembly.dll` + `metadata.global.dat`
3. Search for GameManager class
4. Find Awake() method and its address

### Option 3: Memory Scanning (Advanced)
1. Use a memory scanner to find known patterns
2. Look for initialization code sequences
3. Hook early system methods that are definitely called

### Option 4: Look in Decompiled Code
Since you have the decompiled assembly:
1. Find GameManager.cs in your decompiled files
2. Look for Awake() method
3. Check for GameAssembly.dll method metadata

## Example Mod Using IL2CPP API

```cpp
#include "IModModule.h"
#include <il2cpp-api.h>

class ExampleMod : public IModModule {
public:
    const char* GetId() const override { return "example-mod"; }
    const char* GetName() const override { return "Example Mod"; }
    const char* GetVersion() const override { return "0.1.0"; }
    
    void OnLoad() override {
        // Initialize IL2CPP API
        il2cpp_api_init();
        
        // Get UnityEngine image
        auto image = il2cpp_image_from_name("UnityEngine.CoreModule");
        if (!image) return;
        
        // Find GameObject class
        auto gameObjectClass = il2cpp_class_from_name(image, "UnityEngine", "GameObject");
        if (!gameObjectClass) return;
        
        // Create a new GameObject
        auto obj = il2cpp_object_new(gameObjectClass);
        
        // Find the SetActive method
        auto setActiveMethod = il2cpp_class_get_method_from_name(gameObjectClass, "SetActive", 1);
        if (!setActiveMethod) return;
        
        // Call SetActive(true)
        bool active = true;
        il2cpp_runtime_invoke(setActiveMethod, obj, (void**)&active, nullptr);
    }
    
    void OnUnload() override {}
    void OnUpdate(float dt) override {}
    void OnLateUpdate(float dt) override {}
    void OnSceneLoaded(const char* name) override {}
};

EXPORT_MOD(ExampleMod)
```

## Files Modified/Created

### New Files
- `ThirdParty/Detours/` - Microsoft Detours library (already present)
- `ThirdParty/include/il2cpp-api.h` - IL2CPP runtime API declarations
- `ThirdParty/include/il2cpp-api.cpp` - IL2CPP function pointer resolution

### Modified Files
- `ModLoaderCore/src/Hooks.cpp` - Updated with Detours integration
  - `Hooks::Initialize()` - Sets up Detours framework
  - `Hooked_GameManager_Awake()` - Intercepts game initialization
  - `OnGameInitialized()` - Triggers mod loading

## Next Steps

### Phase 1: Find Hook Target (IMMEDIATE)
- [ ] Analyze `GameAssembly.dll` to find `GameManager::Awake()` method address
- [ ] Use IDA Pro, Il2CppInspector, or decompiled code search
- [ ] Document the RVA/address

### Phase 2: Activate Hooks (HIGH PRIORITY)
- [ ] Update `Hooks::HookGameManagerAwake()` with actual method address
- [ ] Compile and test DLL injection
- [ ] Verify hook fires during game startup

### Phase 3: Enable Mod IL2CPP Interaction (HIGH PRIORITY)
- [ ] Update test mod to use `il2cpp_api_init()` and IL2CPP functions
- [ ] Test creating GameObjects and calling methods
- [ ] Verify UI rendering works

### Phase 4: Implement Version Display (MEDIUM)
- [ ] Create TextMeshPro UI element showing "sbg-mod-loader-0.1.0-beta"
- [ ] Position at bottom-left of screen
- [ ] Verify user can see mod loader is active

### Phase 5: Mirror Networking Integration (FUTURE)
- [ ] Hook lobby list rendering
- [ ] Tag modded lobbies
- [ ] Implement server-side registry

## Technical Reference

### IL2CPP Runtime Memory Layout
```cpp
// IL2CPP objects are heap-allocated pointers
Il2CppObject* obj = il2cpp_object_new(klass);
// obj->klass points back to the class metadata
// obj->fields contain instance data

// IL2CPP strings are immutable
Il2CppString* str = il2cpp_string_new("hello");
// str->chars contains UTF-16 characters
// str->length is character count
```

### Method Invocation Pattern
```cpp
// All methods need parameters packed in a void** array
void* params[2] = { (void*)value1, (void*)value2 };

// Exception handled in third parameter
void* exception = nullptr;
il2cpp_runtime_invoke(method, object, params, &exception);

if (exception) {
    // Exception occurred
}
```

### Finding Methods and Fields
```cpp
// Method with exact parameter count
auto method = il2cpp_class_get_method_from_name(klass, "MethodName", 1);

// Field lookup
auto field = il2cpp_class_get_field_from_name(klass, "fieldName");

// Get parent class hierarchy
auto parent = il2cpp_class_get_parent(klass);
```

## Detours Command Reference

### Transaction-Based Hooking
```cpp
// Start transaction (must be paired with Commit)
DetourTransactionBegin();

// Update current thread state
DetourUpdateThread(GetCurrentThread());

// Attach a hook
DetourAttach(&(PVOID&)targetFunction, hookedFunction);

// Detach a hook
DetourDetach(&(PVOID&)targetFunction, hookedFunction);

// Commit all changes atomically
LONG result = DetourTransactionCommit();
if (result != NO_ERROR) {
    // Error occurred
}
```

## Building with Detours and IL2CPP

When compiling mods that use IL2CPP:

```bash
cl.exe /nologo /W3 /EHsc /MD /std:c++17 /LD \
    /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" \
    /I "...\ModSDK\include" \
    /I "...\ThirdParty\include" \
    /I "...\ThirdParty\Detours\include" \
    /Fe:output.dll \
    mod_source.cpp \
    /link /LIBPATH:"...\ThirdParty\Detours\lib.x64" \
    detours.lib kernel32.lib user32.lib
```

## Troubleshooting

### IL2CPP functions return nullptr
- Call `il2cpp_api_init()` first to resolve function pointers
- Check if image/class/method names are correct
- Use exact C# class names, not decompiled names

### Hook doesn't fire
- Verify method address is correct (check in IDA/Il2CppInspector)
- Make sure Detours transaction committed successfully
- Add logging before and after hook to verify execution

### Game crashes with Detours
- Ensure method signature matches (calling convention, parameters)
- Check that original function pointer is called correctly
- Use -SafeDetour flag if available

## Resources

- **Microsoft Detours**: https://github.com/microsoft/Detours
- **Il2CppVersions**: https://github.com/nneonneo/Il2CppVersions
- **Il2CppInspector**: https://github.com/djkaty/Il2CppInspector
- **IDA Pro**: https://www.hex-rays.com/ida-pro/

## Summary

✅ **Ready for game hooking** - Detours is configured and Hooks.cpp updated  
✅ **Ready for IL2CPP interaction** - Complete IL2CPP API wrapper in place  
✅ **Ready for mod development** - Mods can now use IL2CPP functions  

**Blockers**: Need GameManager::Awake() method address to activate hooks
