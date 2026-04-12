#include "SceneHooks.h"
#include "MonoHelper.h"
#include "Log.h"
#include <algorithm>

using namespace ModLoader;
using namespace ModLoader::Mono;

SceneHooks::State SceneHooks::s_State;

void SceneHooks::Initialize() {
    Log::Info("[SceneHooks] Initializing scene management system...");
    
    if (!FindSceneManagerClass()) {
        Log::Error("[SceneHooks] Failed to find Unity SceneManager class!");
        return;
    }
    
    // Get initial scene
    std::string initialScene = GetActiveSceneName();
    if (!initialScene.empty()) {
        s_State.currentSceneName = initialScene;
        s_State.currentSceneType = DetermineSceneType(initialScene);
        Log::Info("[SceneHooks] Initial scene: %s (Type: %d)", initialScene.c_str(), (int)s_State.currentSceneType);
    }
    
    Log::Info("[SceneHooks] Initialized successfully!");
}

bool SceneHooks::FindSceneManagerClass() {
    // Try the old Unity API first - Application.loadedLevelName
    // This is simpler and returns a string directly (no struct handling needed)
    MonoAssembly* coreAsm = MonoHelper::FindAssembly("UnityEngine.CoreModule");
    if (!coreAsm) {
        Log::Error("[SceneHooks] Failed to find UnityEngine.CoreModule assembly");
        return false;
    }
    
    MonoImage* coreModule = MonoHelper::mono_assembly_get_image(coreAsm);
    if (!coreModule) {
        Log::Error("[SceneHooks] Failed to get image from UnityEngine.CoreModule");
        return false;
    }
    
    // Try to find Application class
    MonoClass* applicationClass = MonoHelper::GetClassFromName(
        coreModule,
        "UnityEngine",
        "Application"
    );
    
    if (applicationClass) {
        // Try to get loadedLevelName property
        MonoProperty* loadedLevelProp = MonoHelper::GetProperty(applicationClass, "loadedLevelName");
        if (loadedLevelProp) {
            s_State.getSceneNameMethod = MonoHelper::GetPropertyGetter(loadedLevelProp);
            if (s_State.getSceneNameMethod) {
                Log::Info("[SceneHooks] Using Application.loadedLevelName (old Unity API)");
                s_State.sceneManagerClass = applicationClass;  // Store for null check
                return true;
            }
        }
    }
    
    Log::Warn("[SceneHooks] Application.loadedLevelName not found, trying SceneManager...");
    
    // Fallback: Try SceneManager API
    s_State.sceneManagerClass = MonoHelper::GetClassFromName(
        coreModule,
        "UnityEngine.SceneManagement",
        "SceneManager"
    );
    
    if (!s_State.sceneManagerClass) {
        Log::Error("[SceneHooks] Failed to find SceneManager class");
        return false;
    }
    
    // Find Scene class
    s_State.sceneClass = MonoHelper::GetClassFromName(
        coreModule,
        "UnityEngine.SceneManagement",
        "Scene"
    );
    
    if (!s_State.sceneClass) {
        Log::Error("[SceneHooks] Failed to find Scene class");
        return false;
    }
    
    // Find GetActiveScene method
    s_State.getActiveSceneMethod = MonoHelper::GetMethodFromName(
        s_State.sceneManagerClass,
        "GetActiveScene",
        0
    );
    
    if (!s_State.getActiveSceneMethod) {
        Log::Error("[SceneHooks] Failed to find GetActiveScene method");
        return false;
    }
    
    // Find Scene.get_name property getter
    MonoProperty* nameProperty = MonoHelper::GetProperty(
        s_State.sceneClass,
        "name"
    );
    
    if (!nameProperty) {
        Log::Error("[SceneHooks] Failed to find Scene.name property");
        return false;
    }
    
    s_State.getSceneNameMethod = MonoHelper::GetPropertyGetter(nameProperty);
    if (!s_State.getSceneNameMethod) {
        Log::Error("[SceneHooks] Failed to get Scene.name getter method");
        return false;
    }
    
    Log::Info("[SceneHooks] Found Unity SceneManager and Scene classes");
    return true;
}

// SEH-protected wrapper for getting scene name (static member function)
bool SceneHooks::TryGetSceneNameSafe(char* outBuffer, size_t bufferSize) {
    __try {
        if (!s_State.sceneManagerClass) {
            Log::Error("[SceneHooks] sceneManagerClass is null!");
            return false;
        }
        
        if (!s_State.getSceneNameMethod) {
            Log::Error("[SceneHooks] getSceneNameMethod is null!");
            return false;
        }
        
        // If we're using Application.loadedLevelName, getActiveSceneMethod will be null
        if (!s_State.getActiveSceneMethod) {
            // Direct property access - Application.loadedLevelName
            MonoObject* exception = nullptr;
            MonoObject* nameObject = (MonoObject*)MonoHelper::InvokeMethod(
                s_State.getSceneNameMethod,
                nullptr,  // Static property
                nullptr,
                &exception
            );
            
            if (exception) {
                Log::Warn("[SceneHooks] Application.loadedLevelName threw Mono exception");
                return false;
            }
            
            if (!nameObject) {
                // This is normal - means no scene is loaded yet
                return false;
            }
            
            // Convert to string
            MonoString* monoStr = (MonoString*)nameObject;
            const char* cstr = MonoHelper::MonoStringToUTF8(monoStr);
            if (!cstr) {
                return false;
            }
            
            strncpy_s(outBuffer, bufferSize, cstr, _TRUNCATE);
            return true;
        }
        
        // Otherwise use SceneManager.GetActiveScene().name (old code path)
        MonoObject* exception = nullptr;
        void* sceneStruct = MonoHelper::InvokeMethod(
            s_State.getActiveSceneMethod,
            nullptr, nullptr, &exception
        );
        
        if (exception) {
            Log::Warn("[SceneHooks] GetActiveScene threw Mono exception");
            return false;
        }
        
        if (!sceneStruct) {
            Log::Warn("[SceneHooks] GetActiveScene returned null struct");
            return false;
        }
        
        // Call get_name
        exception = nullptr;
        MonoObject* nameObject = (MonoObject*)MonoHelper::InvokeMethod(
            s_State.getSceneNameMethod,
            sceneStruct, nullptr, &exception
        );
        
        if (exception) {
            Log::Warn("[SceneHooks] Scene.get_name threw Mono exception");
            return false;
        }
        
        if (!nameObject) {
            Log::Warn("[SceneHooks] Scene.get_name returned null");
            return false;
        }
        
        // Convert to string
        MonoString* monoStr = (MonoString*)nameObject;
        const char* cstr = MonoHelper::MonoStringToUTF8(monoStr);
        if (!cstr) {
            Log::Warn("[SceneHooks] MonoStringToUTF8 returned null");
            return false;
        }
        
        // Copy to buffer
        strncpy_s(outBuffer, bufferSize, cstr, _TRUNCATE);
        return true;
    }
    __except(EXCEPTION_EXECUTE_HANDLER) {
        Log::Warn("[SceneHooks] SEH exception caught in TryGetSceneNameSafe");
        return false;
    }
}

