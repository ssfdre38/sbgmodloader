#pragma once
#include <Windows.h>
#include <string>
#include <vector>

// Mono type definitions (from mono/metadata/*.h)
typedef void* MonoDomain;
typedef void* MonoAssembly;
typedef void* MonoImage;
typedef void* MonoClass;
typedef void* MonoObject;
typedef void* MonoMethod;
typedef void* MonoType;
typedef void* MonoString;
typedef void* MonoArray;
typedef void* MonoThread;
typedef void* MonoMethodDesc;

namespace ModLoader {
namespace Mono {

// Mono API function pointers
typedef MonoDomain* (*mono_get_root_domain_fn)();
typedef MonoDomain* (*mono_domain_get_fn)();
typedef void (*mono_domain_foreach_fn)(void (*func)(MonoDomain*, void*), void* user_data);
typedef void (*mono_assembly_foreach_fn)(void (*func)(MonoAssembly*, void*), void* user_data);
typedef MonoImage* (*mono_assembly_get_image_fn)(MonoAssembly* assembly);
typedef const char* (*mono_image_get_name_fn)(MonoImage* image);
typedef MonoClass* (*mono_class_from_name_fn)(MonoImage* image, const char* name_space, const char* name);
typedef MonoMethod* (*mono_class_get_method_from_name_fn)(MonoClass* klass, const char* name, int param_count);
typedef const char* (*mono_class_get_name_fn)(MonoClass* klass);
typedef const char* (*mono_class_get_namespace_fn)(MonoClass* klass);
typedef MonoImage* (*mono_class_get_image_fn)(MonoClass* klass);
typedef MonoThread* (*mono_thread_attach_fn)(MonoDomain* domain);
typedef void (*mono_thread_detach_fn)(MonoThread* thread);
typedef MonoString* (*mono_string_new_fn)(MonoDomain* domain, const char* text);
typedef char* (*mono_string_to_utf8_fn)(MonoString* string_obj);
typedef MonoObject* (*mono_object_new_fn)(MonoDomain* domain, MonoClass* klass);
typedef MonoObject* (*mono_runtime_invoke_fn)(MonoMethod* method, void* obj, void** params, MonoObject** exc);
typedef void (*mono_free_fn)(void* ptr);
typedef MonoMethodDesc* (*mono_method_desc_new_fn)(const char* name, int include_namespace);
typedef MonoMethod* (*mono_method_desc_search_in_image_fn)(MonoMethodDesc* desc, MonoImage* image);
typedef void (*mono_method_desc_free_fn)(MonoMethodDesc* desc);
typedef void* (*mono_class_get_methods_fn)(MonoClass* klass, void** iter);
typedef const char* (*mono_method_get_name_fn)(MonoMethod* method);
typedef void* (*mono_signature_get_params_fn)(void* sig, void** iter);
typedef void* (*mono_method_signature_fn)(MonoMethod* method);
typedef int (*mono_signature_get_param_count_fn)(void* sig);
typedef MonoClass* (*mono_object_get_class_fn)(MonoObject* obj);
typedef void* (*mono_object_unbox_fn)(MonoObject* obj);

class MonoHelper {
public:
    // Initialize Mono API by finding exported functions
    static bool Initialize(HMODULE monoModule);
    
    // Check if Mono is initialized
    static bool IsInitialized() { return s_Initialized; }
    
    // Get the Mono root domain
    static MonoDomain* GetRootDomain();
    
    // Get all assemblies
    static std::vector<MonoAssembly*> GetAssemblies();
    
    // Find an assembly by name
    static MonoAssembly* FindAssembly(const char* name);
    
    // Find a class by namespace and name
    static MonoClass* FindClass(const char* assemblyName, const char* nameSpace, const char* className);
    
    // Find a method in a class
    static MonoMethod* FindMethod(MonoClass* klass, const char* methodName, int paramCount = -1);
    
    // Invoke a static method
    static MonoObject* InvokeStaticMethod(MonoMethod* method, void** params = nullptr);
    
