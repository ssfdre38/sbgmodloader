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
            
            // Show setup prompt if game not found
            if (!GameInstalled)
            {
                var result = MessageBox.Show(
                    "Super Battle Golf was not found automatically.\n\n" +
                    "Would you like to browse for the game installation folder?\n\n" +
                    "The game folder should contain 'Super Battle Golf.exe'.",
                    "Game Not Found - First Time Setup",
                    MessageBoxButton.YesNo,
                    MessageBoxImage.Question);
                    
                if (result == MessageBoxResult.Yes)
                {
                    BrowseGamePath();
                }
            }
            else
            {
                StatusMessage = $"Ready! Game found at: {GamePath}";
            }
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
        
        [RelayCommand]
        private void OpenModBrowser()
        {
            var browserWindow = new Views.ModBrowserWindow(GamePath);
            browserWindow.Owner = Application.Current.MainWindow;
            browserWindow.ShowDialog();
            
            // Refresh mods after browser closes (user may have installed new mods)
            RefreshMods();
        }
        
        private void CheckGameInstallation()
        {
            GameInstalled = _gameLauncher.IsGameInstalled();
            GameVersion = _gameLauncher.GetGameVersion();
        }
        
        private string AutoDetectGamePath()
        {
            // Check launcher's parent directory first (if launcher is in game folder)
            var launcherDir = AppDomain.CurrentDomain.BaseDirectory;
            if (File.Exists(Path.Combine(launcherDir, "Super Battle Golf.exe")))
            {
                return launcherDir;
            }
            
            // Check parent of launcher directory
            var parentDir = Directory.GetParent(launcherDir)?.FullName;
            if (parentDir != null && File.Exists(Path.Combine(parentDir, "Super Battle Golf.exe")))
            {
                return parentDir;
            }
            
            // Steam common install locations
            var steamPaths = new[]
            {
                @"C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf",
                @"C:\Program Files\Steam\steamapps\common\Super Battle Golf",
                @"D:\SteamLibrary\steamapps\common\Super Battle Golf",
                @"D:\Steam\steamapps\common\Super Battle Golf",
                @"E:\SteamLibrary\steamapps\common\Super Battle Golf",
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFilesX86), @"Steam\steamapps\common\Super Battle Golf")
            };
            
            foreach (var path in steamPaths)
            {
                if (Directory.Exists(path) && File.Exists(Path.Combine(path, "Super Battle Golf.exe")))
                {
                    return path;
                }
            }
            
            // Epic Games Store locations
            var epicPaths = new[]
            {
                @"C:\Program Files\Epic Games\Super Battle Golf",
                @"D:\Epic Games\Super Battle Golf",
                @"E:\Epic Games\Super Battle Golf"
            };
            
            foreach (var path in epicPaths)
            {
                if (Directory.Exists(path) && File.Exists(Path.Combine(path, "Super Battle Golf.exe")))
                {
                    return path;
                }
            }
            
            // Common install locations
            var commonPaths = new[]
            {
                @"C:\Program Files\Super Battle Golf",
                @"C:\Program Files (x86)\Super Battle Golf",
                @"D:\Games\Super Battle Golf",
                @"C:\Games\Super Battle Golf",
                @"E:\Games\Super Battle Golf",
                Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ProgramFiles), "Super Battle Golf")
            };
            
            foreach (var path in commonPaths)
            {
                if (Directory.Exists(path) && File.Exists(Path.Combine(path, "Super Battle Golf.exe")))
                {
                    return path;
                }
            }
            
            // Search all drives for the game
            foreach (var drive in DriveInfo.GetDrives())
            {
                if (drive.IsReady && drive.DriveType == DriveType.Fixed)
                {
                    var searchPaths = new[]
                    {
                        Path.Combine(drive.Name, "Games", "Super Battle Golf"),
                        Path.Combine(drive.Name, "Program Files", "Super Battle Golf"),
                        Path.Combine(drive.Name, "Program Files (x86)", "Super Battle Golf"),
                        Path.Combine(drive.Name, "SteamLibrary", "steamapps", "common", "Super Battle Golf"),
                        Path.Combine(drive.Name, "Epic Games", "Super Battle Golf")
                    };
                    
                    foreach (var path in searchPaths)
                    {
                        try
                        {
                            if (Directory.Exists(path) && File.Exists(Path.Combine(path, "Super Battle Golf.exe")))
                            {
                                return path;
                            }
                        }
                        catch
                        {
                            // Skip inaccessible paths
                        }
                    }
                }
            }
            
            // Default to current directory if nothing found
            return launcherDir;
        }
    }
}
