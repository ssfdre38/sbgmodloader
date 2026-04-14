using UnityEngine;

namespace SBGMapMaker
{
    /// <summary>
    /// Quick setup tool for adding common golf course elements
    /// </summary>
    public static class CourseElementFactory
    {
        /// <summary>
        /// Creates a basic tee box with markers
        /// </summary>
        public static GameObject CreateTeeBox(Vector3 position, Vector3 forward)
        {
            GameObject tee = new GameObject("TeeBox");
            tee.transform.position = position;
            tee.transform.forward = forward;
            
            // Create platform
            GameObject platform = GameObject.CreatePrimitive(PrimitiveType.Cube);
            platform.name = "TeePlatform";
            platform.transform.parent = tee.transform;
            platform.transform.localPosition = Vector3.zero;
            platform.transform.localScale = new Vector3(4f, 0.1f, 3f);
            
            // Create markers
            CreateTeeMarker(tee.transform, new Vector3(-0.5f, 0.1f, 0), Color.blue);
            CreateTeeMarker(tee.transform, new Vector3(0.5f, 0.1f, 0), Color.red);
            
            return tee;
        }
        
        private static void CreateTeeMarker(Transform parent, Vector3 localPos, Color color)
        {
            GameObject marker = GameObject.CreatePrimitive(PrimitiveType.Sphere);
            marker.name = $"Marker_{color.ToString()}";
            marker.transform.parent = parent;
            marker.transform.localPosition = localPos;
            marker.transform.localScale = Vector3.one * 0.3f;
            
            var renderer = marker.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = color;
            }
        }
        
        /// <summary>
        /// Creates a cup/hole at the target position
        /// </summary>
        public static GameObject CreateCup(Vector3 position)
        {
            GameObject cup = new GameObject("Cup");
            cup.transform.position = position;
            
            // Create flagpole
            GameObject pole = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
            pole.name = "Flagpole";
            pole.transform.parent = cup.transform;
            pole.transform.localPosition = Vector3.up * 1f;
            pole.transform.localScale = new Vector3(0.05f, 1f, 0.05f);
            
            // Create flag
            GameObject flag = GameObject.CreatePrimitive(PrimitiveType.Cube);
            flag.name = "Flag";
            flag.transform.parent = cup.transform;
            flag.transform.localPosition = new Vector3(0.25f, 1.8f, 0);
            flag.transform.localScale = new Vector3(0.5f, 0.3f, 0.01f);
            
            var renderer = flag.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = Color.red;
            }
            
            // Create hole
            GameObject hole = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
            hole.name = "Hole";
            hole.transform.parent = cup.transform;
            hole.transform.localPosition = Vector3.zero;
            hole.transform.localScale = new Vector3(0.2f, 0.01f, 0.2f);
            
            renderer = hole.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = Color.black;
            }
            
            return cup;
        }
        
        /// <summary>
        /// Creates a water hazard area
        /// </summary>
        public static GameObject CreateWaterHazard(Vector3 position, Vector3 size)
        {
            GameObject water = GameObject.CreatePrimitive(PrimitiveType.Cube);
            water.name = "WaterHazard";
            water.transform.position = position;
            water.transform.localScale = size;
            
            var renderer = water.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0, 0.5f, 1f, 0.7f);
            }
            
            // Add trigger collider
            var collider = water.GetComponent<Collider>();
            if (collider != null)
            {
                collider.isTrigger = true;
            }
            
            return water;
        }
        
        /// <summary>
        /// Creates a sand trap
        /// </summary>
        public static GameObject CreateSandTrap(Vector3 position, Vector3 size)
        {
            GameObject sand = GameObject.CreatePrimitive(PrimitiveType.Cube);
            sand.name = "SandTrap";
            sand.transform.position = position;
            sand.transform.localScale = size;
            
            var renderer = sand.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0.9f, 0.8f, 0.6f);
            }
            
            return sand;
        }
        
        /// <summary>
        /// Creates a simple obstacle (tree, rock, etc.)
        /// </summary>
        public static GameObject CreateObstacle(Vector3 position, float height = 2f, float radius = 0.5f)
        {
            GameObject obstacle = GameObject.CreatePrimitive(PrimitiveType.Cylinder);
            obstacle.name = "Obstacle";
            obstacle.transform.position = position + Vector3.up * (height / 2f);
            obstacle.transform.localScale = new Vector3(radius, height / 2f, radius);
            
            var renderer = obstacle.GetComponent<Renderer>();
            if (renderer != null)
            {
                renderer.material.color = new Color(0.3f, 0.5f, 0.2f);
            }
            
            return obstacle;
        }
    }
}
