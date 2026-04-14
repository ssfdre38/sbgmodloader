# Neon Golfer - Example Character Mod

Example showing how to create custom character skins and cosmetics.

## What This Example Shows

- Creating character models in Unity
- Setting up materials with emission (glow)
- Configuring Addressables for cosmetics
- Defining multiple cosmetic items in one mod

## Cosmetics Included

### Neon Golfer (Skin)
- Full character replacement
- Neon glow material
- Rarity: Epic (purple)

### Neon Visor (Hat)
- Hat accessory
- Light-up effect
- Rarity: Rare (blue)

## Unity Setup

### Character Model
1. Import character model (FBX/OBJ)
2. Setup rig for animation (humanoid)
3. Create materials with emission shader
4. Add to prefab

### Addressables
Cosmetics MUST have addresses starting with `CustomCosmetic`:
- Skin: `CustomCosmeticNeonGolfer`
- Hat: `CustomCosmeticNeonVisor`

## mod.json Structure

```json
{
  "character": {
    "cosmetics": [
      {
        "id": "unique-id",
        "name": "Display Name",
        "type": "skin|hat|outfit|accessory|emote|trail",
        "addressable": "CustomCosmetic[Name]",
        "rarity": "common|uncommon|rare|epic|legendary",
        "description": "..."
      }
    ]
  }
}
```

## Cosmetic Types

- **skin** - Full character replacement
- **outfit** - Clothing/costume
- **hat** - Headwear
- **accessory** - Glasses, backpack, etc.
- **emote** - Victory animation
- **trail** - Ball trail effect

## Rarity Tiers

- **common** - Gray, easy to get
- **uncommon** - Green
- **rare** - Blue
- **epic** - Purple
- **legendary** - Gold

## Building

1. Setup character models and materials
2. Add to Addressables with `CustomCosmetic` prefix
3. Build asset bundles
4. Create mod.json with cosmetic definitions
5. Copy to `[Game]/Mods/Characters/YourMod/`

## Testing

1. Copy to `[Game]/Mods/Characters/ExampleCharacter/`
2. Launch game with mod loader
3. Go to Character Select / Cosmetics menu
4. Your items should appear in the list!
5. Equip and enjoy!

## Creating Your Own

1. Model character in Blender/Maya
2. Export as FBX
3. Import to Unity 6000.3.10f1
4. Setup materials (URP shaders)
5. Add to Addressables
6. Build bundles
7. Create mod.json
8. Test in-game!

## Tips

- Keep poly count reasonable (< 50k tris)
- Use texture atlases for efficiency
- Test materials in play mode first
- Use Unity's character rig for animations
- Preview in-game before publishing

---

This example demonstrates the cosmetics system. Customize for your own skins!
