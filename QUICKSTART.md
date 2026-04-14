# Map Maker - Quick Start Guide

Get from zero to finished map in 15 minutes!

## Prerequisites
- Unity 6000.3.10f1 installed
- This project opened in Unity

## 5-Minute Quick Map

### Step 1: Create Scene (1 minute)
1. File → New Scene
2. File → Save As → `Assets/Scenes/MyFirstMap.unity`

### Step 2: Add Ground (1 minute)
1. GameObject → 3D Object → Terrain
2. Use terrain tools to paint landscape
3. Or just leave flat for testing

### Step 3: Add Hole (2 minutes)
1. GameObject → Super Battle Golf → Create New Hole
2. Move tee box to start position
3. Move cup to end position (default: 50m forward)
4. Adjust fairway size and position

### Step 4: Build & Export (1 minute)
1. Window → Super Battle Golf → Map Maker
2. Fill in:
   - Map Name: "My First Map"
   - Author: Your name
   - Description: "My first custom course!"
3. Click "Quick Build (All Steps)"
4. Done!

**Output:** Desktop/SBGMaps/MyFirstMap/

Copy that folder to `[Game]/Mods/Maps/` and test!

---

## 15-Minute Full Map

Everything above, plus:

### Step 5: Add Hazards (5 minutes)
1. GameObject → Super Battle Golf → Hazards → Water Hazard
2. Position near fairway
3. Scale to desired size
4. Repeat for sand traps

### Step 6: Add Obstacles (5 minutes)
1. GameObject → Super Battle Golf → Obstacles → Tree
2. Place along fairway edges
3. Add rocks for variety
4. Group obstacles under "Obstacles" parent

### Step 7: Polish (3 minutes)
1. Adjust lighting (Directional Light)
2. Set skybox (Window → Rendering → Lighting → Skybox)
3. Test camera angles
4. Add ambient objects (props, decorations)

### Step 8: Final Export (1 minute)
Same as Step 4 - rebuild and export!

---

## Pro Tips

### Faster Workflow
- **Duplicate holes** - Copy/paste "Hole1" to create "Hole2"
- **Prefab obstacles** - Create once, reuse many times
- **Asset packs** - Import free Unity terrain assets
- **Shortcuts** - Learn GameObject menu shortcuts

### Better Design
- **Start simple** - 3 holes is fine for first map
- **Playtest early** - Test in-game before adding detail
- **Reference reality** - Look at real golf courses
- **Iterate** - Make small changes, test, repeat

### Common First-Time Issues
1. **Forgot to save scene** → Save As first!
2. **Wrong Addressables name** → Let Map Maker handle it
3. **Too ambitious** → Start with 1-3 holes, not 18!
4. **No collision** → Terrain has collision by default, but custom objects need Collider components

---

## What's Next?

After your first map works:

1. **Add more holes** (up to 18!)
2. **Import assets** (Unity Asset Store has free terrain packs)
3. **Custom materials** (make water actually look like water)
4. **Scripted elements** (moving platforms, triggers)
5. **Lighting effects** (dynamic time of day)
6. **Audio** (ambient sounds, music)

## Learning Resources

### Unity Basics
- Official Unity Learn: https://learn.unity.com
- Terrain tutorial: Search "Unity Terrain Tutorial"
- Addressables guide: Unity documentation

### Golf Course Design
- Study real courses
- Play the base game for inspiration
- Watch golf course design videos

### Community
- Share your maps on Discord
- Get feedback from players
- Collaborate with other creators

---

**You've got this! Make something amazing!** ⛳

Questions? Check the full README.md or ask on Discord.
