#pragma once

#include <string>

/*
 * IMapModule - Interface for custom golf course maps
 * 
 * Custom maps must implement this interface and export a CreateMap() function.
 * The mod loader will discover map DLLs in the Maps/ folder and call the
 * exported function to instantiate the map module.
 * 
 * Example usage:
 *   class MyCustomMap : public IMapModule {
 *       const char* GetMapName() override { return "My Awesome Course"; }
 *       const char* GetMapDescription() override { return "A challenging 18-hole course"; }
 *       // ... implement other methods
 *   };
 *   
 *   extern "C" __declspec(dllexport) IMapModule* CreateMap() {
 *       return new MyCustomMap();
 *   }
 */

namespace MapSDK {

    // Map difficulty rating
    enum class MapDifficulty {
        Easy = 1,
        Medium = 2,
        Hard = 3,
        Expert = 4
    };

    // Map theme/environment type
    enum class MapTheme {
        Tropical,      // Beach, island themes
        Desert,        // Sand, canyon themes
        Snow,          // Winter, ice themes
        Forest,        // Jungle, woodland themes
        Space,         // Sci-fi, zero-gravity themes
        Urban,         // City, industrial themes
        Fantasy,       // Magical, surreal themes
        Custom         // Custom theme
    };

    // Spawn point information
    struct SpawnPoint {
        float x, y, z;           // World position
        float rotationY;         // Y-axis rotation in degrees
        int maxPlayers;          // Maximum players for this spawn
        const char* name;        // Optional name/label
    };

    // Goal/hole information
    struct GoalInfo {
        float x, y, z;           // World position
        float radius;            // Trigger radius
        int par;                 // Par for this hole
        const char* name;        // Hole name
    };

    // Map bounds (out-of-bounds detection)
    struct MapBounds {
        float minX, minY, minZ;  // Minimum bounds
        float maxX, maxY, maxZ;  // Maximum bounds
        float killZ;             // Z position that triggers instant respawn
    };

    class IMapModule {
    public:
        virtual ~IMapModule() = default;

        // ===== Map Identity =====
        
        // Get the display name of the map (shown in UI)
        virtual const char* GetMapName() = 0;
        
        // Get a brief description of the map
        virtual const char* GetMapDescription() = 0;
        
        // Get the map author/creator name
        virtual const char* GetAuthor() = 0;
        
        // Get map version (e.g., "1.0.0")
        virtual const char* GetVersion() = 0;

        // ===== Map Properties =====
        
        // Get the map difficulty rating
        virtual MapDifficulty GetDifficulty() = 0;
        
        // Get the map theme/environment type
        virtual MapTheme GetTheme() = 0;
        
        // Get recommended player count (min)
        virtual int GetMinPlayers() = 0;
        
        // Get recommended player count (max)
        virtual int GetMaxPlayers() = 0;
        
        // Get estimated completion time in minutes
        virtual int GetEstimatedTime() = 0;

        // ===== Asset Bundle Information =====
        
        // Get the path to the asset bundle file containing this map
        // Path is relative to the Maps/ folder
        // Example: "MyMap/mycourse.bundle"
        virtual const char* GetAssetBundlePath() = 0;
        
        // Get the Unity scene name within the asset bundle
        // This is the addressable key used to load the scene
        // Example: "Assets/Scenes/MyCourse.unity"
        virtual const char* GetSceneName() = 0;

        // ===== Map Geometry =====
        
        // Get array of spawn points (where players start)
        // Returns nullptr if using scene-embedded spawns
        virtual SpawnPoint* GetSpawnPoints(int& outCount) = 0;
        
        // Get goal/hole information
        // Returns nullptr if using scene-embedded goal
        virtual GoalInfo* GetGoalInfo() = 0;
        
        // Get map bounds for out-of-bounds detection
        // Returns nullptr to use auto-calculated bounds
        virtual MapBounds* GetBounds() = 0;

        // ===== Lifecycle Callbacks =====
        
        // Called when the map is registered with the mod loader
        virtual void OnRegister() = 0;
        
        // Called before the map scene is loaded
        virtual void OnBeforeLoad() = 0;
        
        // Called after the map scene has finished loading
        virtual void OnLoaded() = 0;
        
        // Called when a player spawns on this map
        virtual void OnPlayerSpawn(void* playerHandle) = 0;
        
        // Called when a player reaches the goal
        virtual void OnPlayerGoal(void* playerHandle, float completionTime) = 0;
        
        // Called when the map is being unloaded
        virtual void OnUnload() = 0;

        // ===== Optional Overrides =====
        
        // Get custom game rules JSON string (optional)
        // Return nullptr for default rules
        // Example: "{\"allowItems\": false, \"timeLimit\": 300}"
        virtual const char* GetCustomRules() { return nullptr; }
        
        // Get preview image path (optional)
        // Path relative to Maps/ folder
        // Example: "MyMap/preview.png"
        virtual const char* GetPreviewImagePath() { return nullptr; }
        
        // Does this map support multiplayer?
        virtual bool SupportsMultiplayer() { return true; }
        
        // Does this map require specific DLC or mods?
        virtual const char* GetRequirements() { return nullptr; }
    };

    // Export function signature that map DLLs must implement
    // Example:
    //   extern "C" __declspec(dllexport) IMapModule* CreateMap() {
    //       return new MyMap();
    //   }
    typedef IMapModule* (*CreateMapFunc)();

} // namespace MapSDK
