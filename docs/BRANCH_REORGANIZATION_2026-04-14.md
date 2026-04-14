# Branch Reorganization - 2026-04-14

## Issue
The SDK and Map Maker branches were created as regular branches, which included the entire master branch history plus their specific content. This made the branches unnecessarily large and confusing.

## Fix
Recreated both branches as **orphan branches** (no shared history) containing ONLY their specific content.

## Changes Made

### Before (Incorrect)
```
master: Core mod loader (~100 files)
sdk-package: Master + SDK (~118 files)
mapmaker-tool: Master + MapMaker (~113 files)
```

### After (Correct)
```
master: Core mod loader only (~100 files)
sdk-package: SDK ONLY (18 files)
mapmaker-tool: MapMaker ONLY (13 files)
```

## Branch Contents

### master
- ModLoaderCore/ (C++ DLL source)
- GUILauncher/ (WPF mod manager)
- docs/ (development documentation)
- Mods/ (test mods)
- Tools, scripts, build files

### sdk-package (Orphan)
- Templates/ (4 mod type templates)
- Examples/ (4 complete example mods)
- Tools/ (BuildMod.ps1, ValidateMod.ps1)
- UnityPackage/ (Unity Package Manager files)
- README.md, QUICKSTART.md, CHANGELOG.md

### mapmaker-tool (Orphan)
- Assets/Scripts/ (6 C# files)
- Packages/ (Unity dependencies)
- ProjectSettings/ (Unity configuration)
- README.md, QUICKSTART.md, CHANGELOG.md

## Technical Details

### How Orphan Branches Work
```bash
# Create branch with no parent commits
git checkout --orphan branchname

# Remove all files from staging
git rm -rf .

# Add only specific content
# Commit creates new root commit (no history)
```

### Benefits
- ✅ Clean separation of concerns
- ✅ Smaller clone size per branch
- ✅ No confusion about what belongs where
- ✅ Independent development
- ✅ Clearer for users ("just checkout the branch you need")

## Verification

### SDK Branch
```bash
git checkout sdk-package
ls
# Output: Examples Templates Tools UnityPackage CHANGELOG.md QUICKSTART.md README.md
```

### MapMaker Branch
```bash
git checkout mapmaker-tool
ls
# Output: Assets Packages ProjectSettings CHANGELOG.md QUICKSTART.md README.md
```

### Master Branch
```bash
git checkout master
ls
# Output: ModLoaderCore GUILauncher docs Mods Tools ...
```

## Impact

**Users:**
- Clone single branch: `git clone -b branchname --single-branch <url>`
- Much smaller downloads
- Clearer purpose per branch

**Developers:**
- Work on mod loader without SDK/MapMaker clutter
- SDK/MapMaker development completely independent
- Can merge master changes selectively if needed

## Commits

- SDK: `9086823` - "SDK v1.0.0 - Mod developer kit"
- MapMaker: `5784460` - "Map Maker v1.0.0 - Unity map creation tool"

Both pushed force to origin (replaced old branches).

## References

- Issue raised: User noticed branches contained duplicate content
- Fix applied: 2026-04-14
- Branches recreated as orphans with clean history

---

**Status:** ✅ RESOLVED - All branches now properly isolated
