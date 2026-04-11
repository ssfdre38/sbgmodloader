#include "../include/GameExplorer.h"
#include "../include/MonoHelper.h"
#include "../include/Log.h"
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace ModLoader::Mono;

namespace ModLoader {

std::vector<ClassInfo> GameExplorer::s_DiscoveredClasses;
std::map<std::string, std::vector<std::string>> GameExplorer::s_AssemblyClasses;

void GameExplorer::ExploreGame() {
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("🔍 EXPLORING GAME ARCHITECTURE");
    Log::Info("═══════════════════════════════════════════════");
    
    s_DiscoveredClasses.clear();
    s_AssemblyClasses.clear();
    
    // Get all assemblies
    auto assemblies = MonoHelper::GetAssemblies();
    Log::Info("Found %d assemblies", assemblies.size());
    
    // Focus on GameAssembly - this is where game code lives
    MonoAssembly* gameAsm = MonoHelper::FindAssembly("GameAssembly");
    if (gameAsm) {
        Log::Info("");
        Log::Info("📦 Enumerating ALL classes in GameAssembly...");
        
        MonoImage* image = MonoHelper::mono_assembly_get_image(gameAsm);
        if (image) {
            Log::Info("  • Got MonoImage for GameAssembly");
            auto allClasses = MonoHelper::GetAllClasses(image);
            Log::Info("Found %d classes in GameAssembly!", allClasses.size());
            
            // Store all class names
            for (auto klass : allClasses) {
                const char* nameSpace = MonoHelper::GetClassNamespace(klass);
                const char* className = MonoHelper::GetClassName(klass);
                
                std::string fullName;
                if (nameSpace && strlen(nameSpace) > 0) {
                    fullName = std::string(nameSpace) + "." + std::string(className);
                } else {
                    fullName = std::string(className);
                }
                
                ClassInfo info;
                info.name = className;
                info.nameSpace = nameSpace ? nameSpace : "";
                info.assembly = "GameAssembly";
                
                auto methods = MonoHelper::GetMethods(klass);
                info.methodCount = methods.size();
                
                // Store first 5 method names
                for (size_t i = 0; i < methods.size() && i < 5; i++) {
                    info.methods.push_back(MonoHelper::GetMethodName(methods[i]));
                }
                
                s_DiscoveredClasses.push_back(info);
            }
        } else {
            Log::Error("Failed to get MonoImage from GameAssembly!");
        }
    } else {
        Log::Error("GameAssembly not found! Cannot enumerate classes.");
    }
    
    Log::Info("");
    Log::Info("Searching for key game systems...");
    
    auto gameModes = FindGameModeClasses();
    auto weapons = FindWeaponClasses();
    auto characters = FindCharacterClasses();
    auto ui = FindUIClasses();
    auto network = FindNetworkClasses();
    
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("✅ EXPLORATION COMPLETE");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("Total classes discovered: %d", s_DiscoveredClasses.size());
    Log::Info("Found:");
    Log::Info("  • %d GameMode-related classes", gameModes.size());
    Log::Info("  • %d Weapon-related classes", weapons.size());
    Log::Info("  • %d Character-related classes", characters.size());
    Log::Info("  • %d UI-related classes", ui.size());
    Log::Info("  • %d Network-related classes", network.size());
}

std::vector<ClassInfo> GameExplorer::FindGameModeClasses() {
    std::vector<ClassInfo> results;
    
    // Common patterns for game mode classes
    const char* patterns[] = {
        "GameMode", "RuleSet", "Rules", "Mode", 
        "Match", "GameType", "GameState", "Settings"
    };
    
    for (const auto& cls : s_DiscoveredClasses) {
        for (const char* pattern : patterns) {
            if (MatchesPattern(cls.name.c_str(), pattern)) {
                results.push_back(cls);
                break;
            }
        }
    }
    
    Log::Info("");
    Log::Info("🎮 GAME MODE CLASSES:");
    for (const auto& cls : results) {
        Log::Info("  • %s.%s (%s)", cls.nameSpace.c_str(), cls.name.c_str(), cls.assembly.c_str());
        Log::Info("    Methods: %d", cls.methodCount);
    }
    
    return results;
}

std::vector<ClassInfo> GameExplorer::FindWeaponClasses() {
    std::vector<ClassInfo> results;
    
    const char* patterns[] = {
        "Weapon", "Gun", "Item", "Projectile", 
        "Bullet", "Ammo", "Launcher", "Throw"
    };
    
    for (const auto& cls : s_DiscoveredClasses) {
        for (const char* pattern : patterns) {
            if (MatchesPattern(cls.name.c_str(), pattern)) {
                results.push_back(cls);
                break;
            }
        }
    }
    
    Log::Info("");
    Log::Info("🔫 WEAPON CLASSES:");
    for (const auto& cls : results) {
        Log::Info("  • %s.%s (%s)", cls.nameSpace.c_str(), cls.name.c_str(), cls.assembly.c_str());
        Log::Info("    Methods: %d", cls.methodCount);
    }
    
    return results;
}

std::vector<ClassInfo> GameExplorer::FindCharacterClasses() {
    std::vector<ClassInfo> results;
    
    const char* patterns[] = {
        "Character", "Player", "Avatar", "Controller",
        "Skin", "Costume", "Loadout", "Pawn"
    };
    
    for (const auto& cls : s_DiscoveredClasses) {
        for (const char* pattern : patterns) {
            if (MatchesPattern(cls.name.c_str(), pattern)) {
                results.push_back(cls);
                break;
            }
        }
    }
    
    Log::Info("");
    Log::Info("👤 CHARACTER CLASSES:");
    for (const auto& cls : results) {
        Log::Info("  • %s.%s (%s)", cls.nameSpace.c_str(), cls.name.c_str(), cls.assembly.c_str());
        Log::Info("    Methods: %d", cls.methodCount);
    }
    
    return results;
}

std::vector<ClassInfo> GameExplorer::FindUIClasses() {
    std::vector<ClassInfo> results;
    
    const char* patterns[] = {
        "Menu", "UI", "HUD", "Panel", "Screen",
        "Canvas", "Dialog", "Popup", "Widget"
    };
    
    for (const auto& cls : s_DiscoveredClasses) {
        for (const char* pattern : patterns) {
            if (MatchesPattern(cls.name.c_str(), pattern)) {
                results.push_back(cls);
                break;
            }
        }
    }
    
    Log::Info("");
    Log::Info("🖥️ UI CLASSES:");
    for (const auto& cls : results) {
        Log::Info("  • %s.%s (%s)", cls.nameSpace.c_str(), cls.name.c_str(), cls.assembly.c_str());
        Log::Info("    Methods: %d", cls.methodCount);
    }
    
    return results;
}

std::vector<ClassInfo> GameExplorer::FindNetworkClasses() {
    std::vector<ClassInfo> results;
    
    const char* patterns[] = {
        "Network", "Multiplayer", "Lobby", "Server",
        "Client", "Connection", "Session", "Sync"
    };
    
    for (const auto& cls : s_DiscoveredClasses) {
        for (const char* pattern : patterns) {
            if (MatchesPattern(cls.name.c_str(), pattern)) {
                results.push_back(cls);
                break;
            }
        }
    }
    
    Log::Info("");
    Log::Info("🌐 NETWORK CLASSES:");
    for (const auto& cls : results) {
        Log::Info("  • %s.%s (%s)", cls.nameSpace.c_str(), cls.name.c_str(), cls.assembly.c_str());
        Log::Info("    Methods: %d", cls.methodCount);
    }
    
    return results;
}

std::vector<ClassInfo> GameExplorer::SearchClasses(const char* pattern) {
    std::vector<ClassInfo> results;
    
    // Get common game assemblies to search
    const char* assembliesToSearch[] = {
        "GameAssembly",
        "Assembly-CSharp",
        "SharedAssembly",
        nullptr
    };
    
    for (int i = 0; assembliesToSearch[i] != nullptr; i++) {
        MonoAssembly* assembly = MonoHelper::FindAssembly(assembliesToSearch[i]);
        if (!assembly) continue;
        
        // Try common namespace patterns
        const char* namespaces[] = {
            "",  // Global namespace
            "Game",
            "SBG",
            "SuperBattleGolf",
            "Gameplay",
            nullptr
        };
        
        for (int j = 0; namespaces[j] != nullptr; j++) {
            // Try to find class with pattern in name
            MonoClass* klass = MonoHelper::FindClass(assembliesToSearch[i], namespaces[j], pattern);
            if (klass) {
                ClassInfo info;
                info.name = MonoHelper::GetClassName(klass);
                info.nameSpace = MonoHelper::GetClassNamespace(klass);
                info.assembly = assembliesToSearch[i];
                
                auto methods = MonoHelper::GetMethods(klass);
                info.methodCount = methods.size();
                
                // Store first 10 method names
                for (size_t k = 0; k < methods.size() && k < 10; k++) {
                    info.methods.push_back(MonoHelper::GetMethodName(methods[k]));
                }
                
                results.push_back(info);
            }
        }
    }
    
    return results;
}

bool GameExplorer::MatchesPattern(const char* str, const char* pattern) {
    std::string strLower = str;
    std::string patternLower = pattern;
    
    std::transform(strLower.begin(), strLower.end(), strLower.begin(),
        [](unsigned char c) { return std::tolower(c); });
    std::transform(patternLower.begin(), patternLower.end(), patternLower.begin(),
        [](unsigned char c) { return std::tolower(c); });
    
    return strLower.find(patternLower) != std::string::npos;
}

void GameExplorer::ExportToFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        Log::Error("Failed to open file for export: %s", filename);
        return;
    }
    
    file << "# Super Battle Golf - Game Architecture Analysis\n\n";
    file << "Total Classes Discovered: " << s_DiscoveredClasses.size() << "\n\n";
    
    file << "## All Classes (GameAssembly)\n\n";
    for (const auto& cls : s_DiscoveredClasses) {
        file << "### " << cls.nameSpace;
        if (!cls.nameSpace.empty()) file << ".";
        file << cls.name << "\n";
        file << "**Methods:** " << cls.methodCount << "\n";
        if (!cls.methods.empty()) {
            file << "**Sample Methods:**\n";
            for (const auto& method : cls.methods) {
                file << "- " << method << "\n";
            }
        }
        file << "\n";
    }
    
    file << "\n## Game Mode Classes\n\n";
    auto gameModes = FindGameModeClasses();
    for (const auto& cls : gameModes) {
        file << "### " << cls.nameSpace << "." << cls.name << "\n";
        file << "**Assembly:** " << cls.assembly << "\n\n";
        file << "**Methods (" << cls.methodCount << "):**\n";
        for (const auto& method : cls.methods) {
            file << "- " << method << "\n";
        }
        file << "\n";
    }
    
    file << "\n## Weapon Classes\n\n";
    auto weapons = FindWeaponClasses();
    for (const auto& cls : weapons) {
        file << "### " << cls.nameSpace << "." << cls.name << "\n";
        file << "**Assembly:** " << cls.assembly << "\n\n";
        file << "**Methods (" << cls.methodCount << "):**\n";
        for (const auto& method : cls.methods) {
            file << "- " << method << "\n";
        }
        file << "\n";
    }
    
    file << "\n## Character Classes\n\n";
    auto characters = FindCharacterClasses();
    for (const auto& cls : characters) {
        file << "### " << cls.nameSpace << "." << cls.name << "\n";
        file << "**Assembly:** " << cls.assembly << "\n\n";
        file << "**Methods (" << cls.methodCount << "):**\n";
        for (const auto& method : cls.methods) {
            file << "- " << method << "\n";
        }
        file << "\n";
    }
    
    file.close();
    Log::Info("✅ Exported architecture analysis to: %s", filename);
}

