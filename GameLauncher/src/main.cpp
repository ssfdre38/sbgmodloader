#include <Windows.h>
#include <stdio.h>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/// Inject a DLL into a running process using CreateRemoteThread
bool InjectDll(HANDLE hProcess, const char* dllPath) {
    printf("[*] Injecting DLL: %s\n", dllPath);
    
    // First, try to load the DLL in our own process to verify it's valid
    HMODULE testLoad = LoadLibraryA(dllPath);
    if (testLoad) {
        printf("[+] DLL is valid and loadable (tested in launcher process)\n");
        FreeLibrary(testLoad);
    } else {
        printf("[-] DLL cannot be loaded even in launcher (error: %lu)\n", GetLastError());
        printf("[-] Trying anyway, but this is suspicious...\n");
    }
    
    // Allocate memory in target process for DLL path
    size_t pathLen = strlen(dllPath) + 1;
    LPVOID remotePath = VirtualAllocEx(hProcess, NULL, pathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    if (!remotePath) {
        printf("[-] Failed to allocate memory in target process (error: %lu)\n", GetLastError());
        return false;
    }
    
    printf("[+] Allocated %zu bytes in target process\n", pathLen);
    
    // Write DLL path to remote process memory
    if (!WriteProcessMemory(hProcess, remotePath, (void*)dllPath, pathLen, NULL)) {
        printf("[-] Failed to write DLL path to target process (error: %lu)\n", GetLastError());
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        return false;
    }
    
    printf("[+] Wrote DLL path to target process\n");
    
    // Get address of LoadLibraryA from kernel32.dll
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(kernel32, "LoadLibraryA");
    
    if (!loadLibraryAddr) {
        printf("[-] Failed to get LoadLibraryA address (error: %lu)\n", GetLastError());
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        return false;
    }
    
    printf("[+] Found LoadLibraryA at: %p\n", loadLibraryAddr);
    
    // Create remote thread to call LoadLibrary
    HANDLE remoteThread = CreateRemoteThread(
        hProcess,
        NULL,
        0,
        (LPTHREAD_START_ROUTINE)loadLibraryAddr,
        remotePath,
        0,
        NULL
    );
    
    if (!remoteThread) {
        printf("[-] Failed to create remote thread (error: %lu)\n", GetLastError());
        VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
        return false;
    }
    
    printf("[+] Remote thread created (TID: %lu)\n", GetThreadId(remoteThread));
    
    // Wait for thread to complete
    printf("[*] Waiting for DLL to load...\n");
    WaitForSingleObject(remoteThread, INFINITE);
    
    // Get exit code (should be non-zero if DLL loaded successfully)
    DWORD exitCode = 0;
    GetExitCodeThread(remoteThread, &exitCode);
    
    CloseHandle(remoteThread);
    VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
    
    printf("[!] LoadLibraryA returned: %p\n", (LPVOID)exitCode);
    
    if (!exitCode) {
        printf("[-] LoadLibraryA returned NULL - injection likely failed\n");
        printf("[-] Check if DLL exists or has dependency issues\n");
        return false;
    }
    
    printf("[+] DLL injection returned success code\n");
    printf("[!] Note: This only means LoadLibraryA returned non-null\n");
    printf("[!] Actual loading should be verified by looking for C:\\sbg_dll_loaded.txt\n");
    return true;
}

/// Simple launcher that injects ModLoaderCore.dll into game process
int main(int argc, char* argv[]) {
    printf("SBG Mod Loader - Game Launcher\n");
    printf("================================\n\n");
    
    char gamePathBuffer[MAX_PATH];
    char dllPathBuffer[MAX_PATH];
    char currentDir[MAX_PATH];
    
    GetCurrentDirectoryA(MAX_PATH, currentDir);
    
    // Try to find DLL in multiple locations (priority order)
    const char* dllLocations[] = {
        "C:\\Windows\\System32\\ModLoaderCore.dll",  // System32 (preferred)
        "ModLoaderCore.dll",                         // Current directory
        ".\\x64\\Release\\ModLoaderCore.dll"         // Fallback to subfolder
    };
    
    const char* modLoaderPath = nullptr;
    for (int i = 0; i < 3; i++) {
        if (fs::exists(dllLocations[i])) {
            modLoaderPath = dllLocations[i];
            break;
        }
    }
    
    snprintf(gamePathBuffer, MAX_PATH, "%s\\Super Battle Golf.exe", currentDir);
    
    const char* gamePath = gamePathBuffer;
    
    printf("Game: %s\n", gamePath);
    printf("Mod Loader DLL: %s\n", modLoaderPath ? modLoaderPath : "(not found)");
    
    // Check if game exists
    if (!fs::exists(gamePath)) {
        printf("ERROR: Game executable not found at: %s\n", gamePath);
        return 1;
    }
    
    printf("✓ Game executable found\n");
    
    // Check if DLL exists
    if (!modLoaderPath) {
        printf("ERROR: ModLoaderCore.dll not found in expected locations\n");
        printf("  Checked:\n");
        for (int i = 0; i < 3; i++) {
            printf("    - %s\n", dllLocations[i]);
        }
        return 1;
    }
    
    printf("✓ ModLoaderCore.dll found\n\n");
    
    // Start game process
    STARTUPINFOA startupInfo = {0};
    startupInfo.cb = sizeof(startupInfo);
    PROCESS_INFORMATION processInfo = {0};
    
    if (!CreateProcessA(gamePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startupInfo, &processInfo)) {
        printf("ERROR: Failed to start game (error: %lu)\n", GetLastError());
        return 1;
    }
    
    printf("✓ Game process started (PID: %lu)\n", processInfo.dwProcessId);
    
    // Inject DLL before resuming game thread
    if (!InjectDll(processInfo.hProcess, modLoaderPath)) {
        printf("ERROR: Failed to inject mod loader DLL\n");
        TerminateProcess(processInfo.hProcess, 1);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        return 1;
    }
    
    printf("\n✓ Mod loader injected successfully!\n");
    printf("[*] Resuming game...\n\n");
    
    // Resume main thread
    ResumeThread(processInfo.hThread);
    
    // Wait for game to exit
    printf("Waiting for game to exit...\n");
    WaitForSingleObject(processInfo.hProcess, INFINITE);
    
    // Cleanup
    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);
    
    printf("✓ Game exited\n");
    return 0;
}
