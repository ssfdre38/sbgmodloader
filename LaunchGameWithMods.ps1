# Super Battle Golf - Custom Map Launcher
# This script launches the game and injects ModLoaderCore.dll

$gameExe = "C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf\Super Battle Golf.exe"
$modDll = "C:\Program Files (x86)\Steam\steamapps\common\Super Battle Golf\ModLoaderCore.dll"
$logPath = "$env:APPDATA\sbg-mod-loader\mod-loader.log"

Write-Host "═══════════════════════════════════════════════════════"
Write-Host "SBG Mod Loader - Custom Map Test Launcher"
Write-Host "═══════════════════════════════════════════════════════"
Write-Host ""
Write-Host "Game: $gameExe"
Write-Host "Mod DLL: $modDll"
Write-Host ""

# Verify files exist
if (-not (Test-Path $gameExe)) {
    Write-Host "❌ Game executable not found!"
    exit 1
}

if (-not (Test-Path $modDll)) {
    Write-Host "❌ ModLoaderCore.dll not found!"
    exit 1
}

Write-Host "✅ Game executable found"
Write-Host "✅ ModLoaderCore.dll found"
Write-Host ""

# Clear old log
if (Test-Path $logPath) {
    Remove-Item $logPath -Force
    Write-Host "✅ Cleared old log file"
}

Write-Host ""
Write-Host "═══════════════════════════════════════════════════════"
Write-Host "🎮 Starting game process..."
Write-Host "═══════════════════════════════════════════════════════"
Write-Host ""
Write-Host "What will happen:"
Write-Host "  1. Game starts (suspended)"
Write-Host "  2. ModLoaderCore.dll gets injected"
Write-Host "  3. Game resumes and mod loader initializes"
Write-Host "  4. Mono runtime detected"
Write-Host "  5. Custom catalog loads from D:\SuperBattleGolfModLoader\TestMapOutput"
Write-Host "  6. Custom scene 'CustomTestMap' loads"
Write-Host "  7. RED CUBE appears if successful!"
Write-Host ""
Write-Host "Check log at: $logPath"
Write-Host ""
Write-Host "Press Enter to launch..."
Read-Host

# Add .NET types for process creation
Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;

public class ProcessInjector {
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr OpenProcess(uint dwDesiredAccess, bool bInheritHandle, int dwProcessId);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesWritten);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr GetModuleHandle(string lpModuleName);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, out IntPtr lpThreadId);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);
    
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool CloseHandle(IntPtr hObject);
    
    public const uint PROCESS_CREATE_THREAD = 0x0002;
    public const uint PROCESS_QUERY_INFORMATION = 0x0400;
    public const uint PROCESS_VM_OPERATION = 0x0008;
    public const uint PROCESS_VM_WRITE = 0x0020;
    public const uint PROCESS_VM_READ = 0x0010;
    public const uint MEM_COMMIT = 0x1000;
    public const uint PAGE_READWRITE = 0x04;
}
"@

# Start game process suspended
$psi = New-Object System.Diagnostics.ProcessStartInfo
$psi.FileName = $gameExe
$psi.UseShellExecute = $false
$psi.WorkingDirectory = Split-Path $gameExe

$process = [System.Diagnostics.Process]::Start($psi)

if (-not $process) {
    Write-Host "❌ Failed to start game process"
    exit 1
}

Write-Host "✅ Game process started (PID: $($process.Id))"
Write-Host ""

# Wait a moment for process to initialize
Start-Sleep -Milliseconds 500

Write-Host "[*] Injecting DLL: $modDll"

