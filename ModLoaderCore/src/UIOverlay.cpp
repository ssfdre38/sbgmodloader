#include "UIOverlay.h"
#include "MonoHelper.h"
#include "Log.h"
#include <Windows.h>

namespace ModLoader {

using namespace ModLoader::Mono;

bool UIOverlay::s_InjectedVersion = false;

void UIOverlay::TestAddVersionText() {
    if (s_InjectedVersion) {
        return; // Already injected or attempted
    }
    
    Log::Info("[UIOverlay] 🎯 Testing UI injection capability...");
    
    // Find Unity core assemblies
    MonoAssembly* unityEngine = MonoHelper::FindAssembly("UnityEngine.CoreModule");
    if (!unityEngine) {
        Log::Warn("[UIOverlay] UnityEngine.CoreModule not found - Unity not ready yet");
        return;
    }
    
    MonoImage* engineImage = MonoHelper::mono_assembly_get_image(unityEngine);
    
    // Find GameObject class
    MonoClass* gameObjectClass = MonoHelper::GetClassFromName(engineImage, "UnityEngine", "GameObject");
    if (!gameObjectClass) {
        Log::Error("[UIOverlay] GameObject class not found");
        s_InjectedVersion = true; // Don't retry
        return;
    }
    
    Log::Info("[UIOverlay] ✓ Found GameObject class");
    
    // Find Transform class
    MonoClass* transformClass = MonoHelper::GetClassFromName(engineImage, "UnityEngine", "Transform");
    if (!transformClass) {
        Log::Error("[UIOverlay] Transform class not found");
        s_InjectedVersion = true;
        return;
    }
    
    Log::Info("[UIOverlay] ✓ Found Transform class");
    
    // Find TextMeshPro assembly
    MonoAssembly* tmpAssembly = MonoHelper::FindAssembly("Unity.TextMeshPro");
    if (!tmpAssembly) {
        Log::Warn("[UIOverlay] Unity.TextMeshPro assembly not found - TMP not loaded yet");
        return;
    }
    
    MonoImage* tmpImage = MonoHelper::mono_assembly_get_image(tmpAssembly);
    
    // Find TextMeshProUGUI class
    MonoClass* tmpTextClass = MonoHelper::GetClassFromName(tmpImage, "TMPro", "TextMeshProUGUI");
    if (!tmpTextClass) {
        tmpTextClass = MonoHelper::GetClassFromName(tmpImage, "TMPro", "TMP_Text");
    }
    
    if (!tmpTextClass) {
        Log::Error("[UIOverlay] TextMeshPro text class not found");
        s_InjectedVersion = true;
        return;
    }
    
    Log::Info("[UIOverlay] ✓ Found TextMeshProUGUI class");
    
    // Find Component class (base for GetComponent<T>)
    MonoClass* componentClass = MonoHelper::GetClassFromName(engineImage, "UnityEngine", "Component");
    if (!componentClass) {
        Log::Error("[UIOverlay] Component class not found");
        s_InjectedVersion = true;
        return;
    }
    
    Log::Info("[UIOverlay] ✓ Found Component class");
    
    // Success! We have all the classes we need
    Log::Info("[UIOverlay] ═══════════════════════════════════════");
    Log::Info("[UIOverlay] ✅ UI INJECTION IS POSSIBLE!");
    Log::Info("[UIOverlay] ═══════════════════════════════════════");
    Log::Info("[UIOverlay]");
    Log::Info("[UIOverlay] Found all required Unity UI classes:");
    Log::Info("[UIOverlay]   • UnityEngine.GameObject");
    Log::Info("[UIOverlay]   • UnityEngine.Transform");
    Log::Info("[UIOverlay]   • UnityEngine.Component");
    Log::Info("[UIOverlay]   • TMPro.TextMeshProUGUI");
    Log::Info("[UIOverlay]");
    Log::Info("[UIOverlay] Next steps:");
    Log::Info("[UIOverlay]   1. Find existing version text GameObject");
    Log::Info("[UIOverlay]   2. Clone it or create new GameObject");
    Log::Info("[UIOverlay]   3. Add TextMeshProUGUI component");
    Log::Info("[UIOverlay]   4. Set text to 'Mod Loader v0.1.0-beta'");
    Log::Info("[UIOverlay]   5. Position below game version");
    Log::Info("[UIOverlay]");
    Log::Info("[UIOverlay] ═══════════════════════════════════════");
    
    s_InjectedVersion = true; // Don't spam logs
}

} // namespace ModLoader
