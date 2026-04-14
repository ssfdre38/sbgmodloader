# Distribution Guide for Super Battle Golf Mod Loader

## About Code Signing

**Why isn't this software code-signed?**

Code signing certificates cost $200-400 per year from trusted Certificate Authorities. For a free, open-source community project, this cost is prohibitive. Many successful open-source projects (including popular game mods) are distributed unsigned.

**Is it safe?**

Yes! The software is:
- ✅ **Open Source** - All code is visible at https://github.com/ssfdre38/sbgmodloader
- ✅ **Community Reviewed** - Anyone can audit the code
- ✅ **No Hidden Code** - What you see is what you get
- ✅ **No Network Spying** - Only connects to mod repository (optional)
- ✅ **No Admin Rights** - Runs with normal user permissions

## Windows SmartScreen Warning

### What Users Will See

When users download and run the installer or launcher for the first time, Windows Defender SmartScreen will show:

```
Windows protected your PC
Microsoft Defender SmartScreen prevented an unrecognized app from starting.
```

**This is expected behavior for unsigned software.**

### How to Run Anyway

1. Click "More info"
2. Click "Run anyway"

That's it! Windows will remember the choice and won't ask again.

### Why Does This Happen?

Windows SmartScreen uses two methods to trust software:
1. **Digital signature** from a trusted Certificate Authority ($$$)
2. **Reputation** - After many users download and run the software safely

As a new release, we don't have either yet. Once the software gains reputation (downloads + no malware reports), the warning frequency decreases.

## Distribution Methods

### Method 1: GitHub Releases (Recommended)

**Setup:**
1. Go to GitHub repository → Releases
2. Click "Create a new release"
3. Tag: `v1.0.0`
4. Title: `Super Battle Golf Mod Loader v1.0.0`
5. Upload files:
   - `SBGModLoader-Setup-v1.0.0.exe` (Inno Setup installer)
   - `SBGModLoader-v1.0.0-Portable.zip` (portable version)
   - Source code (auto-generated)

**Benefits:**
- ✅ Free hosting
- ✅ Automatic checksums (SHA-256)
- ✅ Version tracking
- ✅ Download statistics
- ✅ Community-trusted platform

### Method 2: Direct Download

Host files on:
- Your own website
- Google Drive (not recommended - has limits)
- Dropbox
- MEGA
- ModDB / Nexus Mods

**Always provide:**
- SHA-256 checksum
- Virus scan report (VirusTotal link)
- Installation instructions
- SmartScreen warning info

### Method 3: Mod Sites

Upload to popular modding sites:
- **ModDB** - https://moddb.com (free, gaming-focused)
- **Nexus Mods** - https://nexusmods.com (popular, $5/month for authors)
- **GameBanana** - https://gamebanana.com (free)
- **CurseForge** - https://curseforge.com (free)

These sites have established reputations and may reduce trust concerns.

## Building Releases

### Option 1: Inno Setup Installer (.exe)

**Requirements:**
- Inno Setup 6.x from https://jrsoftware.org/isdl.php
- Visual Studio 2022 (for C++ build)
- .NET 8.0 SDK

**Steps:**
```bash
# 1. Build C++ mod loader
cd ModLoaderCore
compile.bat

# 2. Build .NET launcher
cd GUILauncher
dotnet publish -c Release

# 3. Compile installer
cd Installer
iscc setup.iss

# Output: Releases/SBGModLoader-Setup-v1.0.0.exe
```

**Pros:**
- Professional appearance
- Guided installation
- Start menu shortcuts
- Uninstaller included
- Auto-detects game path

**Cons:**
- Larger file size (~15-20 MB)
- Triggers SmartScreen more than ZIP

### Option 2: Portable ZIP Release

**Build:**
```powershell
cd Installer
.\build-release.ps1 -Version "1.0.0"
```

**Pros:**
- ✅ No installation needed
- ✅ Portable (USB stick friendly)
- ✅ Easier to trust (just extract and run)
- ✅ Smaller SmartScreen concern
- ✅ No admin rights needed

**Cons:**
- No shortcuts created
- Users must manage updates manually

### Option 3: Both! (Recommended)

Provide both installer and portable ZIP:
- **Installer** for casual users who want easy setup
- **ZIP** for advanced users and those concerned about SmartScreen

## Checksums & Verification

Always provide SHA-256 checksums:

```powershell
# Generate checksums
Get-FileHash .\Releases\*.exe -Algorithm SHA256 | Format-List
Get-FileHash .\Releases\*.zip -Algorithm SHA256 | Format-List
```

**Include in release notes:**
```
SHA-256 Checksums:
- SBGModLoader-Setup-v1.0.0.exe: [hash]
- SBGModLoader-v1.0.0-Portable.zip: [hash]

To verify: Right-click file → Properties → Digital Signatures (none) or use:
certutil -hashfile filename.exe SHA256
```

## VirusTotal Scan

Before every release:

1. Upload to https://www.virustotal.com
2. Wait for scan (all 70+ engines)
3. Include link in release notes

