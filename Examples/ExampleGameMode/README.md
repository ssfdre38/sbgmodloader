# Test Battle Royale - Example Custom Game Mode

This is an example showing how to create custom game modes using only JSON.

## What This Example Shows

- Creating game modes without Unity (just JSON!)
- Configuring holes from the base game
- Setting custom rules and parameters
- Using mod.json for game mode mods

## Features

- **3 Desert Holes** - Uses built-in desert courses
- **120 Second Overtime** - Longer matches
- **High Item Spawn Rate** - 80% chance for items
- **Custom Items Enabled** - Can use modded items
- **4 Player Max** - Standard battle royale

## How It Works

Game modes are pure JSON - no Unity project needed!

The mod loader:
1. Reads mod.json
2. Parses the gamemode section
3. Creates Unity CourseData object
4. Injects into MatchSetupMenu
5. Players can select it in-game!

## Customization

Edit `mod.json` to change:

### Holes
```json
"holes": [
  "CourseSelectionDesert01",
  "CourseSelectionForest02",
  "CourseSelectionSnow03",
  "CustomCourseYourMap"  // Can reference custom maps!
]
```

**Available hole IDs:**
- Desert: `CourseSelectionDesert01` through `05`
- Forest: `CourseSelectionForest01` through `05`
- Snow: `CourseSelectionSnow01` through `05`
- Space: `CourseSelectionSpace01` through `05`
- Custom: `CustomCourse[YourMapName]`

### Rules
```json
"rules": {
  "overtimeDuration": 60.0,      // Seconds
  "itemSpawnChance": 0.5,        // 0.0 - 1.0
  "allowCustomItems": true,      // Enable mod items
  "maxPlayers": 8,               // Player limit
  "teamMode": false              // Team vs team
}
```

## Testing

1. Copy this folder to `[Game]/Mods/GameModes/ExampleMode/`
2. Launch game with mod loader
3. Go to Match Setup
4. "Test Battle Royale" should appear in game mode list
5. Select it and start match!

## Creating Your Own

1. Copy this folder
2. Change `id` to unique identifier (lowercase-with-dashes)
3. Change `name` to display name
4. Edit holes array (add/remove courses)
5. Tweak rules to your preference
6. Update meta fields
7. Copy to Mods folder and test!

## No Unity Required!

This is the easiest type of mod to create - just edit JSON and test!

---

Use this as a template for your own custom game modes.
