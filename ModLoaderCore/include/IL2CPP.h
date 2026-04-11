#pragma once
#include <Windows.h>
#include <string>
#include <vector>

// IL2CPP type definitions
typedef void* Il2CppDomain;
typedef void* Il2CppAssembly;
typedef void* Il2CppImage;
typedef void* Il2CppClass;
typedef void* Il2CppObject;
typedef void* Il2CppMethodInfo;
typedef void* Il2CppType;
typedef void* Il2CppString;
typedef void* Il2CppArray;
typedef void* Il2CppThread;

namespace ModLoader {
namespace IL2CPP {

// IL2CPP API function pointers
typedef Il2CppDomain* (*il2cpp_domain_get_fn)();
typedef Il2CppAssembly** (*il2cpp_domain_get_assemblies_fn)(const Il2CppDomain* domain, size_t* size);
typedef Il2CppImage* (*il2cpp_assembly_get_image_fn)(Il2CppAssembly* assembly);
typedef Il2CppClass* (*il2cpp_class_from_name_fn)(Il2CppImage* image, const char* namespaze, const char* name);
typedef Il2CppMethodInfo* (*il2cpp_class_get_method_from_name_fn)(Il2CppClass* klass, const char* name, int argsCount);
typedef const char* (*il2cpp_class_get_name_fn)(Il2CppClass* klass);
typedef const char* (*il2cpp_class_get_namespace_fn)(Il2CppClass* klass);
typedef Il2CppImage* (*il2cpp_class_get_image_fn)(Il2CppClass* klass);
typedef Il2CppThread* (*il2cpp_thread_attach_fn)(Il2CppDomain* domain);
typedef void (*il2cpp_thread_detach_fn)(Il2CppThread* thread);
typedef Il2CppString* (*il2cpp_string_new_fn)(const char* str);
typedef const char* (*il2cpp_string_chars_fn)(Il2CppString* str);
typedef void* (*il2cpp_object_new_fn)(Il2CppClass* klass);
typedef void* (*il2cpp_runtime_invoke_fn)(Il2CppMethodInfo* method, void* obj, void** params, void** exc);
typedef size_t (*il2cpp_array_length_fn)(Il2CppArray* array);
typedef void* (*il2cpp_array_get_fn)(Il2CppArray* array, size_t index);

class IL2CPPHelper {
public:
    // Initialize IL2CPP API by finding exported functions
    static bool Initialize();
    
    // Check if IL2CPP is initialized
    static bool IsInitialized() { return s_Initialized; }
    
    // Get the IL2CPP domain
    static Il2CppDomain* GetDomain();
    
    // Get all assemblies
    static std::vector<Il2CppAssembly*> GetAssemblies();
    
    // Find an assembly by name
    static Il2CppAssembly* FindAssembly(const char* name);
    
    // Find a class by namespace and name
    static Il2CppClass* FindClass(const char* assemblyName, const char* namespaze, const char* className);
    
    // Find a method in a class
    static Il2CppMethodInfo* FindMethod(Il2CppClass* klass, const char* methodName, int argCount = -1);
    
    // Invoke a static method
    static void* InvokeStaticMethod(Il2CppMethodInfo* method, void** params = nullptr);
    
    // Invoke an instance method
    static void* InvokeInstanceMethod(Il2CppMethodInfo* method, void* instance, void** params = nullptr);
    
    // Create a new C# string
    static Il2CppString* CreateString(const char* str);
    
    // Get C string from IL2CPP string
    static const char* GetStringChars(Il2CppString* str);
    
    // Attach current thread to IL2CPP domain (required for calling IL2CPP functions)
    static Il2CppThread* AttachThread();
    
    // Detach current thread from IL2CPP domain
    static void DetachThread(Il2CppThread* thread);
    
    // Get class info
    static const char* GetClassName(Il2CppClass* klass);
    static const char* GetClassNamespace(Il2CppClass* klass);
    
    // Dump all loaded assemblies and classes (for debugging)
    static void DumpAssemblies();
    
private:
    static bool s_Initialized;
    static HMODULE s_GameAssemblyModule;
    
    // IL2CPP API function pointers
    static il2cpp_domain_get_fn il2cpp_domain_get;
    static il2cpp_domain_get_assemblies_fn il2cpp_domain_get_assemblies;
    static il2cpp_assembly_get_image_fn il2cpp_assembly_get_image;
    static il2cpp_class_from_name_fn il2cpp_class_from_name;
    static il2cpp_class_get_method_from_name_fn il2cpp_class_get_method_from_name;
    static il2cpp_class_get_name_fn il2cpp_class_get_name;
    static il2cpp_class_get_namespace_fn il2cpp_class_get_namespace;
    static il2cpp_class_get_image_fn il2cpp_class_get_image;
    static il2cpp_thread_attach_fn il2cpp_thread_attach;
    static il2cpp_thread_detach_fn il2cpp_thread_detach;
    static il2cpp_string_new_fn il2cpp_string_new;
    static il2cpp_string_chars_fn il2cpp_string_chars;
    static il2cpp_object_new_fn il2cpp_object_new;
    static il2cpp_runtime_invoke_fn il2cpp_runtime_invoke;
    static il2cpp_array_length_fn il2cpp_array_length;
    static il2cpp_array_get_fn il2cpp_array_get;
    
    // Helper to get exported function from GameAssembly.dll
    template<typename T>
    static bool GetExport(const char* name, T& outFunc);
};

// RAII wrapper for IL2CPP thread attachment
class IL2CPPThreadScope {
public:
    IL2CPPThreadScope() {
        m_Thread = IL2CPPHelper::AttachThread();
    }
    
    ~IL2CPPThreadScope() {
        if (m_Thread) {
            IL2CPPHelper::DetachThread(m_Thread);
        }
    }
    
    IL2CPPThreadScope(const IL2CPPThreadScope&) = delete;
    IL2CPPThreadScope& operator=(const IL2CPPThreadScope&) = delete;
    
private:
    Il2CppThread* m_Thread;
};

} // namespace IL2CPP
} // namespace ModLoader
