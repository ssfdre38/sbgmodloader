#pragma once
#include <string>
#include <vector>
#include <functional>

// Forward declarations for Mono types
typedef void* MonoClass;
typedef void* MonoMethod;
typedef void* MonoProperty;

/**
 * SceneHooks - Unity Scene Management Integration
 * 
 * Provides context awareness by tracking Unity scene changes.
 * Enables content managers to react to scene transitions.
 */
class SceneHooks {
public:
    enum class SceneType {
        Unknown,
        MainMenu,
        MapSelection,
        Gameplay,
        PostGame,
        Settings,
        Loading
    };

    // Initialize scene hooking system
    static void Initialize();
    
    // Get current scene information
    static SceneType GetCurrentSceneType();
    static std::string GetCurrentSceneName();
    
    // Check if we're in a specific scene type
    static bool IsInMainMenu() { return GetCurrentSceneType() == SceneType::MainMenu; }
    static bool IsInMapSelection() { return GetCurrentSceneType() == SceneType::MapSelection; }
    static bool IsInGameplay() { return GetCurrentSceneType() == SceneType::Gameplay; }
    static bool IsInPostGame() { return GetCurrentSceneType() == SceneType::PostGame; }
    
    // Callback system for scene changes
    using SceneChangeCallback = std::function<void(SceneType newScene, const std::string& sceneName)>;
    static void RegisterSceneChangeCallback(SceneChangeCallback callback);
    
    // Manual polling (called from update loop)
    static void Update();

private:
    struct State {
        MonoClass* sceneManagerClass = nullptr;
        MonoClass* sceneClass = nullptr;
        MonoMethod* getActiveSceneMethod = nullptr;
        MonoMethod* getSceneNameMethod = nullptr;
        
        std::string currentSceneName;
        SceneType currentSceneType = SceneType::Unknown;
        
        std::vector<SceneChangeCallback> callbacks;
    };
    
    static State s_State;
    
    // Internal helpers
    static bool FindSceneManagerClass();
    static std::string GetActiveSceneName();
    static bool TryGetSceneNameSafe(char* outBuffer, size_t bufferSize);  // SEH-protected wrapper
    static SceneType DetermineSceneType(const std::string& sceneName);
    static void OnSceneChanged(const std::string& newSceneName);
};
