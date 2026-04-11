#include "ModManager.h"
#include "MonoHelper.h"
#include "Log.h"
#include <Windows.h>
#include <filesystem>
#include <algorithm>
#include <set>

namespace fs = std::filesystem;

namespace ModLoader {

ModManager& ModManager::Instance() {
    static ModManager instance;
    return instance;
}

void ModManager::DiscoverMods(const std::string& modsPath) {
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("🔍 Discovering Mods");
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("Mods Root: %s", modsPath.c_str());
    LOG_INFO("");
    
    if (!fs::exists(modsPath)) {
        LOG_WARN("❌ Mods directory does not exist: %s", modsPath.c_str());
        LOG_WARN("   No mods will be loaded");
        return;
    }
    
    // Category folders to scan
    const std::vector<std::string> categories = {
        "Core",        // Load first (dependencies)
        "Scripts",     // Load second (behavior mods)
        "Audio",
        "UI",
        "Weapons",
        "Characters",
        "GameModes",
        "Maps"         // Load last (may depend on everything)
    };
    
    // Scan each category folder
    int totalMods = 0;
    for (const auto& category : categories) {
        std::string categoryPath = modsPath + "\\" + category;
        if (fs::exists(categoryPath)) {
            ScanCategoryFolder(categoryPath, category);
            
            // Count mods in this category
            int categoryCount = 0;
            for (const auto& mod : discoveredMods) {
                if (mod.type == category || 
                    (category == "Scripts" && mod.type == "script") ||
                    (category == "Maps" && mod.type == "map") ||
                    (category == "GameModes" && mod.type == "gamemode")) {
                    categoryCount++;
                }
            }
            if (categoryCount > 0) {
                LOG_INFO("  📁 %s: %d mod(s)", category.c_str(), categoryCount);
                totalMods += categoryCount;
            }
        }
    }
    
    LOG_INFO("");
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("✅ Discovery Complete: %d mod(s) found", totalMods);
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("");
    
    // Log discovered mods
    if (!discoveredMods.empty()) {
        LOG_INFO("Discovered Mods:");
        for (const auto& mod : discoveredMods) {
            LOG_INFO("  • %s [%s]", mod.GetDisplayName().c_str(), mod.type.c_str());
            LOG_INFO("    Author: %s", mod.author.c_str());
            LOG_INFO("    Path: %s", mod.folderPath.c_str());
            if (!mod.dependencies.empty()) {
                LOG_INFO("    Dependencies: %zu", mod.dependencies.size());
            }
            if (mod.content.addressables) {
                LOG_INFO("    Addressables: %s", mod.content.catalogPath.c_str());
            }
        }
        LOG_INFO("");
    }
}

void ModManager::ScanCategoryFolder(const std::string& categoryPath, const std::string& categoryName) {
    if (!fs::exists(categoryPath) || !fs::is_directory(categoryPath)) {
        return;
    }
    
    // Iterate through subfolders (each is a potential mod)
    for (const auto& entry : fs::directory_iterator(categoryPath)) {
        if (entry.is_directory()) {
            // Look for mod.json
            std::string modJsonPath = entry.path().string() + "\\mod.json";
            
            if (fs::exists(modJsonPath)) {
                LOG_INFO("   Found mod.json: %s", entry.path().filename().string().c_str());
                
                // Parse mod.json
                ModInfo modInfo = ModInfo::FromJsonFile(modJsonPath);
                
                // Validate
                std::string validationError;
                if (!modInfo.Validate(validationError)) {
                    LOG_ERROR("   ❌ Validation failed: %s", validationError.c_str());
                    modInfo.hasErrors = true;
                    modInfo.errorMessage = validationError;
                } else if (!modInfo.hasErrors) {
                    LOG_INFO("   ✅ Valid mod: %s", modInfo.GetDisplayName().c_str());
                }
                
                discoveredMods.push_back(modInfo);
            }
        }
    }
}

void ModManager::LoadAllMods() {
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("📦 Loading Mods");
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("");
    
    if (discoveredMods.empty()) {
        LOG_INFO("No mods to load");
        return;
    }
    
    // Resolve dependency order
    std::vector<ModInfo> loadOrder = ResolveDependencyOrder();
    
    LOG_INFO("Load order determined: %zu mod(s)", loadOrder.size());
    for (size_t i = 0; i < loadOrder.size(); i++) {
        LOG_INFO("  %zu. %s", i + 1, loadOrder[i].GetDisplayName().c_str());
    }
    LOG_INFO("");
    
    // Load each mod in order
    int successCount = 0;
    int failCount = 0;
    
    for (auto& modInfo : loadOrder) {
        if (modInfo.hasErrors) {
            LOG_WARN("⏭️  Skipping %s (validation errors)", modInfo.name.c_str());
            failCount++;
            continue;
        }
        
        LOG_INFO("Loading: %s", modInfo.GetDisplayName().c_str());
        
        bool loaded = false;
        
        // Load DLL if it's a script mod
        if (modInfo.type == "script" || modInfo.type == "core") {
            if (LoadModDll(modInfo)) {
                loaded = true;
            }
        }
        
        // Load Addressables catalog if present
        if (modInfo.content.addressables) {
            if (LoadModCatalog(modInfo)) {
                loaded = true;
            }
        }
        
        if (loaded) {
            LOG_INFO("✅ Loaded successfully");
            successCount++;
            
            // Mark as loaded in discoveredMods
            for (auto& mod : discoveredMods) {
                if (mod.id == modInfo.id) {
                    mod.isLoaded = true;
                    break;
                }
            }
        } else {
            LOG_WARN("❌ Failed to load");
            failCount++;
        }
        
        LOG_INFO("");
    }
    
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("✅ Loading Complete: %d loaded, %d failed", successCount, failCount);
    LOG_INFO("═══════════════════════════════════════════════════");
    LOG_INFO("");
}

std::vector<ModInfo> ModManager::ResolveDependencyOrder() {
    // Simple topological sort - load mods without dependencies first
    // For now, just return in discovery order (dependencies not yet enforced)
    // TODO: Implement proper topological sort with cycle detection
    
    std::vector<ModInfo> sorted;
    
    // Copy all valid mods
    for (const auto& mod : discoveredMods) {
        if (!mod.hasErrors) {
            sorted.push_back(mod);
        }
    }
    
    // Sort by category priority (Core first, Maps last)
    std::map<std::string, int> priority = {
        {"core", 0},
        {"script", 1},
        {"audio", 2},
        {"ui", 3},
        {"weapon", 4},
        {"character", 5},
        {"gamemode", 6},
        {"map", 7}
    };
    
    std::sort(sorted.begin(), sorted.end(), [&](const ModInfo& a, const ModInfo& b) {
        int aPrio = priority.count(a.type) ? priority[a.type] : 999;
        int bPrio = priority.count(b.type) ? priority[b.type] : 999;
        return aPrio < bPrio;
    });
    
    return sorted;
}

bool ModManager::LoadModDll(const ModInfo& modInfo) {
    // Look for DLL in mod folder
    std::string dllPath = modInfo.folderPath + "\\" + modInfo.id + ".dll";
    
    // Try alternate name
    if (!fs::exists(dllPath)) {
        dllPath = modInfo.folderPath + "\\" + modInfo.name + ".dll";
    }
    
    // Check all DLLs in folder
    if (!fs::exists(dllPath)) {
        for (const auto& entry : fs::directory_iterator(modInfo.folderPath)) {
            if (entry.path().extension() == ".dll") {
                dllPath = entry.path().string();
                break;
            }
        }
    }
    
    if (!fs::exists(dllPath)) {
        LOG_WARN("  No DLL found in mod folder");
        return false;
    }
    
    LOG_INFO("  Loading DLL: %s", fs::path(dllPath).filename().string().c_str());
    
    // Load the DLL
    HMODULE handle = LoadLibraryA(dllPath.c_str());
    if (!handle) {
        LOG_ERROR("  Failed to load DLL (error: %lu)", GetLastError());
        return false;
    }
    
    // Get the CreateModInstance function
    typedef ModSDK::IModModule* (*CreateModFn)();
    CreateModFn createMod = (CreateModFn)GetProcAddress(handle, "CreateModInstance");
    
    if (!createMod) {
        LOG_WARN("  DLL does not export CreateModInstance");
        FreeLibrary(handle);
        return false;
    }
    
    // Create the mod instance
    ModSDK::IModModule* mod = nullptr;
    try {
        mod = createMod();
    } catch (...) {
        LOG_ERROR("  Exception creating mod instance");
        FreeLibrary(handle);
        return false;
    }
    
    if (!mod) {
        LOG_ERROR("  CreateModInstance returned null");
        FreeLibrary(handle);
        return false;
    }
    
    loadedMods.push_back({handle, mod});
    LOG_INFO("  DLL loaded: %s v%s", mod->GetName(), mod->GetVersion());
    
    return true;
}

bool ModManager::LoadModCatalog(const ModInfo& modInfo) {
    if (!modInfo.content.addressables) {
        return false;
    }
    
    // Build full catalog path
    std::string catalogPath = modInfo.folderPath + "\\" + modInfo.content.catalogPath;
    
    if (!fs::exists(catalogPath)) {
        LOG_ERROR("  Catalog not found: %s", catalogPath.c_str());
        return false;
    }
    
    LOG_INFO("  Loading Addressables catalog: %s", modInfo.content.catalogPath.c_str());
    
    // Check if already loaded
    if (loadedCatalogs.count(catalogPath)) {
        LOG_WARN("  Catalog already loaded, skipping");
        return true;
    }
    
    // Find Addressables.LoadContentCatalogAsync
    MonoClass* addressablesClass = Mono::MonoHelper::FindClass("Unity.Addressables", 
                                                          "UnityEngine.AddressableAssets", 
                                                          "Addressables");
    if (!addressablesClass) {
        LOG_ERROR("  Failed to find Addressables class");
        return false;
    }
    
    MonoMethod* loadCatalogMethod = Mono::MonoHelper::FindMethod(addressablesClass, 
                                                            "LoadContentCatalogAsync", 
                                                            2);  // path + autoReleaseHandle
    if (!loadCatalogMethod) {
        LOG_ERROR("  Failed to find LoadContentCatalogAsync method");
        return false;
    }
    
    // Create path string
    MonoString* pathStr = Mono::MonoHelper::CreateString(catalogPath.c_str());
    if (!pathStr) {
        LOG_ERROR("  Failed to create path string");
        return false;
    }
    
    // Call LoadContentCatalogAsync
    void* args[2] = { pathStr, nullptr };  // autoReleaseHandle defaults to true
    MonoObject* asyncHandle = Mono::MonoHelper::InvokeStaticMethod(loadCatalogMethod, args);
    
    if (!asyncHandle) {
        LOG_ERROR("  LoadContentCatalogAsync returned null");
        return false;
    }
    
    LOG_INFO("  ✅ Catalog load initiated!");
    loadedCatalogs[catalogPath] = true;
    
    return true;
}

void ModManager::InitializeAllMods() {
    LOG_INFO("Initializing %zu DLL mod(s)", loadedMods.size());
    
    for (size_t i = 0; i < loadedMods.size(); i++) {
        auto& [handle, mod] = loadedMods[i];
        try {
            LOG_INFO("[%zu/%zu] Calling OnLoad() for %s", i + 1, loadedMods.size(), mod->GetName());
            mod->OnLoad();
        } catch (...) {
            LOG_ERROR("Exception in OnLoad() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::UpdateAllMods(float deltaTime) {
    for (auto& [handle, mod] : loadedMods) {
        try {
            mod->OnUpdate(deltaTime);
        } catch (...) {
            LOG_ERROR("Exception in OnUpdate() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::LateUpdateAllMods(float deltaTime) {
    for (auto& [handle, mod] : loadedMods) {
        try {
            mod->OnLateUpdate(deltaTime);
        } catch (...) {
            LOG_ERROR("Exception in OnLateUpdate() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::UnloadAllMods() {
    LOG_INFO("Unloading %zu DLL mod(s)", loadedMods.size());
    
    for (auto& [handle, mod] : loadedMods) {
        try {
            mod->OnUnload();
        } catch (...) {
            LOG_ERROR("Exception in OnUnload() for mod: %s", mod->GetName());
        }
        
        // Get DestroyModInstance function
        typedef void (*DestroyModFn)(ModSDK::IModModule*);
        DestroyModFn destroyMod = (DestroyModFn)GetProcAddress((HMODULE)handle, "DestroyModInstance");
        
        if (destroyMod) {
            try {
                destroyMod(mod);
            } catch (...) {
                LOG_ERROR("Exception destroying mod: %s", mod->GetName());
            }
        }
        
        FreeLibrary((HMODULE)handle);
    }
    
    loadedMods.clear();
    loadedCatalogs.clear();
    discoveredMods.clear();
    LOG_INFO("All mods unloaded");
}

}  // namespace ModLoader
