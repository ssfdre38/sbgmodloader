using UnityEngine;

namespace SBGMapMaker
{
    /// <summary>
    /// Course metadata component
    /// Attach to the root GameObject of your course
    /// </summary>
    public class CourseData : MonoBehaviour
    {
        [Header("Course Information")]
        public string courseName = "My Custom Course";
        public string courseDescription = "An amazing custom golf course";
        public string author = "YourName";
        
        [Header("Settings")]
        public int totalHoles = 3;
        public int totalPar = 9;
        public string difficulty = "Medium";
        public string environment = "Custom";
        
        [Header("Hole References")]
        public HoleData[] holes;
        
        [Header("Lighting")]
        public Light directionalLight;
        public Color ambientColor = Color.gray;
        
        [Header("Audio")]
        public AudioClip ambientMusic;
        public AudioClip[] soundEffects;
        
        private void OnValidate()
        {
            // Auto-calculate total par from holes
            if (holes != null && holes.Length > 0)
            {
                totalPar = 0;
                foreach (var hole in holes)
                {
                    if (hole != null)
                    {
                        totalPar += hole.par;
                    }
                }
                totalHoles = holes.Length;
            }
        }
        
        private void OnDrawGizmos()
        {
            // Draw course bounds
            Gizmos.color = Color.cyan;
            Gizmos.DrawWireCube(transform.position, new Vector3(100, 10, 100));
        }
    }
}
