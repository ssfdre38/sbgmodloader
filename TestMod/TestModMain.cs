using System;
using System.IO;
using SuperBattleGolf.ModSdk;
using UnityEngine;

namespace SuperBattleGolf.TestMod
{
    /// <summary>
    /// Simple test mod that logs when it's loaded.
    /// </summary>
    public class TestModMain : IMod, IGameInitHook
    {
        private static string LogFilePath => Path.Combine(
            Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData),
            "SuperBattleGolfModLoader",
            "TestMod.log"
        );

        public string Id => "TestMod";
        public string Name => "Test Mod";
        public string Version => "1.0.0";

        public void OnLoad()
        {
            Log("=== TestMod Loaded ===");
            Log($"Timestamp: {DateTime.Now:yyyy-MM-dd HH:mm:ss}");
            Log("This is a test mod for PoC validation");
        }

        public void OnUnload()
        {
            Log("TestMod Unloading");
        }

        public void OnGameInitialized()
        {
            Log("Game initialized - TestMod hook executed!");
        }

        private static void Log(string message)
        {
            try
            {
                Directory.CreateDirectory(Path.GetDirectoryName(LogFilePath));
                File.AppendAllText(LogFilePath, $"[{DateTime.Now:HH:mm:ss.fff}] {message}\n");
                Debug.Log($"[TestMod] {message}");
            }
            catch { }
        }
    }
}
