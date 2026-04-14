using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http;
using System.Threading.Tasks;
using Newtonsoft.Json;
using SBGModLauncher.Models;

namespace SBGModLauncher.Services
{
    /// <summary>
    /// Service for browsing and downloading mods from online repositories
    /// </summary>
    public class ModRepositoryService
    {
        private readonly HttpClient _httpClient;
        private readonly string _repositoryUrl;
        private readonly string _cacheDir;
        
        public ModRepositoryService(string repositoryUrl = "https://sbgmods.github.io/repository")
        {
            _httpClient = new HttpClient();
            _repositoryUrl = repositoryUrl;
            _cacheDir = Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
                "sbg-mod-loader",
                "repository-cache");
            
            Directory.CreateDirectory(_cacheDir);
        }
        
        /// <summary>
        /// Fetches the list of available mods from the repository
        /// </summary>
        public async Task<List<RepositoryMod>> FetchAvailableModsAsync()
        {
            try
            {
                var url = $"{_repositoryUrl}/index.json";
                var json = await _httpClient.GetStringAsync(url);
                
                // Cache the response
                var cacheFile = Path.Combine(_cacheDir, "index.json");
                await File.WriteAllTextAsync(cacheFile, json);
                
                var index = JsonConvert.DeserializeObject<RepositoryIndex>(json);
                return index?.Mods ?? new List<RepositoryMod>();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error fetching mods: {ex.Message}");
                
                // Try to use cached version
                var cacheFile = Path.Combine(_cacheDir, "index.json");
                if (File.Exists(cacheFile))
                {
                    var json = await File.ReadAllTextAsync(cacheFile);
                    var index = JsonConvert.DeserializeObject<RepositoryIndex>(json);
                    return index?.Mods ?? new List<RepositoryMod>();
                }
                
                return new List<RepositoryMod>();
            }
        }
        
        /// <summary>
        /// Downloads a mod from the repository
        /// </summary>
        public async Task<bool> DownloadModAsync(RepositoryMod mod, string targetDirectory, IProgress<double>? progress = null)
        {
            try
            {
                var downloadUrl = $"{_repositoryUrl}/mods/{mod.Id}/{mod.Version}/{mod.Id}.zip";
                
                using var response = await _httpClient.GetAsync(downloadUrl, HttpCompletionOption.ResponseHeadersRead);
                response.EnsureSuccessStatusCode();
                
                var totalBytes = response.Content.Headers.ContentLength ?? 0;
                var downloadedBytes = 0L;
                
                var tempFile = Path.Combine(Path.GetTempPath(), $"{mod.Id}.zip");
                
                using (var contentStream = await response.Content.ReadAsStreamAsync())
                using (var fileStream = new FileStream(tempFile, FileMode.Create, FileAccess.Write, FileShare.None, 8192, true))
                {
                    var buffer = new byte[8192];
                    int bytesRead;
                    
                    while ((bytesRead = await contentStream.ReadAsync(buffer, 0, buffer.Length)) > 0)
                    {
                        await fileStream.WriteAsync(buffer, 0, bytesRead);
                        downloadedBytes += bytesRead;
                        
                        if (totalBytes > 0)
                        {
                            progress?.Report((double)downloadedBytes / totalBytes * 100);
                        }
                    }
                }
                
                // Extract to target directory
                var modFolder = Path.Combine(targetDirectory, mod.Id);
                if (Directory.Exists(modFolder))
                {
                    Directory.Delete(modFolder, true);
                }
                
                System.IO.Compression.ZipFile.ExtractToDirectory(tempFile, modFolder);
                File.Delete(tempFile);
                
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error downloading mod {mod.Name}: {ex.Message}");
                return false;
            }
        }
        
        /// <summary>
        /// Checks if a mod has an update available
        /// </summary>
        public async Task<bool> HasUpdateAsync(ModInfo installedMod)
        {
            var availableMods = await FetchAvailableModsAsync();
            var repoMod = availableMods.FirstOrDefault(m => m.Id == installedMod.Id);
            
            if (repoMod == null) return false;
            
            return CompareVersions(repoMod.Version, installedMod.Version) > 0;
        }
        
