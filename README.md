# Super Battle Golf - Map Maker

A Unity project template for creating custom golf courses for Super Battle Golf.

## Quick Start

### 1. Open in Unity

1. Install **Unity 6000.3.10f1** (exact version required!)
2. Open Unity Hub → Add → Browse to this folder
3. Open the project
4. Wait for initial import (may take a few minutes)

### 2. Install Required Packages

If not auto-installed:
1. Window → Package Manager
2. Find and install:
   - **Addressables 2.8.1**
   - **Universal RP 17.0.3**

### 3. Create Your First Map

**Option A: Quick Start (Automated)**
1. GameObject → Super Battle Golf → Create New Hole
2. Customize terrain, add hazards
3. Window → Super Battle Golf → Map Maker
4. Fill in map details
5. Click "Quick Build (All Steps)"
6. Done!

**Option B: Manual (More Control)**
1. File → New Scene
2. Create terrain and environment
3. GameObject → Super Battle Golf → Course Elements → Tee Box
4. GameObject → Super Battle Golf → Course Elements → Cup
5. Add hazards, obstacles, decorations
6. Window → Super Battle Golf → Map Maker
7. Follow the 3-step process

## Editor Tools

### Map Maker Window
**Location:** Window → Super Battle Golf → Map Maker

**Features:**
- One-click Addressables setup
- Automated asset bundle building
- mod.json generation
- Export ready-to-use mod folder

### Course Element Menu
**Location:** GameObject → Super Battle Golf → ...

**Quick Create:**
- **Course Elements**
  - Tee Box (start position)
  - Cup (hole/flag)
  
- **Hazards**
  - Water Hazard (blue trigger zone)
  - Sand Trap (yellow rough terrain)
  
- **Obstacles**
  - Tree (tall cylinder)
  - Rock (sphere)

- **Complete Hole** (tee + fairway + cup)

## Components

### CourseData
Attach to root GameObject of your course.

**Fields:**
- Course Name, Description, Author
- Total Holes, Total Par
- Difficulty (easy/medium/hard)
- Environment (desert/forest/snow/space/custom)
- Hole References (array of HoleData)
- Lighting Settings
- Audio Settings

**Auto-calculates:**
- Total par from hole components
- Hole count from array

### HoleData
Attach to each hole GameObject.

**Fields:**
- Hole Number, Par, Name
- Tee Position (Transform)
- Cup Position (Transform)
- Playable Bounds
- Hazard Arrays (water, sand, OOB)

**Visual Gizmos:**
- Green sphere = Tee area
- Red sphere = Cup position
- Yellow box = Playable bounds
- Blue/yellow overlays = Hazards (when selected)

## Workflow

### Step 1: Scene Setup

Create your golf course environment:

```
MyCustomCourse (Scene)
├── Lighting
│   └── Directional Light
├── Environment
│   ├── Terrain
│   ├── Skybox
│   └── Props
├── Hole1
│   ├── TeeBox (HoleData component)
│   ├── Fairway
│   ├── Cup
│   ├── Hazards
│   │   ├── WaterHazard
│   │   └── SandTrap
│   └── Obstacles
│       ├── Trees
│       └── Rocks
├── Hole2
│   └── ...
└── CourseRoot (CourseData component)
```

### Step 2: Component Setup

1. **Add CourseData to root:**
   - Select course root GameObject
   - Add Component → SBGMapMaker → CourseData
   - Fill in metadata (name, author, etc.)
   
2. **Add HoleData to each hole:**
   - Select hole GameObject
   - Add Component → SBGMapMaker → HoleData
   - Set tee and cup transforms
   - Configure hazards

3. **Link holes to course:**
   - Select course root
   - In CourseData, expand "Holes" array
   - Drag hole GameObjects into array

### Step 3: Addressables

Two options:

**A. Automated (Map Maker Window)**
1. Window → Super Battle Golf → Map Maker
2. Enter map name
3. Click "1. Setup Addressables"
4. Follow dialog instructions

**B. Manual**
1. Window → Asset Management → Addressables → Groups
2. Create new group: "MyMap"
3. Drag scene into group
4. Set Address: `CustomCourseMyMapName`
   - **CRITICAL:** Must start with `CustomCourse`

### Step 4: Build Asset Bundles

**A. Via Map Maker:**
- Click "2. Build Asset Bundles"

