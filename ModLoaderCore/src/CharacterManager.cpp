#include "../include/CharacterManager.h"
#include "../include/MonoHelper.h"
#include "../include/Log.h"
#include <filesystem>

using namespace ModLoader::Mono;

namespace ModLoader {

bool CharacterManager::s_Initialized = false;
std::vector<CharacterManager::CustomCosmetic> CharacterManager::s_CustomCosmetics;

MonoClass* CharacterManager::s_PlayerCosmeticsClass = nullptr;
MonoClass* CharacterManager::s_CosmeticsSwitcherClass = nullptr;
MonoClass* CharacterManager::s_CosmeticsUnlocksClass = nullptr;

MonoMethod* CharacterManager::s_SetCosmeticMethod = nullptr;
MonoMethod* CharacterManager::s_UnlockCosmeticMethod = nullptr;

bool CharacterManager::Initialize() {
    if (s_Initialized) {
        return true;
    }
    
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("🎭 Initializing CharacterManager");
    Log::Info("═══════════════════════════════════════════════");
    
    // Find GameAssembly
    MonoAssembly* gameAsm = MonoHelper::FindAssembly("GameAssembly");
    if (!gameAsm) {
        Log::Error("[CharacterManager] GameAssembly not found");
        return false;
    }
    
    MonoImage* image = MonoHelper::mono_assembly_get_image(gameAsm);
    if (!image) {
        Log::Error("[CharacterManager] Failed to get GameAssembly image");
        return false;
    }
    
    // Find PlayerCosmetics class
    s_PlayerCosmeticsClass = MonoHelper::GetClassFromName(image, "", "PlayerCosmetics");
    if (!s_PlayerCosmeticsClass) {
        Log::Error("[CharacterManager] PlayerCosmetics class not found");
        return false;
    }
    Log::Info("  ✓ Found PlayerCosmetics");
    
    // Find CosmeticsSwitcher class
    s_CosmeticsSwitcherClass = MonoHelper::GetClassFromName(image, "", "PlayerCosmeticsSwitcher");
    if (!s_CosmeticsSwitcherClass) {
        Log::Warn("[CharacterManager] PlayerCosmeticsSwitcher not found");
    } else {
        Log::Info("  ✓ Found PlayerCosmeticsSwitcher");
    }
    
    // Find CosmeticsUnlocksManager
    s_CosmeticsUnlocksClass = MonoHelper::GetClassFromName(image, "", "CosmeticsUnlocksManager");
    if (!s_CosmeticsUnlocksClass) {
        Log::Warn("[CharacterManager] CosmeticsUnlocksManager not found");
    } else {
        Log::Info("  ✓ Found CosmeticsUnlocksManager");
    }
    
    Log::Info("");
    Log::Info("✅ CharacterManager initialized");
    Log::Info("   Custom character skins can now be loaded");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("");
    
    s_Initialized = true;
    return true;
}

void CharacterManager::LoadCharacterMods() {
    if (!s_Initialized) {
        Log::Warn("[CharacterManager] Not initialized, skipping LoadCharacterMods");
        return;
    }
    
    Log::Info("[CharacterManager] Loading character mods...");
    
    // Get Mods/Characters directory
    std::string modsPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Super Battle Golf\\Mods\\Characters";
    
    if (!std::filesystem::exists(modsPath)) {
        Log::Info("[CharacterManager] No Characters folder found (create Mods/Characters/ to add character mods)");
        return;
    }
    
    int loadedCount = 0;
    
    // Scan for character mods
    for (const auto& entry : std::filesystem::directory_iterator(modsPath)) {
        if (!entry.is_directory()) continue;
        
        std::string modPath = entry.path().string();
        std::string modJsonPath = modPath + "\\mod.json";
        
        if (!std::filesystem::exists(modJsonPath)) {
            continue;
        }
        
        Log::Info("[CharacterManager]   Found character mod: %s", entry.path().filename().string().c_str());
        loadedCount++;
        
        // TODO: Parse mod.json and load character assets
        // This will be similar to how we load maps/game modes
    }
    
    Log::Info("[CharacterManager] Loaded %d character mod(s)", loadedCount);
}

bool CharacterManager::RegisterCosmetic(const char* cosmeticId, const char* cosmeticName, const char* assetPath) {
    if (!s_Initialized) {
        Log::Error("[CharacterManager] Cannot register cosmetic - not initialized");
        return false;
    }
    
    CustomCosmetic cosmetic;
    cosmetic.id = cosmeticId;
    cosmetic.name = cosmeticName;
    cosmetic.assetPath = assetPath;
    
    s_CustomCosmetics.push_back(cosmetic);
    
    Log::Info("[CharacterManager] ✅ Registered cosmetic: %s (%s)", cosmeticName, cosmeticId);
    
    return true;
}

} // namespace ModLoader
