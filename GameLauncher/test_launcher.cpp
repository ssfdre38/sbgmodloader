#include <Windows.h>
#include <stdio.h>
#include <filesystem>

namespace fs = std::filesystem;

bool InjectDll(HANDLE hProcess, const char* dllPath) {
    printf("[TEST] Attempting to inject: %s\n", dllPath);
    
    // Check if DLL exists
    if (!fs::exists(dllPath)) {
        printf("[TEST] DLL not found!\n");
        return false;
    }
    
    printf("[TEST] DLL exists\n");
    
    // Allocate and write path
    size_t pathLen = strlen(dllPath) + 1;
    LPVOID remotePath = VirtualAllocEx(hProcess, NULL, pathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(hProcess, remotePath, (void*)dllPath, pathLen, NULL);
    
    // Call LoadLibraryA
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(kernel32, "LoadLibraryA");
    
    HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remotePath, 0, NULL);
    WaitForSingleObject(remoteThread, INFINITE);
    
    DWORD exitCode = 0;
    GetExitCodeThread(remoteThread, &exitCode);
    
    printf("[TEST] LoadLibraryA returned: %p\n", (LPVOID)exitCode);
    
    CloseHandle(remoteThread);
    VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
    
    return exitCode != 0;
}

int main() {
    const char* gamePath = "C:\\\\Program Files (x86)\\\\Steam\\\\steamapps\\\\common\\\\Super Battle Golf\\\\Super Battle Golf.exe";
    const char* testDllPath = "C:\\\\Windows\\\\System32\\\\test_dll.dll";
    
    printf("Starting game with test DLL injection...\n");
    
    STARTUPINFOA si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};
    
    if (!CreateProcessA(gamePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        printf("Failed to start game\n");
        return 1;
    }
    
    printf("Game started (PID %lu), injecting test DLL...\n", pi.dwProcessId);
    
    if (!InjectDll(pi.hProcess, testDllPath)) {
        printf("Injection failed!\n");
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return 1;
    }
    
    printf("Injection complete, resuming game...\n");
    ResumeThread(pi.hThread);
    
    printf("Waiting for game to exit...\n");
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return 0;
}
