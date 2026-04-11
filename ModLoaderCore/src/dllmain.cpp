#include <Windows.h>
#include "Log.h"
#include "ModManager.h"
#include "Hooks.h"
#include "IL2CPP.h"
#include "AddressablesHook.h"
#include <thread>

using namespace ModLoader;

/// Called when ModLoaderCore.dll is injected into game process
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {
            // Prove we loaded
            HANDLE hFile = CreateFileA("C:\\sbg_dll_loaded.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (hFile != INVALID_HANDLE_VALUE) {
                WriteFile(hFile, "OK\n", 3, nullptr, NULL);
                CloseHandle(hFile);
            }
            
            Log::Info("[CORE] ModLoaderCore.dll attached to process");
            Log::Info("[CORE] DllMain: DLL_PROCESS_ATTACH called with hModule=%p", hModule);
            
            // Keep DLL in memory by incrementing its reference count
            // This prevents the DLL from being unloaded unexpectedly
            char dllPath[MAX_PATH];
            GetModuleFileNameA(hModule, dllPath, MAX_PATH);
            LoadLibraryA(dllPath);  // Increment reference count
            Log::Info("[CORE] Incremented DLL reference count to prevent unload");
            
            // Initialize IL2CPP integration FIRST (required for everything else)
            Log::Info("[CORE] Initializing IL2CPP integration...");
            bool il2cppSuccess = IL2CPP::IL2CPPHelper::Initialize();
            if (il2cppSuccess) {
                Log::Info("[CORE] ✓ IL2CPP integration initialized!");
                
                // Dump loaded assemblies for debugging
                IL2CPP::IL2CPPHelper::DumpAssemblies();
                
                // Initialize Addressables hooks (for custom maps!)
                bool addressablesSuccess = Addressables::AddressablesHook::Initialize();
                if (addressablesSuccess) {
                    Log::Info("[CORE] ✓ Addressables hooks initialized!");
                    Addressables::AddressablesHook::DumpAddressablesInfo();
                } else {
                    Log::Info("[CORE] ⚠ Addressables hooks initialization failed (may not be loaded yet)");
                }
            } else {
                Log::Info("[CORE] ✗ IL2CPP integration failed! Some features will be unavailable.");
            }
            
            // Initialize hooks (overlay system)
            Hooks::Initialize();
            Log::Info("[CORE] Hooks initialized");
            
            // Initialize mod manager
            ModManager::Instance();
            Log::Info("[CORE] ModManager initialized");
            
            break;
        }
        
        case DLL_PROCESS_DETACH: {
            Log::Info("[CORE] ModLoaderCore.dll detaching");
            
            // Cleanup
            ModManager::Instance().UnloadAllMods();
            Hooks::Shutdown();
            
            Log::Info("[CORE] Cleanup complete");
            break;
        }
        
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    
    return TRUE;
}


