# SDK Changelog

All notable changes to the Super Battle Golf Mod Loader SDK will be documented here.

## [0.1.0] - 2026-04-14

### Added
- Initial SDK release
- Unity package manifest (package.json)
- Complete documentation suite:
  - README.md - SDK overview and installation
  - QUICKSTART.md - 5-minute getting started guide
- Templates for all mod types:
  - MapTemplate - Custom golf course template
  - GameModeTemplate - JSON game mode template
  - CharacterTemplate - Cosmetics template
  - ItemTemplate - Weapon/item template
- Example mods with full documentation:
  - ExampleMap - Red Cube Arena (minimal test map)
  - ExampleGameMode - Test Battle Royale (3-hole mode)
  - ExampleCharacter - Neon Golfer (skin with glow)
  - ExampleItem - Mega Weapons Pack (3 items)
- Build tools:
  - BuildMod.ps1 - Automated asset bundle building
  - ValidateMod.ps1 - Pre-publish validation
- Unity Package Manager integration

### Requirements
- Unity 6000.3.10f1 (exact version)
- Unity Addressables 2.8.1 (exact version)

### Notes
This is the first public release of the SDK. Feedback welcome!

---

## Version Format

We use [Semantic Versioning](https://semver.org/):
- MAJOR.MINOR.PATCH
- Example: 1.2.3

### Version Increments
- **MAJOR** - Breaking changes (mod compatibility breaks)
- **MINOR** - New features (backwards compatible)
- **PATCH** - Bug fixes (backwards compatible)
