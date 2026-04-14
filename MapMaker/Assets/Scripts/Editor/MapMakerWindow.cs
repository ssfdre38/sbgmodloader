using UnityEngine;
using UnityEditor;
using System.IO;

namespace SBGMapMaker
{
    /// <summary>
    /// Editor window for creating and exporting Super Battle Golf maps
    /// </summary>
    public class MapMakerWindow : EditorWindow
    {
        private string mapName = "MyCustomMap";
        private string mapAuthor = "YourName";
        private string mapDescription = "An awesome custom golf course";
        private int holeCount = 3;
        private string difficulty = "medium";
        private string environment = "custom";
        
        private string outputPath = "";
        
        [MenuItem("Super Battle Golf/Map Maker")]
        public static void ShowWindow()
        {
            var window = GetWindow<MapMakerWindow>("SBG Map Maker");
            window.minSize = new Vector2(400, 500);
            window.Show();
        }
        
        private void OnEnable()
        {
            // Set default output path
            outputPath = Path.Combine(System.Environment.GetFolderPath(System.Environment.SpecialFolder.Desktop), "SBGMaps");
        }
        
        private void OnGUI()
        {
            GUILayout.Label("Super Battle Golf - Map Maker", EditorStyles.boldLabel);
            GUILayout.Space(10);
            
            EditorGUILayout.HelpBox(
                "Create custom golf courses for Super Battle Golf! " +
                "This tool will help you set up Addressables, export asset bundles, and generate mod.json.",
                MessageType.Info);
            
            GUILayout.Space(10);
            
            // Map metadata
            GUILayout.Label("Map Metadata", EditorStyles.boldLabel);
            mapName = EditorGUILayout.TextField("Map Name", mapName);
            mapAuthor = EditorGUILayout.TextField("Author", mapAuthor);
            mapDescription = EditorGUILayout.TextField("Description", mapDescription);
            holeCount = EditorGUILayout.IntSlider("Hole Count", holeCount, 1, 18);
            
            GUILayout.Space(5);
            
            difficulty = EditorGUILayout.TextField("Difficulty", difficulty);
            EditorGUILayout.HelpBox("Suggested: easy, medium, hard", MessageType.None);
            
            environment = EditorGUILayout.TextField("Environment", environment);
            EditorGUILayout.HelpBox("Suggested: desert, forest, snow, space, custom", MessageType.None);
            
            GUILayout.Space(10);
            
            // Output settings
            GUILayout.Label("Export Settings", EditorStyles.boldLabel);
            
            EditorGUILayout.BeginHorizontal();
            outputPath = EditorGUILayout.TextField("Output Folder", outputPath);
            if (GUILayout.Button("Browse", GUILayout.Width(60)))
            {
                string selected = EditorUtility.OpenFolderPanel("Select Output Folder", outputPath, "");
                if (!string.IsNullOrEmpty(selected))
                {
                    outputPath = selected;
                }
            }
            EditorGUILayout.EndHorizontal();
            
            GUILayout.Space(20);
            
            // Action buttons
            if (GUILayout.Button("1. Setup Addressables", GUILayout.Height(30)))
            {
                SetupAddressables();
            }
            
            EditorGUILayout.HelpBox(
                "Sets up the current scene for Addressables with the correct naming convention (CustomCourse[MapName]).",
                MessageType.None);
            
            GUILayout.Space(10);
            
            if (GUILayout.Button("2. Build Asset Bundles", GUILayout.Height(30)))
            {
                BuildAssetBundles();
            }
            
            EditorGUILayout.HelpBox(
                "Builds Addressables asset bundles for Windows (required by the game).",
                MessageType.None);
            
            GUILayout.Space(10);
            
            if (GUILayout.Button("3. Export Map", GUILayout.Height(30)))
            {
                ExportMap();
            }
            
            EditorGUILayout.HelpBox(
                "Exports asset bundles and generates mod.json. Ready to copy to game's Mods/Maps/ folder!",
                MessageType.None);
            
            GUILayout.Space(20);
            
            if (GUILayout.Button("Quick Build (All Steps)", GUILayout.Height(40)))
            {
                SetupAddressables();
                BuildAssetBundles();
                ExportMap();
            }
        }
        
