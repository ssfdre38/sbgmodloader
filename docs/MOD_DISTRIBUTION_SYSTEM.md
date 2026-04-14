# Mod Distribution & Workshop System

Complete mod browsing, downloading, and installation system integrated into the GUI Launcher.

## Features

### 🌐 Mod Browser
- Browse all available mods from online repository
- Search by name, author, description, or tags
- Filter by type (Maps, Game Modes, Characters, Items)
- Show featured/popular mods
- View recently updated mods
- Detailed mod information with ratings and download counts

### 📥 One-Click Installation
- Download and install mods directly from browser
- Progress tracking during download
- Automatic extraction and placement
- Supports all mod types (Maps, GameModes, Characters, Items)

### 🔄 Update System
- Check for mod updates
- Compare installed vs. available versions
- Auto-update capability (future)

### ⭐ Mod Ratings & Reviews
- Star ratings (1-5 stars)
- Download counts
- Featured mod highlighting
- Community engagement metrics

## Architecture

### Repository Structure

**Repository URL:** `https://sbgmods.github.io/repository`

**Index File:** `https://sbgmods.github.io/repository/index.json`

```json
{
  "version": "1.0.0",
  "mods": [
    {
      "id": "awesome-desert-course",
      "name": "Awesome Desert Course",
      "author": "ModMaster",
      "version": "1.2.0",
      "description": "A challenging 18-hole desert themed golf course",
      "type": "map",
      "downloads": 1523,
      "rating": 4.7,
      "ratingCount": 89,
      "featured": true,
      "updatedDate": "2026-04-10",
      "tags": ["desert", "challenging", "18-hole"],
      "thumbnailUrl": "https://sbgmods.github.io/repository/thumbs/awesome-desert-course.jpg",
      "downloadUrl": "https://sbgmods.github.io/repository/mods/awesome-desert-course/1.2.0/awesome-desert-course.zip",
      "fileSize": 15728640,
      "minLoaderVersion": "1.0.0"
    }
  ]
}
```

### Mod Download Structure

```
https://sbgmods.github.io/repository/mods/
├── [mod-id]/
│   ├── [version]/
│   │   ├── [mod-id].zip
│   │   └── metadata.json
│   └── latest/
│       └── [mod-id].zip
```

**Zip Contents:**
```
mod-id.zip
├── mod.json
├── assets/
│   └── [asset files]
└── README.md (optional)
```

## Components

### Services

**ModRepositoryService.cs**
- `FetchAvailableModsAsync()` - Gets mod list from repository
- `DownloadModAsync()` - Downloads and installs a mod
- `HasUpdateAsync()` - Checks if update available
- `SearchModsAsync()` - Searches mods by query
- `GetFeaturedModsAsync()` - Gets featured mods
- `GetRecentModsAsync()` - Gets recently updated mods

### ViewModels

**ModBrowserViewModel.cs**
- Manages mod browser state
- Handles search and filtering
- Coordinates downloads
- Progress tracking

### Views

**ModBrowserWindow.xaml**
- Mod browsing interface
- Search and filter UI
- Mod details panel
- Install buttons
- Progress indicators

## User Workflow

### 1. Open Mod Browser
```
Main Launcher → "Browse Mods" button → Mod Browser opens
```

### 2. Browse Mods
- **All Mods:** View complete catalog
- **Search:** Type query, press Enter or click Search
- **Featured:** Click "Featured" button
- **Filter:** Select mod type dropdown
- **Sort:** By downloads (automatic)

### 3. View Details
- Click any mod in the list
- Details panel shows: name, author, description, version, size, ratings, downloads
- Tags displayed
- Install button available

### 4. Install Mod
- Click "Install" button on mod
- Confirmation dialog appears
- Downloads with progress bar
- Automatically extracts to correct Mods/ subfolder
- Success notification
- Prompt to restart game

### 5. Use Installed Mod
- Close browser
- Main launcher auto-refreshes mod list
- New mod appears (enabled by default)
- Launch game to use it

## Integration

### Main Launcher Integration

Added to `MainViewModel.cs`:
```csharp
[RelayCommand]
private void OpenModBrowser()
{
    var browserWindow = new Views.ModBrowserWindow(GamePath);
    browserWindow.Owner = Application.Current.MainWindow;
    browserWindow.ShowDialog();
    RefreshMods(); // Auto-refresh after closing
}
```

Sidebar button:
```xml
<Button Content="🌐 Browse Mods" Command="{Binding OpenModBrowserCommand}"
        Style="{StaticResource PrimaryButton}" Background="{StaticResource AccentBrush}"/>
```

### Network Requirements

**Dependencies:**
- `System.Net.Http` - HTTP requests
- `System.IO.Compression` - Zip extraction
- `Newtonsoft.Json` - JSON parsing

**Endpoints:**
- Repository index: GET `/index.json`
- Mod download: GET `/mods/{id}/{version}/{id}.zip`
- Thumbnails: GET `/thumbs/{id}.jpg`

## Setting Up a Repository

### Option 1: GitHub Pages (Recommended)

1. Create repository: `sbgmods/repository`
2. Enable GitHub Pages (Settings → Pages)
3. Create `index.json` with mod listings
4. Upload mod zips to `mods/[id]/[version]/`
5. URL: `https://sbgmods.github.io/repository`

