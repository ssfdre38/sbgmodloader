#pragma once
#include <vector>
#include <string>
#include "IModModule.h"

namespace ModLoader {

/// Manages mod discovery and lifecycle
class ModManager {
public:
    static ModManager& Instance();
    
    /// Discover and load all mods from Mods/ folder
    void DiscoverMods(const std::string& modsPath);
    
    /// Initialize all loaded mods
    void InitializeAllMods();
    
    /// Call OnUpdate for all mods
    void UpdateAllMods(float deltaTime);
    
    /// Call OnLateUpdate for all mods
    void LateUpdateAllMods(float deltaTime);
    
    /// Unload all mods and cleanup
    void UnloadAllMods();
    
    /// Get mod count
    int GetModCount() const { return mods.size(); }
    
private:
    ModManager() = default;
    
    /// Load a single mod DLL
    bool LoadModDll(const std::string& dllPath);
    
    std::vector<std::pair<void*, ModSDK::IModModule*>> mods;  // Handle, Instance
};

}  // namespace ModLoader
