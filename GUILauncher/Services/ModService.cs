using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using SBGModLauncher.Models;

namespace SBGModLauncher.Services
{
    /// <summary>
    /// Service for discovering and managing mods
    /// </summary>
    public class ModService
    {
        private readonly string _modsPath;
        private readonly string _configPath;
        private Dictionary<string, bool> _modStates = new();
        
        public ModService(string gamePath)
        {
            _modsPath = Path.Combine(gamePath, "Mods");
            _configPath = Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                "sbg-mod-loader",
                "launcher-config.json");
            
            LoadModStates();
        }
        
        /// <summary>
        /// Scans all mod folders and returns discovered mods
        /// </summary>
        public List<ModInfo> DiscoverMods()
        {
            var mods = new List<ModInfo>();
            
            if (!Directory.Exists(_modsPath))
            {
                Directory.CreateDirectory(_modsPath);
                return mods;
            }
            
            // Scan each mod type folder
            var modTypes = new[] { "Maps", "GameModes", "Characters", "Items" };
            
            foreach (var typeFolder in modTypes)
            {
                var typePath = Path.Combine(_modsPath, typeFolder);
                if (!Directory.Exists(typePath)) continue;
                
                foreach (var modFolder in Directory.GetDirectories(typePath))
                {
                    var modJsonPath = Path.Combine(modFolder, "mod.json");
                    if (!File.Exists(modJsonPath)) continue;
                    
                    try
                    {
                        var mod = ParseModJson(modJsonPath, modFolder, typeFolder);
                        if (mod != null)
                        {
                            // Apply saved state
                            if (_modStates.TryGetValue(mod.Id, out bool isEnabled))
                            {
                                mod.IsEnabled = isEnabled;
                            }
                            mods.Add(mod);
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Error parsing mod.json in {modFolder}: {ex.Message}");
                    }
                }
            }
            
            // Detect conflicts
            DetectConflicts(mods);
            
            return mods;
        }
        
        private ModInfo? ParseModJson(string jsonPath, string folderPath, string typeFolder)
        {
            var json = File.ReadAllText(jsonPath);
            var jobj = JObject.Parse(json);
            
            var mod = new ModInfo
            {
                Id = jobj["id"]?.ToString() ?? Path.GetFileName(folderPath),
                Name = jobj["name"]?.ToString() ?? "Unknown Mod",
                Author = jobj["author"]?.ToString() ?? "Unknown",
                Version = jobj["version"]?.ToString() ?? "1.0.0",
                Description = jobj["description"]?.ToString() ?? "",
                FolderPath = folderPath,
                Type = typeFolder switch
                {
                    "Maps" => ModType.Map,
                    "GameModes" => ModType.GameMode,
                    "Characters" => ModType.Character,
                    "Items" => ModType.Item,
                    _ => ModType.Unknown
                }
            };
            
            // Parse dependencies
            if (jobj["dependencies"] is JArray deps)
            {
                mod.Dependencies = deps.Select(d => d.ToString()).ToArray();
            }
            
            // Parse metadata
            if (jobj["meta"] is JObject meta)
            {
                mod.Meta = new ModMetadata
                {
                    Difficulty = meta["difficulty"]?.ToString(),
                    Holes = meta["holes"]?.ToObject<int>() ?? 0,
                    Environment = meta["environment"]?.ToString(),
                    Tags = meta["tags"]?.ToObject<string[]>()
                };
            }
            
            return mod;
        }
        
        private void DetectConflicts(List<ModInfo> mods)
        {
            // Simple conflict detection: same ID
            var modGroups = mods.GroupBy(m => m.Id);
            
            foreach (var group in modGroups.Where(g => g.Count() > 1))
            {
                foreach (var mod in group)
                {
                    mod.HasConflicts = true;
                    mod.ConflictsWith = group
                        .Where(m => m != mod)
                        .Select(m => m.Name)
                        .ToArray();
                }
            }
        }
        
        /// <summary>
        /// Save mod enabled/disabled states
        /// </summary>
        public void SaveModStates(List<ModInfo> mods)
        {
            _modStates = mods.ToDictionary(m => m.Id, m => m.IsEnabled);
            
            var directory = Path.GetDirectoryName(_configPath);
            if (!string.IsNullOrEmpty(directory) && !Directory.Exists(directory))
            {
                Directory.CreateDirectory(directory);
            }
            
            File.WriteAllText(_configPath, JsonConvert.SerializeObject(_modStates, Formatting.Indented));
        }
        
        private void LoadModStates()
        {
            if (File.Exists(_configPath))
            {
                try
                {
                    var json = File.ReadAllText(_configPath);
                    _modStates = JsonConvert.DeserializeObject<Dictionary<string, bool>>(json) 
                        ?? new Dictionary<string, bool>();
                }
                catch
                {
                    _modStates = new Dictionary<string, bool>();
                }
            }
        }
        
        /// <summary>
        /// Enables or disables a mod by renaming its folder
        /// </summary>
        public bool ToggleMod(ModInfo mod, bool enable)
        {
            try
            {
                var folderName = Path.GetFileName(mod.FolderPath);
                var parentDir = Path.GetDirectoryName(mod.FolderPath);
                
                if (string.IsNullOrEmpty(parentDir)) return false;
                
                if (enable && folderName.StartsWith(".disabled_"))
                {
                    // Enable: Remove .disabled_ prefix
                    var newName = folderName.Substring(".disabled_".Length);
                    var newPath = Path.Combine(parentDir, newName);
                    Directory.Move(mod.FolderPath, newPath);
                    mod.FolderPath = newPath;
                    mod.IsEnabled = true;
                }
                else if (!enable && !folderName.StartsWith(".disabled_"))
                {
                    // Disable: Add .disabled_ prefix
                    var newName = ".disabled_" + folderName;
                    var newPath = Path.Combine(parentDir, newName);
                    Directory.Move(mod.FolderPath, newPath);
                    mod.FolderPath = newPath;
                    mod.IsEnabled = false;
                }
                
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error toggling mod {mod.Name}: {ex.Message}");
                return false;
            }
        }
    }
}
