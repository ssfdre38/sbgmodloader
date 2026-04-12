#pragma once
#include <string>
#include <vector>
#include "ModInfo.h"
#include "SceneHooks.h"

// Forward declarations for Mono types
typedef void* MonoClass;
typedef void* MonoMethod;
typedef void* MonoObject;
typedef void* MonoProperty;

namespace ModLoader {

/**
 * GameModeManager - Custom Game Mode Loading System
 * 
 * Manages custom game modes by hooking into the game's MatchSetupMenu
 * and injecting custom CourseData objects.
 * 
 * Integration Points:
 * - MatchSetupMenu.CustomCourseData property (THE injection point)
 * - HoleData.Scene property (references Addressables scenes)
 * - MatchSetupRules for rule modifications
 */
class GameModeManager {
public:
    /**
     * Initialize the game mode manager
     * Finds required classes and sets up scene callbacks
     */
    static void Initialize();
    
    /**
     * Load custom game modes from discovered mods
     * Parses JSON configs and prepares for injection
     */
    static void LoadGameModes(const std::vector<ModInfo>& mods);
    
    /**
     * Check if a custom game mode is active
     */
    static bool HasActiveGameMode();
    
    /**
     * Get the name of the active custom game mode
     */
    static std::string GetActiveGameModeName();

private:
    struct GameModeConfig {
        std::string id;
        std::string name;
        std::string description;
        int holeCount = 18;
        std::vector<std::string> holeScenes;  // Scene names from Addressables
        
        // Optional: Rule modifications
        float overtimeDuration = 0.0f;
        float itemSpawnChance = 0.5f;
        bool allowCustomItems = true;
    };
    
    struct State {
        // Mono classes and methods
        MonoClass* matchSetupMenuClass = nullptr;
        MonoClass* courseDataClass = nullptr;
        MonoClass* holeDataClass = nullptr;
        MonoClass* matchSetupRulesClass = nullptr;
        
        MonoProperty* customCourseDataProperty = nullptr;
        MonoMethod* customCourseDataSetter = nullptr;
        
        // Loaded game modes
        std::vector<GameModeConfig> gameModes;
        int activeGameModeIndex = -1;
        
        bool initialized = false;
    };
    
    static State s_State;
    
    // Internal helpers
    static bool FindRequiredClasses();
    static bool ParseGameModeConfig(const ModInfo& mod, GameModeConfig& outConfig);
    static MonoObject* BuildCourseData(const GameModeConfig& config);
    static MonoObject* BuildHoleData(const std::string& sceneName, int par);
    static void OnSceneChanged(SceneHooks::SceneType sceneType, const std::string& sceneName);
    static void InjectCustomGameMode();
};

} // namespace ModLoader
