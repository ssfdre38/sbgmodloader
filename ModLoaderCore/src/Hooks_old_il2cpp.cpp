#include "Hooks.h"
#include "Log.h"
#include "ModManager.h"
#include <detours.h>
#include <Windows.h>
#include <psapi.h>
#include <thread>
#include <chrono>
#include <string>

namespace ModLoader {

// Forward declarations
void Overlay_Initialize();
void Overlay_Shutdown();

// NOTE: Original approach using RVAs from decompiled code failed
// The RVAs pointed to non-executable memory (PAGE_READONLY) instead of actual code
// Root cause: Decompiled assembly was from different build or IL2CPP reorganized code
// 
// NEW APPROACH: Use Win32 GDI overlay to draw version directly on game window
// This bypasses the need to hook game-specific IL2CPP methods entirely

void Hooks::Initialize() {
    LOG_INFO("Initializing mod loader display system...");
    LOG_INFO("Using Win32 overlay approach (IL2CPP hook RVAs were invalid)");
    
    // Wait for game window to be created
    std::thread overlayThread([]() {
        LOG_INFO("Overlay thread started - waiting for game window...");
        
        // Game takes time to create window - wait up to 30 seconds
        for (int attempt = 0; attempt < 60; attempt++) {
            Sleep(500);  // Check every 0.5 seconds
            
            // Try to find Unity window
            HWND gameWindow = FindWindowA("UnityWndClass", nullptr);
            
            if (!gameWindow) {
                // Also try finding by enumerating all windows
                DWORD processId = GetCurrentProcessId();
                EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
                    DWORD windowProcessId;
                    GetWindowThreadProcessId(hwnd, &windowProcessId);
                    
                    if (windowProcessId == (DWORD)lParam && IsWindowVisible(hwnd)) {
                        char windowTitle[256];
                        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
                        
                        // Look for main game window (has title, visible, not a child)
                        if (strlen(windowTitle) > 0 && GetParent(hwnd) == nullptr) {
                            *(HWND*)lParam = hwnd;  // Store window handle
                            return FALSE;  // Stop enumeration
                        }
                    }
                    
                    return TRUE;  // Continue
                }, (LPARAM)&gameWindow);
            }
            
            if (gameWindow) {
                char windowTitle[256];
                GetWindowTextA(gameWindow, windowTitle, sizeof(windowTitle));
                LOG_INFO("✓ Found game window after %d attempts: '%s'", attempt + 1, windowTitle);
                
                // Initialize overlay
                Overlay_Initialize();
                
                // Initialize mod system after overlay is ready
                LOG_INFO("Initializing mod manager...");
                ModManager::Get().InitializeAllMods();
                
                return;
            }
        }
        
        LOG_INFO("✗ Timeout waiting for game window - overlay not initialized");
    });
    
    overlayThread.detach();
    
    LOG_INFO("✓ Mod loader initialized (overlay mode)");
}

// Function pointer for the original GameManager::Awake method
typedef void(*GameManagerAwakeOriginal)(void* thisPtr);
GameManagerAwakeOriginal original_GameManager_Awake = nullptr;

// Function pointer for the original GameVersionLabel::GetVersion method
typedef Il2CppString*(*GameVersionGetVersionOriginal)(bool shorten);
GameVersionGetVersionOriginal original_GameVersion_GetVersion = nullptr;

// Function pointer for the original GameVersionLabel::Awake method
typedef void(*GameVersionAwakeOriginal)(void* thisPtr);
GameVersionAwakeOriginal original_GameVersion_Awake = nullptr;

// Hooked GameManager::Awake function
void WINAPI Hooked_GameManager_Awake(void* thisPtr) {
    LOG_INFO("=== HOOKED: GameManager::Awake called! ===");
    
    // Call the original method
    if (original_GameManager_Awake) {
        LOG_INFO("Calling original GameManager::Awake...");
        original_GameManager_Awake(thisPtr);
        LOG_INFO("Original GameManager::Awake completed");
    }
    
    // Now trigger mod initialization
    LOG_INFO("Triggering mod initialization...");
    Hooks::OnGameInitialized();
}

