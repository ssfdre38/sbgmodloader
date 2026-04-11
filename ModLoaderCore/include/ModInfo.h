#pragma once
#include <string>
#include <vector>

namespace ModLoader {

/// Dependency specification
struct ModDependency {
    std::string id;
    std::string version;  // Semantic version range (e.g., ">=1.0.0", "^2.1.0")
    
    ModDependency() = default;
    ModDependency(const std::string& id_, const std::string& version_)
        : id(id_), version(version_) {}
};

/// Addressables content configuration
struct ModContent {
    bool addressables = false;
    std::string catalogPath;
    std::string primaryAsset;
    std::string assetType;  // scene, prefab, material, etc.
};

/// Complete mod metadata from mod.json
struct ModInfo {
    // Required fields
    std::string id;
    std::string name;
    std::string author;
    std::string version;
    std::string description;
    std::string type;  // map, gamemode, weapon, character, audio, ui, script, core
    
    // Optional fields
    std::string gameVersion;
    std::string url;
    std::vector<std::string> tags;
    std::vector<ModDependency> dependencies;
    
    // Content configuration
    ModContent content;
    
    // Runtime info (set after loading)
    std::string folderPath;     // Full path to mod folder
    bool isLoaded = false;      // Has the mod been loaded?
    bool hasErrors = false;     // Did loading fail?
    std::string errorMessage;   // Error details if failed
    
    ModInfo() = default;
    
    /// Parse from JSON file
    static ModInfo FromJsonFile(const std::string& jsonFilePath);
    
    /// Validate that required fields are present
    bool Validate(std::string& outError) const;
    
    /// Get display name with version
    std::string GetDisplayName() const { 
        return name + " v" + version; 
    }
};

}  // namespace ModLoader
