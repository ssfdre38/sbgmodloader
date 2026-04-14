using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Input;
using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Ookii.Dialogs.Wpf;
using SBGModLauncher.Models;
using SBGModLauncher.Services;

namespace SBGModLauncher.ViewModels
{
    public partial class MainViewModel : ObservableObject
    {
        private readonly ModService _modService;
        private readonly GameLauncherService _gameLauncher;
        
        [ObservableProperty]
        private string _gamePath = string.Empty;
        
        [ObservableProperty]
        private string _statusMessage = "Ready";
        
        [ObservableProperty]
        private bool _isLoading;
        
        [ObservableProperty]
        private ObservableCollection<ModInfo> _allMods = new();
        
        [ObservableProperty]
        private ObservableCollection<ModInfo> _maps = new();
        
        [ObservableProperty]
        private ObservableCollection<ModInfo> _gameModes = new();
        
        [ObservableProperty]
        private ObservableCollection<ModInfo> _characters = new();
        
        [ObservableProperty]
        private ObservableCollection<ModInfo> _items = new();
        
        [ObservableProperty]
        private ModInfo? _selectedMod;
        
        [ObservableProperty]
        private int _totalModsCount;
        
        [ObservableProperty]
        private int _enabledModsCount;
        
        [ObservableProperty]
        private bool _gameInstalled;
        
        [ObservableProperty]
        private string _gameVersion = "Unknown";
        
        public MainViewModel()
        {
            // Try to auto-detect game path
            _gamePath = AutoDetectGamePath();
            
            _modService = new ModService(_gamePath);
            _gameLauncher = new GameLauncherService(_gamePath);
            
            RefreshMods();
            CheckGameInstallation();
        }
        
        [RelayCommand]
        private void RefreshMods()
        {
            IsLoading = true;
            StatusMessage = "Scanning for mods...";
            
            try
            {
                var mods = _modService.DiscoverMods();
                
                AllMods.Clear();
                Maps.Clear();
                GameModes.Clear();
                Characters.Clear();
                Items.Clear();
                
                foreach (var mod in mods)
                {
                    AllMods.Add(mod);
                    
                    switch (mod.Type)
                    {
                        case ModType.Map:
                            Maps.Add(mod);
                            break;
                        case ModType.GameMode:
                            GameModes.Add(mod);
                            break;
                        case ModType.Character:
                            Characters.Add(mod);
                            break;
                        case ModType.Item:
                            Items.Add(mod);
                            break;
                    }
                }
                
                TotalModsCount = AllMods.Count;
                EnabledModsCount = AllMods.Count(m => m.IsEnabled);
                
                StatusMessage = $"Found {TotalModsCount} mods ({EnabledModsCount} enabled)";
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
        private void ToggleMod(ModInfo mod)
        {
            if (mod == null) return;
            
            bool newState = !mod.IsEnabled;
            
            if (_modService.ToggleMod(mod, newState))
            {
                mod.IsEnabled = newState;
                EnabledModsCount = AllMods.Count(m => m.IsEnabled);
                _modService.SaveModStates(AllMods.ToList());
                StatusMessage = $"{mod.Name} {(newState ? "enabled" : "disabled")}";
            }
            else
            {
                StatusMessage = $"Failed to toggle {mod.Name}";
            }
        }
        
        [RelayCommand]
        private void LaunchWithMods()
        {
            try
            {
                StatusMessage = "Launching game with mods...";
                _gameLauncher.LaunchWithMods();
                StatusMessage = "Game launched successfully!";
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    $"Failed to launch game:\n{ex.Message}",
                    "Launch Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
                StatusMessage = "Launch failed";
            }
        }
        
        [RelayCommand]
        private void LaunchVanilla()
        {
            try
            {
                StatusMessage = "Launching vanilla game...";
                _gameLauncher.LaunchVanilla();
                StatusMessage = "Game launched successfully!";
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    $"Failed to launch game:\n{ex.Message}",
                    "Launch Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
                StatusMessage = "Launch failed";
            }
        }
        
        [RelayCommand]
        private void BrowseGamePath()
        {
            var dialog = new VistaFolderBrowserDialog
            {
                Description = "Select Super Battle Golf installation folder",
                SelectedPath = GamePath,
                UseDescriptionForTitle = true
            };
            
            if (dialog.ShowDialog() == true)
            {
                GamePath = dialog.SelectedPath;
                CheckGameInstallation();
                RefreshMods();
            }
        }
        
        [RelayCommand]
        private void EnableAllMods()
        {
            foreach (var mod in AllMods.Where(m => !m.IsEnabled))
            {
                _modService.ToggleMod(mod, true);
                mod.IsEnabled = true;
            }
            
            EnabledModsCount = AllMods.Count;
            _modService.SaveModStates(AllMods.ToList());
            StatusMessage = "All mods enabled";
        }
        
        [RelayCommand]
        private void DisableAllMods()
        {
            foreach (var mod in AllMods.Where(m => m.IsEnabled))
            {
                _modService.ToggleMod(mod, false);
                mod.IsEnabled = false;
            }
            
            EnabledModsCount = 0;
            _modService.SaveModStates(AllMods.ToList());
            StatusMessage = "All mods disabled";
        }
        
        [RelayCommand]
        private void OpenModsFolder()
        {
            var modsPath = Path.Combine(GamePath, "Mods");
            if (Directory.Exists(modsPath))
            {
                System.Diagnostics.Process.Start("explorer.exe", modsPath);
            }
            else
            {
                MessageBox.Show(
                    "Mods folder not found. Check game path.",
                    "Folder Not Found",
                    MessageBoxButton.OK,
                    MessageBoxImage.Warning);
            }
        }
        
        private void CheckGameInstallation()
        {
            GameInstalled = _gameLauncher.IsGameInstalled();
            GameVersion = _gameLauncher.GetGameVersion();
        }
        
        private string AutoDetectGamePath()
        {
            // Common install locations
            var possiblePaths = new[]
            {
                @"C:\Program Files\Super Battle Golf",
                @"C:\Program Files (x86)\Super Battle Golf",
                @"D:\Games\Super Battle Golf",
                @"C:\Games\Super Battle Golf",
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Super Battle Golf")
            };
            
            foreach (var path in possiblePaths)
            {
                if (Directory.Exists(path) && File.Exists(Path.Combine(path, "Super Battle Golf.exe")))
                {
                    return path;
                }
            }
            
            // Check current directory
            var currentDir = Directory.GetCurrentDirectory();
            if (File.Exists(Path.Combine(currentDir, "Super Battle Golf.exe")))
            {
                return currentDir;
            }
            
            // Default to Program Files
            return Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Super Battle Golf");
        }
    }
}