// Hooked GameVersionLabel::Awake function
// This is called when the version label UI component initializes
void WINAPI Hooked_GameVersionLabel_Awake(void* thisPtr) {
    LOG_INFO("╔════════════════════════════════════════════════════════════╗");
    LOG_INFO("║ ✓✓✓ HOOKED: GameVersionLabel::Awake called! ✓✓✓          ║");
    LOG_INFO("║ This is where the version label UI is initialized           ║");
    LOG_INFO("║ Mod Loader can now inject version string here               ║");
    LOG_INFO("╚════════════════════════════════════════════════════════════╝");
    
    // Call the original method to set up the UI
    if (original_GameVersion_Awake) {
        LOG_INFO("Calling original GameVersionLabel::Awake...");
        original_GameVersion_Awake(thisPtr);
        LOG_INFO("Original GameVersionLabel::Awake completed");
        LOG_INFO("✓✓✓ Version label UI is now visible on screen ✓✓✓");
    }
}

// Hooked GameVersionLabel::GetVersion function
// This hook is kept minimal - we instead hook the Awake method to modify the UI text
Il2CppString* WINAPI Hooked_GameVersionLabel_GetVersion(bool shorten) {
    LOG_INFO("=== HOOKED: GameVersionLabel::GetVersion called! ===");
    
    // Call the original method to get the base version string
    Il2CppString* baseVersion = nullptr;
    if (original_GameVersion_GetVersion) {
        baseVersion = original_GameVersion_GetVersion(shorten);
        LOG_INFO("Original GetVersion returned result");
    }
    
    // Return the original version - the mod loader version will be appended
    // by the VersionDisplayMod when it handles the scene load event
    if (baseVersion) {
        LOG_INFO("✓ Version label hooked - mod loader version will be displayed");
        return baseVersion;
    }
    
    return nullptr;
}

