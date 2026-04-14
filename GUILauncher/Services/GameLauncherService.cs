using System;
using System.Diagnostics;
using System.IO;

namespace SBGModLauncher.Services
{
    /// <summary>
    /// Service for launching the game with or without mods
    /// </summary>
    public class GameLauncherService
    {
        private readonly string _gamePath;
        private readonly string _gameExe;
        private readonly string _modLoaderDll;
        
        public GameLauncherService(string gamePath)
        {
            _gamePath = gamePath;
            _gameExe = Path.Combine(gamePath, "Super Battle Golf.exe");
            _modLoaderDll = Path.Combine(gamePath, "ModLoader.dll");
        }
        
        public bool IsGameInstalled()
        {
            return File.Exists(_gameExe);
        }
        
        public bool IsModLoaderInstalled()
        {
            return File.Exists(_modLoaderDll);
        }
        
        /// <summary>
        /// Launches the game with mod loader
        /// </summary>
        public bool LaunchWithMods()
        {
            if (!IsGameInstalled())
            {
                throw new FileNotFoundException("Game executable not found", _gameExe);
            }
            
            if (!IsModLoaderInstalled())
            {
                throw new FileNotFoundException("Mod loader DLL not found", _modLoaderDll);
            }
            
            try
            {
                // Use PowerShell to inject DLL
                var psScript = Path.Combine(_gamePath, "LaunchGameWithMods.ps1");
                
                if (File.Exists(psScript))
                {
                    // Use existing PowerShell script
                    var psi = new ProcessStartInfo
                    {
                        FileName = "powershell.exe",
                        Arguments = $"-ExecutionPolicy Bypass -File \"{psScript}\"",
                        WorkingDirectory = _gamePath,
                        UseShellExecute = false
                    };
                    
                    Process.Start(psi);
                    return true;
                }
                else
                {
                    // Direct launch (DLL will be auto-loaded if injector is set up)
                    var psi = new ProcessStartInfo
                    {
                        FileName = _gameExe,
                        WorkingDirectory = _gamePath,
                        UseShellExecute = false
                    };
                    
                    Process.Start(psi);
                    return true;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error launching game: {ex.Message}");
                return false;
            }
        }
        
        /// <summary>
        /// Launches the game without mods (vanilla)
        /// </summary>
        public bool LaunchVanilla()
        {
            if (!IsGameInstalled())
            {
                throw new FileNotFoundException("Game executable not found", _gameExe);
            }
            
            try
            {
                // Temporarily rename mod loader DLL
                var backupPath = _modLoaderDll + ".backup";
                bool dllRenamed = false;
                
                if (File.Exists(_modLoaderDll))
                {
                    File.Move(_modLoaderDll, backupPath);
                    dllRenamed = true;
                }
                
                var psi = new ProcessStartInfo
                {
                    FileName = _gameExe,
                    WorkingDirectory = _gamePath,
                    UseShellExecute = false
                };
                
                var process = Process.Start(psi);
                
                // Wait a bit then restore DLL
                if (dllRenamed && process != null)
                {
                    System.Threading.Tasks.Task.Delay(5000).ContinueWith(_ =>
                    {
                        try
                        {
                            if (File.Exists(backupPath))
                            {
                                File.Move(backupPath, _modLoaderDll);
                            }
                        }
                        catch { }
                    });
                }
                
                return true;
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error launching vanilla game: {ex.Message}");
                return false;
            }
        }
        
        public string GetGameVersion()
        {
            if (!IsGameInstalled()) return "Not Found";
            
            try
            {
                var versionInfo = FileVersionInfo.GetVersionInfo(_gameExe);
                return versionInfo.FileVersion ?? "Unknown";
            }
            catch
            {
                return "Unknown";
            }
        }
    }
}