void GameExplorer::InspectClass(const char* assemblyName, const char* nameSpace, const char* className) {
    Log::Info("");
    Log::Info("🔬 Inspecting Class: %s.%s", nameSpace, className);
    Log::Info("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
    
    MonoClass* klass = MonoHelper::FindClass(assemblyName, nameSpace, className);
    if (!klass) {
        Log::Error("  ❌ Class not found!");
        return;
    }
    
    // Get all methods
    auto methods = MonoHelper::GetMethods(klass);
    Log::Info("  📋 Methods (%d):", methods.size());
    for (size_t i = 0; i < methods.size() && i < 20; i++) {
        std::string methodName = MonoHelper::GetMethodName(methods[i]);
        Log::Info("    • %s", methodName.c_str());
    }
    if (methods.size() > 20) {
        Log::Info("    ... and %d more", methods.size() - 20);
    }
    
    // Get all fields
    // TODO: Add GetFields and GetFieldName to MonoHelper
    /*
    auto fields = MonoHelper::GetFields(klass);
    Log::Info("  📦 Fields (%d):", fields.size());
    for (size_t i = 0; i < fields.size() && i < 20; i++) {
        std::string fieldName = MonoHelper::GetFieldName(fields[i]);
        Log::Info("    • %s", fieldName.c_str());
    }
    if (fields.size() > 20) {
        Log::Info("    ... and %d more", fields.size() - 20);
    }
    */
    
    Log::Info("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
}

void GameExplorer::InspectGameModeSystem() {
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("🎮 INSPECTING GAME MODE SYSTEM");
    Log::Info("═══════════════════════════════════════════════");
    
    // Key classes to inspect
    const char* classesToInspect[][3] = {
        {"GameAssembly", "", "MatchSetupRules"},
        {"GameAssembly", "", "MatchSettings"},
        {"GameAssembly", "", "MatchState"},
        {"GameAssembly", "", "Rule"},
        {"GameAssembly", "", "RuleCategory"},
        {"GameAssembly", "", "Preset"},
        {"GameAssembly", "", "MatchSetupMenu"},
        {"GameAssembly", "", "GolfHole"},
        {"GameAssembly", "", "HoleData"},
        {"GameAssembly", "", "PlayerMatchResolution"}
    };
    
    for (int i = 0; i < 10; i++) {
        InspectClass(classesToInspect[i][0], classesToInspect[i][1], classesToInspect[i][2]);
    }
    
    Log::Info("");
    Log::Info("═══════════════════════════════════════════════");
    Log::Info("✅ GAME MODE SYSTEM INSPECTION COMPLETE");
    Log::Info("═══════════════════════════════════════════════");
}

} // namespace ModLoader
