#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        // Simplest possible DllMain - just create marker file
        HANDLE hFile = CreateFileA(
            "C:\\test_dll_loaded.txt",
            GENERIC_WRITE,
            0,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );
        
        if (hFile != INVALID_HANDLE_VALUE) {
            const char msg[] = "Test DLL loaded!\r\n";
            DWORD written;
            WriteFile(hFile, msg, sizeof(msg) - 1, &written, NULL);
            CloseHandle(hFile);
        }
    }
    return TRUE;
}

