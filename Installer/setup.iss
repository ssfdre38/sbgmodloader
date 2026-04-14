; Super Battle Golf Mod Loader Installer
; Inno Setup Script
; Download Inno Setup from: https://jrsoftware.org/isdl.php

#define MyAppName "Super Battle Golf Mod Loader"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "SBG Modding Community"
#define MyAppURL "https://github.com/ssfdre38/sbgmodloader"
#define MyAppExeName "SBGModLauncher.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
AppId={{A7B8C9D0-1234-5678-90AB-CDEF12345678}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=..\LICENSE
OutputDir=..\Releases
OutputBaseFilename=SBGModLoader-Setup-v{#MyAppVersion}
Compression=lzma2/max
SolidCompression=yes
WizardStyle=modern
PrivilegesRequired=lowest
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; Mod Loader Core (C++ DLL)
Source: "..\ModLoaderCore\Release\ModLoaderCore.dll"; DestDir: "{app}"; Flags: ignoreversion

; GUI Launcher (.NET WPF)
Source: "..\GUILauncher\bin\Release\net8.0-windows\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

; PowerShell Launch Script
Source: "..\LaunchGameWithMods.ps1"; DestDir: "{app}"; Flags: ignoreversion

; Documentation
Source: "..\README.md"; DestDir: "{app}"; Flags: ignoreversion isreadme
Source: "..\BRANCHES.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\docs\*"; DestDir: "{app}\docs"; Flags: ignoreversion recursesubdirs createallsubdirs

[Dirs]
; Create Mods folder structure
Name: "{app}\Mods\Maps"
Name: "{app}\Mods\GameModes"
Name: "{app}\Mods\Characters"
Name: "{app}\Mods\Items"
Name: "{app}\Mods\Audio"
Name: "{app}\Mods\UI"
Name: "{app}\Mods\Scripts"
Name: "{app}\Mods\Core"

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
var
  GamePathPage: TInputDirWizardPage;

procedure InitializeWizard;
begin
  // Create custom page for game path selection
  GamePathPage := CreateInputDirPage(wpSelectDir,
    'Select Super Battle Golf Installation', 
    'Where is Super Battle Golf installed?',
    'Select the folder where Super Battle Golf is installed (the folder containing Super Battle Golf.exe), then click Next.' + #13#10#13#10 +
    'If you''re not sure, the launcher will auto-detect it when you first run it.',
    False, '');
  
  GamePathPage.Add('');
  
  // Try to auto-detect game path
  if DirExists('C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf') then
    GamePathPage.Values[0] := 'C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf'
  else if DirExists('C:\Program Files\Steam\steamapps\common\Super Battle Golf') then
    GamePathPage.Values[0] := 'C:\Program Files\Steam\steamapps\common\Super Battle Golf'
  else if DirExists('D:\SteamLibrary\steamapps\common\Super Battle Golf') then
    GamePathPage.Values[0] := 'D:\SteamLibrary\steamapps\common\Super Battle Golf'
  else if DirExists('C:\Program Files\Super Battle Golf') then
    GamePathPage.Values[0] := 'C:\Program Files\Super Battle Golf'
  else if DirExists('D:\Games\Super Battle Golf') then
    GamePathPage.Values[0] := 'D:\Games\Super Battle Golf';
end;

function NextButtonClick(CurPageID: Integer): Boolean;
begin
  Result := True;
  
  if CurPageID = GamePathPage.ID then
  begin
    // Allow skipping if game not found (launcher will auto-detect later)
    if GamePathPage.Values[0] = '' then
      Result := True
    else if not FileExists(GamePathPage.Values[0] + '\Super Battle Golf.exe') then
    begin
      if MsgBox('Super Battle Golf.exe not found in the selected folder. Continue anyway? (The launcher will auto-detect it later)', mbConfirmation, MB_YESNO) = IDYES then
        Result := True
      else
        Result := False;
    end;
  end;
end;

procedure CurStepChanged(CurStep: TSetupStep);
var
  ConfigPath: String;
  ConfigContent: String;
begin
  if CurStep = ssPostInstall then
  begin
    // Create launcher config with game path if specified
    if GamePathPage.Values[0] <> '' then
    begin
      ConfigPath := ExpandConstant('{userappdata}\sbg-mod-loader\launcher-config.json');
      ForceDirectories(ExtractFilePath(ConfigPath));
      
      ConfigContent := '{' + #13#10 +
        '  "GamePath": "' + StringChange(GamePathPage.Values[0], '\', '\\') + '",' + #13#10 +
        '  "AutoRefresh": true,' + #13#10 +
        '  "CheckUpdates": true' + #13#10 +
        '}';
      
      SaveStringToFile(ConfigPath, ConfigContent, False);
    end;
  end;
end;

[UninstallDelete]
Type: filesandordirs; Name: "{userappdata}\sbg-mod-loader"