std::string SceneHooks::GetActiveSceneName() {
    static int debugCount = 0;
    debugCount++;
    
    char sceneNameBuffer[256] = {0};
    bool success = TryGetSceneNameSafe(sceneNameBuffer, sizeof(sceneNameBuffer));
    
    if (!success) {
        // Only log first 5 failures to avoid spam
        if (debugCount <= 5) {
            Log::Warn("[SceneHooks] TryGetSceneNameSafe failed (call #%d)", debugCount);
        }
        return "";
    }
    
    std::string sceneName(sceneNameBuffer);
    
    // Always log successful scene detection
    Log::Info("[SceneHooks] ✅ Got scene name: '%s'", sceneName.c_str());
    
    return sceneName;
}

SceneHooks::SceneType SceneHooks::DetermineSceneType(const std::string& sceneName) {
    if (sceneName.empty()) {
        return SceneType::Unknown;
    }
    
    // Pattern matching based on common Unity scene naming conventions
    std::string lowerName = sceneName;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    
    // Main Menu detection
    if (lowerName.find("menu") != std::string::npos ||
        lowerName.find("main") != std::string::npos ||
        lowerName.find("title") != std::string::npos) {
        return SceneType::MainMenu;
    }
    
    // Map Selection / Lobby detection
    if (lowerName.find("lobby") != std::string::npos ||
        lowerName.find("selection") != std::string::npos ||
        lowerName.find("setup") != std::string::npos ||
        lowerName.find("matchsetup") != std::string::npos) {
        return SceneType::MapSelection;
    }
    
    // Gameplay detection
    if (lowerName.find("course") != std::string::npos ||
        lowerName.find("game") != std::string::npos ||
        lowerName.find("play") != std::string::npos ||
        lowerName.find("match") != std::string::npos ||
        lowerName.find("hole") != std::string::npos) {
        return SceneType::Gameplay;
    }
    
    // Post-Game / Results detection
    if (lowerName.find("result") != std::string::npos ||
        lowerName.find("score") != std::string::npos ||
        lowerName.find("end") != std::string::npos ||
        lowerName.find("victory") != std::string::npos) {
        return SceneType::PostGame;
    }
    
    // Settings detection
    if (lowerName.find("setting") != std::string::npos ||
        lowerName.find("option") != std::string::npos ||
        lowerName.find("config") != std::string::npos) {
        return SceneType::Settings;
    }
    
    // Loading screen detection
    if (lowerName.find("load") != std::string::npos) {
        return SceneType::Loading;
    }
    
    return SceneType::Unknown;
}

void SceneHooks::Update() {
    static int updateCount = 0;
    updateCount++;
    
    // Log first few updates to verify it's being called
    if (updateCount <= 3) {
        Log::Info("[SceneHooks] Update() called (count: %d)", updateCount);
    }
    
    std::string currentScene = GetActiveSceneName();
    
    // Log if we got a scene name
    if (updateCount <= 3 && !currentScene.empty()) {
        Log::Info("[SceneHooks] Got scene name: '%s'", currentScene.c_str());
    }
    
    // Check if scene has changed
    if (!currentScene.empty() && currentScene != s_State.currentSceneName) {
        OnSceneChanged(currentScene);
    }
}

void SceneHooks::OnSceneChanged(const std::string& newSceneName) {
    SceneType oldType = s_State.currentSceneType;
    SceneType newType = DetermineSceneType(newSceneName);
    
    Log::Info("[SceneHooks] Scene changed: '%s' -> '%s' (Type: %d -> %d)",
        s_State.currentSceneName.c_str(), newSceneName.c_str(),
        (int)oldType, (int)newType);
    
    s_State.currentSceneName = newSceneName;
    s_State.currentSceneType = newType;
    
    // Notify all registered callbacks
    for (const auto& callback : s_State.callbacks) {
        callback(newType, newSceneName);
    }
}

SceneHooks::SceneType SceneHooks::GetCurrentSceneType() {
    return s_State.currentSceneType;
}

std::string SceneHooks::GetCurrentSceneName() {
    return s_State.currentSceneName;
}

void SceneHooks::RegisterSceneChangeCallback(SceneChangeCallback callback) {
    s_State.callbacks.push_back(callback);
    Log::Info("[SceneHooks] Registered scene change callback (total: %zu)", s_State.callbacks.size());
}
