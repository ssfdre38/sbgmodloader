#include "../include/NetworkSyncManager.h"
#include "../include/MonoHelper.h"
#include "../include/ModManager.h"
#include "../include/Log.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace ModLoader;
using namespace Mono;

bool NetworkSyncManager::initialized = false;
bool NetworkSyncManager::isHost = false;
std::vector<ModSyncInfo> NetworkSyncManager::localMods;
std::vector<ModSyncInfo> NetworkSyncManager::hostMods;
std::vector<NetworkSyncManager::ModMismatchCallback> NetworkSyncManager::mismatchCallbacks;

void* NetworkSyncManager::networkManagerClass = nullptr;
void* NetworkSyncManager::networkConnectionClass = nullptr;
void* NetworkSyncManager::networkMessageClass = nullptr;

void* NetworkSyncManager::sendMethod = nullptr;
void* NetworkSyncManager::receiveMethod = nullptr;

void NetworkSyncManager::Initialize() {
    if (initialized) {
        Log::Info("[NetworkSync] Already initialized");
        return;
    }
    
    Log::Info("[NetworkSync] Initializing network synchronization...");
    
    if (!FindNetworkingClasses()) {
        Log::Info("[NetworkSync] No multiplayer networking detected");
        Log::Info("[NetworkSync] Network sync disabled (single-player only)");
        return;
    }
    
    // Build local mod list
    localMods = GetLocalModList();
    Log::Info("[NetworkSync] Local mods: %d total", localMods.size());
    
    for (const auto& mod : localMods) {
        Log::Info("[NetworkSync]   - %s v%s (%s)", 
            mod.id.c_str(), mod.version.c_str(), mod.isRequired ? "required" : "optional");
    }
    
    // Hook networking events
    HookNetworkingEvents();
    
    initialized = true;
    Log::Info("[NetworkSync] ✅ Network sync initialized");
}

void NetworkSyncManager::Shutdown() {
    if (!initialized) return;
    
    Log::Info("[NetworkSync] Shutting down...");
    
    localMods.clear();
    hostMods.clear();
    mismatchCallbacks.clear();
    
    initialized = false;
    Log::Info("[NetworkSync] Shutdown complete");
}

bool NetworkSyncManager::FindNetworkingClasses() {
    Log::Info("[NetworkSync] Searching for Unity networking classes...");
    
    // For now, just return false - networking detection would be complex
    // This is a placeholder for future implementation
    Log::Info("[NetworkSync] No supported networking framework found");
    return false;
}

void NetworkSyncManager::HookNetworkingEvents() {
    // Placeholder - would hook Unity networking events
    Log::Info("[NetworkSync] Network hooks installed (manual trigger mode)");
}

std::vector<ModSyncInfo> NetworkSyncManager::GetLocalModList() {
    std::vector<ModSyncInfo> mods;
    
    Log::Info("[NetworkSync] Building local mod list...");
    
    // TODO: Integrate with ModManager to get actual loaded mods
    // For now, return empty list as placeholder
    
    return mods;
}

std::string NetworkSyncManager::CalculateModChecksum(const std::string& modPath) {
    // Simple CRC32 implementation (placeholder)
    std::ifstream file(modPath + "\\mod.json", std::ios::binary);
    if (!file.is_open()) {
        return "00000000";
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    uint32_t checksum = 0;
    for (char c : content) {
        checksum = ((checksum << 5) + checksum) + static_cast<unsigned char>(c);
    }
    
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << checksum;
    return ss.str();
}

void NetworkSyncManager::OnMultiplayerHost() {
    if (!initialized) {
        Log::Warn("[NetworkSync] Not initialized - skipping host sync");
        return;
    }
    
    Log::Info("[NetworkSync] 🎮 Hosting multiplayer session");
    isHost = true;
    
    Log::Info("[NetworkSync] Hosting with %d mods", localMods.size());
}

void NetworkSyncManager::OnMultiplayerJoin() {
    if (!initialized) {
        Log::Warn("[NetworkSync] Not initialized - skipping join sync");
        return;
    }
    
    Log::Info("[NetworkSync] 🎮 Joining multiplayer session");
    isHost = false;
    
    Log::Info("[NetworkSync] Requesting host mod list...");
}

bool NetworkSyncManager::ValidateModCompatibility(const std::vector<ModSyncInfo>& hostMods) {
    Log::Info("[NetworkSync] Validating mod compatibility...");
    
    bool compatible = true;
    std::vector<std::string> missingMods;
    std::vector<std::string> versionMismatches;
    std::vector<std::string> checksumMismatches;
    
    for (const auto& hostMod : hostMods) {
        if (!hostMod.isRequired) continue;
        
        auto it = std::find_if(localMods.begin(), localMods.end(),
            [&hostMod](const ModSyncInfo& local) { return local.id == hostMod.id; });
        
        if (it == localMods.end()) {
            missingMods.push_back(hostMod.id);
            compatible = false;
        } else {
            if (it->version != hostMod.version) {
                versionMismatches.push_back(hostMod.id + " (host: " + hostMod.version + 
                    ", local: " + it->version + ")");
                compatible = false;
            }
            
            if (it->checksum != hostMod.checksum) {
                checksumMismatches.push_back(hostMod.id);
                Log::Warn("[NetworkSync] Checksum mismatch for mod: %s", hostMod.id.c_str());
            }
        }
    }
    
    if (!compatible) {
        std::string message = "❌ Mod mismatch detected!\n\n";
        
        if (!missingMods.empty()) {
            message += "Missing required mods:\n";
            for (const auto& mod : missingMods) {
                message += "  • " + mod + "\n";
            }
        }
        
        if (!versionMismatches.empty()) {
            message += "\nVersion mismatches:\n";
            for (const auto& mod : versionMismatches) {
                message += "  • " + mod + "\n";
            }
        }
        
        message += "\nPlease ensure all players have the same mods installed.";
        
        OnModMismatch(message);
        
        Log::Error("[NetworkSync] %s", message.c_str());
        return false;
    }
    
    Log::Info("[NetworkSync] ✅ All mods compatible!");
    return true;
}

void NetworkSyncManager::SendModList(void* networkConnection) {
    if (!initialized || !sendMethod) {
        Log::Warn("[NetworkSync] Cannot send mod list - not initialized or no send method");
        return;
    }
    
    Log::Info("[NetworkSync] Sending mod list (%d mods)...", localMods.size());
    
    for (const auto& mod : localMods) {
        Log::Info("[NetworkSync]   Sending: %s v%s (checksum: %s)", 
            mod.id.c_str(), mod.version.c_str(), mod.checksum.c_str());
    }
}

void NetworkSyncManager::ReceiveModList(void* data) {
    if (!initialized) {
        Log::Warn("[NetworkSync] Cannot receive mod list - not initialized");
        return;
    }
    
    Log::Info("[NetworkSync] Receiving host mod list...");
}

void NetworkSyncManager::RegisterMismatchCallback(ModMismatchCallback callback) {
    mismatchCallbacks.push_back(callback);
}

void NetworkSyncManager::OnModMismatch(const std::string& message) {
    for (const auto& callback : mismatchCallbacks) {
        callback(message);
    }
}
