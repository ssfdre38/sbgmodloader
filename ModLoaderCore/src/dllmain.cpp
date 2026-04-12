#include <Windows.h>
#include "Log.h"
#include "MonoHelper.h"
#include "ModManager.h"
#include "Hooks.h"
#include "GameExplorer.h"
#include "SceneHooks.h"
#include "GameModeManager.h"
#include "UIOverlay.h"

using namespace ModLoader;

namespace {

// Global flag to control update loop
static bool g_UpdateLoopRunning = true;

// UI test loop - tries to inject version text periodically
DWORD WINAPI UITestLoopThread(LPVOID) {
    Log::Info("[CORE] UI test loop thread started");
    
    // Wait for game to get to main menu
    Log::Info("[CORE] Waiting 30 seconds for game to reach main menu...");
    Sleep(30000);
    Log::Info("[CORE] Starting UI injection test loop");
    
    int attemptCount = 0;
    while (g_UpdateLoopRunning) {
        attemptCount++;
        Log::Info("[CORE] UI injection attempt #%d", attemptCount);
        
        // Try to inject version text
        UIOverlay::TestAddVersionText();
        
        // Try every 10 seconds until successful
        Sleep(10000);
    }
    
    Log::Info("[CORE] UI test loop thread exiting");
    return 0;
}

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
            
            // Explore game architecture
            Log::Info("[CORE] Exploring game architecture...");
            GameExplorer::ExploreGame();
            
            // Deep inspection of game mode system
            Log::Info("[CORE] Inspecting game mode system...");
            GameExplorer::InspectGameModeSystem();
            
            // Export findings to file
            std::string exportPath = std::string(getenv("APPDATA")) + "\\sbg-mod-loader\\game-architecture.md";
            GameExplorer::ExportToFile(exportPath.c_str());
            Log::Info("");
            
            // Initialize scene hooks
            Log::Info("[CORE] Initializing scene hooks...");
            SceneHooks::Initialize();
            
            // Initialize game mode manager
            Log::Info("[CORE] Initializing game mode manager...");
            GameModeManager::Initialize();
            
            // Start UI test loop thread
            HANDLE uiTestThread = CreateThread(nullptr, 0, UITestLoopThread, nullptr, 0, nullptr);
            if (uiTestThread) {
                CloseHandle(uiTestThread);
                Log::Info("[CORE] UI test loop thread started");
            }
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
    
    // Pass discovered mods to GameModeManager
    Log::Info("[CORE] Loading custom game modes...");
    GameModeManager::LoadGameModes(ModManager::Instance().GetDiscoveredMods());
    
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
            g_UpdateLoopRunning = false;
            Sleep(100); // Give update thread time to exit
            ModManager::Instance().UnloadAllMods();
            break;
    }
    return TRUE;
}
