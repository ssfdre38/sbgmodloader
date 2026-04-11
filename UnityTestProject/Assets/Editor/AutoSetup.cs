using UnityEngine;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine.SceneManagement;
using System.IO;

public class AutoSetup
{
    [MenuItem("Tools/Create Test Map")]
    public static void CreateTestMap()
    {
        Debug.Log("Creating test map scene...");
        
        // Create new scene
        var scene = EditorSceneManager.NewScene(NewSceneSetup.DefaultGameObjects, NewSceneMode.Single);
        
        // Create ground plane
        var ground = GameObject.CreatePrimitive(PrimitiveType.Plane);
        ground.name = "Ground";
        ground.transform.position = Vector3.zero;
        ground.transform.localScale = new Vector3(10, 1, 10);
        
        // Create test cube
        var cube = GameObject.CreatePrimitive(PrimitiveType.Cube);
        cube.name = "TestCube";
        cube.transform.position = new Vector3(0, 0.5f, 0);
        
        // Make cube bright red so it's obvious
        var renderer = cube.GetComponent<Renderer>();
        var material = new Material(Shader.Find("Standard"));
        material.color = Color.red;
        renderer.material = material;
        
        // Save scene
        var scenesDir = "Assets/Scenes";
        if (!Directory.Exists(scenesDir))
            Directory.CreateDirectory(scenesDir);
        
        var scenePath = scenesDir + "/CustomTestMap.unity";
        EditorSceneManager.SaveScene(scene, scenePath);
        
        Debug.Log("✅ Test map created: " + scenePath);
    }
    
    [InitializeOnLoadMethod]
    private static void OnProjectLoaded()
    {
        EditorApplication.delayCall += () =>
        {
            Debug.Log("Project loaded - running auto setup...");
            CreateTestMap();
            
            // Write completion marker
            File.WriteAllText("setup_complete.txt", "Scene created successfully");
            
            // Exit Unity
            EditorApplication.Exit(0);
        };
    }
}
