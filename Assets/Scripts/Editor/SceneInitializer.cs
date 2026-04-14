using UnityEngine;
using UnityEditor;
using UnityEditor.SceneManagement;
using UnityEngine.SceneManagement;

namespace SBGMapMaker
{
    /// <summary>
    /// Initializes a new map scene with basic structure
    /// </summary>
    public static class SceneInitializer
    {
        [MenuItem("Super Battle Golf/Create Example Scene", false, 0)]
        public static void CreateExampleScene()
        {
            if (!EditorUtility.DisplayDialog(
                "Create Example Scene?",
                "This will create a new scene with a sample hole setup.\n\n" +
                "Your current scene will be saved if needed.",
                "Create", "Cancel"))
            {
                return;
            }
            
            // Prompt to save current scene
            if (!EditorSceneManager.SaveCurrentModifiedScenesIfUserWantsTo())
            {
                return;
            }
            
            // Create new scene
            Scene newScene = EditorSceneManager.NewScene(NewSceneSetup.DefaultGameObjects, NewSceneMode.Single);
            
            Debug.Log("Creating example golf course scene...");
            
            // Create course root
            GameObject courseRoot = new GameObject("MyGolfCourse");
            var courseData = courseRoot.AddComponent<CourseData>();
            courseData.courseName = "My First Course";
            courseData.description = "A simple 3-hole golf course";
            courseData.author = System.Environment.UserName;
            courseData.totalHoles = 3;
            courseData.difficulty = CourseData.CourseDifficulty.Medium;
            courseData.environment = CourseData.CourseEnvironment.Custom;
            
            Undo.RegisterCreatedObjectUndo(courseRoot, "Create Course Root");
            
            // Create 3 holes
            GameObject[] holes = new GameObject[3];
            for (int i = 0; i < 3; i++)
            {
                holes[i] = CreateExampleHole(i + 1, courseRoot.transform);
            }
            
            // Link holes to course
            courseData.holes = new HoleData[3];
            for (int i = 0; i < 3; i++)
            {
                courseData.holes[i] = holes[i].GetComponent<HoleData>();
            }
            
            // Create lighting
            GameObject lightObj = GameObject.Find("Directional Light");
            if (lightObj != null)
            {
                lightObj.transform.rotation = Quaternion.Euler(50, -30, 0);
                var light = lightObj.GetComponent<Light>();
                if (light != null)
                {
                    light.color = new Color(1f, 0.95f, 0.9f);
                    light.intensity = 1.2f;
                }
            }
            
            // Create ground plane
            GameObject ground = GameObject.CreatePrimitive(PrimitiveType.Plane);
            ground.name = "Ground";
            ground.transform.position = Vector3.zero;
            ground.transform.localScale = new Vector3(50, 1, 50);
            
            var groundRenderer = ground.GetComponent<Renderer>();
            if (groundRenderer != null)
            {
                groundRenderer.material.color = new Color(0.3f, 0.7f, 0.3f);
            }
            
            Undo.RegisterCreatedObjectUndo(ground, "Create Ground");
            
            // Position camera for good overview
            SceneView sceneView = SceneView.lastActiveSceneView;
            if (sceneView != null)
            {
                sceneView.pivot = new Vector3(0, 10, 50);
                sceneView.rotation = Quaternion.Euler(30, 0, 0);
                sceneView.size = 100;
                sceneView.Repaint();
            }
            
            // Save scene
            string scenePath = "Assets/Scenes";
            if (!System.IO.Directory.Exists(scenePath))
            {
                System.IO.Directory.CreateDirectory(scenePath);
                AssetDatabase.Refresh();
            }
            
            string sceneName = "ExampleCourse.unity";
            string fullPath = $"{scenePath}/{sceneName}";
            
            EditorSceneManager.SaveScene(newScene, fullPath);
            
            Debug.Log($"✅ Example scene created: {fullPath}");
            Debug.Log("Next steps:");
            Debug.Log("1. Customize the holes (move tees, cups, add hazards)");
            Debug.Log("2. Open Window → Super Battle Golf → Map Maker");
            Debug.Log("3. Build and export your map!");
            
            EditorUtility.DisplayDialog(
                "Scene Created!",
                $"Example golf course created at:\n{fullPath}\n\n" +
                "The scene has 3 holes ready to customize.\n\n" +
                "Next: Open 'Window → Super Battle Golf → Map Maker' to build!",
                "Got it!");
        }
        
