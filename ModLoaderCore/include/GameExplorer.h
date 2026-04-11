#pragma once
#include <string>
#include <vector>
#include <map>

namespace ModLoader {

struct ClassInfo {
    std::string name;
    std::string nameSpace;
    std::string assembly;
    std::vector<std::string> methods;
    int methodCount = 0;
};

struct AssemblyInfo {
    std::string name;
    std::vector<std::string> classes;
    int classCount = 0;
};

class GameExplorer {
public:
    // Explore all game assemblies and find key systems
    static void ExploreGame();
    
    // Find classes related to specific systems
    static std::vector<ClassInfo> FindGameModeClasses();
    static std::vector<ClassInfo> FindWeaponClasses();
    static std::vector<ClassInfo> FindCharacterClasses();
    static std::vector<ClassInfo> FindUIClasses();
    static std::vector<ClassInfo> FindNetworkClasses();
    
    // Get all assemblies
    static std::vector<AssemblyInfo> GetAllAssemblies();
    
    // Search for classes by name pattern
    static std::vector<ClassInfo> SearchClasses(const char* pattern);
    
    // Get detailed info about a specific class
    static ClassInfo GetClassDetails(const char* assemblyName, const char* nameSpace, const char* className);
    
    // Inspect a class deeply - get all fields, properties, methods
    static void InspectClass(const char* assemblyName, const char* nameSpace, const char* className);
    static void InspectGameModeSystem(); // Inspect all game mode related classes
    
    // Export findings to file
    static void ExportToFile(const char* filename);
    
private:
    static bool MatchesPattern(const char* str, const char* pattern);
    static std::vector<ClassInfo> s_DiscoveredClasses;
    static std::map<std::string, std::vector<std::string>> s_AssemblyClasses;
};

} // namespace ModLoader
