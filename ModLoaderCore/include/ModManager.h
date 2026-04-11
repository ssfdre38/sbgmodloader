#pragma once
#include <vector>
#include <string>
#include <map>
#include "IModModule.h"
#include "ModInfo.h"

namespace ModLoader {

/// Manages mod discovery and lifecycle
class ModManager {
public:
    static ModManager& Instance();
    
    /// Discover mods by scanning category folders
    void DiscoverMods(const std::string& modsPath);
    
    /// Load discovered mods in dependency order
    void LoadAllMods();
    
    /// Initialize all loaded mods
    void InitializeAllMods();
    
    /// Call OnUpdate for all mods
    void UpdateAllMods(float deltaTime);
    
    /// Call OnLateUpdate for all mods
    void LateUpdateAllMods(float deltaTime);
    
    /// Unload all mods and cleanup
    void UnloadAllMods();
    
    /// Get discovered mod count
    size_t GetModCount() const { return discoveredMods.size(); }
    
    /// Get loaded mod count
    size_t GetLoadedModCount() const { return loadedMods.size(); }
    
    /// Get all discovered mods
    const std::vector<ModInfo>& GetDiscoveredMods() const { return discoveredMods; }
    
private:
    ModManager() = default;
    
    /// Scan a category folder for mods
    void ScanCategoryFolder(const std::string& categoryPath, const std::string& categoryName);
    
    /// Load a single mod DLL
    bool LoadModDll(const ModInfo& modInfo);
    
    /// Load Addressables catalog for a mod
    bool LoadModCatalog(const ModInfo& modInfo);
    
    /// Resolve dependency order
    std::vector<ModInfo> ResolveDependencyOrder();
    
    std::vector<ModInfo> discoveredMods;  // All discovered mods (from mod.json files)
    std::vector<std::pair<void*, ModSDK::IModModule*>> loadedMods;  // DLL mods (Handle, Instance)
    std::map<std::string, bool> loadedCatalogs;  // Track loaded Addressables catalogs
};

}  // namespace ModLoader
