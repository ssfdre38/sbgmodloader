#include "../include/ItemManager.h"
#include "../include/MonoHelper.h"
#include "../include/Log.h"
#include <filesystem>

using namespace ModLoader::Mono;

namespace ModLoader {

bool ItemManager::s_Initialized = false;
std::vector<ItemManager::CustomItem> ItemManager::s_CustomItems;

MonoClass* ItemManager::s_ItemSettingsClass = nullptr;
MonoClass* ItemManager::s_ItemPoolClass = nullptr;

MonoMethod* ItemManager::s_AddItemMethod = nullptr;
MonoMethod* ItemManager::s_UpdateItemPoolMethod = nullptr;

bool ItemManager::Initialize() {
    if (s_Initialized) {
        return true;
    }
    
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("⚔️ Initializing ItemManager");
    Log::Info("═══════════════════════════════════════════════");
    
    // Find GameAssembly
    MonoAssembly* gameAsm = MonoHelper::FindAssembly("GameAssembly");
    if (!gameAsm) {
        Log::Error("[ItemManager] GameAssembly not found");
        return false;
    }
    
    MonoImage* image = MonoHelper::mono_assembly_get_image(gameAsm);
    if (!image) {
        Log::Error("[ItemManager] Failed to get GameAssembly image");
        return false;
    }
    
    // Find ItemSettings class
    s_ItemSettingsClass = MonoHelper::GetClassFromName(image, "", "ItemSettings");
    if (!s_ItemSettingsClass) {
        Log::Warn("[ItemManager] ItemSettings class not found");
    } else {
        Log::Info("  ✓ Found ItemSettings");
    }
    
    // Try to find item pool related classes
    MonoClass* itemPoolClass = MonoHelper::GetClassFromName(image, "", "CurrentItemPool");
    if (!itemPoolClass) {
        itemPoolClass = MonoHelper::GetClassFromName(image, "", "ItemPool");
    }
    
    if (itemPoolClass) {
        s_ItemPoolClass = itemPoolClass;
        Log::Info("  ✓ Found item pool class");
    } else {
        Log::Warn("[ItemManager] Item pool class not found");
    }
    
    Log::Info("");
    Log::Info("✅ ItemManager initialized");
    Log::Info("   Custom weapons and items can now be loaded");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("");
    
    s_Initialized = true;
    return true;
}

void ItemManager::LoadItemMods() {
    if (!s_Initialized) {
        Log::Warn("[ItemManager] Not initialized, skipping LoadItemMods");
        return;
    }
    
    Log::Info("[ItemManager] Loading item mods...");
    
    // Get Mods/Items directory
    std::string modsPath = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Super Battle Golf\\Mods\\Items";
    
    if (!std::filesystem::exists(modsPath)) {
        Log::Info("[ItemManager] No Items folder found (create Mods/Items/ to add item mods)");
        return;
    }
    
    int loadedCount = 0;
    
    // Scan for item mods
    for (const auto& entry : std::filesystem::directory_iterator(modsPath)) {
        if (!entry.is_directory()) continue;
        
        std::string modPath = entry.path().string();
        std::string modJsonPath = modPath + "\\mod.json";
        
        if (!std::filesystem::exists(modJsonPath)) {
            continue;
        }
        
        Log::Info("[ItemManager]   Found item mod: %s", entry.path().filename().string().c_str());
        loadedCount++;
        
        // TODO: Parse mod.json and load item assets
        // This will be similar to how we load maps/game modes
    }
    
    Log::Info("[ItemManager] Loaded %d item mod(s)", loadedCount);
}

bool ItemManager::RegisterItem(const char* itemId, const char* itemName, const char* itemType, const char* assetPath) {
    if (!s_Initialized) {
        Log::Error("[ItemManager] Cannot register item - not initialized");
        return false;
    }
    
    CustomItem item;
    item.id = itemId;
    item.name = itemName;
    item.type = itemType;
    item.assetPath = assetPath;
    item.spawnWeight = 1.0f; // Default weight
    
    s_CustomItems.push_back(item);
    
    Log::Info("[ItemManager] ✅ Registered item: %s (%s) [%s]", itemName, itemId, itemType);
    
    return true;
}

} // namespace ModLoader
