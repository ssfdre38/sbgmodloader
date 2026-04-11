#pragma once
#include <cstdint>

namespace ModLoader {

/// Detours hook management
class Hooks {
public:
    /// Initialize all hooks (call early in DLL injection)
    static void Initialize();
    
    /// Remove all hooks (call on cleanup)
    static void Shutdown();
    
    /// Callback when game initializes (called from hooked method)
    static void OnGameInitialized();
    
    /// Callback when game updates
    static void OnGameUpdate(float deltaTime);

private:
    /// Hook on GameManager::Awake
    static void HookGameManagerAwake();
    
    /// Hook on game Update loop
    static void HookGameUpdate();
};

}  // namespace ModLoader
