#include <Windows.h>
#include "Log.h"
#include "ModManager.h"
#include "Hooks.h"
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
            
            // Initialize hooks first (before any game initialization)
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


