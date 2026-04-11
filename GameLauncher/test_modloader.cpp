#include <Windows.h>
#include <stdio.h>

bool InjectDll(HANDLE hProcess, const char* dllPath) {
    size_t pathLen = strlen(dllPath) + 1;
    LPVOID remotePath = VirtualAllocEx(hProcess, NULL, pathLen, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    WriteProcessMemory(hProcess, remotePath, (void*)dllPath, pathLen, NULL);
    
    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    LPVOID loadLibraryAddr = (LPVOID)GetProcAddress(kernel32, "LoadLibraryA");
    
    HANDLE remoteThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remotePath, 0, NULL);
    WaitForSingleObject(remoteThread, INFINITE);
    
    DWORD exitCode = 0;
    GetExitCodeThread(remoteThread, &exitCode);
    printf("[INJECT] LoadLibraryA returned: %p\n", (LPVOID)exitCode);
    
    CloseHandle(remoteThread);
    VirtualFreeEx(hProcess, remotePath, 0, MEM_RELEASE);
    return exitCode != 0;
}

int main() {
    const char* gamePath = "C:\\\\Program Files (x86)\\\\Steam\\\\steamapps\\\\common\\\\Super Battle Golf\\\\Super Battle Golf.exe";
    const char* dllPath = "C:\\\\Windows\\\\System32\\\\ModLoaderCore_test.dll";
    
    printf("Testing ModLoaderCore_test.dll injection...\n");
    
    STARTUPINFOA si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};
    
    if (!CreateProcessA(gamePath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        printf("Failed to start game\n");
        return 1;
    }
    
    printf("Game started, injecting...\n");
    InjectDll(pi.hProcess, dllPath);
    
    printf("Resuming...\n");
    ResumeThread(pi.hThread);
    
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    
    return 0;
}
