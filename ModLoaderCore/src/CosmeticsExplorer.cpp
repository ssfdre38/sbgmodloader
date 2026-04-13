#include "../include/CosmeticsExplorer.h"
#include "../include/MonoHelper.h"
#include "../include/Log.h"
#include <string>
#include <vector>

using namespace ModLoader::Mono;

namespace ModLoader {

static void ExplorePlayerCosmetics(MonoImage* image) {
    Log::Info("🔍 Exploring PlayerCosmetics class...");
    
    MonoClass* klass = MonoHelper::GetClassFromName(image, "", "PlayerCosmetics");
    if (!klass) {
        Log::Warn("  PlayerCosmetics class not found");
        return;
    }
    
    Log::Info("  ✓ Found PlayerCosmetics");
    
    // Look for interesting methods
    std::vector<std::string> interestingMethods = {
        "SetClubCosmetic",
        "SetFaceCosmetic", 
        "SetBodyCosmetic",
        "SetHatCosmetic",
        "LoadCosmetic",
        "ApplyCosmetic",
        "get_Switcher",
        "ClubCosmeticUpdated"
    };
    
    for (const auto& methodName : interestingMethods) {
        MonoMethod* method = MonoHelper::FindMethod(klass, methodName.c_str());
        if (method) {
            Log::Info("    • Found method: %s", methodName.c_str());
        }
    }
    
    Log::Info("");
}

static void ExploreCosmeticsSwitcher(MonoImage* image) {
    Log::Info("🔍 Exploring PlayerCosmeticsSwitcher class...");
    
    MonoClass* klass = MonoHelper::GetClassFromName(image, "", "PlayerCosmeticsSwitcher");
    if (!klass) {
        Log::Warn("  PlayerCosmeticsSwitcher class not found");
        return;
    }
    
    Log::Info("  ✓ Found PlayerCosmeticsSwitcher");
    
    // Look for switch methods
    std::vector<std::string> switchMethods = {
        "SwitchClub",
        "SwitchFace",
        "SwitchBody",
        "SwitchHat",
        "GetCurrentCosmetic",
        "SetCosmetic"
    };
    
    for (const auto& methodName : switchMethods) {
        MonoMethod* method = MonoHelper::FindMethod(klass, methodName.c_str());
        if (method) {
            Log::Info("    • Found method: %s", methodName.c_str());
        }
    }
    
    Log::Info("");
}

static void ExploreCosmeticsUnlocks(MonoImage* image) {
    Log::Info("🔍 Exploring CosmeticsUnlocksManager class...");
    
    MonoClass* klass = MonoHelper::GetClassFromName(image, "", "CosmeticsUnlocksManager");
    if (!klass) {
        Log::Warn("  CosmeticsUnlocksManager class not found");
        return;
    }
    
    Log::Info("  ✓ Found CosmeticsUnlocksManager");
    
    // Look for unlock/list methods
    std::vector<std::string> unlockMethods = {
        "ListCosmeticsUnlocks",
        "UnlockCosmetic",
        "IsUnlocked",
        "GetAllCosmetics",
        "GetAvailableCosmetics"
    };
    
    for (const auto& methodName : unlockMethods) {
        MonoMethod* method = MonoHelper::FindMethod(klass, methodName.c_str());
        if (method) {
            Log::Info("    • Found method: %s", methodName.c_str());
        }
    }
    
    Log::Info("");
}

void CosmeticsExplorer::ExploreCosmeticsSystem() {
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("🎨 EXPLORING COSMETICS SYSTEM");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("");
    
    MonoAssembly* gameAsm = MonoHelper::FindAssembly("GameAssembly");
    if (!gameAsm) {
        Log::Error("GameAssembly not found!");
        return;
    }
    
    MonoImage* image = MonoHelper::mono_assembly_get_image(gameAsm);
    if (!image) {
        Log::Error("Failed to get GameAssembly image");
        return;
    }
    
    // Find key cosmetics classes
    ExplorePlayerCosmetics(image);
    ExploreCosmeticsSwitcher(image);
    ExploreCosmeticsUnlocks(image);
    
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════");
}

} // namespace ModLoader