        /// <summary>
        /// Gets the latest version info for a mod
        /// </summary>
        public async Task<RepositoryMod?> GetModInfoAsync(string modId)
        {
            var availableMods = await FetchAvailableModsAsync();
            return availableMods.FirstOrDefault(m => m.Id == modId);
        }
        
        /// <summary>
        /// Searches mods by name, author, or tags
        /// </summary>
        public async Task<List<RepositoryMod>> SearchModsAsync(string query)
        {
            var allMods = await FetchAvailableModsAsync();
            
            query = query.ToLower();
            
            return allMods.Where(m =>
                m.Name.ToLower().Contains(query) ||
                m.Author.ToLower().Contains(query) ||
                m.Description.ToLower().Contains(query) ||
                (m.Tags != null && m.Tags.Any(t => t.ToLower().Contains(query)))
            ).ToList();
        }
        
        /// <summary>
        /// Gets featured/popular mods
        /// </summary>
        public async Task<List<RepositoryMod>> GetFeaturedModsAsync()
        {
            var allMods = await FetchAvailableModsAsync();
            return allMods.Where(m => m.Featured).OrderByDescending(m => m.Downloads).ToList();
        }
        
        /// <summary>
        /// Gets recently updated mods
        /// </summary>
        public async Task<List<RepositoryMod>> GetRecentModsAsync(int count = 10)
        {
            var allMods = await FetchAvailableModsAsync();
            return allMods.OrderByDescending(m => m.UpdatedDate).Take(count).ToList();
        }
        
        private int CompareVersions(string version1, string version2)
        {
            var v1Parts = version1.Split('.').Select(int.Parse).ToArray();
            var v2Parts = version2.Split('.').Select(int.Parse).ToArray();
            
            for (int i = 0; i < Math.Max(v1Parts.Length, v2Parts.Length); i++)
            {
                int v1 = i < v1Parts.Length ? v1Parts[i] : 0;
                int v2 = i < v2Parts.Length ? v2Parts[i] : 0;
                
                if (v1 > v2) return 1;
                if (v1 < v2) return -1;
            }
            
            return 0;
        }
    }
    
    public class RepositoryIndex
    {
        public string Version { get; set; } = "1.0.0";
        public List<RepositoryMod> Mods { get; set; } = new();
    }
    
    public class RepositoryMod
    {
        public string Id { get; set; } = string.Empty;
        public string Name { get; set; } = string.Empty;
        public string Author { get; set; } = string.Empty;
        public string Version { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public string Type { get; set; } = string.Empty;
        public long Downloads { get; set; }
        public double Rating { get; set; }
        public int RatingCount { get; set; }
        public bool Featured { get; set; }
        public string UpdatedDate { get; set; } = string.Empty;
        public string[] Tags { get; set; } = Array.Empty<string>();
        public string ThumbnailUrl { get; set; } = string.Empty;
        public string DownloadUrl { get; set; } = string.Empty;
        public long FileSize { get; set; }
        public string MinLoaderVersion { get; set; } = "1.0.0";
        
        public string TypeDisplay => Type switch
        {
            "map" => "🗺️ Map",
            "gamemode" => "🎮 Game Mode",
            "character" => "👤 Character",
            "item" => "⚔️ Item",
            _ => "❓ Unknown"
        };
        
        public string FileSizeDisplay => FileSize switch
        {
            < 1024 => $"{FileSize} B",
            < 1024 * 1024 => $"{FileSize / 1024:F1} KB",
            _ => $"{FileSize / (1024 * 1024):F1} MB"
        };
        
        public string RatingDisplay => $"⭐ {Rating:F1} ({RatingCount})";
        
        public string DownloadsDisplay => Downloads switch
        {
            < 1000 => $"{Downloads}",
            < 1000000 => $"{Downloads / 1000:F1}K",
            _ => $"{Downloads / 1000000:F1}M"
        };
    }
}