void Hooks::Initialize() {
    LOG_INFO("Initializing Detours hooks...");
    
    // Start a background thread to hook GameManager::Awake once GameAssembly.dll loads
    std::thread hookThread([]() {
        LOG_INFO("Hook thread started - waiting for GameAssembly.dll...");
        
        // Keep trying for up to 60 seconds (game takes time to initialize)
        for (int attempt = 0; attempt < 60; attempt++) {
            Sleep(1000);  // Wait 1 second between attempts
            
            // Try method 1: GetModuleHandleA (standard approach)
            HMODULE gameAssembly = GetModuleHandleA("GameAssembly.dll");
            
            // Try method 2: Load from known path if method 1 fails
            if (!gameAssembly) {
                // The DLL might be in a specific folder that Windows loader knows about
                // Try to load it explicitly from the game data directory
                gameAssembly = LoadLibraryA("Super Battle Golf_Data\\Managed\\GameAssembly.dll");
                
                if (gameAssembly) {
                    LOG_INFO("✓ Loaded GameAssembly.dll from relative path on attempt %d", attempt + 1);
                }
            } else {
                LOG_INFO("✓ Found GameAssembly.dll via GetModuleHandleA on attempt %d!", attempt + 1);
            }
            
            if (gameAssembly) {
                // === DIAGNOSTIC: Check if our target RVA points to valid code ===
                LOG_INFO("═══════════════════════════════════════════════════════");
                LOG_INFO("DIAGNOSTIC: Verifying RVA addresses point to valid code");
                LOG_INFO("═══════════════════════════════════════════════════════");
                
                MODULEINFO modInfo = {};
                GetModuleInformation(GetCurrentProcess(), gameAssembly, &modInfo, sizeof(modInfo));
                LOG_INFO("GameAssembly.dll loaded at: 0x%p", gameAssembly);
                LOG_INFO("Module size: %llu bytes (%.2f MB)", modInfo.SizeOfImage, modInfo.SizeOfImage / (1024.0 * 1024.0));
                
                // Check each RVA we're trying to hook
                uintptr_t baseAddr = (uintptr_t)gameAssembly;
                
                struct RVACheck {
                    const char* name;
                    uintptr_t rva;
                };
                
                RVACheck checks[] = {
                    {"GameManager::Awake", GAMEMANAGER_AWAKE_RVA},
                    {"GameVersionLabel::GetVersion", GAMEVERSION_GETVERSION_RVA},
                    {"GameVersionLabel::Awake", GAMEVERSION_AWAKE_RVA}
                };
                
                for (int i = 0; i < 3; i++) {
                    void* addr = (void*)(baseAddr + checks[i].rva);
                    LOG_INFO("");
                    LOG_INFO("Checking %s:", checks[i].name);
                    LOG_INFO("  RVA: 0x%08X", checks[i].rva);
                    LOG_INFO("  Absolute: 0x%p", addr);
                    
                    // Check if address is within module bounds
                    if (checks[i].rva >= modInfo.SizeOfImage) {
                        LOG_INFO("  ✗ RVA OUTSIDE MODULE BOUNDS! (module size: 0x%X)", modInfo.SizeOfImage);
                        continue;
                    }
                    
                    // Check if memory is executable
                    MEMORY_BASIC_INFORMATION mbi;
                    if (VirtualQuery(addr, &mbi, sizeof(mbi))) {
                        bool isExecutable = (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)) != 0;
                        LOG_INFO("  Memory protection: 0x%X %s", mbi.Protect, isExecutable ? "(executable)" : "(NOT executable!)");
                        
                        if (!isExecutable) {
                            LOG_INFO("  ✗ MEMORY IS NOT EXECUTABLE - THIS RVA IS WRONG!");
                        } else {
                            // Read first few bytes to see if it looks like code
                            BYTE bytes[16];
                            SIZE_T bytesRead;
                            if (ReadProcessMemory(GetCurrentProcess(), addr, bytes, 16, &bytesRead) && bytesRead == 16) {
                                LOG_INFO("  First 16 bytes: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",
                                    bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7],
                                    bytes[8], bytes[9], bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]);
                                
                                // Check for common x64 function prologues
                                bool looksLikeCode = false;
                                if (bytes[0] == 0x48 && bytes[1] == 0x89) looksLikeCode = true; // mov [rsp+??], rbx
                                if (bytes[0] == 0x48 && bytes[1] == 0x83 && bytes[2] == 0xEC) looksLikeCode = true; // sub rsp, ??
                                if (bytes[0] == 0x40 && bytes[1] == 0x53) looksLikeCode = true; // push rbx (with REX)
                                if (bytes[0] == 0x55) looksLikeCode = true; // push rbp
                                
                                LOG_INFO("  %s", looksLikeCode ? "✓ Looks like valid x64 code" : "✗ DOES NOT look like code!");
                            }
                        }
                    }
                }
                
                LOG_INFO("═══════════════════════════════════════════════════════");
                LOG_INFO("");
                
                // Calculate absolute address: base + RVA
                PVOID targetFunction = (PVOID)((uintptr_t)gameAssembly + GAMEMANAGER_AWAKE_RVA);
                
                LOG_INFO("GameManager::Awake address calculation:");
                LOG_INFO("  Module base: 0x%p", gameAssembly);
                LOG_INFO("  RVA: 0x%X", GAMEMANAGER_AWAKE_RVA);
                LOG_INFO("  Absolute address: 0x%p", targetFunction);
                
                // Attach the Detours hook
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                
                LONG attach_result = DetourAttach(&(PVOID&)targetFunction, Hooked_GameManager_Awake);
                if (attach_result != NO_ERROR) {
                    LOG_INFO("ERROR: DetourAttach failed with code 0x%X", attach_result);
                    DetourTransactionAbort();
                    return;
                }
                
                LONG commit_result = DetourTransactionCommit();
                if (commit_result != NO_ERROR) {
                    LOG_INFO("ERROR: DetourTransactionCommit failed with code 0x%X", commit_result);
                    return;
                }
                
                // Store the original function pointer
                original_GameManager_Awake = (GameManagerAwakeOriginal)targetFunction;
                
                LOG_INFO("✓✓✓ DETOURS HOOK ACTIVATED SUCCESSFULLY ✓✓✓");
                LOG_INFO("GameManager::Awake will trigger mod loader when called");
                
                // Now hook GameVersionLabel::GetVersion to show mod loader version
                LOG_INFO("Setting up GameVersionLabel::GetVersion hook...");
                PVOID versionFunction = (PVOID)((uintptr_t)gameAssembly + GAMEVERSION_GETVERSION_RVA);
                
                LOG_INFO("GameVersionLabel::GetVersion address calculation:");
                LOG_INFO("  Module base: 0x%p", gameAssembly);
                LOG_INFO("  RVA: 0x%X", GAMEVERSION_GETVERSION_RVA);
                LOG_INFO("  Absolute address: 0x%p", versionFunction);
                
                // Attach the version label hook
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                
                LONG version_attach = DetourAttach(&(PVOID&)versionFunction, Hooked_GameVersionLabel_GetVersion);
                if (version_attach != NO_ERROR) {
                    LOG_INFO("WARNING: Failed to hook GameVersionLabel::GetVersion (code 0x%X)", version_attach);
                    DetourTransactionAbort();
                } else {
                    LONG version_commit = DetourTransactionCommit();
                    if (version_commit == NO_ERROR) {
                        original_GameVersion_GetVersion = (GameVersionGetVersionOriginal)versionFunction;
                        LOG_INFO("✓ GameVersionLabel::GetVersion hook attached successfully");
                    } else {
                        LOG_INFO("WARNING: Failed to commit version label hook (code 0x%X)", version_commit);
                    }
                }
                
                // Now hook GameVersionLabel::Awake to detect when version label is displayed
                LOG_INFO("Setting up GameVersionLabel::Awake hook...");
                PVOID versionAwakeFunction = (PVOID)((uintptr_t)gameAssembly + GAMEVERSION_AWAKE_RVA);
                
                LOG_INFO("GameVersionLabel::Awake address calculation:");
                LOG_INFO("  Module base: 0x%p", gameAssembly);
                LOG_INFO("  RVA: 0x%X", GAMEVERSION_AWAKE_RVA);
                LOG_INFO("  Absolute address: 0x%p", versionAwakeFunction);
                
                // Attach the version label Awake hook
                DetourTransactionBegin();
                DetourUpdateThread(GetCurrentThread());
                
                LONG awake_attach = DetourAttach(&(PVOID&)versionAwakeFunction, Hooked_GameVersionLabel_Awake);
                if (awake_attach != NO_ERROR) {
                    LOG_INFO("WARNING: Failed to hook GameVersionLabel::Awake (code 0x%X)", awake_attach);
                    DetourTransactionAbort();
                } else {
                    LONG awake_commit = DetourTransactionCommit();
                    if (awake_commit == NO_ERROR) {
                        original_GameVersion_Awake = (GameVersionAwakeOriginal)versionAwakeFunction;
                        LOG_INFO("✓✓✓ GameVersionLabel::Awake hook attached successfully ✓✓✓");
                    } else {
                        LOG_INFO("WARNING: Failed to commit version label Awake hook (code 0x%X)", awake_commit);
                    }
                }
                
                return;
            }
            
            if (attempt % 10 == 0 && attempt > 0) {
                LOG_INFO("Still waiting for GameAssembly.dll... (attempt %d/60)", attempt);
            }
        }
        
        LOG_INFO("ERROR: Timeout waiting for GameAssembly.dll (60 seconds)");
        LOG_INFO("The DLL may not be loaded, or might use a different loading mechanism");
        LOG_INFO("Hook will not be activated");
    });
    
    // Detach thread - let it run in background
    hookThread.detach();
}

