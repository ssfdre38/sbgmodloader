#pragma once
#include "IL2CPP.h"
#include <string>
#include <vector>
#include <functional>

namespace ModLoader {
namespace Addressables {

// Callback types for addressables hooks
using OnCatalogLoadCallback = std::function<void(const char* catalogPath)>;
using OnAssetLoadCallback = std::function<void(const char* assetKey)>;
using OnSceneLoadCallback = std::function<void(const char* scenePath)>;

class AddressablesHook {
public:
    // Initialize Addressables hooks
    static bool Initialize();
    
    // Check if hooks are active
    static bool IsInitialized() { return s_Initialized; }
    
    // Register custom catalog (will be injected when game loads catalogs)
    static void RegisterCustomCatalog(const char* catalogPath);
    
    // Get all registered custom catalogs
    static const std::vector<std::string>& GetCustomCatalogs() { return s_CustomCatalogs; }
    
    // Register callbacks
    static void OnCatalogLoad(OnCatalogLoadCallback callback);
    static void OnAssetLoad(OnAssetLoadCallback callback);
    static void OnSceneLoad(OnSceneLoadCallback callback);
    
    // Manually load a custom catalog (for testing)
    static bool LoadCustomCatalog(const char* catalogPath);
    
    // Get addressables system info
    static void DumpAddressablesInfo();
    
private:
    static bool s_Initialized;
    static std::vector<std::string> s_CustomCatalogs;
    static std::vector<OnCatalogLoadCallback> s_CatalogLoadCallbacks;
    static std::vector<OnAssetLoadCallback> s_AssetLoadCallbacks;
    static std::vector<OnSceneLoadCallback> s_SceneLoadCallbacks;
    
    // IL2CPP class/method pointers
    static IL2CPP::Il2CppClass* s_AddressablesClass;
    static IL2CPP::Il2CppClass* s_ResourceManagerClass;
    static IL2CPP::Il2CppClass* s_AsyncOperationClass;
    static IL2CPP::Il2CppMethodInfo* s_LoadContentCatalogAsync;
    static IL2CPP::Il2CppMethodInfo* s_LoadAssetAsync;
    static IL2CPP::Il2CppMethodInfo* s_LoadSceneAsync;
    
    // Hook the addressables system
    static bool HookAddressablesAPI();
    
    // Find addressables classes and methods
    static bool FindAddressablesClasses();
};

} // namespace Addressables
} // namespace ModLoader
