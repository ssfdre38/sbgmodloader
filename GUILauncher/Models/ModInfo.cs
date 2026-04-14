using System;

namespace SBGModLauncher.Models
{
    /// <summary>
    /// Represents a mod with its metadata and state
    /// </summary>
    public class ModInfo
    {
        public string Id { get; set; } = string.Empty;
        public string Name { get; set; } = string.Empty;
        public string Author { get; set; } = string.Empty;
        public string Version { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public ModType Type { get; set; }
        public string FolderPath { get; set; } = string.Empty;
        public bool IsEnabled { get; set; } = true;
        public bool HasConflicts { get; set; }
        public string[] ConflictsWith { get; set; } = Array.Empty<string>();
        public string[] Dependencies { get; set; } = Array.Empty<string>();
        public ModMetadata? Meta { get; set; }
        
        /// <summary>
        /// Display text for mod type
        /// </summary>
        public string TypeDisplay => Type switch
        {
            ModType.Map => "🗺️ Map",
            ModType.GameMode => "🎮 Game Mode",
            ModType.Character => "👤 Character",
            ModType.Item => "⚔️ Item",
            _ => "❓ Unknown"
        };
        
        /// <summary>
        /// Full display name with version
        /// </summary>
        public string DisplayName => $"{Name} v{Version}";
        
        /// <summary>
        /// Status indicator
        /// </summary>
        public string StatusIndicator => IsEnabled 
            ? (HasConflicts ? "⚠️ Enabled (Conflicts)" : "✅ Enabled")
            : "❌ Disabled";
    }
    
    public enum ModType
    {
        Unknown,
        Map,
        GameMode,
        Character,
        Item
    }
    
    public class ModMetadata
    {
        public string? Difficulty { get; set; }
        public int Holes { get; set; }
        public string? Environment { get; set; }
        public string[]? Tags { get; set; }
    }
}
