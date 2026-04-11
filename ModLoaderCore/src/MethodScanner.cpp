#include <windows.h>
#include <psapi.h>
#include <vector>
#include <string>
#include "../include/Log.h"

namespace ModLoader {

struct MethodScanResult {
    const char* name;
    void* address;
    bool found;
};

// Scan for method by looking for common IL2CPP method prologues
std::vector<void*> ScanForMethodPrologue(HMODULE module) {
    std::vector<void*> results;
    
    MODULEINFO modInfo = {};
    GetModuleInformation(GetCurrentProcess(), module, &modInfo, sizeof(modInfo));
    
    BYTE* baseAddr = (BYTE*)module;
    SIZE_T size = modInfo.SizeOfImage;
    
    Log::Info("Scanning GameAssembly.dll for method prologues...");
    Log::Info("  Base: 0x%p", baseAddr);
    Log::Info("  Size: %llu bytes (%.2f MB)", size, size / (1024.0 * 1024.0));
    
    // Common IL2CPP method prologue patterns (x64)
    // Pattern 1: push rbp; mov rbp, rsp
    BYTE pattern1[] = { 0x48, 0x89, 0x5C, 0x24 }; // mov [rsp+??], rbx
    
    // Pattern 2: sub rsp, ??
    BYTE pattern2[] = { 0x48, 0x83, 0xEC }; // sub rsp, ??
    
    int foundCount = 0;
    for (SIZE_T i = 0; i < size - 16; i++) {
        // Check if memory is readable
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(baseAddr + i, &mbi, sizeof(mbi)) && 
            (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE))) {
            
            // Look for pattern
            bool match = false;
            if (memcmp(baseAddr + i, pattern1, sizeof(pattern1)) == 0 ||
                memcmp(baseAddr + i, pattern2, sizeof(pattern2)) == 0) {
                match = true;
            }
            
            if (match) {
                results.push_back(baseAddr + i);
                foundCount++;
                
                // Log first 10 findings
                if (foundCount <= 10) {
                    Log::Info("  Found method prologue #%d at RVA: 0x%08llX (absolute: 0x%p)", 
                              foundCount, i, baseAddr + i);
                }
            }
        }
    }
    
    Log::Info("Total method prologues found: %d", foundCount);
    return results;
}

// Scan for specific string references (like "MainMenu" scene name)
void* ScanForStringReference(HMODULE module, const char* searchString) {
    MODULEINFO modInfo = {};
    GetModuleInformation(GetCurrentProcess(), module, &modInfo, sizeof(modInfo));
    
    BYTE* baseAddr = (BYTE*)module;
    SIZE_T size = modInfo.SizeOfImage;
    
    Log::Info("Scanning for string: '%s'", searchString);
    
    size_t searchLen = strlen(searchString);
    for (SIZE_T i = 0; i < size - searchLen; i++) {
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(baseAddr + i, &mbi, sizeof(mbi)) && 
            (mbi.State == MEM_COMMIT) && 
            (mbi.Protect & (PAGE_READONLY | PAGE_READWRITE))) {
            
            if (memcmp(baseAddr + i, searchString, searchLen) == 0) {
                Log::Info("  ✓ Found '%s' at RVA: 0x%08llX (absolute: 0x%p)", 
                          searchString, i, baseAddr + i);
                return baseAddr + i;
            }
        }
    }
    
    Log::Info("  ✗ String '%s' not found", searchString);
    return nullptr;
}

// Dump memory around an address to see what's there
void DumpMemoryRegion(void* addr, size_t beforeBytes, size_t afterBytes) {
    BYTE* ptr = (BYTE*)addr - beforeBytes;
    size_t totalBytes = beforeBytes + afterBytes;
    
    Log::Info("Memory dump around 0x%p:", addr);
    
    for (size_t i = 0; i < totalBytes; i += 16) {
        char hexStr[80] = {};
        char asciiStr[20] = {};
        
        sprintf_s(hexStr, "  %p: ", ptr + i);
        
        for (int j = 0; j < 16 && i + j < totalBytes; j++) {
            BYTE b = ptr[i + j];
            sprintf_s(hexStr + strlen(hexStr), sizeof(hexStr) - strlen(hexStr), "%02X ", b);
            asciiStr[j] = (b >= 32 && b < 127) ? (char)b : '.';
        }
        
        Log::Info("%s  %s", hexStr, asciiStr);
    }
}

// Try to verify if an address points to actual executable code
bool IsExecutableCode(void* addr) {
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(addr, &mbi, sizeof(mbi))) {
        return (mbi.State == MEM_COMMIT) && 
               (mbi.Protect & (PAGE_EXECUTE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE));
    }
    return false;
}

} // namespace ModLoader
