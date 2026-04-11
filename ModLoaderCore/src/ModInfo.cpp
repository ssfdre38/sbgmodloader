#include "ModInfo.h"
#include "Log.h"
#include <fstream>
#include <filesystem>

// Include nlohmann/json single-header library
#include "../../ThirdParty/json/json.hpp"
using json = nlohmann::json;

namespace fs = std::filesystem;

namespace ModLoader {

ModInfo ModInfo::FromJsonFile(const std::string& jsonFilePath) {
    ModInfo info;
    
    try {
        // Read file
        std::ifstream file(jsonFilePath);
        if (!file.is_open()) {
            LOG_ERROR("Failed to open mod.json: %s", jsonFilePath.c_str());
            info.hasErrors = true;
            info.errorMessage = "Failed to open file";
            return info;
        }
        
        // Parse JSON
        json j;
        file >> j;
        
        // Required fields
        if (j.contains("id")) info.id = j["id"].get<std::string>();
        if (j.contains("name")) info.name = j["name"].get<std::string>();
        if (j.contains("author")) info.author = j["author"].get<std::string>();
        if (j.contains("version")) info.version = j["version"].get<std::string>();
        if (j.contains("description")) info.description = j["description"].get<std::string>();
        if (j.contains("type")) info.type = j["type"].get<std::string>();
        
        // Optional fields
        if (j.contains("gameVersion")) info.gameVersion = j["gameVersion"].get<std::string>();
        if (j.contains("url")) info.url = j["url"].get<std::string>();
        
        // Tags array
        if (j.contains("tags") && j["tags"].is_array()) {
            for (const auto& tag : j["tags"]) {
                info.tags.push_back(tag.get<std::string>());
            }
        }
        
        // Dependencies array
        if (j.contains("dependencies") && j["dependencies"].is_array()) {
            for (const auto& dep : j["dependencies"]) {
                ModDependency dependency;
                if (dep.contains("id")) dependency.id = dep["id"].get<std::string>();
                if (dep.contains("version")) dependency.version = dep["version"].get<std::string>();
                info.dependencies.push_back(dependency);
            }
        }
        
        // Content configuration
        if (j.contains("content") && j["content"].is_object()) {
            const auto& content = j["content"];
            if (content.contains("addressables")) 
                info.content.addressables = content["addressables"].get<bool>();
            if (content.contains("catalogPath")) 
                info.content.catalogPath = content["catalogPath"].get<std::string>();
            if (content.contains("primaryAsset")) 
                info.content.primaryAsset = content["primaryAsset"].get<std::string>();
            if (content.contains("assetType")) 
                info.content.assetType = content["assetType"].get<std::string>();
        }
        
        // Store folder path (parent directory of mod.json)
        info.folderPath = fs::path(jsonFilePath).parent_path().string();
        
        LOG_INFO("✅ Parsed mod.json: %s", info.GetDisplayName().c_str());
        
    } catch (const json::parse_error& e) {
        LOG_ERROR("JSON parse error in %s: %s", jsonFilePath.c_str(), e.what());
        info.hasErrors = true;
        info.errorMessage = std::string("JSON parse error: ") + e.what();
    } catch (const std::exception& e) {
        LOG_ERROR("Error reading mod.json %s: %s", jsonFilePath.c_str(), e.what());
        info.hasErrors = true;
        info.errorMessage = e.what();
    }
    
    return info;
}

bool ModInfo::Validate(std::string& outError) const {
    // Check required fields
    if (id.empty()) {
        outError = "Missing required field: id";
        return false;
    }
    if (name.empty()) {
        outError = "Missing required field: name";
        return false;
    }
    if (author.empty()) {
        outError = "Missing required field: author";
        return false;
    }
    if (version.empty()) {
        outError = "Missing required field: version";
        return false;
    }
    if (type.empty()) {
        outError = "Missing required field: type";
        return false;
    }
    
    // Validate type
    const std::vector<std::string> validTypes = {
        "map", "gamemode", "weapon", "character", "audio", "ui", "script", "core"
    };
    bool validType = false;
    for (const auto& validT : validTypes) {
        if (type == validT) {
            validType = true;
            break;
        }
    }
    if (!validType) {
        outError = "Invalid type: " + type + " (must be one of: map, gamemode, weapon, character, audio, ui, script, core)";
        return false;
    }
    
    // If addressables content, validate catalog path
    if (content.addressables && content.catalogPath.empty()) {
        outError = "Addressables enabled but catalogPath is missing";
        return false;
    }
    
    return true;
}

}  // namespace ModLoader
