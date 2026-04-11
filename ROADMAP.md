# Super Battle Golf Mod Loader - Development Roadmap

This document outlines the planned features and development phases for the SBG Mod Loader project.

## 🎯 Project Vision

Transform Super Battle Golf into a fully moddable experience with:
- Custom maps and courses
- Custom gameplay modes (teams, variants, etc.)
- Easy-to-use tools for content creators
- User-friendly mod management
- Thriving modding community

---

## ✅ Phase 1: Foundation (COMPLETE)

**Status:** ✅ Done  
**Version:** v0.1.0-beta

### Completed Features:
- ✅ Native C++ DLL injection system
- ✅ ModLoaderCore framework
- ✅ Mod discovery and lifecycle management
- ✅ IModModule interface for mod developers
- ✅ Comprehensive logging system
- ✅ Update-proof architecture (tested across game versions)
- ✅ Example mod (VersionDisplayMod)
- ✅ Build scripts and documentation
- ✅ GitHub repository setup

**Deliverable:** Working mod loader that can inject code and load plugins

---

## 🔧 Phase 2: Game Integration (IN PLANNING)

**Status:** 🟡 Pending - Requires game method addresses  
**Target:** v0.2.0

### Goals:
Enable mods to interact with actual game state and mechanics

### Required Work:

#### 2.1 Hook Game Methods
- **Blocker:** Need correct RVAs/addresses from game devs or reverse engineering
- Hook scene loading/unloading
- Hook game state changes (menu → gameplay → results)
- Hook player spawn/despawn
- Hook ball physics/collision

#### 2.2 Create Game State API
- Expose player data (position, score, name, etc.)
- Expose ball data (position, velocity, last hit)
- Expose map/course data
- Expose game mode information
- Event system for game state changes

#### 2.3 Scene Management
- Detect current scene (MainMenu, Gameplay, MapSelect, etc.)
- Notify mods of scene transitions
- Per-scene mod activation

### Deliverables:
- `GameAPI.h` - C++ API for accessing game state
- `Events.h` - Event system for game callbacks
- Updated IModModule with game interaction methods
- Example mods demonstrating API usage

### Dependencies:
- Correct method addresses from:
  - Scene loading functions
  - Game state manager
  - Player controller
  - Ball physics system

---

## 🗺️ Phase 3: Custom Content (FUTURE)

**Status:** 🔴 Blocked by Phase 2  
**Target:** v0.3.0

### 3.1 Custom Map Loading

#### Goals:
- Load custom map/course files from disk
- Inject custom maps into game's map selection
- Support custom terrain, obstacles, holes

#### Technical Approach:
1. Reverse engineer Unity map format
2. Create map serialization/deserialization
3. Hook map loading system
4. Inject custom map data
5. Handle map assets (models, textures)

#### Map File Format (TBD):
- JSON or binary format
- Define: terrain, holes, spawn points, obstacles
- Asset references (models, textures)

### 3.2 Custom Gameplay Modes

#### Goals:
- Team-based gameplay
- Custom scoring rules
- Game mode variants (time attack, stroke limit, etc.)
- Multi-ball modes
- Custom power-ups/mechanics

#### Technical Approach:
1. Hook game rules/scoring system
2. Override scoring calculations
3. Modify player grouping/teams
4. Custom UI overlays for new modes

### Deliverables:
- Map loader API
- Map file format specification
- Example custom maps
- Gameplay modifier API
- Example custom game modes

---

## 🛠️ Phase 4: Tools & SDK (FUTURE)

**Status:** 🔴 Blocked by Phase 3  
**Target:** v0.4.0

### 4.1 Enhanced Mod Developer SDK

#### Goals:
- Complete API documentation
- Helper libraries and utilities
- Code examples and templates
- Best practices guide

#### Components:
- **API Reference:** Full documentation of all hooks and APIs
- **Helper Libraries:** Common utilities (logging, config, UI)
- **Templates:** Starter templates for common mod types
- **Debugging Tools:** Live debugging support, profiling

### 4.2 Map Maker Tool

#### Approach Options:

**Option A: Unity Editor Plugin** (Recommended)
- Use Unity Editor directly
- Custom editor scripts for map creation
- Export to SBG format
- Pros: Full Unity features, terrain editor, asset pipeline
- Cons: Requires Unity knowledge

