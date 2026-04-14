using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using SBGModLauncher.Services;

namespace SBGModLauncher.ViewModels
{
    public partial class ModBrowserViewModel : ObservableObject
    {
        private readonly ModRepositoryService _repoService;
        private readonly string _gamePath;
        
        [ObservableProperty]
        private ObservableCollection<RepositoryMod> _availableMods = new();
        
        [ObservableProperty]
        private ObservableCollection<RepositoryMod> _filteredMods = new();
        
        [ObservableProperty]
        private RepositoryMod? _selectedMod;
        
        [ObservableProperty]
        private string _searchQuery = string.Empty;
        
        [ObservableProperty]
        private bool _isLoading;
        
        [ObservableProperty]
        private string _statusMessage = "Ready";
        
        [ObservableProperty]
        private double _downloadProgress;
        
        [ObservableProperty]
        private bool _showFeaturedOnly;
        
        [ObservableProperty]
        private string _selectedTypeFilter = "All";
        
        public ObservableCollection<string> TypeFilters { get; } = new()
        {
            "All", "Maps", "Game Modes", "Characters", "Items"
        };
        
        public ModBrowserViewModel(string gamePath)
        {
            _gamePath = gamePath;
            _repoService = new ModRepositoryService();
            
            // Load mods on startup
            _ = RefreshModsAsync();
        }
        
        [RelayCommand]
        private async Task RefreshModsAsync()
        {
            IsLoading = true;
            StatusMessage = "Fetching mods from repository...";
            
            try
            {
                var mods = await _repoService.FetchAvailableModsAsync();
                
                AvailableMods.Clear();
                foreach (var mod in mods)
                {
                    AvailableMods.Add(mod);
                }
                
                ApplyFilters();
                StatusMessage = $"Found {AvailableMods.Count} mods";
            }
            catch (Exception ex)
            {
                StatusMessage = $"Error: {ex.Message}";
                MessageBox.Show(
                    $"Failed to fetch mods:\n{ex.Message}",
                    "Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }
            finally
            {
                IsLoading = false;
            }
        }
        
        [RelayCommand]
        private async Task SearchModsAsync()
        {
            if (string.IsNullOrWhiteSpace(SearchQuery))
            {
                ApplyFilters();
                return;
            }
            
            IsLoading = true;
            StatusMessage = $"Searching for '{SearchQuery}'...";
            
            try
            {
                var results = await _repoService.SearchModsAsync(SearchQuery);
                
                FilteredMods.Clear();
                foreach (var mod in results)
                {
                    FilteredMods.Add(mod);
                }
                
                StatusMessage = $"Found {FilteredMods.Count} results";
            }
            catch (Exception ex)
            {
                StatusMessage = $"Search error: {ex.Message}";
            }
            finally
            {
                IsLoading = false;
            }
        }
        
        [RelayCommand]
        private async Task DownloadModAsync(RepositoryMod? mod)
        {
            if (mod == null) return;
            
            var result = MessageBox.Show(
                $"Download and install '{mod.Name}' v{mod.Version}?\n\n" +
                $"Author: {mod.Author}\n" +
                $"Size: {mod.FileSizeDisplay}\n" +
                $"Type: {mod.Type}",
                "Confirm Download",
                MessageBoxButton.YesNo,
                MessageBoxImage.Question);
            
            if (result != MessageBoxResult.Yes) return;
            
            IsLoading = true;
            StatusMessage = $"Downloading {mod.Name}...";
            DownloadProgress = 0;
            
            try
            {
                var typeFolder = mod.Type switch
                {
                    "map" => "Maps",
                    "gamemode" => "GameModes",
                    "character" => "Characters",
                    "item" => "Items",
                    _ => "Mods"
                };
                
                var targetDir = System.IO.Path.Combine(_gamePath, "Mods", typeFolder);
                
                var progress = new Progress<double>(p =>
                {
                    DownloadProgress = p;
                    StatusMessage = $"Downloading {mod.Name}... {p:F0}%";
                });
                
                bool success = await _repoService.DownloadModAsync(mod, targetDir, progress);
                
                if (success)
                {
                    StatusMessage = $"✅ {mod.Name} installed successfully!";
                    MessageBox.Show(
                        $"'{mod.Name}' has been installed!\n\nRestart the game to use it.",
                        "Install Complete",
                        MessageBoxButton.OK,
                        MessageBoxImage.Information);
                }
                else
                {
                    StatusMessage = $"❌ Failed to install {mod.Name}";
                    MessageBox.Show(
                        $"Failed to install '{mod.Name}'.\nCheck your internet connection and try again.",
                        "Install Failed",
                        MessageBoxButton.OK,
                        MessageBoxImage.Error);
                }
            }
            catch (Exception ex)
            {
                StatusMessage = $"Error: {ex.Message}";
                MessageBox.Show(
                    $"Download failed:\n{ex.Message}",
                    "Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }
            finally
            {
                IsLoading = false;
                DownloadProgress = 0;
            }
        }
        
        [RelayCommand]
        private async Task ShowFeaturedModsAsync()
        {
            IsLoading = true;
            StatusMessage = "Loading featured mods...";
            
            try
            {
                var featured = await _repoService.GetFeaturedModsAsync();
                
                FilteredMods.Clear();
                foreach (var mod in featured)
                {
                    FilteredMods.Add(mod);
                }
                
                StatusMessage = $"Showing {FilteredMods.Count} featured mods";
            }
            catch (Exception ex)
            {
                StatusMessage = $"Error: {ex.Message}";
            }
            finally
            {
                IsLoading = false;
            }
        }
        
        [RelayCommand]
        private async Task ShowRecentModsAsync()
        {
            IsLoading = true;
            StatusMessage = "Loading recent mods...";
            
            try
            {
                var recent = await _repoService.GetRecentModsAsync(20);
                
                FilteredMods.Clear();
                foreach (var mod in recent)
                {
                    FilteredMods.Add(mod);
                }
                
                StatusMessage = $"Showing {FilteredMods.Count} recent mods";
            }
            catch (Exception ex)
            {
                StatusMessage = $"Error: {ex.Message}";
            }
            finally
            {
                IsLoading = false;
            }
        }
        
        partial void OnSelectedTypeFilterChanged(string value)
        {
            ApplyFilters();
        }
        
        partial void OnShowFeaturedOnlyChanged(bool value)
        {
            ApplyFilters();
        }
        
        private void ApplyFilters()
        {
            var filtered = AvailableMods.AsEnumerable();
            
            if (ShowFeaturedOnly)
            {
                filtered = filtered.Where(m => m.Featured);
            }
            
            if (SelectedTypeFilter != "All")
            {
                var typeFilter = SelectedTypeFilter.ToLower().TrimEnd('s');
                filtered = filtered.Where(m => m.Type.ToLower() == typeFilter || 
                    (typeFilter == "game mode" && m.Type == "gamemode"));
            }
            
            FilteredMods.Clear();
            foreach (var mod in filtered.OrderByDescending(m => m.Downloads))
            {
                FilteredMods.Add(mod);
            }
            
            StatusMessage = $"Showing {FilteredMods.Count} of {AvailableMods.Count} mods";
        }
    }
}
