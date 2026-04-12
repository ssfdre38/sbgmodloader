#include "GameModeManager.h"
#include "MonoHelper.h"
#include "SceneHooks.h"
#include "Log.h"
#include "UIOverlay.h"
#include "json.hpp"
#include <fstream>
#include <sstream>

namespace ModLoader {

using namespace ModLoader::Mono;
using json = nlohmann::json;

GameModeManager::State GameModeManager::s_State;

void GameModeManager::Initialize() {
    Log::Info("[GameModeManager] Initializing...");
    
    if (!MonoHelper::IsInitialized()) {
        Log::Error("[GameModeManager] Mono not initialized");
        return;
    }
    
    // Find required game classes
    if (!FindRequiredClasses()) {
        Log::Error("[GameModeManager] Failed to find required classes");
        return;
    }
    
    // Register for scene change callbacks
    SceneHooks::RegisterSceneChangeCallback(OnSceneChanged);
    
    s_State.initialized = true;
    Log::Info("[GameModeManager] Initialized successfully");
}

void GameModeManager::LoadGameModes(const std::vector<ModInfo>& mods) {
    if (!s_State.initialized) {
        Log::Warn("[GameModeManager] Not initialized, skipping LoadGameModes");
        return;
    }
    
    Log::Info("[GameModeManager] Loading game modes from %d mods...", (int)mods.size());
    
    s_State.gameModes.clear();
    
    for (const auto& mod : mods) {
        if (mod.type != "gamemode") continue;
        
        GameModeConfig config;
        if (ParseGameModeConfig(mod, config)) {
            s_State.gameModes.push_back(config);
            Log::Info("[GameModeManager] ✅ Loaded game mode: %s (id: %s)", 
                     config.name.c_str(), config.id.c_str());
        } else {
            Log::Warn("[GameModeManager] ⚠️  Failed to parse game mode: %s", mod.name.c_str());
        }
    }
    
    Log::Info("[GameModeManager] Loaded %d custom game modes", (int)s_State.gameModes.size());
}

bool GameModeManager::HasActiveGameMode() {
    return s_State.activeGameModeIndex >= 0 && 
           s_State.activeGameModeIndex < (int)s_State.gameModes.size();
}

std::string GameModeManager::GetActiveGameModeName() {
    if (HasActiveGameMode()) {
        return s_State.gameModes[s_State.activeGameModeIndex].name;
    }
    return "";
}

// ========================
// INTERNAL IMPLEMENTATIONS
// ========================

bool GameModeManager::FindRequiredClasses() {
    Log::Info("[GameModeManager] Finding required game classes...");
    
    // Get the GameAssembly (this game uses "GameAssembly" not "Assembly-CSharp")
    MonoAssembly* assembly = MonoHelper::FindAssembly("GameAssembly");
    if (!assembly) {
        Log::Error("[GameModeManager] Failed to find GameAssembly");
        return false;
    }
    
    MonoImage* image = MonoHelper::mono_assembly_get_image(assembly);
    if (!image) {
        Log::Error("[GameModeManager] Failed to get game image");
        return false;
    }
    
    // Find MatchSetupMenu
    s_State.matchSetupMenuClass = MonoHelper::GetClassFromName(image, "", "MatchSetupMenu");
    if (!s_State.matchSetupMenuClass) {
        Log::Error("[GameModeManager] Failed to find MatchSetupMenu class");
        return false;
    }
    Log::Info("[GameModeManager]  ✓ Found MatchSetupMenu");
    
    // Find CourseData
    s_State.courseDataClass = MonoHelper::GetClassFromName(image, "", "CourseData");
    if (!s_State.courseDataClass) {
        Log::Error("[GameModeManager] Failed to find CourseData class");
        return false;
    }
    Log::Info("[GameModeManager]  ✓ Found CourseData");
    
    // Find HoleData
    s_State.holeDataClass = MonoHelper::GetClassFromName(image, "", "HoleData");
    if (!s_State.holeDataClass) {
        Log::Error("[GameModeManager] Failed to find HoleData class");
        return false;
    }
    Log::Info("[GameModeManager]  ✓ Found HoleData");
    
    // Find MatchSetupRules
    s_State.matchSetupRulesClass = MonoHelper::GetClassFromName(image, "", "MatchSetupRules");
    if (!s_State.matchSetupRulesClass) {
        Log::Warn("[GameModeManager] Failed to find MatchSetupRules (optional)");
    } else {
        Log::Info("[GameModeManager]  ✓ Found MatchSetupRules");
    }
    
    // Get CustomCourseData property from MatchSetupMenu
    s_State.customCourseDataProperty = MonoHelper::GetProperty(
        s_State.matchSetupMenuClass, "CustomCourseData"
    );
    
    if (!s_State.customCourseDataProperty) {
        Log::Error("[GameModeManager] Failed to find CustomCourseData property");
        return false;
    }
    Log::Info("[GameModeManager]  ✓ Found CustomCourseData property");
    
    // Get the setter method (try to find it by name)
    s_State.customCourseDataSetter = MonoHelper::GetMethodFromName(
        s_State.matchSetupMenuClass, "set_CustomCourseData", 1
    );
    
    if (!s_State.customCourseDataSetter) {
        Log::Warn("[GameModeManager] Failed to find CustomCourseData setter (will retry at injection)");
    } else {
        Log::Info("[GameModeManager]  ✓ Found CustomCourseData setter");
    }
    
    return true;
}

bool GameModeManager::ParseGameModeConfig(const ModInfo& mod, GameModeConfig& outConfig) {
    std::string jsonPath = mod.folderPath + "\\mod.json";
    
    try {
        // Read JSON file
        std::ifstream file(jsonPath);
        if (!file.is_open()) {
            Log::Error("[GameModeManager] Failed to open mod.json: %s", jsonPath.c_str());
            return false;
        }
        
        json j;
        file >> j;
        
        // Parse basic fields
        outConfig.id = j.value("id", "");
        outConfig.name = j.value("name", "");
        outConfig.description = j.value("description", "");
        
        if (outConfig.id.empty() || outConfig.name.empty()) {
            Log::Error("[GameModeManager] Invalid mod.json: missing id or name");
            return false;
        }
        
        // Check if there's a gamemode section
        if (!j.contains("gamemode")) {
            Log::Error("[GameModeManager] No 'gamemode' section in mod.json");
            return false;
        }
        
        json gmSection = j["gamemode"];
        
        // Parse holes array
        if (!gmSection.contains("holes")) {
            Log::Error("[GameModeManager] No 'holes' array in gamemode section");
            return false;
        }
        
        json holes = gmSection["holes"];
        if (!holes.is_array()) {
            Log::Error("[GameModeManager] 'holes' must be an array");
            return false;
        }
        
        outConfig.holeScenes.clear();
        for (const auto& hole : holes) {
            if (hole.is_string()) {
                outConfig.holeScenes.push_back(hole.get<std::string>());
            } else if (hole.is_object() && hole.contains("scene")) {
                outConfig.holeScenes.push_back(hole["scene"].get<std::string>());
            }
        }
        
        outConfig.holeCount = (int)outConfig.holeScenes.size();
        
        // Parse optional rules
        if (gmSection.contains("rules")) {
            json rules = gmSection["rules"];
            outConfig.overtimeDuration = rules.value("overtimeDuration", 0.0f);
            outConfig.itemSpawnChance = rules.value("itemSpawnChance", 0.5f);
            outConfig.allowCustomItems = rules.value("allowCustomItems", true);
        }
        
        Log::Info("[GameModeManager] Parsed game mode: %s (%d holes)", 
                 outConfig.name.c_str(), outConfig.holeCount);
        
        return true;
        
    } catch (const std::exception& e) {
        Log::Error("[GameModeManager] JSON parse error: %s", e.what());
        return false;
    }
}

MonoObject* GameModeManager::BuildCourseData(const GameModeConfig& config) {
    if (!s_State.courseDataClass) {
        Log::Error("[GameModeManager] CourseData class not found");
        return nullptr;
    }
    
    // Create CourseData instance using MonoHelper
    MonoObject* courseData = MonoHelper::CreateInstance((MonoClass*)s_State.courseDataClass);
    if (!courseData) {
        Log::Error("[GameModeManager] Failed to create CourseData instance");
        return nullptr;
    }
    
    Log::Info("[GameModeManager] Created CourseData instance for '%s'", config.name.c_str());
    
    // TODO: Set properties on CourseData
    // - CourseName = config.name (need string conversion)
    // - HoleCount = config.holeCount (need int boxing)
    // - Holes = array of HoleData (need array creation)
    
    // For now, we've created the object successfully
    Log::Info("[GameModeManager] CourseData object created (properties not yet set)");
    
    return courseData;
}

MonoObject* GameModeManager::BuildHoleData(const std::string& sceneName, int par) {
    if (!s_State.holeDataClass) {
        Log::Error("[GameModeManager] HoleData class not found");
        return nullptr;
    }
    
    // Create HoleData instance
    MonoObject* holeData = MonoHelper::CreateInstance((MonoClass*)s_State.holeDataClass);
    if (!holeData) {
        Log::Error("[GameModeManager] Failed to create HoleData instance");
        return nullptr;
    }
    
    Log::Info("[GameModeManager] Created HoleData for scene '%s'", sceneName.c_str());
    
    // TODO: Set properties
    // - Scene = sceneName (Addressables scene reference)
    // - Par = par (int)
    
    return holeData;
}

void GameModeManager::OnSceneChanged(SceneHooks::SceneType sceneType, const std::string& sceneName) {
    if (!s_State.initialized) return;
    
    Log::Info("[GameModeManager] Scene changed: %s (type %d)", sceneName.c_str(), (int)sceneType);
    
    // Test UI injection on main menu
    if (sceneType == SceneHooks::SceneType::MainMenu) {
        Log::Info("[GameModeManager] Entered MainMenu - testing UI injection...");
        UIOverlay::TestAddVersionText();
    }
    
    // Check if we're entering MapSelection scene
    if (sceneType == SceneHooks::SceneType::MapSelection) {
        Log::Info("[GameModeManager] Entered MapSelection - checking for custom game modes...");
        
        if (!s_State.gameModes.empty()) {
            // For now, activate the first game mode
            s_State.activeGameModeIndex = 0;
            InjectCustomGameMode();
        }
    }
}

void GameModeManager::InjectCustomGameMode() {
    if (!HasActiveGameMode()) {
        Log::Warn("[GameModeManager] No active game mode to inject");
        return;
    }
    
    const GameModeConfig& config = s_State.gameModes[s_State.activeGameModeIndex];
    Log::Info("[GameModeManager] Injecting custom game mode: %s", config.name.c_str());
    
    // Build CourseData object
    MonoObject* courseData = BuildCourseData(config);
    if (!courseData) {
        Log::Error("[GameModeManager] Failed to build CourseData");
        return;
    }
    
    // TODO: Find MatchSetupMenu instance in the scene
    // This requires:
    // 1. mono_class_get_instances() or equivalent (not in our API yet)
    // 2. Or find via UnityEngine.Object.FindObjectOfType<MatchSetupMenu>()
    
    Log::Info("[GameModeManager] CourseData built - TODO: Find MatchSetupMenu instance and inject");
    
    // For now, log success
    Log::Info("[GameModeManager] ✅ Custom game mode ready for injection: %s", config.name.c_str());
}

} // namespace ModLoader
