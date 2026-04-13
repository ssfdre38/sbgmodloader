#pragma once
#include <string>
#include <vector>
#include <map>

// Forward declarations
typedef void* MonoClass;
typedef void* MonoMethod;
typedef void* MonoObject;

namespace ModLoader {

/**
 * @brief Manages custom weapons and items
 * 
 * Hooks into the game's ItemSettings and item pool systems to inject
 * custom weapons, power-ups, and items.
 */
class ItemManager {
public:
    /**
     * @brief Initialize the item manager
     * Finds ItemSettings, item pool, and related classes
     */
    static bool Initialize();
    
    /**
     * @brief Load custom item mods
     * Scans Mods/Items/ folder for custom weapons and items
     */
    static void LoadItemMods();
    
    /**
     * @brief Register a custom item
     * @param itemId Unique ID for the item
     * @param itemName Display name
     * @param itemType Type: "weapon", "powerup", "consumable"
     * @param assetPath Path to asset bundle
     * @return true if registered successfully
     */
    static bool RegisterItem(const char* itemId, const char* itemName, const char* itemType, const char* assetPath);
    
private:
    struct CustomItem {
        std::string id;
        std::string name;
        std::string type;
        std::string assetPath;
        float spawnWeight; // Probability of spawning
    };
    
    static bool s_Initialized;
    static std::vector<CustomItem> s_CustomItems;
    
    // Unity class references
    static MonoClass* s_ItemSettingsClass;
    static MonoClass* s_ItemPoolClass;
    
    // Methods for injecting items
    static MonoMethod* s_AddItemMethod;
    static MonoMethod* s_UpdateItemPoolMethod;
};

} // namespace ModLoader