try {
    # Open process
    $hProcess = [ProcessInjector]::OpenProcess(
        [ProcessInjector]::PROCESS_CREATE_THREAD -bor 
        [ProcessInjector]::PROCESS_QUERY_INFORMATION -bor
        [ProcessInjector]::PROCESS_VM_OPERATION -bor
        [ProcessInjector]::PROCESS_VM_WRITE -bor
        [ProcessInjector]::PROCESS_VM_READ,
        $false,
        $process.Id
    )
    
    if ($hProcess -eq [IntPtr]::Zero) {
        throw "Failed to open process"
    }
    
    Write-Host "[+] Process handle obtained"
    
    # Allocate memory in target process
    $dllPathBytes = [System.Text.Encoding]::Unicode.GetBytes($modDll + "`0")
    $allocSize = $dllPathBytes.Length
    
    $pRemotePath = [ProcessInjector]::VirtualAllocEx(
        $hProcess,
        [IntPtr]::Zero,
        $allocSize,
        [ProcessInjector]::MEM_COMMIT,
        [ProcessInjector]::PAGE_READWRITE
    )
    
    if ($pRemotePath -eq [IntPtr]::Zero) {
        throw "Failed to allocate memory in target process"
    }
    
    Write-Host "[+] Allocated $allocSize bytes in target process"
    
    # Write DLL path
    $bytesWritten = 0
    $writeResult = [ProcessInjector]::WriteProcessMemory(
        $hProcess,
        $pRemotePath,
        $dllPathBytes,
        $dllPathBytes.Length,
        [ref]$bytesWritten
    )
    
    if (-not $writeResult) {
        throw "Failed to write DLL path to target process"
    }
    
    Write-Host "[+] Wrote DLL path to target process"
    
    # Get LoadLibraryW address
    $hKernel32 = [ProcessInjector]::GetModuleHandle("kernel32.dll")
    $pLoadLibrary = [ProcessInjector]::GetProcAddress($hKernel32, "LoadLibraryW")
    
    Write-Host "[+] Found LoadLibraryW at: $($pLoadLibrary.ToString('X16'))"
    
    # Create remote thread
    $threadId = [IntPtr]::Zero
    $hThread = [ProcessInjector]::CreateRemoteThread(
        $hProcess,
        [IntPtr]::Zero,
        0,
        $pLoadLibrary,
        $pRemotePath,
        0,
        [ref]$threadId
    )
    
    if ($hThread -eq [IntPtr]::Zero) {
        throw "Failed to create remote thread"
    }
    
    Write-Host "[+] Remote thread created (TID: $threadId)"
    Write-Host "[*] Waiting for DLL to load..."
    
    # Wait for thread to complete
    [ProcessInjector]::WaitForSingleObject($hThread, 5000) | Out-Null
    
    [ProcessInjector]::CloseHandle($hThread) | Out-Null
    [ProcessInjector]::CloseHandle($hProcess) | Out-Null
    
    Write-Host ""
    Write-Host "✅ Mod loader injected successfully!"
    Write-Host "[*] Game is now running with mod loader"
    Write-Host ""
    Write-Host "═══════════════════════════════════════════════════════"
    Write-Host "Waiting 5 seconds for mod loader to initialize..."
    Write-Host "═══════════════════════════════════════════════════════"
    
    Start-Sleep -Seconds 5
    
    # Check log
    if (Test-Path $logPath) {
        Write-Host ""
        Write-Host "✅ Log file created! Mod loader is working!"
        Write-Host ""
        
        $log = Get-Content $logPath -Raw
        
        if ($log -match "CUSTOM SCENE LOAD INITIATED") {
            Write-Host ""
            Write-Host "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉"
            Write-Host "✅✅✅ CUSTOM MAP LOADING CONFIRMED! ✅✅✅"
            Write-Host "🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉"
            Write-Host ""
            Write-Host "Look for a RED CUBE in the game!"
            Write-Host ""
        }
        
        Write-Host "Recent log entries:"
        Write-Host "-------------------"
        $log -split "`n" | Select-Object -Last 30 | ForEach-Object { Write-Host $_ }
    } else {
        Write-Host ""
        Write-Host "⚠️ No log file yet. Mod loader may still be initializing..."
    }
    
    Write-Host ""
    Write-Host "Waiting for game to exit..."
    $process.WaitForExit()
    
} catch {
    Write-Host ""
    Write-Host "❌ Injection failed: $_"
    if ($process -and -not $process.HasExited) {
        $process.Kill()
    }
    exit 1
}
