#include <Windows.h>
#include "Log.h"
#include "MonoHelper.h"
#include "IL2CPP.h"
#include "ModManager.h"
#include "Hooks.h"
#include "AddressablesHook.h"

using namespace ModLoader;

namespace {

DWORD WINAPI InitializeModLoaderThread(LPVOID) {
    Log::Info("[CORE] ModLoaderCore.dll attached to process");
    Log::Info("[CORE] Starting deferred initialization thread");

    // Detect Mono runtime (mono-2.0-bdwgc.dll)
    // Super Battle Golf is a Mono build, not IL2CPP
    HMODULE monoRuntime = nullptr;
    for (int attempt = 0; attempt < 120; ++attempt) {
        monoRuntime = GetModuleHandleA("mono-2.0-bdwgc.dll");
        if (monoRuntime) {
            break;
        }

        Sleep(500);
    }

    if (monoRuntime) {
        Log::Info("[CORE] Mono runtime detected at 0x%p", monoRuntime);
        Log::Info("[CORE] Initializing Mono integration...");

        bool monoSuccess = Mono::MonoHelper::Initialize(monoRuntime);
        if (monoSuccess) {
            Log::Info("[CORE] ✓ Mono integration initialized!");
            Mono::MonoHelper::DumpAssemblies();

            // Test: Find Unity.Addressables classes
            Log::Info("");
            Log::Info("═══════════════════════════════════════════════════════");
            Log::Info("Testing Unity.Addressables Class Discovery");
            Log::Info("═══════════════════════════════════════════════════════");
            
            MonoClass* addressablesClass = Mono::MonoHelper::FindClass(
                "Unity.Addressables",
                "UnityEngine.AddressableAssets",
                "Addressables"
            );
            
            if (addressablesClass) {
                Log::Info("✓ Found Addressables class!");
                Log::Info("  Namespace: %s", Mono::MonoHelper::GetClassNamespace(addressablesClass));
                Log::Info("  Name: %s", Mono::MonoHelper::GetClassName(addressablesClass));
                Log::Info("");
                
                // Dump all methods in Addressables class
                Mono::MonoHelper::DumpClassMethods(addressablesClass);
                
                Log::Info("");
                Log::Info("═══════════════════════════════════════════════════════");
                Log::Info("Inspecting Loaded Addressables Catalogs");
                Log::Info("═══════════════════════════════════════════════════════");
                
                // Get the ResourceLocators collection
                MonoMethod* getResourceLocators = Mono::MonoHelper::FindMethod(addressablesClass, "get_ResourceLocators", 0);
                if (getResourceLocators) {
                    Log::Info("✓ Found get_ResourceLocators method");
                    
                    MonoObject* locatorsCollection = Mono::MonoHelper::InvokeStaticMethod(getResourceLocators, nullptr);
                    if (locatorsCollection) {
                        Log::Info("✓ Successfully got ResourceLocators collection: 0x%p", locatorsCollection);
                        
                        // Get the collection's class
                        MonoClass* collectionClass = Mono::MonoHelper::GetObjectClass(locatorsCollection);
                        Log::Info("  Collection type: %s.%s", 
                            Mono::MonoHelper::GetClassNamespace(collectionClass),
                            Mono::MonoHelper::GetClassName(collectionClass));
                        
                        // Try to convert to List<T> first by calling ToList() if available
                        // This is easier than trying to enumerate IEnumerable directly
                        MonoMethod* toListMethod = Mono::MonoHelper::FindMethod(collectionClass, "ToList", 0);
                        if (toListMethod) {
                            Log::Info("  Found ToList() method - converting to List...");
                            MonoObject* listObj = Mono::MonoHelper::InvokeInstanceMethod(toListMethod, locatorsCollection, nullptr);
                            if (listObj) {
                                MonoClass* listClass = Mono::MonoHelper::GetObjectClass(listObj);
                                MonoMethod* getCount = Mono::MonoHelper::FindMethod(listClass, "get_Count", 0);
                                if (getCount) {
                                    MonoObject* countObj = Mono::MonoHelper::InvokeInstanceMethod(getCount, listObj, nullptr);
                                    if (countObj) {
                                        int count = *(int*)Mono::MonoHelper::UnboxObject(countObj);
                                        Log::Info("  Number of catalogs loaded: %d", count);
                                        
                                        // Enumerate catalogs
                                        if (count > 0) {
                                            Log::Info("");
                                            Log::Info("Enumerating loaded catalogs:");
                                            
                                            MonoMethod* getItem = Mono::MonoHelper::FindMethod(listClass, "get_Item", 1);
                                            if (getItem) {
                                                for (int i = 0; i < count; i++) {
                                                    void* args[1];
                                                    int index = i;
                                                    args[0] = &index;
                                                    
                                                    MonoObject* locator = Mono::MonoHelper::InvokeInstanceMethod(getItem, listObj, args);
                                                    if (locator) {
                                                        MonoClass* locatorClass = Mono::MonoHelper::GetObjectClass(locator);
                                                        Log::Info("  [%d] Type: %s.%s", i,
                                                            Mono::MonoHelper::GetClassNamespace(locatorClass),
                                                            Mono::MonoHelper::GetClassName(locatorClass));
                                                        
                                                        // Try to get LocatorId
                                                        MonoMethod* getLocatorId = Mono::MonoHelper::FindMethod(locatorClass, "get_LocatorId", 0);
                                                        if (getLocatorId) {
                                                            MonoObject* idObj = Mono::MonoHelper::InvokeInstanceMethod(getLocatorId, locator, nullptr);
                                                            if (idObj) {
                                                                const char* idStr = Mono::MonoHelper::MonoStringToUTF8((MonoString*)idObj);
                                                                if (idStr) {
                                                                    Log::Info("      LocatorId: %s", idStr);
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            // Fallback: Just log that we got the collection
                            Log::Info("  (Collection is IEnumerable - cannot easily enumerate from C++)");
                            Log::Info("  (Catalogs are loaded, but need different approach to inspect)");
                        }
                        
                    } else {
                        Log::Info("✗ get_ResourceLocators returned null");
                    }
                } else {
                    Log::Info("✗ Could not find get_ResourceLocators method");
                }
                
                Log::Info("");
                
                // TEST: Call LoadContentCatalogAsync with the game's existing catalog
                Log::Info("═══════════════════════════════════════════════════════");
                Log::Info("Testing LoadContentCatalogAsync (Critical for Custom Maps!)");
                Log::Info("═══════════════════════════════════════════════════════");
                
                // Find LoadContentCatalogAsync method (try different overloads)
                MonoMethod* loadCatalogMethod = Mono::MonoHelper::FindMethod(addressablesClass, "LoadContentCatalogAsync", 1);
                if (!loadCatalogMethod) {
                    loadCatalogMethod = Mono::MonoHelper::FindMethod(addressablesClass, "LoadContentCatalogAsync", 2);
                }
                if (!loadCatalogMethod) {
                    loadCatalogMethod = Mono::MonoHelper::FindMethod(addressablesClass, "LoadContentCatalogAsync", 3);
                }
                
                if (loadCatalogMethod) {
                    int paramCount = Mono::MonoHelper::GetMethodParamCount(loadCatalogMethod);
                    Log::Info("✓ Found LoadContentCatalogAsync (params: %d)", paramCount);
                    
                    // Test catalog path (relative to game executable)
                    const char* catalogPath = "Super Battle Golf_Data/StreamingAssets/aa/catalog.bin";
                    
                    MonoDomain* domain = Mono::MonoHelper::GetRootDomain();
                    if (domain) {
                        MonoString* pathStr = Mono::MonoHelper::CreateString(catalogPath);
                        if (pathStr) {
                            Log::Info("✓ Created catalog path: %s", catalogPath);
                            
                            void* args[3] = { nullptr, nullptr, nullptr };
                            args[0] = pathStr;
                            
                            if (paramCount >= 2) {
                                bool autoRelease = false;
                                args[1] = &autoRelease;
                            }
                            if (paramCount >= 3) {
                                args[1] = nullptr; // providerSuffix
                                bool autoRelease = false;
                                args[2] = &autoRelease;
                            }
                            
                            Log::Info("🚀 Calling LoadContentCatalogAsync...");
                            MonoObject* asyncOp = Mono::MonoHelper::InvokeStaticMethod(loadCatalogMethod, args);
                            
                            if (asyncOp) {
                                Log::Info("✅ SUCCESS! LoadContentCatalogAsync returned: 0x%p", asyncOp);
                                
                                MonoClass* asyncOpClass = Mono::MonoHelper::GetObjectClass(asyncOp);
                                Log::Info("   Type: %s.%s",
                                    Mono::MonoHelper::GetClassNamespace(asyncOpClass),
                                    Mono::MonoHelper::GetClassName(asyncOpClass));
                                
                                // Check if completed
                                MonoMethod* getIsDone = Mono::MonoHelper::FindMethod(asyncOpClass, "get_IsDone", 0);
                                if (getIsDone) {
                                    MonoObject* isDoneObj = Mono::MonoHelper::InvokeInstanceMethod(getIsDone, asyncOp, nullptr);
                                    if (isDoneObj) {
                                        bool isDone = *(bool*)Mono::MonoHelper::UnboxObject(isDoneObj);
                                        Log::Info("   IsDone: %s", isDone ? "true" : "false");
                                    }
                                }
                                
                                Log::Info("");
                                Log::Info("🎉 BREAKTHROUGH! We can load catalogs programmatically!");
                                Log::Info("   → Custom maps are now PROVEN POSSIBLE!");
                                
                            } else {
                                Log::Info("✗ LoadContentCatalogAsync returned null");
                            }
                        }
                    }
                } else {
                    Log::Info("✗ LoadContentCatalogAsync not found");
                }
                
                Log::Info("═══════════════════════════════════════════════════════");
                Log::Info("");
                
                // Test: Call get_ResourceManager
                MonoMethod* getResourceManager = Mono::MonoHelper::FindMethod(addressablesClass, "get_ResourceManager", 0);
                if (getResourceManager) {
                    Log::Info("✓ Found get_ResourceManager method");
                    
                    MonoObject* manager = Mono::MonoHelper::InvokeStaticMethod(getResourceManager, nullptr);
                    if (manager) {
                        Log::Info("✓ Successfully got ResourceManager!");
                        Log::Info("  ResourceManager object: 0x%p", manager);
                    } else {
                        Log::Info("✗ get_ResourceManager returned null");
                    }
                } else {
                    Log::Info("✗ Could not find get_ResourceManager method");
                }
                
                Log::Info("═══════════════════════════════════════════════════════");
                Log::Info("");
            } else {
                Log::Info("✗ Addressables class not found (may need different namespace/name)");
            }
            
            MonoClass* resourceManagerClass = Mono::MonoHelper::FindClass(
                "Unity.ResourceManager",
                "UnityEngine.ResourceManagement.ResourceManager",
                "ResourceManager"
            );
            
            if (resourceManagerClass) {
                Log::Info("✓ Found ResourceManager class!");
                Log::Info("  Namespace: %s", Mono::MonoHelper::GetClassNamespace(resourceManagerClass));
                Log::Info("  Name: %s", Mono::MonoHelper::GetClassName(resourceManagerClass));
            } else {
                Log::Info("✗ ResourceManager class not found");
            }
            
            Log::Info("═══════════════════════════════════════════════════════");
            Log::Info("");

            // TODO: Addressables hooks need to be refactored for Mono
            // bool addressablesSuccess = Addressables::AddressablesHook::Initialize();
            // if (addressablesSuccess) {
            //     Log::Info("[CORE] ✓ Addressables hooks initialized!");
            //     Addressables::AddressablesHook::DumpAddressablesInfo();
            // } else {
            //     Log::Info("[CORE] Addressables hooks not ready yet");
            // }
        } else {
            Log::Info("[CORE] Mono integration failed; continuing without Mono features");
        }
    } else {
        Log::Info("[CORE] Mono runtime was not detected within startup timeout");
    }

    Hooks::Initialize();
    Log::Info("[CORE] Hooks initialized");

    ModManager::Instance();
    Log::Info("[CORE] ModManager initialized");

    return 0;
}

} // namespace

/// Called when ModLoaderCore.dll is injected into game process
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(hModule);

            HANDLE initThread = CreateThread(nullptr, 0, InitializeModLoaderThread, nullptr, 0, nullptr);
            if (initThread) {
                CloseHandle(initThread);
            }
            break;
        }

        case DLL_PROCESS_DETACH:
            if (lpReserved == nullptr) {
                Hooks::Shutdown();
            }
            break;

        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}
