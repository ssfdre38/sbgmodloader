#pragma once
#include <string>

// Forward declarations for Mono types
typedef void* MonoClass;
typedef void* MonoMethod;
typedef void* MonoObject;

namespace ModLoader {

/**
 * UIOverlay - Simple UI Test
 * 
 * Tests if we can inject text into the game UI
 */
class UIOverlay {
public:
    /**
     * Test: Try to add version text to main menu
     */
    static void TestAddVersionText();

private:
    static bool s_InjectedVersion;
};

} // namespace ModLoader
