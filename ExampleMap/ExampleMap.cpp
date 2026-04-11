#include "../MapSDK/include/IMapModule.h"
#include <cstring>

using namespace MapSDK;

// Example custom map implementation
class ExampleCustomMap : public IMapModule {
private:
    SpawnPoint m_spawns[4];
    GoalInfo m_goal;
    MapBounds m_bounds;

public:
    ExampleCustomMap() {
        // Initialize spawn points
        m_spawns[0] = { 0.0f, 0.0f, 0.0f, 0.0f, 4, "Main Spawn" };
        m_spawns[1] = { 10.0f, 0.0f, 0.0f, 90.0f, 4, "East Spawn" };
        m_spawns[2] = { -10.0f, 0.0f, 0.0f, 270.0f, 4, "West Spawn" };
        m_spawns[3] = { 0.0f, 0.0f, 10.0f, 180.0f, 4, "South Spawn" };

        // Initialize goal
        m_goal = { 0.0f, 0.0f, 100.0f, 2.0f, 3, "Center Hole" };

        // Initialize bounds
        m_bounds = { -50.0f, -10.0f, -50.0f, 50.0f, 50.0f, 50.0f, -15.0f };
    }

    const char* GetMapName() override { return "Example Test Course"; }
    const char* GetMapDescription() override { return "A simple test course"; }
    const char* GetAuthor() override { return "MapSDK Example"; }
    const char* GetVersion() override { return "1.0.0"; }
    
    MapDifficulty GetDifficulty() override { return MapDifficulty::Easy; }
    MapTheme GetTheme() override { return MapTheme::Tropical; }
    int GetMinPlayers() override { return 1; }
    int GetMaxPlayers() override { return 16; }
    int GetEstimatedTime() override { return 5; }
    
    const char* GetAssetBundlePath() override { return "ExampleMap/examplecourse.bundle"; }
    const char* GetSceneName() override { return "Assets/Scenes/ExampleCourse.unity"; }
    
    SpawnPoint* GetSpawnPoints(int& outCount) override { outCount = 4; return m_spawns; }
    GoalInfo* GetGoalInfo() override { return &m_goal; }
    MapBounds* GetBounds() override { return &m_bounds; }
    
    void OnRegister() override {}
    void OnBeforeLoad() override {}
    void OnLoaded() override {}
    void OnPlayerSpawn(void* playerHandle) override {}
    void OnPlayerGoal(void* playerHandle, float completionTime) override {}
    void OnUnload() override {}
};

extern "C" __declspec(dllexport) IMapModule* CreateMap() {
    return new ExampleCustomMap();
}
