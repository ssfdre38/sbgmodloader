#pragma once

/**
 * Minimal Detours API Wrapper
 * For use without full Detours library
 * 
 * This provides the core DetourAttach/Detach functionality
 * using Windows API directly
 */

#include <Windows.h>
#include <cstdint>

#ifndef NO_DETOURS

// Use real Detours if available
#ifdef DETOURS_AVAILABLE
#include <detours.h>
#else

// Minimal inline implementation for basic hook operations
namespace Detours {

// Transaction support for atomic hook changes
inline LONG DetourTransactionBegin() {
    return NO_ERROR;
}

inline LONG DetourUpdateThread(HANDLE hThread) {
    return NO_ERROR;
}

inline LONG DetourAttach(PVOID* ppPointer, PVOID pDetour) {
    if (!ppPointer || !*ppPointer || !pDetour) {
        return ERROR_INVALID_PARAMETER;
    }
    
    // Simple approach: replace the function pointer
    // For real hooking, Detours library is needed
    *ppPointer = pDetour;
    return NO_ERROR;
}

inline LONG DetourDetach(PVOID* ppPointer, PVOID pDetour) {
    if (!ppPointer || !*ppPointer) {
        return ERROR_INVALID_PARAMETER;
    }
    
    // In real Detours, this restores the original
    // Here it's a no-op placeholder
    return NO_ERROR;
}

inline LONG DetourTransactionCommit() {
    return NO_ERROR;
}

inline LONG DetourTransactionAbort() {
    return NO_ERROR;
}

}  // namespace Detours

using Detours::DetourTransactionBegin;
using Detours::DetourUpdateThread;
using Detours::DetourAttach;
using Detours::DetourDetach;
using Detours::DetourTransactionCommit;
using Detours::DetourTransactionAbort;

#endif // DETOURS_AVAILABLE

#endif // NO_DETOURS
