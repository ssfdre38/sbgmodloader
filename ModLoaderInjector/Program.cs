using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace SuperBattleGolf.ModLoaderInjector
{
    static class Program
    {
        private static readonly string GameExePath = @"C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf\Super Battle Golf.exe";
        private static readonly string ModAgentDllPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "ModAgent.dll");

        [STAThread]
        static void Main()
        {
            try
            {
                Console.WriteLine("[ModLoaderInjector] Starting...");
                Console.WriteLine($"[ModLoaderInjector] Game path: {GameExePath}");
                Console.WriteLine($"[ModLoaderInjector] ModAgent DLL: {ModAgentDllPath}");

                if (!File.Exists(GameExePath))
                {
                    MessageBox.Show($"Game not found at:\n{GameExePath}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                if (!File.Exists(ModAgentDllPath))
                {
                    MessageBox.Show($"ModAgent.dll not found at:\n{ModAgentDllPath}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                Console.WriteLine("[ModLoaderInjector] Launching game process...");
                
                // Start game process
                var gameProcess = Process.Start(new ProcessStartInfo
                {
                    FileName = GameExePath,
                    UseShellExecute = false,
                    RedirectStandardOutput = false,
                    WorkingDirectory = Path.GetDirectoryName(GameExePath)
                });

                if (gameProcess == null)
                {
                    throw new Exception("Failed to start game process");
                }

                Console.WriteLine($"[ModLoaderInjector] Game process started (PID: {gameProcess.Id})");
                Console.WriteLine("[ModLoaderInjector] Waiting for game to initialize...");
                
                // Wait a bit for game to initialize
                System.Threading.Thread.Sleep(3000);

                Console.WriteLine("[ModLoaderInjector] Attempting DLL injection...");
                
                // Attempt to inject ModAgent.dll
                try
                {
                    EasyHook.RemoteHooking.Inject(
                        gameProcess.Id,
                        EasyHook.InjectionOptions.Default,
                        ModAgentDllPath,
                        ModAgentDllPath
                    );
                    
                    Console.WriteLine("[ModLoaderInjector] ✓ Injection successful!");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"[ModLoaderInjector] ✗ Injection failed: {ex.Message}");
                    MessageBox.Show($"DLL injection failed:\n{ex.Message}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }

                Console.WriteLine("[ModLoaderInjector] Waiting for game process to exit...");
                gameProcess.WaitForExit();
                Console.WriteLine("[ModLoaderInjector] Game process exited");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[ModLoaderInjector] Fatal error: {ex}");
                MessageBox.Show($"Fatal error:\n{ex.Message}\n\n{ex.StackTrace}", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}
