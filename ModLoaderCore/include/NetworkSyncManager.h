#pragma once
#include <string>
#include <vector>
#include <map>
#include <functional>

#include "MonoHelper.h"

struct ModSyncInfo {
    std::string id;
    std::string version;
    std::string checksum;  // Hash of mod files for integrity check
    bool isRequired;       // Game modes/maps are required, cosmetics are optional
};

class NetworkSyncManager {
public:
    static void Initialize();
    static void OnMultiplayerJoin();
    static void OnMultiplayerHost();
    static void Shutdown();
    
    // Mod synchronization
    static std::vector<ModSyncInfo> GetLocalModList();
    static bool ValidateModCompatibility(const std::vector<ModSyncInfo>& hostMods);
    static void SendModList(void* networkConnection);
    static void ReceiveModList(void* data);
    
    // Callbacks
    using ModMismatchCallback = std::function<void(const std::string& message)>;
    static void RegisterMismatchCallback(ModMismatchCallback callback);
    
private:
    static bool initialized;
    static bool isHost;
    static std::vector<ModSyncInfo> localMods;
    static std::vector<ModSyncInfo> hostMods;
    static std::vector<ModMismatchCallback> mismatchCallbacks;
    
    // Unity networking classes (using void* to avoid type conflicts)
    static void* networkManagerClass;
    static void* networkConnectionClass;
    static void* networkMessageClass;
    
    // Methods
    static void* sendMethod;
    static void* receiveMethod;
    
    // Helper functions
    static std::string CalculateModChecksum(const std::string& modPath);
    static bool FindNetworkingClasses();
    static void OnModMismatch(const std::string& message);
    static void HookNetworkingEvents();
};
