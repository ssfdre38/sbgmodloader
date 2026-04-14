# Mega Weapons Pack - Example Item Mod

Example showing how to create custom weapons, power-ups, and items.

## What This Example Shows

- Creating item prefabs in Unity
- Setting up item stats and behavior
- Configuring Addressables for items
- Different item types (weapon, powerup, trap)

## Items Included

### Mega Rocket Launcher (Weapon)
- **Damage:** 100
- **Explosion Radius:** 10 meters
- **Cooldown:** 5 seconds
- **Ammo:** 3 shots

### Speed Boost Ultra (Power-Up)
- **Duration:** 10 seconds
- **Speed Multiplier:** 2.5x
- Temporary player buff

### Teleport Trap (Trap)
- **Trigger Radius:** 2 meters
- **Duration:** 30 seconds
- Randomly teleports players

## Unity Setup

### Item Prefab Structure
```
ItemPrefab
├── Model (visual mesh)
├── Collider (physics)
├── ItemBehavior (script)
└── Effects (particles, sounds)
```

### Addressables
Items MUST have addresses starting with `CustomItem`:
- `CustomItemMegaRocket`
- `CustomItemSpeedBoostUltra`
- `CustomItemTeleportTrap`

## Item Types

### Weapon
Throwable/shootable items that deal damage:
```json
{
  "type": "weapon",
  "stats": {
    "damage": 50.0,
    "explosionRadius": 5.0,
    "cooldown": 3.0,
    "ammo": 5
  }
}
```

### Power-Up
Temporary buffs for players:
```json
{
  "type": "powerup",
  "stats": {
    "duration": 10.0,
    "speedMultiplier": 1.5
  }
}
```

### Consumable
One-time use items:
```json
{
  "type": "consumable",
  "stats": {
    "effect": "heal",
    "amount": 50.0
  }
}
```

### Trap
Placeable hazards:
```json
{
  "type": "trap",
  "stats": {
    "triggerRadius": 2.0,
    "duration": 30.0
  }
}
```

## Creating Items in Unity

### Step 1: Create Prefab
1. Create GameObject for item
2. Add 3D model/sprite
3. Add Collider (trigger or solid)
4. Add Rigidbody if needed

### Step 2: Add Behavior Script
```csharp
using UnityEngine;

public class MyCustomItem : MonoBehaviour {
    public float damage = 50f;
    public float radius = 5f;
    
    void OnTriggerEnter(Collider other) {
        // Item behavior here
    }
}
```

### Step 3: Add Effects
- Particle systems for explosions
- Audio sources for sounds
- Trail renderers for projectiles

### Step 4: Configure Addressables
1. Add prefab to Addressables group
2. Set address: `CustomItem[YourItemName]`
3. Build bundles

## Building

1. Create item prefabs with scripts
2. Add to Addressables (with `CustomItem` prefix)
3. Build asset bundles
4. Create mod.json with item stats
5. Copy to `[Game]/Mods/Items/YourMod/`

## Testing

1. Copy to `[Game]/Mods/Items/ExampleItems/`
2. Launch game with mod loader
3. Start match with custom items enabled
4. Items should spawn during gameplay!
5. Test behavior and balance

## Balance Considerations

- **Weapons:** High damage = longer cooldown
- **Power-ups:** Strong effects = short duration
- **Traps:** Large radius = shorter lifetime
- **Ammo:** Powerful weapons = limited ammo

## Creating Your Own

1. Design item concept
2. Create 3D model or use Unity primitives
3. Write C# behavior script
4. Add visual/audio effects
5. Balance stats through testing
6. Add to Addressables
7. Build and deploy

## Tips

- Start simple (cube + collider + script)
- Test behavior in Unity play mode
- Balance carefully (OP items ruin fun!)
- Add juice (particles, sounds, screen shake)
- Playtest with friends
- Iterate based on feedback

---

This example shows the item system. Create your own weapons and power-ups!
