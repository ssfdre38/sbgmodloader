#include "AddressablesHook.h"
#include "IL2CPP.h"
#include "Log.h"
#include <detours.h>

namespace ModLoader {
namespace Addressables {

// Static member initialization
bool AddressablesHook::s_Initialized = false;
std::vector<std::string> AddressablesHook::s_CustomCatalogs;
std::vector<OnCatalogLoadCallback> AddressablesHook::s_CatalogLoadCallbacks;
std::vector<OnAssetLoadCallback> AddressablesHook::s_AssetLoadCallbacks;
std::vector<OnSceneLoadCallback> AddressablesHook::s_SceneLoadCallbacks;

IL2CPP::Il2CppClass* AddressablesHook::s_AddressablesClass = nullptr;
IL2CPP::Il2CppClass* AddressablesHook::s_ResourceManagerClass = nullptr;
IL2CPP::Il2CppClass* AddressablesHook::s_AsyncOperationClass = nullptr;
IL2CPP::Il2CppMethodInfo* AddressablesHook::s_LoadContentCatalogAsync = nullptr;
IL2CPP::Il2CppMethodInfo* AddressablesHook::s_LoadAssetAsync = nullptr;
IL2CPP::Il2CppMethodInfo* AddressablesHook::s_LoadSceneAsync = nullptr;

bool AddressablesHook::Initialize() {
    if (s_Initialized) {
        LOG_INFO("Addressables hooks already initialized");
        return true;
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Initializing Addressables Hook System");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    // Make sure IL2CPP is initialized first
    if (!IL2CPP::IL2CPPHelper::IsInitialized()) {
        LOG_ERROR("IL2CPP not initialized! Call IL2CPPHelper::Initialize() first!");
        return false;
    }
    
    // Find Addressables classes
    if (!FindAddressablesClasses()) {
        LOG_ERROR("Failed to find Addressables classes!");
        return false;
    }
    
    // Hook Addressables API (if we have methods to hook)
    // NOTE: We may not be able to hook until runtime, so this is optional
    if (s_LoadContentCatalogAsync || s_LoadAssetAsync || s_LoadSceneAsync) {
        LOG_INFO("Found Addressables methods - hooking is possible");
        // TODO: Implement Detours hooks for these methods
    } else {
        LOG_INFO("No Addressables methods found yet (may load later)");
    }
    
    s_Initialized = true;
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("✓ Addressables Hook System Initialized!");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    return true;
}

bool AddressablesHook::FindAddressablesClasses() {
    using namespace IL2CPP;
    
    LOG_INFO("Searching for Unity Addressables classes...");
    
    // Try to find Addressables class
    // Assembly name: "Unity.Addressables" or "Unity.ResourceManager"
    // Namespace: "UnityEngine.AddressableAssets"
    // Class: "Addressables"
    
    s_AddressablesClass = IL2CPPHelper::FindClass("Unity.Addressables", "UnityEngine.AddressableAssets", "Addressables");
    if (s_AddressablesClass) {
        LOG_INFO("✓ Found Addressables class: %s.%s",
            IL2CPPHelper::GetClassNamespace(s_AddressablesClass),
            IL2CPPHelper::GetClassName(s_AddressablesClass));
        
        // Try to find methods
        s_LoadContentCatalogAsync = IL2CPPHelper::FindMethod(s_AddressablesClass, "LoadContentCatalogAsync", -1);
        if (s_LoadContentCatalogAsync) {
            LOG_INFO("  ✓ Found method: LoadContentCatalogAsync");
        }
        
        s_LoadAssetAsync = IL2CPPHelper::FindMethod(s_AddressablesClass, "LoadAssetAsync", -1);
        if (s_LoadAssetAsync) {
            LOG_INFO("  ✓ Found method: LoadAssetAsync");
        }
        
        s_LoadSceneAsync = IL2CPPHelper::FindMethod(s_AddressablesClass, "LoadSceneAsync", -1);
        if (s_LoadSceneAsync) {
            LOG_INFO("  ✓ Found method: LoadSceneAsync");
        }
    } else {
        LOG_INFO("  ⚠ Addressables class not found (may not be loaded yet)");
    }
    
    // Try to find ResourceManager (lower-level API)
    s_ResourceManagerClass = IL2CPPHelper::FindClass("Unity.ResourceManager", "UnityEngine.ResourceManagement", "ResourceManager");
    if (s_ResourceManagerClass) {
        LOG_INFO("✓ Found ResourceManager class: %s.%s",
            IL2CPPHelper::GetClassNamespace(s_ResourceManagerClass),
            IL2CPPHelper::GetClassName(s_ResourceManagerClass));
    } else {
        LOG_INFO("  ⚠ ResourceManager class not found");
    }
    
    // We consider success if we found at least one class
    return (s_AddressablesClass != nullptr || s_ResourceManagerClass != nullptr);
}

void AddressablesHook::RegisterCustomCatalog(const char* catalogPath) {
    LOG_INFO("Registering custom catalog: %s", catalogPath);
    s_CustomCatalogs.push_back(catalogPath);
}

void AddressablesHook::OnCatalogLoad(OnCatalogLoadCallback callback) {
    s_CatalogLoadCallbacks.push_back(callback);
}

void AddressablesHook::OnAssetLoad(OnAssetLoadCallback callback) {
    s_AssetLoadCallbacks.push_back(callback);
}

void AddressablesHook::OnSceneLoad(OnSceneLoadCallback callback) {
    s_SceneLoadCallbacks.push_back(callback);
}

bool AddressablesHook::LoadCustomCatalog(const char* catalogPath) {
    using namespace IL2CPP;
    
    if (!s_LoadContentCatalogAsync) {
        LOG_ERROR("LoadContentCatalogAsync method not found!");
        return false;
    }
    
    LOG_INFO("Loading custom catalog: %s", catalogPath);
    
    // Create IL2CPP string for catalog path
    IL2CPPThreadScope threadScope;
    Il2CppString* pathString = IL2CPPHelper::CreateString(catalogPath);
    
    if (!pathString) {
        LOG_ERROR("Failed to create IL2CPP string for catalog path!");
        return false;
    }
    
    // Call LoadContentCatalogAsync(catalogPath)
    void* params[] = { pathString };
    void* asyncOp = IL2CPPHelper::InvokeStaticMethod(s_LoadContentCatalogAsync, params);
    
    if (!asyncOp) {
        LOG_ERROR("Failed to invoke LoadContentCatalogAsync!");
        return false;
    }
    
    LOG_INFO("✓ Custom catalog load started (async operation: 0x%p)", asyncOp);
    
    // Notify callbacks
    for (auto& callback : s_CatalogLoadCallbacks) {
        callback(catalogPath);
    }
    
    return true;
}

void AddressablesHook::DumpAddressablesInfo() {
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Addressables System Info");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    if (s_AddressablesClass) {
        LOG_INFO("Addressables Class: FOUND");
        LOG_INFO("  Namespace: %s", IL2CPP::IL2CPPHelper::GetClassNamespace(s_AddressablesClass));
        LOG_INFO("  Name: %s", IL2CPP::IL2CPPHelper::GetClassName(s_AddressablesClass));
        LOG_INFO("  Methods:");
        LOG_INFO("    LoadContentCatalogAsync: %s", s_LoadContentCatalogAsync ? "FOUND" : "NOT FOUND");
        LOG_INFO("    LoadAssetAsync: %s", s_LoadAssetAsync ? "FOUND" : "NOT FOUND");
        LOG_INFO("    LoadSceneAsync: %s", s_LoadSceneAsync ? "FOUND" : "NOT FOUND");
    } else {
        LOG_INFO("Addressables Class: NOT FOUND");
    }
    
    if (s_ResourceManagerClass) {
        LOG_INFO("ResourceManager Class: FOUND");
        LOG_INFO("  Namespace: %s", IL2CPP::IL2CPPHelper::GetClassNamespace(s_ResourceManagerClass));
        LOG_INFO("  Name: %s", IL2CPP::IL2CPPHelper::GetClassName(s_ResourceManagerClass));
    } else {
        LOG_INFO("ResourceManager Class: NOT FOUND");
    }
    
    LOG_INFO("");
    LOG_INFO("Custom Catalogs: %zu registered", s_CustomCatalogs.size());
    for (const auto& catalog : s_CustomCatalogs) {
        LOG_INFO("  - %s", catalog.c_str());
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
}

} // namespace Addressables
} // namespace ModLoader
