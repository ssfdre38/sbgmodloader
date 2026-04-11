#include "Hooks.h"
#include "Log.h"
#include "ModManager.h"
#include <Windows.h>
#include <thread>

namespace ModLoader {

// Forward declarations from Overlay.cpp
void Overlay_Initialize();
void Overlay_Shutdown();

// NOTE: Original approach using RVAs from decompiled IL2CPP code FAILED
// Root cause: RVAs pointed to non-executable memory (PAGE_READONLY protection)
// The decompiled code was from a different build than the shipped binary
//
// SOLUTION: Use Win32 GDI overlay to draw mod loader version directly on game window
// This completely bypasses the need to hook IL2CPP methods

// Static flag to prevent double initialization
static bool g_overlayInitialized = false;

void Hooks::Initialize() {
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Initializing Mod Loader Display System");
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Method: Win32 Window Title Modification");
    LOG_INFO("");
    
    // Prevent double initialization
    if (g_overlayInitialized) {
        LOG_INFO("Already initialized, skipping");
        return;
    }
    g_overlayInitialized = true;
    
    // Wait for game window to be created, then attach overlay
    std::thread overlayThread([]() {
        LOG_INFO("Overlay thread started - waiting for game window...");
        
        // Game takes time to create window - wait up to 30 seconds
        for (int attempt = 0; attempt < 60; attempt++) {
            Sleep(500);  // Check every 0.5 seconds
            
            // Try to find Unity window
            HWND gameWindow = FindWindowA("UnityWndClass", nullptr);
            
            if (!gameWindow) {
                // Also try finding by enumerating process windows
                DWORD processId = GetCurrentProcessId();
                EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
                    DWORD windowProcessId;
                    GetWindowThreadProcessId(hwnd, &windowProcessId);
                    
                    DWORD* pProcessId = (DWORD*)lParam;
                    if (windowProcessId == *pProcessId && IsWindowVisible(hwnd)) {
                        char windowTitle[256];
                        GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
                        
                        // Look for main game window (has title, visible, not a child)
                        if (strlen(windowTitle) > 0 && GetParent(hwnd) == nullptr) {
                            // Store in second DWORD of lParam
                            *(HWND*)(pProcessId + 1) = hwnd;
                            return FALSE;  // Stop enumeration
                        }
                    }
                    
                    return TRUE;  // Continue
                }, (LPARAM)&processId);
                
                // Check if we found a window
                gameWindow = *(HWND*)((DWORD*)&processId + 1);
            }
            
            if (gameWindow) {
                char windowTitle[256];
                GetWindowTextA(gameWindow, windowTitle, sizeof(windowTitle));
                LOG_INFO("✓ Found game window after %d attempts (%.1f seconds)", 
                         attempt + 1, (attempt + 1) * 0.5);
                LOG_INFO("  Window: '%s' (HWND: 0x%p)", windowTitle, gameWindow);
                LOG_INFO("");
                
                // Initialize overlay
                Overlay_Initialize();
                
                // Initialize mod system after overlay is ready
                LOG_INFO("");
                LOG_INFO("Initializing mod manager...");
                ModManager::Instance().InitializeAllMods();
                
                return;
            }
        }
        
        LOG_INFO("✗ Timeout waiting for game window (30 seconds)");
        LOG_INFO("  Overlay will not be initialized");
    });
    
    overlayThread.detach();
    
    LOG_INFO("✓ Mod loader initialized (overlay mode)");
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("");
}

void Hooks::Shutdown() {
    LOG_INFO("Shutting down mod loader...");
    Overlay_Shutdown();
    LOG_INFO("✓ Mod loader shutdown complete");
}

// Deprecated methods (kept for interface compatibility)
void Hooks::HookGameManagerAwake() {
    // No longer used - overlay approach doesn't need IL2CPP hooks
}

void Hooks::HookGameUpdate() {
    // No longer used - overlay approach doesn't need IL2CPP hooks
}

void Hooks::OnGameInitialized() {
    // No longer used - mod initialization happens in overlay thread
}

void Hooks::OnGameUpdate(float deltaTime) {
    // Could be used for per-frame mod updates if needed
    ModManager::Instance().UpdateAllMods(deltaTime);
}

} // namespace ModLoader
