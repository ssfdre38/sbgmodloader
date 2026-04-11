#include "..\ModSDK\include\IModModule.h"
#include "..\ThirdParty\include\il2cpp-api.h"
#include <Windows.h>
#include <cstdio>
#include <cstring>

// Version display mod that appends mod loader version to the game version label
class VersionDisplayMod : public ModSDK::IModModule {
private:
    const char* mod_id = "version-display";
    const char* mod_name = "Mod Loader Version Display";
    const char* mod_version = "0.1.0";
    const char* mod_loader_version = "sbg-mod-loader-0.1.0-beta";
    bool initialized = false;

public:
    const char* GetId() const override {
        return mod_id;
    }

    const char* GetName() const override {
        return mod_name;
    }

    const char* GetVersion() const override {
        return mod_version;
    }

    void OnLoad() override {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "[VersionDisplayMod] OnLoad - Mod Loader v%s\n", mod_loader_version);
        OutputDebugStringA(buffer);
        
        initialized = true;
    }

    void OnUnload() override {
        OutputDebugStringA("[VersionDisplayMod] OnUnload called\n");
        initialized = false;
    }

    void OnUpdate(float deltaTime) override {
        // Called every frame
    }

    void OnLateUpdate(float deltaTime) override {
        // Called after update
    }

    void OnSceneLoaded(const char* sceneName) override {
        if (!sceneName || !initialized) return;
        
        char buffer[512];
        snprintf(buffer, sizeof(buffer), "[VersionDisplayMod] Scene loaded: %s\n", sceneName);
        OutputDebugStringA(buffer);
        
        // Try to update version display on main menu and in-game scenes
        if (strcmp(sceneName, "MainMenu") == 0 || 
            strcmp(sceneName, "MainMenuScene") == 0 ||
            strcmp(sceneName, "GameplayScene") == 0) {
            
            snprintf(buffer, sizeof(buffer), "[VersionDisplayMod] Attempting to update version label for scene: %s\n", sceneName);
            OutputDebugStringA(buffer);
            
            // In the future, this would use IL2CPP API to:
            // 1. Find the GameVersionLabel component
            // 2. Get its text field
            // 3. Append mod loader version
            // For now, just log that we're ready
            snprintf(buffer, sizeof(buffer), "[VersionDisplayMod] ✓ Mod Loader v%s is active\n", mod_loader_version);
            OutputDebugStringA(buffer);
        }
    }
};

// Export factory functions so ModManager can load this DLL
extern "C" {
    __declspec(dllexport) ModSDK::IModModule* CreateModInstance() {
        return new VersionDisplayMod();
    }

    __declspec(dllexport) void DestroyModInstance(ModSDK::IModModule* instance) {
        delete instance;
    }
}