    // Invoke an instance method
    static MonoObject* InvokeInstanceMethod(MonoMethod* method, void* instance, void** params = nullptr);
    
    // Object inspection helpers
    static MonoClass* GetObjectClass(MonoObject* obj);
    static void* UnboxObject(MonoObject* obj);
    static const char* MonoStringToUTF8(MonoString* monoStr);
    
    // Create a new C# string
    static MonoString* CreateString(const char* str);
    
    // Get C string from Mono string (must be freed with mono_free)
    static char* GetStringChars(MonoString* str);
    
    // Free memory allocated by Mono
    static void Free(void* ptr);
    
    // Attach current thread to Mono domain (required for calling Mono functions)
    static MonoThread* AttachThread();
    
    // Detach current thread from Mono domain
    static void DetachThread(MonoThread* thread);
    
    // Get class info
    static const char* GetClassName(MonoClass* klass);
    static const char* GetClassNamespace(MonoClass* klass);
    
    // Enumerate methods in a class
    static std::vector<MonoMethod*> GetMethods(MonoClass* klass);
    static const char* GetMethodName(MonoMethod* method);
    static int GetMethodParamCount(MonoMethod* method);
    
    // Dump all loaded assemblies and classes (for debugging)
    static void DumpAssemblies();
    static void DumpClassMethods(MonoClass* klass);
    
private:
    static bool s_Initialized;
    static HMODULE s_MonoModule;
    static MonoDomain* s_RootDomain;
    
    // Mono API function pointers
    static mono_get_root_domain_fn mono_get_root_domain;
    static mono_domain_get_fn mono_domain_get;
    static mono_domain_foreach_fn mono_domain_foreach;
    static mono_assembly_foreach_fn mono_assembly_foreach;
    static mono_assembly_get_image_fn mono_assembly_get_image;
    static mono_image_get_name_fn mono_image_get_name;
    static mono_class_from_name_fn mono_class_from_name;
    static mono_class_get_method_from_name_fn mono_class_get_method_from_name;
    static mono_class_get_name_fn mono_class_get_name;
    static mono_class_get_namespace_fn mono_class_get_namespace;
    static mono_class_get_image_fn mono_class_get_image;
    static mono_thread_attach_fn mono_thread_attach;
    static mono_thread_detach_fn mono_thread_detach;
    static mono_string_new_fn mono_string_new;
    static mono_string_to_utf8_fn mono_string_to_utf8;
    static mono_object_new_fn mono_object_new;
    static mono_runtime_invoke_fn mono_runtime_invoke;
    static mono_free_fn mono_free;
    static mono_method_desc_new_fn mono_method_desc_new;
    static mono_method_desc_search_in_image_fn mono_method_desc_search_in_image;
    static mono_method_desc_free_fn mono_method_desc_free;
    static mono_class_get_methods_fn mono_class_get_methods;
    static mono_method_get_name_fn mono_method_get_name;
    static mono_method_signature_fn mono_method_signature;
    static mono_signature_get_param_count_fn mono_signature_get_param_count;
    static mono_object_get_class_fn mono_object_get_class;
    static mono_object_unbox_fn mono_object_unbox;
    
    // Helper to get exported function from mono-2.0-bdwgc.dll
    template<typename T>
    static bool GetExport(const char* name, T& outFunc);
    
    // Callback for assembly enumeration
    static void AssemblyForeachCallback(MonoAssembly* assembly, void* user_data);
};

// RAII wrapper for Mono thread attachment
class MonoThreadScope {
public:
    MonoThreadScope() {
        m_Thread = MonoHelper::AttachThread();
    }
    
    ~MonoThreadScope() {
        if (m_Thread) {
            MonoHelper::DetachThread(m_Thread);
        }
    }
    
    MonoThreadScope(const MonoThreadScope&) = delete;
    MonoThreadScope& operator=(const MonoThreadScope&) = delete;
    
private:
    MonoThread* m_Thread;
};

} // namespace Mono
} // namespace ModLoader
