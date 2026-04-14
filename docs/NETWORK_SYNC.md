# Network Synchronization

The NetworkSyncManager ensures all players in a multiplayer match have compatible mods loaded.

## How It Works

### 1. Detection
When a player hosts or joins a multiplayer session:
- Hosting: `NetworkSyncManager::OnMultiplayerHost()` is called
- Joining: `NetworkSyncManager::OnMultiplayerJoin()` is called

### 2. Mod List Exchange
- **Host sends** their mod list to all joining clients
- **Clients receive** the host's mod list and compare with local mods

### 3. Compatibility Validation
Each mod is checked for:
- **Presence** - Required mods must be installed
- **Version** - Versions must match exactly
- **Checksum** - File integrity validation (warning only)

### 4. Enforcement
- ✅ **Compatible** - Player joins normally
- ❌ **Incompatible** - Connection blocked with detailed error message

## Mod Synchronization Types

### Required Mods (Must Match)
- **Maps** - All players need the same course
- **Game Modes** - All players need matching rules
- **Items** - All players need same weapons/power-ups

### Optional Mods (Don't Block)
- **Cosmetics** - Character skins (client-side only)
- **UI Mods** - Interface customizations

## ModSyncInfo Structure

```cpp
struct ModSyncInfo {
    std::string id;         // Mod identifier (e.g., "battle-royale-extreme")
    std::string version;    // Semantic version (e.g., "1.2.0")
    std::string checksum;   // File hash for integrity
    bool isRequired;        // True for gameplay mods, false for cosmetics
};
```

## Example Flow

### Scenario: Player joins match with incompatible mods

**Host has:**
- custom-map-v2 (v2.0.0)
- mega-weapons (v1.5.0)

**Client has:**
- custom-map-v2 (v1.8.0) ❌ Version mismatch
- cool-skins (v1.0.0) ✅ Cosmetic (optional)

**Result:**
```
❌ Mod mismatch detected!

Version mismatches:
  • custom-map-v2 (host: 2.0.0, local: 1.8.0)

Missing required mods:
  • mega-weapons

Please ensure all players have the same mods installed.
```

Connection blocked until mods are synchronized.

## Networking System Detection

NetworkSyncManager automatically detects the game's networking system:

### Supported Systems
1. **Unity Netcode for GameObjects** - Modern Unity networking
2. **Unity UNet (legacy)** - Older Unity built-in
3. **Mirror Networking** - Popular third-party
4. **Photon** - Another popular solution
5. **Custom** - Game-specific networking classes

### Fallback
If no networking system is detected:
- Network sync disabled
- Mod loader works in single-player only
- Warning logged

## API Usage

### Register Mismatch Callback
```cpp
NetworkSyncManager::RegisterMismatchCallback([](const std::string& message) {
    // Show error UI to player
    UIManager::ShowError("Mod Mismatch", message);
});
```

### Manual Trigger (if auto-detection fails)
```cpp
// When hosting
NetworkSyncManager::OnMultiplayerHost();

// When joining
NetworkSyncManager::OnMultiplayerJoin();
```

### Get Local Mod List
```cpp
auto mods = NetworkSyncManager::GetLocalModList();
for (const auto& mod : mods) {
    printf("Mod: %s v%s\n", mod.id.c_str(), mod.version.c_str());
}
```

## Future Enhancements

### Planned Features
- **Auto-Download** - Fetch missing mods from workshop
- **Partial Sync** - Join with subset of mods
- **Quick Fix** - Offer to disable incompatible mods
- **Compatibility Matrix** - Pre-check before matchmaking
- **Mod Bundles** - Download preset mod packs

### Security Improvements
- SHA256 checksums (currently using simple CRC32)
- Digital signatures for verified mods
- Replay validation for anti-cheat

## Troubleshooting

### "Network sync disabled"
- Game doesn't use supported networking system
- Mod loader will work in single-player only

### "Cannot send mod list"
- Networking classes not found
- Check log for details on detection

### Checksum mismatch warning
- Mod files differ slightly between players
- Usually harmless (whitespace, metadata)
- Versions match, so connection allowed

### Version mismatch
- Players have different mod versions
- Update mods to match host's version
- Or host can downgrade to client's version

## Technical Details

### Checksum Calculation
Currently uses simple CRC32 hash of mod.json:
```cpp
uint32_t checksum = 0;
for (char c : mod_json_content) {
    checksum = ((checksum << 5) + checksum) + c;
}
```

**Future:** Will use SHA256 for better security.

### Network Message Format
```
[Message Type: 0x01 = ModList]
[Mod Count: uint32]
For each mod:
  [ID Length: uint16]
  [ID String: UTF-8]
  [Version Length: uint16]
  [Version String: UTF-8]
  [Checksum: 32 bytes]
  [Is Required: bool]
```

### Threading
- NetworkSyncManager is thread-safe
- Validation runs on networking thread
- Callbacks execute on main thread

---

**Status:** ✅ Implemented  
**Dependencies:** MonoHelper, ModManager  
**Version:** 1.0.0 (Initial implementation)
