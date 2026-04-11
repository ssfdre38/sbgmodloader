#include "ModManager.h"
#include "Log.h"
#include <Windows.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace ModLoader {

ModManager& ModManager::Instance() {
    static ModManager instance;
    return instance;
}

void ModManager::DiscoverMods(const std::string& modsPath) {
    LOG_INFO("Discovering mods from: %s", modsPath.c_str());
    
    if (!fs::exists(modsPath)) {
        LOG_WARN("❌ Mods directory does not exist: %s", modsPath.c_str());
        LOG_WARN("DiscoverMods returning early - no mods will load");
        return;
    }
    
    LOG_INFO("✓ Mods directory found: %s", modsPath.c_str());
    
    int modCount = 0;
    int fileCount = 0;
    for (const auto& entry : fs::directory_iterator(modsPath)) {
        fileCount++;
        LOG_INFO("  Found file: %s", entry.path().filename().string().c_str());
        
        if (entry.path().extension() == ".dll") {
            LOG_INFO("    -> Attempting to load DLL: %s", entry.path().string().c_str());
            if (LoadModDll(entry.path().string())) {
                modCount++;
                LOG_INFO("    -> ✓ Successfully loaded mod from: %s", entry.path().filename().string().c_str());
            } else {
                LOG_WARN("    -> ❌ Failed to load mod from: %s", entry.path().filename().string().c_str());
            }
        }
    }
    
    LOG_INFO("Directory scan complete: %d files found, %d mods loaded", fileCount, modCount);
    LOG_INFO("Discovered %d mod(s)", modCount);
}

bool ModManager::LoadModDll(const std::string& dllPath) {
    LOG_INFO("Loading mod DLL: %s", dllPath.c_str());
    
    // Load the DLL
    HMODULE handle = LoadLibraryA(dllPath.c_str());
    if (!handle) {
        LOG_ERROR("Failed to load DLL: %s (error: %lu)", dllPath.c_str(), GetLastError());
        return false;
    }
    
    // Get the CreateModInstance function
    typedef ModSDK::IModModule* (*CreateModFn)();
    CreateModFn createMod = (CreateModFn)GetProcAddress(handle, "CreateModInstance");
    
    if (!createMod) {
        LOG_ERROR("DLL does not export CreateModInstance: %s", dllPath.c_str());
        FreeLibrary(handle);
        return false;
    }
    
    // Create the mod instance
    ModSDK::IModModule* mod = nullptr;
    try {
        mod = createMod();
    } catch (...) {
        LOG_ERROR("Exception creating mod instance from: %s", dllPath.c_str());
        FreeLibrary(handle);
        return false;
    }
    
    if (!mod) {
        LOG_ERROR("CreateModInstance returned null");
        FreeLibrary(handle);
        return false;
    }
    
    mods.push_back({handle, mod});
    LOG_INFO("Loaded mod: %s v%s (ID: %s)", mod->GetName(), mod->GetVersion(), mod->GetId());
    
    return true;
}

void ModManager::InitializeAllMods() {
    LOG_INFO("Initializing %zu mod(s)", mods.size());
    
    for (size_t i = 0; i < mods.size(); i++) {
        auto& [handle, mod] = mods[i];
        try {
            LOG_INFO("[%zu/%zu] Calling OnLoad() for %s", i + 1, mods.size(), mod->GetName());
            mod->OnLoad();
            LOG_INFO("OnLoad() complete for %s", mod->GetName());
        } catch (...) {
            LOG_ERROR("Exception in OnLoad() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::UpdateAllMods(float deltaTime) {
    for (auto& [handle, mod] : mods) {
        try {
            mod->OnUpdate(deltaTime);
        } catch (...) {
            LOG_ERROR("Exception in OnUpdate() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::LateUpdateAllMods(float deltaTime) {
    for (auto& [handle, mod] : mods) {
        try {
            mod->OnLateUpdate(deltaTime);
        } catch (...) {
            LOG_ERROR("Exception in OnLateUpdate() for mod: %s", mod->GetName());
        }
    }
}

void ModManager::UnloadAllMods() {
    LOG_INFO("Unloading %zu mod(s)", mods.size());
    
    for (auto& [handle, mod] : mods) {
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
    
    mods.clear();
    LOG_INFO("All mods unloaded");
}

}  // namespace ModLoader
