#include "IModModule.h"

using namespace ModSDK;

/// Test mod that displays version info
class VersionDisplayMod : public IModModule {
public:
    const char* GetId() const override {
        return "version-display";
    }
    
    const char* GetName() const override {
        return "SBG Mod Loader - Version Display";
    }
    
    const char* GetVersion() const override {
        return "0.1.0-beta";
    }
    
    void OnLoad() override {
        // Version display mod loaded
    }
    
    void OnUnload() override {
        // Version display mod unloaded
    }
    
    void OnUpdate(float deltaTime) override {
        // Called every frame
    }
    
    void OnLateUpdate(float deltaTime) override {
        // Called after update
    }
    
    void OnSceneLoaded(const char* sceneName) override {
        // Called when scene loads
    }
};

// Export factory functions so ModManager can load this DLL
extern "C" {
    __declspec(dllexport) IModModule* CreateModInstance() {
        return new VersionDisplayMod();
    }
    
    __declspec(dllexport) void DestroyModInstance(IModModule* instance) {
        delete instance;
    }
}
