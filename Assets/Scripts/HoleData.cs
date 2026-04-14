using UnityEngine;

namespace SBGMapMaker
{
    /// <summary>
    /// Component for defining hole metadata
    /// Attach to your hole start position
    /// </summary>
    public class HoleData : MonoBehaviour
    {
        [Header("Hole Information")]
        public int holeNumber = 1;
        public int par = 3;
        public string holeName = "Hole 1";
        
        [Header("Start Position")]
        public Transform teePosition;
        public float teeAreaRadius = 2f;
        
        [Header("End Position")]
        public Transform cupPosition;
        public float cupRadius = 0.1f;
        
        [Header("Boundaries")]
        public Bounds playableBounds;
        
        [Header("Hazards")]
        public GameObject[] waterHazards;
        public GameObject[] sandTraps;
        public GameObject[] outOfBounds;
        
        private void OnDrawGizmos()
        {
            // Draw tee area
            if (teePosition != null)
            {
                Gizmos.color = Color.green;
                Gizmos.DrawWireSphere(teePosition.position, teeAreaRadius);
                Gizmos.DrawLine(teePosition.position, teePosition.position + teePosition.forward * 2f);
            }
            
            // Draw cup
            if (cupPosition != null)
            {
                Gizmos.color = Color.red;
                Gizmos.DrawWireSphere(cupPosition.position, cupRadius);
                Gizmos.DrawIcon(cupPosition.position + Vector3.up * 0.5f, "sv_icon_dot1_pix16_gizmo", true);
            }
            
            // Draw playable bounds
            Gizmos.color = Color.yellow;
            Gizmos.DrawWireCube(playableBounds.center, playableBounds.size);
        }
        
        private void OnDrawGizmosSelected()
        {
            // Draw hazards in selected mode
            Gizmos.color = new Color(0, 0.5f, 1f, 0.3f);
            if (waterHazards != null)
            {
                foreach (var hazard in waterHazards)
                {
                    if (hazard != null)
                    {
                        Gizmos.DrawCube(hazard.transform.position, hazard.transform.localScale);
                    }
                }
            }
            
            Gizmos.color = new Color(1f, 0.8f, 0f, 0.3f);
            if (sandTraps != null)
            {
                foreach (var trap in sandTraps)
                {
                    if (trap != null)
                    {
                        Gizmos.DrawCube(trap.transform.position, trap.transform.localScale);
                    }
                }
            }
        }
    }
}