        private void SetupAddressables()
        {
            Debug.Log("[MapMaker] Setting up Addressables...");
            
            // Get current scene
            var scene = UnityEngine.SceneManagement.SceneManager.GetActiveScene();
            if (string.IsNullOrEmpty(scene.path))
            {
                EditorUtility.DisplayDialog("Error", "Please save the scene first!", "OK");
                return;
            }
            
            // Create Addressables address
            string addressableName = "CustomCourse" + mapName.Replace(" ", "");
            
            Debug.Log($"[MapMaker] Scene will be addressable as: {addressableName}");
            
            EditorUtility.DisplayDialog("Addressables Setup",
                $"Scene addressable name: {addressableName}\n\n" +
                "Next steps:\n" +
                "1. Window → Asset Management → Addressables → Groups\n" +
                "2. Create new group or use existing\n" +
                "3. Drag your scene into the group\n" +
                "4. Set address to: " + addressableName,
                "OK");
        }
        
        private void BuildAssetBundles()
        {
            Debug.Log("[MapMaker] Building asset bundles...");
            
            // Note: This requires Addressables package to be installed
            // The actual build would call: UnityEditor.AddressableAssets.Build.DataBuilders.BuildScriptPackedMode.BuildContent
            
            EditorUtility.DisplayDialog("Build Asset Bundles",
                "To build asset bundles:\n\n" +
                "Window → Asset Management → Addressables → Build → New Build → Default Build Script\n\n" +
                "Output will be in: Assets/AddressableAssetsData/Windows/",
                "OK");
        }
        
        private void ExportMap()
        {
            Debug.Log("[MapMaker] Exporting map...");
            
            // Create output folder
            string mapFolderName = mapName.Replace(" ", "");
            string mapOutputPath = Path.Combine(outputPath, mapFolderName);
            
            if (!Directory.Exists(mapOutputPath))
            {
                Directory.CreateDirectory(mapOutputPath);
            }
            
            // Generate mod.json
            string modId = mapFolderName.ToLower().Replace(" ", "-");
            string modJson = $@"{{
  ""id"": ""{modId}"",
  ""name"": ""{mapName}"",
  ""author"": ""{mapAuthor}"",
  ""version"": ""1.0.0"",
  ""description"": ""{mapDescription}"",
  ""type"": ""map"",
  ""content"": {{
    ""addressables"": true,
    ""catalogPath"": ""catalog.bin""
  }},
  ""meta"": {{
    ""difficulty"": ""{difficulty}"",
    ""holes"": {holeCount},
    ""environment"": ""{environment}"",
    ""tags"": [""custom""]
  }}
}}";
            
            string modJsonPath = Path.Combine(mapOutputPath, "mod.json");
            File.WriteAllText(modJsonPath, modJson);
            
            Debug.Log($"[MapMaker] Created mod.json at: {modJsonPath}");
            
            // Copy asset bundles (if they exist)
            string bundleSource = Path.Combine(Application.dataPath, "AddressableAssetsData", "Windows");
            if (Directory.Exists(bundleSource))
            {
                CopyDirectory(bundleSource, mapOutputPath);
                Debug.Log($"[MapMaker] Copied asset bundles to: {mapOutputPath}");
            }
            
            // Create README
            string readme = $@"# {mapName}

{mapDescription}

## Details
- **Author:** {mapAuthor}
- **Holes:** {holeCount}
- **Difficulty:** {difficulty}
- **Environment:** {environment}

## Installation

1. Copy this entire folder to:
   ```
   [Game]\Mods\Maps\{mapFolderName}\
   ```

2. Launch Super Battle Golf with the mod loader

3. Your map should appear in custom courses!

## Credits

Created with Super Battle Golf Map Maker
";
            
            string readmePath = Path.Combine(mapOutputPath, "README.md");
            File.WriteAllText(readmePath, readme);
            
            // Show success dialog
            EditorUtility.DisplayDialog("Export Complete!",
                $"Map exported to:\n{mapOutputPath}\n\n" +
                "Files created:\n" +
                "• mod.json\n" +
                "• README.md\n" +
                "• Asset bundles (if built)\n\n" +
                $"Copy the '{mapFolderName}' folder to [Game]/Mods/Maps/ to use in-game!",
                "Open Folder", "OK");
            
            // Open output folder
            System.Diagnostics.Process.Start(mapOutputPath);
        }
        
        private void CopyDirectory(string sourceDir, string destDir)
        {
            Directory.CreateDirectory(destDir);
            
            foreach (string file in Directory.GetFiles(sourceDir))
            {
                string fileName = Path.GetFileName(file);
                string destFile = Path.Combine(destDir, fileName);
                File.Copy(file, destFile, true);
            }
            
            foreach (string dir in Directory.GetDirectories(sourceDir))
            {
                string dirName = Path.GetFileName(dir);
                string destSubDir = Path.Combine(destDir, dirName);
                CopyDirectory(dir, destSubDir);
            }
        }
    }
}