**B. Manual:**
- Window → Asset Management → Addressables → Build
- Build → New Build → Default Build Script
- Output: `Assets/AddressableAssetsData/Windows/`

### Step 5: Export

**Via Map Maker:**
1. Click "3. Export Map"
2. Choose output folder
3. Tool generates:
   - `mod.json` (metadata)
   - `README.md` (instructions)
   - Copies asset bundles
   - Opens folder automatically

**Manual:**
1. Copy files from `Assets/AddressableAssetsData/Windows/` to mod folder
2. Create `mod.json` (see template below)
3. Done!

## mod.json Template

```json
{
  "id": "my-custom-map",
  "name": "My Custom Golf Course",
  "author": "YourName",
  "version": "1.0.0",
  "description": "An amazing custom course",
  "type": "map",
  "content": {
    "addressables": true,
    "catalogPath": "catalog.bin"
  },
  "meta": {
    "difficulty": "medium",
    "holes": 3,
    "environment": "custom",
    "tags": ["fun", "challenging"]
  }
}
```

## Testing Your Map

1. Copy entire mod folder to:
   ```
   [Game]\Mods\Maps\YourMapName\
   ```

2. Launch Super Battle Golf with mod loader

3. Check log file:
   ```
   %APPDATA%\sbg-mod-loader\mod-loader.log
   ```

4. Look for:
   ```
   [ModLoader] Loading map: YourMapName
   [Addressables] Catalog loaded: ...
   [MapLoader] ✅ Map loaded successfully
   ```

5. Your map should appear in custom courses!

## Tips & Best Practices

### Performance
- ✅ Keep poly count reasonable (< 100k tris per scene)
- ✅ Use LODs for distant objects
- ✅ Bake lighting when possible
- ✅ Use texture atlases
- ✅ Optimize colliders (use simple shapes)

### Design
- ✅ Playtest thoroughly
- ✅ Mark clear paths (visual cues)
- ✅ Balance difficulty
- ✅ Add variety (terrain, hazards, obstacles)
- ✅ Consider different player skill levels

### Technical
- ✅ **ALWAYS** use `CustomCourse` prefix for Addressables
- ✅ Use exact Unity version (6000.3.10f1)
- ✅ Test in-game before publishing
- ✅ Include README.md with installation instructions
- ✅ Use meaningful file names

### Common Mistakes
- ❌ Wrong Unity version → Asset bundles won't load
- ❌ Wrong Addressables prefix → Map won't appear in-game
- ❌ Missing mod.json → Mod loader skips it
- ❌ No collision on terrain → Ball falls through
- ❌ Too many objects → Performance issues

## Troubleshooting

### "Asset bundle won't load in game"
- Check Unity version (must be 6000.3.10f1)
- Check Addressables version (must be 2.8.1)
- Verify address starts with `CustomCourse`

### "Map not appearing in game"
- Check mod.json syntax (use JSON validator)
- Verify folder is in `[Game]/Mods/Maps/`
- Check log file for errors

### "Game crashes when loading map"
- Too many objects (reduce poly count)
- Missing required components
- Corrupted asset bundle (rebuild)

### "Build fails"
- Install Addressables package
- Save scene before building
- Check for script errors in Console

## Advanced Topics

### Custom Materials
1. Create materials in Unity
2. Assign to objects
3. Materials auto-included in bundles

### Custom Prefabs
1. Create prefab in Unity
2. Add to Addressables
3. Reference in scene
4. Will be included in build

### Multiple Scenes
- Each scene = separate Addressable
- Create transitions between scenes
- Link via custom scripts

### Dynamic Elements
- Add scripts for moving platforms
- Animated obstacles
- Interactive hazards
- Particle effects

## Publishing Your Map

1. Test thoroughly!
2. Export via Map Maker
3. Zip the mod folder
4. Upload to:
   - GitHub
   - Nexus Mods
   - Discord community
5. Include:
   - Screenshots
   - Video preview
   - Clear installation instructions

## Example Maps

See `SDK/Examples/ExampleMap/` for a minimal working example.

## Getting Help

- **Log File:** `%APPDATA%\sbg-mod-loader\mod-loader.log`
- **Discord:** [TBD]
- **GitHub Issues:** https://github.com/ssfdre38/sbgmodloader/issues

---

**Happy Map Making!** ⛳🏌️

Version: 1.0.0
