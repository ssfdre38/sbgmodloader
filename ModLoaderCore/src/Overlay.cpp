#include <Windows.h>
#include <string>
#include "../include/Log.h"

namespace ModLoader {

static HWND g_gameWindow = nullptr;
static WNDPROC g_originalWndProc = nullptr;
static HDC g_overlayDC = nullptr;
static HFONT g_font = nullptr;

static int g_paintCallCount = 0;

// Window procedure hook to draw overlay
LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // After game draws, add our overlay
    if (msg == WM_PAINT) {
        g_paintCallCount++;
        if (g_paintCallCount <= 5) {
            Log::Info("WM_PAINT received (count: %d)", g_paintCallCount);
        }
        
        // Let game paint first
        LRESULT result = CallWindowProc(g_originalWndProc, hwnd, msg, wParam, lParam);
        
        // Now draw our overlay on top
        HDC hdc = GetDC(hwnd);
        if (hdc) {
            // Set text properties
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 0)); // Yellow text
            
            // Select font
            HFONT oldFont = (HFONT)SelectObject(hdc, g_font);
            
            // Draw mod loader version in bottom-left corner
            RECT windowRect;
            GetClientRect(hwnd, &windowRect);
            
            // Position: bottom-left, offset from game version
            int x = 10;
            int y = windowRect.bottom - 60;
            
            std::string versionText = "Mod Loader v0.1.0-beta";
            int drawResult = TextOutA(hdc, x, y, versionText.c_str(), (int)versionText.length());
            
            if (g_paintCallCount <= 5) {
                Log::Info("Drew text at (%d,%d), window size: %dx%d, TextOut result: %d", 
                          x, y, windowRect.right, windowRect.bottom, drawResult);
            }
            
            // Restore font
            SelectObject(hdc, oldFont);
            
            ReleaseDC(hwnd, hdc);
        } else {
            if (g_paintCallCount <= 5) {
                Log::Info("GetDC failed!");
            }
        }
        
        return result;
    }
    
    // For all other messages, just call original
    return CallWindowProc(g_originalWndProc, hwnd, msg, wParam, lParam);
}

void Overlay_Initialize() {
    Log::Info("Initializing mod loader visibility indicator...");
    
    // Find the game window
    g_gameWindow = FindWindowA("UnityWndClass", nullptr);
    
    if (!g_gameWindow) {
        // Try finding by process
        DWORD processId = GetCurrentProcessId();
        
        EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
            DWORD windowProcessId;
            GetWindowThreadProcessId(hwnd, &windowProcessId);
            
            if (windowProcessId == (DWORD)lParam && IsWindowVisible(hwnd)) {
                char windowTitle[256];
                GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
                
                // Look for main game window (has title)
                if (strlen(windowTitle) > 0 && GetParent(hwnd) == nullptr) {
                    g_gameWindow = hwnd;
                    return FALSE;  // Stop enumeration
                }
            }
            
            return TRUE;  // Continue
        }, (LPARAM)processId);
    }
    
    if (!g_gameWindow) {
        Log::Info("✗ Failed to find game window");
        return;
    }
    
    char originalTitle[256];
    GetWindowTextA(g_gameWindow, originalTitle, sizeof(originalTitle));
    Log::Info("✓ Found game window: '%s' (HWND: 0x%p)", originalTitle, g_gameWindow);
    
    // Check if we've already modified the title (prevent duplication)
    std::string currentTitle(originalTitle);
    if (currentTitle.find("[Mod Loader") != std::string::npos) {
        Log::Info("✓ Window title already contains mod loader indicator - skipping");
        return;
    }
    
    // SIMPLE TEST: Modify window title to prove mod loader is active
    std::string newTitle = std::string(originalTitle) + " [Mod Loader v0.1.0-beta]";
    SetWindowTextA(g_gameWindow, newTitle.c_str());
    
    Log::Info("✓✓✓ Window title updated to show mod loader is active! ✓✓✓");
    Log::Info("Old title: '%s'", originalTitle);
    Log::Info("New title: '%s'", newTitle.c_str());
    Log::Info("");
    Log::Info("👀 Check the game window title bar - it should show '[Mod Loader v0.1.0-beta]'");
}

void Overlay_Shutdown() {
    Log::Info("Shutting down mod loader indicator...");
    
    if (g_gameWindow) {
        // Restore original window title
        char currentTitle[256];
        GetWindowTextA(g_gameWindow, currentTitle, sizeof(currentTitle));
        
        // Remove the mod loader suffix if present
        std::string title(currentTitle);
        size_t pos = title.find(" [Mod Loader");
        if (pos != std::string::npos) {
            title = title.substr(0, pos);
            SetWindowTextA(g_gameWindow, title.c_str());
            Log::Info("✓ Restored original window title");
        }
        
        g_gameWindow = nullptr;
    }
    
    Log::Info("✓ Mod loader indicator shutdown complete");
}

} // namespace ModLoader