**Option B: Standalone Map Editor**
- Custom C# or C++ application
- 3D viewport for map editing
- Asset importer
- Pros: Simpler for users, no Unity required
- Cons: More development effort, limited features

**Features:**
- Visual terrain editor
- Hole placement and configuration
- Obstacle/hazard placement
- Spawn point editor
- Playtest mode (if possible)
- Export to map format

### 4.3 Documentation Site

#### Content:
- Getting Started guide
- API reference (auto-generated from code)
- Tutorials (beginner to advanced)
- Map creation guide
- Community showcase
- FAQ and troubleshooting

#### Platform:
- GitHub Pages or dedicated site
- DocFX or MkDocs for generation

### Deliverables:
- Complete SDK package
- Map maker application (Unity plugin or standalone)
- Documentation website
- Video tutorials
- Community Discord/forum

---

## 🖥️ Phase 5: User Experience (FUTURE)

**Status:** 🔴 Blocked by Phase 4  
**Target:** v1.0.0

### 5.1 GUI Mod Manager/Launcher

#### Goals:
- User-friendly mod management
- No command line required
- Visual mod browser
- Easy mod installation

#### Features:
- **Mod List:** Show installed mods with thumbnails
- **Enable/Disable:** Toggle mods on/off
- **Launch Buttons:** 
  - "Play Vanilla" (no mods)
  - "Play Modded" (with enabled mods)
- **Mod Details:** Description, version, author, dependencies
- **Mod Configuration:** Per-mod settings GUI
- **Update Checker:** Check for mod updates
- **Error Handling:** Show mod load errors clearly

#### Technology Options:
- **WPF** (C# with .NET) - Native Windows, good UI
- **Electron** (JavaScript) - Cross-platform, web tech
- **Qt** (C++) - Cross-platform, native performance
- **Dear ImGui** (C++) - Immediate mode, lightweight

### 5.2 Mod Distribution System

#### Options:

**Option A: Steam Workshop** (If supported by devs)
- Built-in to Steam
- Easy discovery and installation
- Automatic updates
- Requires game dev approval

**Option B: Custom Mod Browser**
- Standalone mod repository
- Web-based browsing
- One-click install via launcher
- Community ratings/reviews

**Option C: Simple GitHub Releases**
- Manual download from GitHub
- User places files in Mods folder
- Simple but works

#### Features (for custom system):
- Mod search and filtering
- Categories (maps, gameplay, visual, etc.)
- Ratings and reviews
- Download tracking
- Dependency management
- Version compatibility checking

### Deliverables:
- GUI Launcher application
- Mod distribution platform (TBD which approach)
- User documentation
- Installer/updater system

---

## 📊 Current Priority: Phase 2 Next Steps

### Immediate Actions Needed:

1. **Get Method Addresses from Game Devs**
   - Reach out to Super Battle Golf developers
   - Request cooperation or at least method addresses
   - Explain community benefits

2. **Alternative: Reverse Engineering**
   - If devs won't help, use advanced RE tools
   - Pattern scanning for method signatures
   - Dynamic analysis with debuggers

3. **Community Building**
   - Discord server for coordination
   - GitHub Discussions for ideas
   - Recruit contributors with Unity/IL2CPP experience

4. **Research & Prototyping**
   - Study Unity IL2CPP internals
   - Experiment with hooking approaches
   - Document findings

---

## 🤝 How to Contribute

See [CONTRIBUTING.md](CONTRIBUTING.md) for details.

### Current Needs:
- **Reverse Engineers:** Help find game method addresses
- **Unity Developers:** Understand game architecture
- **C++ Developers:** Improve core framework
- **Documentation Writers:** Help write guides
- **Testers:** Test on different systems

---

## 📅 Timeline Estimates

**Phase 2:** 2-4 weeks (once we have method addresses)  
**Phase 3:** 4-8 weeks  
**Phase 4:** 6-12 weeks  
**Phase 5:** 4-6 weeks  

**Total to v1.0.0:** ~4-7 months of active development

*Note: These are rough estimates assuming consistent development effort and community contributions.*

---

## 💬 Discussion & Feedback

Have ideas or suggestions? Open a [GitHub Discussion](https://github.com/ssfdre38/sbgmodloader/discussions) or join our Discord!

---

**Last Updated:** April 11, 2026  
**Current Version:** v0.1.0-beta (Phase 1 Complete)