**Expected results:**
- Most engines: 0/70 detections (clean)
- 1-3 engines: May flag as "unknown" (not malware, just unsigned)

**If 5+ engines flag it:** Investigate! Could be false positive or actual issue.

## Communication with Users

### In README.md

```markdown
## Download & Installation

### ⚠️ Windows SmartScreen Warning
When first running the launcher, Windows may show a warning because the 
software isn't code-signed (signing costs $400/year). This is normal for 
community projects!

**To run anyway:**
1. Click "More info"
2. Click "Run anyway"

**Why it's safe:**
- Open source code (auditable)
- No admin rights required
- No network spying
- Active community
```

### In Release Notes

```markdown
## Security Notice

This software is NOT code-signed due to cost ($400/year). This means:
- ✅ Windows SmartScreen may warn you on first run
- ✅ This is NORMAL and EXPECTED
- ✅ The software is safe (open-source, community-reviewed)

**Verification:**
- SHA-256: [checksum]
- VirusTotal: [link] (0/70 detections)
- Source code: [GitHub link]
```

### On Website/Discord

Create a pinned message/FAQ:

**"Why does Windows say it's unsafe?"**

Our mod loader isn't code-signed because certificates cost $400/year - more 
than we can afford for a free community project. Click "More info" → 
"Run anyway" and you're good to go! The software is open-source and safe.

## Building Reputation

Over time, SmartScreen warnings will decrease as:

1. **More users download** - SmartScreen tracks download counts
2. **No malware reports** - Clean record builds reputation
3. **Stable releases** - Consistent updates help
4. **Community trust** - GitHub stars, positive reviews

## Long-Term Options

### Free Code Signing (Limited)

Some options for free certificates:
- **Authenticode (EV certificate)** - Still costs money
- **Let's Encrypt** - Only for websites, not code
- **Self-signed** - Worse than unsigned (more warnings)

❌ **None are practical for desktop software**

### Paid Code Signing ($200-400/year)

If the project grows, consider:
- **DigiCert** - $200-400/year
- **Sectigo** - $200-300/year
- **GlobalSign** - $250-350/year

**Break-even point:** If project generates $400+/year in donations, worth considering.

## Best Practices Checklist

For each release:

- [ ] Build both installer and portable ZIP
- [ ] Generate SHA-256 checksums
- [ ] Scan on VirusTotal
- [ ] Test installation on clean Windows VM
- [ ] Document SmartScreen warning in README
- [ ] Include verification instructions
- [ ] Create GitHub release with detailed notes
- [ ] Post in Discord/forums with links
- [ ] Monitor for false positive reports

## Community Trust Building

**Do:**
- ✅ Be transparent about unsigned software
- ✅ Provide source code links
- ✅ Respond to security questions quickly
- ✅ Include checksums and VirusTotal scans
- ✅ Build on trusted platforms (GitHub)
- ✅ Welcome code audits

**Don't:**
- ❌ Hide the SmartScreen warning
- ❌ Tell users to "disable antivirus"
- ❌ Get defensive about questions
- ❌ Use suspicious hosting (file lockers)
- ❌ Obfuscate code

## Example Release Checklist

```markdown
## Release v1.0.0 Checklist

**Build:**
- [ ] Update version in setup.iss
- [ ] Build C++ mod loader (Release mode)
- [ ] Build .NET launcher (Release mode)
- [ ] Compile Inno Setup installer
- [ ] Build portable ZIP

**Verification:**
- [ ] Test installer on clean VM
- [ ] Test portable ZIP on clean VM
- [ ] Generate SHA-256 checksums
- [ ] Upload to VirusTotal
- [ ] Verify all links work

**Documentation:**
- [ ] Update README.md with new version
- [ ] Update CHANGELOG.md
- [ ] Prepare release notes
- [ ] Document SmartScreen warning

**Distribution:**
- [ ] Create GitHub release
- [ ] Upload installer + ZIP
- [ ] Add checksums to release notes
- [ ] Add VirusTotal link
- [ ] Post in Discord
- [ ] Post on Reddit/forums
- [ ] Update website
```

## Support Resources

When users have concerns:

**Point them to:**
1. **Source code** - "Here's every line of code: [GitHub link]"
2. **VirusTotal** - "Here's a scan by 70+ antivirus engines: [link]"
3. **Community** - "Join Discord - 1000+ users safely using it"
4. **Alternatives** - "Prefer portable? Download the ZIP instead"

## Summary

**TL;DR:**
- Code signing is expensive ($400/year) 
- SmartScreen warnings are expected and normal
- Users can easily bypass with "Run anyway"
- Open-source nature provides trust
- Both installer and ZIP options maximize accessibility
- Transparency and checksums build community trust

**You're in good company!** Many popular game mods and community tools are unsigned:
- BepInEx (Unity modding framework)
- MelonLoader (Unity/Il2Cpp mod loader)
- Mod Organizer 2 (modding tool)
- Many Nexus Mods tools

Unsigned ≠ Unsafe. Open source + community = trustworthy. 🎯

---

**Questions?** Open an issue on GitHub or ask in Discord!