### Option 2: Custom Server

1. Set up web server (Apache, Nginx, etc.)
2. Configure CORS headers:
   ```
   Access-Control-Allow-Origin: *
   Access-Control-Allow-Methods: GET
   ```
3. Create directory structure
4. Update repository URL in launcher

### Option 3: CDN

1. Use Cloudflare Pages, Netlify, Vercel
2. Deploy static files
3. Low cost, high performance
4. Global distribution

## Mod Submission Process

### For Mod Creators

1. **Create Mod:**
   - Follow SDK guidelines
   - Test thoroughly
   - Include README.md

2. **Package:**
   - Zip mod folder
   - Name: `[mod-id].zip`
   - Include mod.json in root

3. **Submit:**
   - Fork repository
   - Add mod to `mods/[id]/[version]/`
   - Update `index.json`
   - Create pull request

4. **Approval:**
   - Automated checks run
   - Manual review (optional)
   - Merge to main branch
   - Instantly available

### Automated Validation

**CI/CD Checks:**
- ✅ Valid mod.json syntax
- ✅ Correct file structure
- ✅ No malicious files
- ✅ File size limits (< 100MB)
- ✅ Version number format
- ✅ Unique mod ID
- ✅ Required fields present

## Future Enhancements

### Planned Features

1. **Auto-Updates**
   - Background update checking
   - One-click update all
   - Update notifications

2. **Ratings & Reviews**
   - Write reviews
   - Upvote/downvote
   - Report issues

3. **Collections**
   - Curated mod packs
   - Theme-based collections
   - User-created lists

4. **Screenshots**
   - Multiple images per mod
   - Image gallery
   - Video previews

5. **Dependencies**
   - Automatic dependency resolution
   - Install required mods
   - Conflict detection

6. **Mod Profiles**
   - Save mod loadouts
   - Quick switch profiles
   - Share configurations

7. **Steam Workshop**
   - Steam Workshop integration
   - Workshop items as repository source
   - Automatic sync

8. **Analytics**
   - Track popular mods
   - Usage statistics
   - Trending mods

## Security

### Safe Downloading

**Protections:**
- ✅ HTTPS only
- ✅ File hash verification (planned)
- ✅ Size limits
- ✅ Malware scanning (repository side)
- ✅ Sandboxed extraction

**User Safeguards:**
- Confirmation before install
- Show mod details
- Report malicious mods
- Trusted sources only

### Privacy

**Data Collection:**
- ❌ No personal info
- ❌ No tracking
- ✅ Download counts (anonymous)
- ✅ Local cache only

## Troubleshooting

### "Can't connect to repository"
- Check internet connection
- Verify repository URL
- Uses cached data if offline

### "Download failed"
- Check disk space
- Verify write permissions
- Try again (resume not supported yet)

### "Mod won't install"
- Check mod type matches folder
- Ensure game path is correct
- Check mod.json validity

### "Updates not showing"
- Click Refresh
- Clear cache: Delete `%APPDATA%\sbg-mod-loader\repository-cache\`

## Example: Creating a Repository

**Step-by-step:**

1. Create `index.json`:
```json
{
  "version": "1.0.0",
  "mods": []
}
```

2. Add first mod:
```json
{
  "mods": [
    {
      "id": "my-first-map",
      "name": "My First Map",
      "author": "YourName",
      "version": "1.0.0",
      "description": "A simple golf course",
      "type": "map",
      "downloads": 0,
      "rating": 0,
      "ratingCount": 0,
      "featured": false,
      "updatedDate": "2026-04-14",
      "tags": ["beginner", "simple"],
      "thumbnailUrl": "",
      "downloadUrl": "https://yoursite.com/mods/my-first-map/1.0.0/my-first-map.zip",
      "fileSize": 1048576,
      "minLoaderVersion": "1.0.0"
    }
  ]
}
```

3. Upload files:
```
/index.json
/mods/my-first-map/1.0.0/my-first-map.zip
```

4. Test in launcher!

## API Reference

### ModRepositoryService Methods

```csharp
// Fetch all mods
List<RepositoryMod> mods = await service.FetchAvailableModsAsync();

// Download mod
bool success = await service.DownloadModAsync(mod, targetDir, progressCallback);

// Check for update
bool hasUpdate = await service.HasUpdateAsync(installedMod);

// Search mods
List<RepositoryMod> results = await service.SearchModsAsync("desert");

// Get featured
List<RepositoryMod> featured = await service.GetFeaturedModsAsync();

// Get recent
List<RepositoryMod> recent = await service.GetRecentModsAsync(10);
```

## Contributing

### Repository Maintainers

**Responsibilities:**
- Review mod submissions
- Update index.json
- Monitor for issues
- Maintain uptime

**Tools Needed:**
- GitHub account
- Text editor
- Zip tool

### Mod Creators

**How to Help:**
- Create quality mods
- Test thoroughly
- Write good descriptions
- Include screenshots
- Respond to feedback

---

**Status:** ✅ Complete and functional  
**Version:** 1.0.0  
**Last Updated:** 2026-04-14
