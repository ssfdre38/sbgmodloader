#include <Windows.h>
#include "Log.h"
#include "MonoHelper.h"
#include "ModManager.h"
#include "Hooks.h"

using namespace ModLoader;

namespace {

DWORD WINAPI InitializeModLoaderThread(LPVOID) {
    Log::Info("[CORE] ModLoaderCore.dll attached to process");
    Log::Info("[CORE] Starting deferred initialization thread");

    // Detect Mono runtime (mono-2.0-bdwgc.dll)
    // Super Battle Golf is a Mono build, not IL2CPP
    HMODULE monoRuntime = nullptr;
    for (int attempt = 0; attempt < 120; ++attempt) {
        monoRuntime = GetModuleHandleA("mono-2.0-bdwgc.dll");
        if (monoRuntime) {
            break;
        }

        Sleep(500);
    }

    if (monoRuntime) {
        Log::Info("[CORE] Mono runtime detected at 0x%p", monoRuntime);
        Log::Info("[CORE] Initializing Mono integration...");

        bool monoSuccess = Mono::MonoHelper::Initialize(monoRuntime);
        if (monoSuccess) {
            Log::Info("[CORE] ✓ Mono integration initialized!");
            Mono::MonoHelper::DumpAssemblies();
            
            Log::Info("");
            Log::Info("✅ Mono integration ready!");
            Log::Info("");
        } else {
            Log::Info("[CORE] Mono integration failed; continuing without Mono features");
        }
    } else {
        Log::Info("[CORE] Mono runtime was not detected within startup timeout");
    }

    Hooks::Initialize();
    Log::Info("[CORE] Hooks initialized");

    // Get game install directory for Mods folder
    char gameDir[MAX_PATH];
    GetModuleFileNameA(nullptr, gameDir, MAX_PATH);
    std::string gamePath(gameDir);
    size_t lastSlash = gamePath.find_last_of("\\/");
    std::string modsPath = gamePath.substr(0, lastSlash) + "\\Mods";
    
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════════════");
    Log::Info("🎮 Super Battle Golf Mod Loader");
    Log::Info("═══════════════════════════════════════════════════════");
    Log::Info("Game Directory: %s", gamePath.substr(0, lastSlash).c_str());
    Log::Info("Mods Directory: %s", modsPath.c_str());
    Log::Info("");
    
    // Discover and load mods
    ModManager::Instance().DiscoverMods(modsPath);
    ModManager::Instance().LoadAllMods();
    ModManager::Instance().InitializeAllMods();
    
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════════════");
    Log::Info("✅ Mod Loader Initialization Complete");
    Log::Info("═══════════════════════════════════════════════════════");
    Log::Info("");

    return 0;
}

} // namespace

/// Called when ModLoaderCore.dll is injected into game process
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(hModule);

            HANDLE initThread = CreateThread(nullptr, 0, InitializeModLoaderThread, nullptr, 0, nullptr);
            if (initThread) {
                CloseHandle(initThread);
            }
            break;
        }
        case DLL_PROCESS_DETACH:
            ModManager::Instance().UnloadAllMods();
            break;
    }
    return TRUE;
}
