#include "IL2CPP.h"
#include "Log.h"
#include <vector>
#include <string>

namespace ModLoader {
namespace IL2CPP {

// Static member initialization
bool IL2CPPHelper::s_Initialized = false;
HMODULE IL2CPPHelper::s_GameAssemblyModule = nullptr;

// IL2CPP API function pointers
il2cpp_domain_get_fn IL2CPPHelper::il2cpp_domain_get = nullptr;
il2cpp_domain_get_assemblies_fn IL2CPPHelper::il2cpp_domain_get_assemblies = nullptr;
il2cpp_assembly_get_image_fn IL2CPPHelper::il2cpp_assembly_get_image = nullptr;
il2cpp_class_from_name_fn IL2CPPHelper::il2cpp_class_from_name = nullptr;
il2cpp_class_get_method_from_name_fn IL2CPPHelper::il2cpp_class_get_method_from_name = nullptr;
il2cpp_class_get_name_fn IL2CPPHelper::il2cpp_class_get_name = nullptr;
il2cpp_class_get_namespace_fn IL2CPPHelper::il2cpp_class_get_namespace = nullptr;
il2cpp_class_get_image_fn IL2CPPHelper::il2cpp_class_get_image = nullptr;
il2cpp_thread_attach_fn IL2CPPHelper::il2cpp_thread_attach = nullptr;
il2cpp_thread_detach_fn IL2CPPHelper::il2cpp_thread_detach = nullptr;
il2cpp_string_new_fn IL2CPPHelper::il2cpp_string_new = nullptr;
il2cpp_string_chars_fn IL2CPPHelper::il2cpp_string_chars = nullptr;
il2cpp_object_new_fn IL2CPPHelper::il2cpp_object_new = nullptr;
il2cpp_runtime_invoke_fn IL2CPPHelper::il2cpp_runtime_invoke = nullptr;
il2cpp_array_length_fn IL2CPPHelper::il2cpp_array_length = nullptr;
il2cpp_array_get_fn IL2CPPHelper::il2cpp_array_get = nullptr;

template<typename T>
bool IL2CPPHelper::GetExport(const char* name, T& outFunc) {
    outFunc = (T)GetProcAddress(s_GameAssemblyModule, name);
    if (!outFunc) {
        LOG_ERROR("Failed to find IL2CPP export: %s", name);
        return false;
    }
    return true;
}

bool IL2CPPHelper::Initialize() {
    if (s_Initialized) {
        LOG_INFO("IL2CPP already initialized");
        return true;
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Initializing IL2CPP Integration");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    // Get GameAssembly.dll handle
    s_GameAssemblyModule = GetModuleHandleA("GameAssembly.dll");
    if (!s_GameAssemblyModule) {
        LOG_ERROR("Failed to get GameAssembly.dll module handle!");
        return false;
    }
    LOG_INFO("✓ Found GameAssembly.dll at 0x%p", s_GameAssemblyModule);
    
    // Load all IL2CPP exports
    LOG_INFO("Loading IL2CPP exports...");
    
    bool success = true;
    success &= GetExport("il2cpp_domain_get", il2cpp_domain_get);
    success &= GetExport("il2cpp_domain_get_assemblies", il2cpp_domain_get_assemblies);
    success &= GetExport("il2cpp_assembly_get_image", il2cpp_assembly_get_image);
    success &= GetExport("il2cpp_class_from_name", il2cpp_class_from_name);
    success &= GetExport("il2cpp_class_get_method_from_name", il2cpp_class_get_method_from_name);
    success &= GetExport("il2cpp_class_get_name", il2cpp_class_get_name);
    success &= GetExport("il2cpp_class_get_namespace", il2cpp_class_get_namespace);
    success &= GetExport("il2cpp_class_get_image", il2cpp_class_get_image);
    success &= GetExport("il2cpp_thread_attach", il2cpp_thread_attach);
    success &= GetExport("il2cpp_thread_detach", il2cpp_thread_detach);
    success &= GetExport("il2cpp_string_new", il2cpp_string_new);
    success &= GetExport("il2cpp_string_chars", il2cpp_string_chars);
    success &= GetExport("il2cpp_object_new", il2cpp_object_new);
    success &= GetExport("il2cpp_runtime_invoke", il2cpp_runtime_invoke);
    success &= GetExport("il2cpp_array_length", il2cpp_array_length);
    success &= GetExport("il2cpp_array_get", il2cpp_array_get);
    
    if (!success) {
        LOG_ERROR("Failed to load all IL2CPP exports!");
        return false;
    }
    
    LOG_INFO("✓ All IL2CPP exports loaded successfully");
    
    // Get IL2CPP domain
    Il2CppDomain* domain = GetDomain();
    if (!domain) {
        LOG_ERROR("Failed to get IL2CPP domain!");
        return false;
    }
    LOG_INFO("✓ IL2CPP domain: 0x%p", domain);
    
    // Attach main thread to IL2CPP
    Il2CppThread* mainThread = AttachThread();
    if (!mainThread) {
        LOG_ERROR("Failed to attach main thread to IL2CPP!");
        return false;
    }
    LOG_INFO("✓ Main thread attached to IL2CPP: 0x%p", mainThread);
    
    s_Initialized = true;
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("✓ IL2CPP Integration Initialized Successfully!");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    return true;
}

Il2CppDomain* IL2CPPHelper::GetDomain() {
    if (!il2cpp_domain_get) {
        LOG_ERROR("il2cpp_domain_get not loaded!");
        return nullptr;
    }
    
    return il2cpp_domain_get();
}

std::vector<Il2CppAssembly*> IL2CPPHelper::GetAssemblies() {
    std::vector<Il2CppAssembly*> assemblies;
    
    Il2CppDomain* domain = GetDomain();
    if (!domain) {
        return assemblies;
    }
    
    size_t assemblyCount = 0;
    Il2CppAssembly** assemblyArray = il2cpp_domain_get_assemblies(domain, &assemblyCount);
    
    if (assemblyArray) {
        for (size_t i = 0; i < assemblyCount; i++) {
            assemblies.push_back(assemblyArray[i]);
        }
    }
    
    return assemblies;
}

Il2CppAssembly* IL2CPPHelper::FindAssembly(const char* name) {
    auto assemblies = GetAssemblies();
    
    for (Il2CppAssembly* assembly : assemblies) {
        Il2CppImage* image = il2cpp_assembly_get_image(assembly);
        if (image) {
            // Get image name (first pointer in Il2CppImage struct)
            const char* imageName = *(const char**)image;
            if (imageName && strstr(imageName, name)) {
                return assembly;
            }
        }
    }
    
    return nullptr;
}

Il2CppClass* IL2CPPHelper::FindClass(const char* assemblyName, const char* namespaze, const char* className) {
    Il2CppAssembly* assembly = FindAssembly(assemblyName);
    if (!assembly) {
        LOG_ERROR("Assembly not found: %s", assemblyName);
        return nullptr;
    }
    
    Il2CppImage* image = il2cpp_assembly_get_image(assembly);
    if (!image) {
        LOG_ERROR("Failed to get image from assembly: %s", assemblyName);
        return nullptr;
    }
    
    Il2CppClass* klass = il2cpp_class_from_name(image, namespaze, className);
    if (!klass) {
        LOG_ERROR("Class not found: %s.%s in assembly %s", namespaze, className, assemblyName);
        return nullptr;
    }
    
    return klass;
}

Il2CppMethodInfo* IL2CPPHelper::FindMethod(Il2CppClass* klass, const char* methodName, int argCount) {
    if (!klass) {
        LOG_ERROR("Cannot find method on null class!");
        return nullptr;
    }
    
    Il2CppMethodInfo* method = il2cpp_class_get_method_from_name(klass, methodName, argCount);
    if (!method) {
        LOG_ERROR("Method not found: %s (args: %d)", methodName, argCount);
        return nullptr;
    }
    
    return method;
}

void* IL2CPPHelper::InvokeStaticMethod(Il2CppMethodInfo* method, void** params) {
    if (!method) {
        LOG_ERROR("Cannot invoke null method!");
        return nullptr;
    }
    
    void* exception = nullptr;
    void* result = il2cpp_runtime_invoke(method, nullptr, params, &exception);
    
    if (exception) {
        LOG_ERROR("Exception thrown when invoking static method!");
        return nullptr;
    }
    
    return result;
}

void* IL2CPPHelper::InvokeInstanceMethod(Il2CppMethodInfo* method, void* instance, void** params) {
    if (!method) {
        LOG_ERROR("Cannot invoke null method!");
        return nullptr;
    }
    
    if (!instance) {
        LOG_ERROR("Cannot invoke instance method on null instance!");
        return nullptr;
    }
    
    void* exception = nullptr;
    void* result = il2cpp_runtime_invoke(method, instance, params, &exception);
    
    if (exception) {
        LOG_ERROR("Exception thrown when invoking instance method!");
        return nullptr;
    }
    
    return result;
}

Il2CppString* IL2CPPHelper::CreateString(const char* str) {
    if (!il2cpp_string_new) {
        LOG_ERROR("il2cpp_string_new not loaded!");
        return nullptr;
    }
    
    return il2cpp_string_new(str);
}

const char* IL2CPPHelper::GetStringChars(Il2CppString* str) {
    if (!str) {
        return "";
    }
    
    if (!il2cpp_string_chars) {
        LOG_ERROR("il2cpp_string_chars not loaded!");
        return "";
    }
    
    return il2cpp_string_chars(str);
}

Il2CppThread* IL2CPPHelper::AttachThread() {
    if (!il2cpp_thread_attach) {
        LOG_ERROR("il2cpp_thread_attach not loaded!");
        return nullptr;
    }
    
    Il2CppDomain* domain = GetDomain();
    if (!domain) {
        LOG_ERROR("Cannot attach thread: no domain!");
        return nullptr;
    }
    
    return il2cpp_thread_attach(domain);
}

void IL2CPPHelper::DetachThread(Il2CppThread* thread) {
    if (!thread) {
        return;
    }
    
    if (!il2cpp_thread_detach) {
        LOG_ERROR("il2cpp_thread_detach not loaded!");
        return;
    }
    
    il2cpp_thread_detach(thread);
}

const char* IL2CPPHelper::GetClassName(Il2CppClass* klass) {
    if (!klass || !il2cpp_class_get_name) {
        return "";
    }
    
    return il2cpp_class_get_name(klass);
}

const char* IL2CPPHelper::GetClassNamespace(Il2CppClass* klass) {
    if (!klass || !il2cpp_class_get_namespace) {
        return "";
    }
    
    return il2cpp_class_get_namespace(klass);
}

void IL2CPPHelper::DumpAssemblies() {
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("IL2CPP Assembly Dump");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    auto assemblies = GetAssemblies();
    LOG_INFO("Found %zu assemblies:", assemblies.size());
    
    for (Il2CppAssembly* assembly : assemblies) {
        Il2CppImage* image = il2cpp_assembly_get_image(assembly);
        if (image) {
            // Get image name (first pointer in Il2CppImage struct)
            const char* imageName = *(const char**)image;
            if (imageName) {
                LOG_INFO("  - %s", imageName);
            }
        }
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
}

} // namespace IL2CPP
} // namespace ModLoader
