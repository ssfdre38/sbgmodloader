#pragma once

namespace ModSDK {

/// Base interface for all mods
class IModModule {
public:
    virtual ~IModModule() = default;

    /// Get unique mod identifier
    virtual const char* GetId() const = 0;

    /// Get human-readable mod name
    virtual const char* GetName() const = 0;

    /// Get semantic version (e.g., "0.1.0-beta")
    virtual const char* GetVersion() const = 0;

    /// Called when mod is loaded and game is ready
    virtual void OnLoad() = 0;

    /// Called when mod is unloaded (before exit or reload)
    virtual void OnUnload() = 0;

    /// Called every frame for game updates
    virtual void OnUpdate(float deltaTime) {}

    /// Called every frame for late updates (physics done)
    virtual void OnLateUpdate(float deltaTime) {}

    /// Called when scene is loaded
    virtual void OnSceneLoaded(const char* sceneName) {}
};

}  // namespace ModSDK

// Macro to export mod factory function
#define EXPORT_MOD(ModClass) \
    extern "C" __declspec(dllexport) ModSDK::IModModule* CreateModInstance() { \
        return new ModClass(); \
    } \
    extern "C" __declspec(dllexport) void DestroyModInstance(ModSDK::IModModule* mod) { \
        delete mod; \
    }
