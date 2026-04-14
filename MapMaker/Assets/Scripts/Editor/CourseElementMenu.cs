using UnityEngine;
using UnityEditor;

namespace SBGMapMaker
{
    /// <summary>
    /// Menu items for quickly creating course elements
    /// </summary>
    public static class CourseElementMenu
    {
        [MenuItem("GameObject/Super Battle Golf/Course Elements/Tee Box", false, 10)]
        public static void CreateTeeBox()
        {
            Vector3 position = GetSpawnPosition();
            GameObject tee = CourseElementFactory.CreateTeeBox(position, Vector3.forward);
            
            // Add HoleData component
            var holeData = tee.AddComponent<HoleData>();
            holeData.teePosition = tee.transform;
            
            Selection.activeGameObject = tee;
            Undo.RegisterCreatedObjectUndo(tee, "Create Tee Box");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Course Elements/Cup", false, 10)]
        public static void CreateCup()
        {
            Vector3 position = GetSpawnPosition();
            GameObject cup = CourseElementFactory.CreateCup(position);
            
            Selection.activeGameObject = cup;
            Undo.RegisterCreatedObjectUndo(cup, "Create Cup");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Hazards/Water Hazard", false, 10)]
        public static void CreateWaterHazard()
        {
            Vector3 position = GetSpawnPosition();
            GameObject water = CourseElementFactory.CreateWaterHazard(position, new Vector3(5, 1, 5));
            
            Selection.activeGameObject = water;
            Undo.RegisterCreatedObjectUndo(water, "Create Water Hazard");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Hazards/Sand Trap", false, 10)]
        public static void CreateSandTrap()
        {
            Vector3 position = GetSpawnPosition();
            GameObject sand = CourseElementFactory.CreateSandTrap(position, new Vector3(3, 0.2f, 3));
            
            Selection.activeGameObject = sand;
            Undo.RegisterCreatedObjectUndo(sand, "Create Sand Trap");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Obstacles/Tree", false, 10)]
        public static void CreateTree()
        {
            Vector3 position = GetSpawnPosition();
            GameObject tree = CourseElementFactory.CreateObstacle(position, 4f, 0.5f);
            tree.name = "Tree";
            
            var renderer = tree.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0.2f, 0.4f, 0.1f);
            }
            
            Selection.activeGameObject = tree;
            Undo.RegisterCreatedObjectUndo(tree, "Create Tree");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Obstacles/Rock", false, 10)]
        public static void CreateRock()
        {
            Vector3 position = GetSpawnPosition();
            GameObject rock = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            rock.name = "Rock";
            rock.transform.position = position + Vector3.up * 0.5f;
            rock.transform.localScale = new Vector3(1, 0.8f, 1);
            
            var renderer = rock.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0.5f, 0.5f, 0.5f);
            }
            
            Selection.activeGameObject = rock;
            Undo.RegisterCreatedObjectUndo(rock, "Create Rock");
        }
        
        [MenuItem("GameObject/Super Battle Golf/Create New Hole", false, 1)]
        public static void CreateCompleteHole()
        {
            Vector3 position = GetSpawnPosition();
            
            GameObject hole = new GameObject("Hole");
            hole.transform.position = position;
            
            // Create tee
            GameObject tee = CourseElementFactory.CreateTeeBox(position, Vector3.forward);
            tee.transform.parent = hole.transform;
            
            // Create cup at far end
            Vector3 cupPos = position + Vector3.forward * 50f;
            GameObject cup = CourseElementFactory.CreateCup(cupPos);
            cup.transform.parent = hole.transform;
            
            // Add HoleData
            var holeData = hole.AddComponent<HoleData>();
            holeData.teePosition = tee.transform;
            holeData.cupPosition = cup.transform;
            holeData.holeNumber = 1;
            holeData.par = 3;
            
            // Create fairway plane
            GameObject fairway = GameObject.CreatePrimitive(PrimitiveType.Plane);
            fairway.name = "Fairway";
            fairway.transform.parent = hole.transform;
            fairway.transform.position = position + Vector3.forward * 25f;
            fairway.transform.localScale = new Vector3(3, 1, 5);
            
            var renderer = fairway.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0.2f, 0.6f, 0.2f);
            }
            
            Selection.activeGameObject = hole;
            Undo.RegisterCreatedObjectUndo(hole, "Create Complete Hole");
            
            Debug.Log("Created complete hole! Add hazards and obstacles as needed.");
        }
        
        private static Vector3 GetSpawnPosition()
        {
            // Try to spawn at scene view camera position
            SceneView sceneView = SceneView.lastActiveSceneView;
            if (sceneView != null)
            {
                return sceneView.camera.transform.position + sceneView.camera.transform.forward * 10f;
            }
            
            // Fallback to origin
            return Vector3.zero;
        }
    }
}
