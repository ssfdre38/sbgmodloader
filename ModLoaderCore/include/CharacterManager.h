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
 * @brief Manages custom character skins and cosmetics
 * 
 * Hooks into the game's PlayerCosmetics system to inject custom skins,
 * colors, and cosmetic items.
 */
class CharacterManager {
public:
    /**
     * @brief Initialize the character manager
     * Finds PlayerCosmetics, CosmeticsSwitcher, and related classes
     */
    static bool Initialize();
    
    /**
     * @brief Load custom character assets from mods
     * Scans Mods/Characters/ folder for custom skins
     */
    static void LoadCharacterMods();
    
    /**
     * @brief Register a custom cosmetic item
     * @param cosmeticId Unique ID for the cosmetic
     * @param cosmeticName Display name
     * @param assetPath Path to asset bundle
     * @return true if registered successfully
     */
    static bool RegisterCosmetic(const char* cosmeticId, const char* cosmeticName, const char* assetPath);
    
private:
    struct CustomCosmetic {
        std::string id;
        std::string name;
        std::string assetPath;
        std::string type; // "face", "body", "hat", "club"
    };
    
    static bool s_Initialized;
    static std::vector<CustomCosmetic> s_CustomCosmetics;
    
    // Unity class references
    static MonoClass* s_PlayerCosmeticsClass;
    static MonoClass* s_CosmeticsSwitcherClass;
    static MonoClass* s_CosmeticsUnlocksClass;
    
    // Methods for injecting cosmetics
    static MonoMethod* s_SetCosmeticMethod;
    static MonoMethod* s_UnlockCosmeticMethod;
};

} // namespace ModLoader