void Hooks::Shutdown() {
    LOG_INFO("Shutting down hooks");
    
    if (original_GameManager_Awake) {
        PVOID targetFunction = (PVOID)original_GameManager_Awake;
        
        // Detach the hook
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)targetFunction, Hooked_GameManager_Awake);
        DetourTransactionCommit();
        
        LOG_INFO("✓ GameManager::Awake hook detached successfully");
    }
    
    if (original_GameVersion_GetVersion) {
        PVOID versionFunction = (PVOID)original_GameVersion_GetVersion;
        
        // Detach the version label hook
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)versionFunction, Hooked_GameVersionLabel_GetVersion);
        DetourTransactionCommit();
        
        LOG_INFO("✓ GameVersionLabel::GetVersion hook detached successfully");
    }
    
    if (original_GameVersion_Awake) {
        PVOID awakeFunction = (PVOID)original_GameVersion_Awake;
        
        // Detach the version label Awake hook
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)awakeFunction, Hooked_GameVersionLabel_Awake);
        DetourTransactionCommit();
        
        LOG_INFO("✓ GameVersionLabel::Awake hook detached successfully");
    }
}

void Hooks::HookGameManagerAwake() {
    // This is called by Initialize() now
}

void Hooks::HookGameUpdate() {
    LOG_INFO("Setting up game Update hook via Detours...");
    // TODO: Find and hook game update method for continuous mod updates
}

void Hooks::OnGameInitialized() {
    LOG_INFO("========== GAME INITIALIZED ==========");
    LOG_INFO("Loading mods from ./Mods directory...");
    
    std::string modsPath = "./Mods";
    LOG_INFO("Current working directory and mod search path: %s", modsPath.c_str());
    
    // Get actual filesystem path for debugging
    char currentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentDir);
    LOG_INFO("Actual current working directory: %s", currentDir);
    LOG_INFO("Will search for mods at: %s\\%s", currentDir, modsPath.c_str());
    
    ModManager::Instance().DiscoverMods(modsPath);
    ModManager::Instance().InitializeAllMods();
    
    LOG_INFO("========== MOD LOADING COMPLETE ==========");
}

void Hooks::OnGameUpdate(float deltaTime) {
    ModManager::Instance().UpdateAllMods(deltaTime);
}

}  // namespace ModLoader