        private static GameObject CreateExampleHole(int holeNumber, Transform parent)
        {
            float holeSpacing = 150f;
            Vector3 basePosition = new Vector3((holeNumber - 2) * holeSpacing, 0, 0);
            
            GameObject hole = new GameObject($"Hole{holeNumber}");
            hole.transform.parent = parent;
            hole.transform.position = basePosition;
            
            // Create tee
            GameObject tee = CourseElementFactory.CreateTeeBox(
                basePosition,
                Vector3.forward);
            tee.transform.parent = hole.transform;
            
            // Create fairway
            GameObject fairway = GameObject.CreatePrimitive(PrimitiveType.Plane);
            fairway.name = "Fairway";
            fairway.transform.parent = hole.transform;
            fairway.transform.position = basePosition + Vector3.forward * 50f;
            fairway.transform.localScale = new Vector3(3, 1, 5);
            
            var fairwayRenderer = fairway.GetComponent<Renderer>();
            if (fairwayRenderer != null)
            {
                fairwayRenderer.material.color = new Color(0.2f, 0.6f, 0.2f);
            }
            
            // Create cup
            float cupDistance = 80f + (holeNumber * 20f); // Increasing distance
            GameObject cup = CourseElementFactory.CreateCup(
                basePosition + Vector3.forward * cupDistance);
            cup.transform.parent = hole.transform;
            
            // Add HoleData
            var holeData = hole.AddComponent<HoleData>();
            holeData.holeNumber = holeNumber;
            holeData.holeName = $"Hole {holeNumber}";
            holeData.par = 3 + (holeNumber > 2 ? 1 : 0); // Par 3, 3, 4
            holeData.teePosition = tee.transform;
            holeData.cupPosition = cup.transform;
            holeData.playableBounds = new Bounds(
                basePosition + Vector3.forward * (cupDistance / 2f),
                new Vector3(80, 50, cupDistance + 20f));
            
            // Add a hazard for variety
            if (holeNumber == 2)
            {
                GameObject water = CourseElementFactory.CreateWaterHazard(
                    basePosition + Vector3.forward * 40f + Vector3.right * 15f,
                    new Vector3(10, 1, 10));
                water.transform.parent = hole.transform;
            }
            else if (holeNumber == 3)
            {
                GameObject sand = CourseElementFactory.CreateSandTrap(
                    basePosition + Vector3.forward * 60f + Vector3.left * 10f,
                    new Vector3(5, 0.2f, 5));
                sand.transform.parent = hole.transform;
            }
            
            // Add some trees
            for (int i = 0; i < 3; i++)
            {
                Vector3 treePos = basePosition + Vector3.forward * Random.Range(20f, 80f) +
                                 new Vector3(Random.Range(-20f, 20f), 0, Random.Range(-10f, 10f));
                GameObject tree = CourseElementFactory.CreateObstacle(treePos, 4f, 0.5f);
                tree.name = $"Tree{i + 1}";
                tree.transform.parent = hole.transform;
                
                var treeRenderer = tree.GetComponent<Renderer>();
                if (treeRenderer != null)
                {
                    treeRenderer.material.color = new Color(0.2f, 0.4f, 0.1f);
                }
            }
            
            Undo.RegisterCreatedObjectUndo(hole, $"Create Hole {holeNumber}");
            
            return hole;
        }
    }
}
