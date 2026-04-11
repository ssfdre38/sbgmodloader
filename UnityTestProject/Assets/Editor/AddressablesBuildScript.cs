using UnityEngine;
using UnityEditor;
using UnityEditor.AddressableAssets;
using UnityEditor.AddressableAssets.Settings;
using UnityEditor.AddressableAssets.Settings.GroupSchemas;
using System.IO;
using System.Linq;

public class AddressablesBuildScript
{
    [MenuItem("Addressables/Setup and Build")]
    public static void SetupAndBuild()
    {
        Debug.Log("═══════════════════════════════════════");
        Debug.Log("Starting Addressables Setup and Build");
        Debug.Log("═══════════════════════════════════════");
        
        // Create or get Addressables settings
        var settings = AddressableAssetSettingsDefaultObject.GetSettings(true);
        if (settings == null)
        {
            Debug.LogError("Failed to create Addressables settings!");
            return;
        }
        
        Debug.Log("✅ Addressables settings created/loaded");
        
        // Create a custom group for our test map
        var group = settings.FindGroup("TestMapGroup");
        if (group == null)
        {
            group = settings.CreateGroup("TestMapGroup", false, false, true, null, typeof(BundledAssetGroupSchema), typeof(ContentUpdateGroupSchema));
            Debug.Log("✅ Created TestMapGroup");
        }
        
        // Configure the group for StandaloneWindows64
        var schema = group.GetSchema<BundledAssetGroupSchema>();
        if (schema != null)
        {
            schema.BuildPath.SetVariableByName(settings, "LocalBuildPath");
            schema.LoadPath.SetVariableByName(settings, "LocalLoadPath");
            schema.BundleMode = BundledAssetGroupSchema.BundlePackingMode.PackTogether;
            Debug.Log("✅ Configured group schema");
        }
        
        // Add the test scene to Addressables
        var sceneGuid = AssetDatabase.AssetPathToGUID("Assets/Scenes/CustomTestMap.unity");
        if (!string.IsNullOrEmpty(sceneGuid))
        {
            var entry = settings.CreateOrMoveEntry(sceneGuid, group, false, false);
            entry.address = "CustomTestMap";
            Debug.Log("✅ Added CustomTestMap scene to Addressables with address: CustomTestMap");
        }
        else
        {
            Debug.LogError("❌ CustomTestMap.unity not found!");
            return;
        }
        
        // Set build target
        EditorUserBuildSettings.SwitchActiveBuildTarget(BuildTargetGroup.Standalone, BuildTarget.StandaloneWindows64);
        Debug.Log("✅ Set build target to Windows 64-bit");
        
        // Save settings
        AssetDatabase.SaveAssets();
        
        // Build Addressables content
        Debug.Log("");
        Debug.Log("Building Addressables content...");
        
        AddressableAssetSettings.BuildPlayerContent(out var result);
        
        if (!string.IsNullOrEmpty(result.Error))
        {
            Debug.LogError("Build failed: " + result.Error);
            File.WriteAllText("build_failed.txt", result.Error);
        }
        else
        {
            Debug.Log("✅ Addressables build completed successfully!");
            Debug.Log("   Duration: " + result.Duration);
            Debug.Log("   Locations: " + result.LocationCount);
            
            // Find the output directory
            var outputPath = "Library/com.unity.addressables/aa/StandaloneWindows64";
            if (Directory.Exists(outputPath))
            {
                Debug.Log("");
                Debug.Log("Build output directory: " + Path.GetFullPath(outputPath));
                var files = Directory.GetFiles(outputPath, "*", SearchOption.AllDirectories);
                Debug.Log("Files created (" + files.Length + "):");
                foreach (var file in files.Take(20))
                {
                    var info = new FileInfo(file);
                    Debug.Log("  - " + file.Replace(outputPath + "\\", "") + " (" + info.Length + " bytes)");
                }
                
                // Copy to output directory for easy access
                var copyToPath = "D:/SuperBattleGolfModLoader/TestMapOutput";
                if (Directory.Exists(copyToPath))
                    Directory.Delete(copyToPath, true);
                
                DirectoryCopy(outputPath, copyToPath, true);
                Debug.Log("");
                Debug.Log("✅ Copied build output to: " + copyToPath);
            }
            
            File.WriteAllText("build_success.txt", "Build completed at " + System.DateTime.Now);
        }
    }
    
    private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
    {
        DirectoryInfo dir = new DirectoryInfo(sourceDirName);
        DirectoryInfo[] dirs = dir.GetDirectories();
        
        Directory.CreateDirectory(destDirName);
        
        FileInfo[] files = dir.GetFiles();
        foreach (FileInfo file in files)
        {
            string tempPath = Path.Combine(destDirName, file.Name);
            file.CopyTo(tempPath, true);
        }
        
        if (copySubDirs)
        {
            foreach (DirectoryInfo subdir in dirs)
            {
                string tempPath = Path.Combine(destDirName, subdir.Name);
                DirectoryCopy(subdir.FullName, tempPath, copySubDirs);
            }
        }
    }
}
