#include "MonoHelper.h"
#include "Log.h"
#include <vector>
#include <string>

namespace ModLoader {
namespace Mono {

// Static member initialization
bool MonoHelper::s_Initialized = false;
HMODULE MonoHelper::s_MonoModule = nullptr;
MonoDomain* MonoHelper::s_RootDomain = nullptr;

// Mono API function pointers
mono_get_root_domain_fn MonoHelper::mono_get_root_domain = nullptr;
mono_domain_get_fn MonoHelper::mono_domain_get = nullptr;
mono_domain_foreach_fn MonoHelper::mono_domain_foreach = nullptr;
mono_assembly_foreach_fn MonoHelper::mono_assembly_foreach = nullptr;
mono_assembly_get_image_fn MonoHelper::mono_assembly_get_image = nullptr;
mono_image_get_name_fn MonoHelper::mono_image_get_name = nullptr;
mono_class_from_name_fn MonoHelper::mono_class_from_name = nullptr;
mono_class_get_method_from_name_fn MonoHelper::mono_class_get_method_from_name = nullptr;
mono_class_get_name_fn MonoHelper::mono_class_get_name = nullptr;
mono_class_get_namespace_fn MonoHelper::mono_class_get_namespace = nullptr;
mono_class_get_image_fn MonoHelper::mono_class_get_image = nullptr;
mono_thread_attach_fn MonoHelper::mono_thread_attach = nullptr;
mono_thread_detach_fn MonoHelper::mono_thread_detach = nullptr;
mono_string_new_fn MonoHelper::mono_string_new = nullptr;
mono_string_to_utf8_fn MonoHelper::mono_string_to_utf8 = nullptr;
mono_object_new_fn MonoHelper::mono_object_new = nullptr;
mono_runtime_invoke_fn MonoHelper::mono_runtime_invoke = nullptr;
mono_free_fn MonoHelper::mono_free = nullptr;
mono_method_desc_new_fn MonoHelper::mono_method_desc_new = nullptr;
mono_method_desc_search_in_image_fn MonoHelper::mono_method_desc_search_in_image = nullptr;
mono_method_desc_free_fn MonoHelper::mono_method_desc_free = nullptr;
mono_class_get_methods_fn MonoHelper::mono_class_get_methods = nullptr;
mono_method_get_name_fn MonoHelper::mono_method_get_name = nullptr;
mono_method_signature_fn MonoHelper::mono_method_signature = nullptr;
mono_signature_get_param_count_fn MonoHelper::mono_signature_get_param_count = nullptr;
mono_object_get_class_fn MonoHelper::mono_object_get_class = nullptr;
mono_object_unbox_fn MonoHelper::mono_object_unbox = nullptr;

template<typename T>
bool MonoHelper::GetExport(const char* name, T& outFunc) {
    outFunc = (T)GetProcAddress(s_MonoModule, name);
    if (!outFunc) {
        LOG_ERROR("Failed to find Mono export: %s", name);
        return false;
    }
    return true;
}

bool MonoHelper::Initialize(HMODULE monoModule) {
    if (s_Initialized) {
        LOG_INFO("Mono already initialized");
        return true;
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Initializing Mono Integration");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    s_MonoModule = monoModule;
    if (!s_MonoModule) {
        LOG_ERROR("Invalid Mono module handle!");
        return false;
    }
    LOG_INFO("✓ Found mono-2.0-bdwgc.dll at 0x%p", s_MonoModule);
    
    // Load all Mono exports
    LOG_INFO("Loading Mono exports...");
    
    bool success = true;
    success &= GetExport("mono_get_root_domain", mono_get_root_domain);
    success &= GetExport("mono_domain_get", mono_domain_get);
    success &= GetExport("mono_domain_foreach", mono_domain_foreach);
    success &= GetExport("mono_assembly_foreach", mono_assembly_foreach);
    success &= GetExport("mono_assembly_get_image", mono_assembly_get_image);
    success &= GetExport("mono_image_get_name", mono_image_get_name);
    success &= GetExport("mono_class_from_name", mono_class_from_name);
    success &= GetExport("mono_class_get_method_from_name", mono_class_get_method_from_name);
    success &= GetExport("mono_class_get_name", mono_class_get_name);
    success &= GetExport("mono_class_get_namespace", mono_class_get_namespace);
    success &= GetExport("mono_class_get_image", mono_class_get_image);
    success &= GetExport("mono_thread_attach", mono_thread_attach);
    success &= GetExport("mono_thread_detach", mono_thread_detach);
    success &= GetExport("mono_string_new", mono_string_new);
    success &= GetExport("mono_string_to_utf8", mono_string_to_utf8);
    success &= GetExport("mono_object_new", mono_object_new);
    success &= GetExport("mono_runtime_invoke", mono_runtime_invoke);
    success &= GetExport("mono_free", mono_free);
    success &= GetExport("mono_method_desc_new", mono_method_desc_new);
    success &= GetExport("mono_method_desc_search_in_image", mono_method_desc_search_in_image);
    success &= GetExport("mono_method_desc_free", mono_method_desc_free);
    success &= GetExport("mono_class_get_methods", mono_class_get_methods);
    success &= GetExport("mono_method_get_name", mono_method_get_name);
    success &= GetExport("mono_method_signature", mono_method_signature);
    success &= GetExport("mono_signature_get_param_count", mono_signature_get_param_count);
    success &= GetExport("mono_object_get_class", mono_object_get_class);
    success &= GetExport("mono_object_unbox", mono_object_unbox);
    
    if (!success) {
        LOG_ERROR("Failed to load all Mono exports!");
        return false;
    }
    
    LOG_INFO("✓ All Mono exports loaded successfully");
    
    // Get Mono root domain
    s_RootDomain = GetRootDomain();
    if (!s_RootDomain) {
        LOG_ERROR("Failed to get Mono root domain!");
        return false;
    }
    LOG_INFO("✓ Mono root domain: 0x%p", s_RootDomain);
    
    // Attach main thread to Mono
    MonoThread* mainThread = AttachThread();
    if (!mainThread) {
        LOG_ERROR("Failed to attach main thread to Mono!");
        return false;
    }
    LOG_INFO("✓ Main thread attached to Mono: 0x%p", mainThread);
    
    s_Initialized = true;
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("✓ Mono Integration Initialized Successfully");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    return true;
}

MonoDomain* MonoHelper::GetRootDomain() {
    if (!mono_get_root_domain) {
        LOG_ERROR("mono_get_root_domain is not loaded!");
        return nullptr;
    }
    
    return mono_get_root_domain();
}

void MonoHelper::AssemblyForeachCallback(MonoAssembly* assembly, void* user_data) {
    std::vector<MonoAssembly*>* assemblies = (std::vector<MonoAssembly*>*)user_data;
    assemblies->push_back(assembly);
}

std::vector<MonoAssembly*> MonoHelper::GetAssemblies() {
    if (!mono_assembly_foreach) {
        LOG_ERROR("mono_assembly_foreach is not loaded!");
        return {};
    }
    
    std::vector<MonoAssembly*> assemblies;
    mono_assembly_foreach(AssemblyForeachCallback, &assemblies);
    return assemblies;
}

MonoAssembly* MonoHelper::FindAssembly(const char* name) {
    auto assemblies = GetAssemblies();
    
    for (auto assembly : assemblies) {
        MonoImage* image = mono_assembly_get_image(assembly);
        if (image) {
            const char* imageName = mono_image_get_name(image);
            if (imageName && strstr(imageName, name) != nullptr) {
                return assembly;
            }
        }
    }
    
    return nullptr;
}

MonoClass* MonoHelper::FindClass(const char* assemblyName, const char* nameSpace, const char* className) {
    if (!mono_assembly_get_image || !mono_class_from_name) {
        LOG_ERROR("Required Mono functions not loaded!");
        return nullptr;
    }
    
    MonoAssembly* assembly = FindAssembly(assemblyName);
    if (!assembly) {
        LOG_ERROR("Assembly not found: %s", assemblyName);
        return nullptr;
    }
    
    MonoImage* image = mono_assembly_get_image(assembly);
    if (!image) {
        LOG_ERROR("Failed to get image from assembly: %s", assemblyName);
        return nullptr;
    }
    
    MonoClass* klass = mono_class_from_name(image, nameSpace, className);
    if (!klass) {
        LOG_ERROR("Class not found: %s.%s in assembly %s", nameSpace, className, assemblyName);
        return nullptr;
    }
    
    return klass;
}

MonoMethod* MonoHelper::FindMethod(MonoClass* klass, const char* methodName, int paramCount) {
    if (!mono_class_get_method_from_name) {
        LOG_ERROR("mono_class_get_method_from_name is not loaded!");
        return nullptr;
    }
    
    if (!klass) {
        LOG_ERROR("Invalid class!");
        return nullptr;
    }
    
    MonoMethod* method = mono_class_get_method_from_name(klass, methodName, paramCount);
    if (!method) {
        LOG_ERROR("Method not found: %s (params: %d)", methodName, paramCount);
        return nullptr;
    }
    
    return method;
}

MonoObject* MonoHelper::InvokeStaticMethod(MonoMethod* method, void** params) {
    if (!mono_runtime_invoke) {
        LOG_ERROR("mono_runtime_invoke is not loaded!");
        return nullptr;
    }
    
    if (!method) {
        LOG_ERROR("Invalid method!");
        return nullptr;
    }
    
    MonoObject* exception = nullptr;
    MonoObject* result = mono_runtime_invoke(method, nullptr, params, &exception);
    
    if (exception) {
        LOG_ERROR("Exception occurred during method invocation!");
        return nullptr;
    }
    
    return result;
}

MonoObject* MonoHelper::InvokeInstanceMethod(MonoMethod* method, void* instance, void** params) {
    if (!mono_runtime_invoke) {
        LOG_ERROR("mono_runtime_invoke is not loaded!");
        return nullptr;
    }
    
    if (!method || !instance) {
        LOG_ERROR("Invalid method or instance!");
        return nullptr;
    }
    
    MonoObject* exception = nullptr;
    MonoObject* result = mono_runtime_invoke(method, instance, params, &exception);
    
    if (exception) {
        LOG_ERROR("Exception occurred during method invocation!");
        return nullptr;
    }
    
    return result;
}

MonoString* MonoHelper::CreateString(const char* str) {
    if (!mono_string_new) {
        LOG_ERROR("mono_string_new is not loaded!");
        return nullptr;
    }
    
    if (!s_RootDomain) {
        LOG_ERROR("Mono root domain not available!");
        return nullptr;
    }
    
    return mono_string_new(s_RootDomain, str);
}

char* MonoHelper::GetStringChars(MonoString* str) {
    if (!mono_string_to_utf8) {
        LOG_ERROR("mono_string_to_utf8 is not loaded!");
        return nullptr;
    }
    
    if (!str) {
        LOG_ERROR("Invalid string!");
        return nullptr;
    }
    
    return mono_string_to_utf8(str);
}

void MonoHelper::Free(void* ptr) {
    if (!mono_free) {
        LOG_ERROR("mono_free is not loaded!");
        return;
    }
    
    if (ptr) {
        mono_free(ptr);
    }
}

MonoThread* MonoHelper::AttachThread() {
    if (!mono_thread_attach) {
        LOG_ERROR("mono_thread_attach is not loaded!");
        return nullptr;
    }
    
    if (!s_RootDomain) {
        LOG_ERROR("Mono root domain not available!");
        return nullptr;
    }
    
    return mono_thread_attach(s_RootDomain);
}

void MonoHelper::DetachThread(MonoThread* thread) {
    if (!mono_thread_detach) {
        LOG_ERROR("mono_thread_detach is not loaded!");
        return;
    }
    
    if (thread) {
        mono_thread_detach(thread);
    }
}

const char* MonoHelper::GetClassName(MonoClass* klass) {
    if (!mono_class_get_name) {
        LOG_ERROR("mono_class_get_name is not loaded!");
        return nullptr;
    }
    
    if (!klass) {
        LOG_ERROR("Invalid class!");
        return nullptr;
    }
    
    return mono_class_get_name(klass);
}

const char* MonoHelper::GetClassNamespace(MonoClass* klass) {
    if (!mono_class_get_namespace) {
        LOG_ERROR("mono_class_get_namespace is not loaded!");
        return nullptr;
    }
    
    if (!klass) {
        LOG_ERROR("Invalid class!");
        return nullptr;
    }
    
    return mono_class_get_namespace(klass);
}

void MonoHelper::DumpAssemblies() {
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Loaded Mono Assemblies:");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    auto assemblies = GetAssemblies();
    LOG_INFO("Total assemblies: %zu", assemblies.size());
    
    for (size_t i = 0; i < assemblies.size(); i++) {
        MonoImage* image = mono_assembly_get_image(assemblies[i]);
        if (image) {
            const char* name = mono_image_get_name(image);
            LOG_INFO("  [%zu] %s", i, name ? name : "<unknown>");
        } else {
            LOG_INFO("  [%zu] <no image>", i);
        }
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
}

std::vector<MonoMethod*> MonoHelper::GetMethods(MonoClass* klass) {
    std::vector<MonoMethod*> methods;
    
    if (!mono_class_get_methods) {
        LOG_ERROR("mono_class_get_methods is not loaded!");
        return methods;
    }
    
    if (!klass) {
        LOG_ERROR("Invalid class!");
        return methods;
    }
    
    void* iter = nullptr;
    MonoMethod* method = nullptr;
    
    while ((method = (MonoMethod*)mono_class_get_methods(klass, &iter)) != nullptr) {
        methods.push_back(method);
    }
    
    return methods;
}

const char* MonoHelper::GetMethodName(MonoMethod* method) {
    if (!mono_method_get_name) {
        LOG_ERROR("mono_method_get_name is not loaded!");
        return nullptr;
    }
    
    if (!method) {
        LOG_ERROR("Invalid method!");
        return nullptr;
    }
    
    return mono_method_get_name(method);
}

int MonoHelper::GetMethodParamCount(MonoMethod* method) {
    if (!mono_method_signature || !mono_signature_get_param_count) {
        LOG_ERROR("Signature functions not loaded!");
        return -1;
    }
    
    if (!method) {
        LOG_ERROR("Invalid method!");
        return -1;
    }
    
    void* sig = mono_method_signature(method);
    if (!sig) {
        return -1;
    }
    
    return mono_signature_get_param_count(sig);
}

void MonoHelper::DumpClassMethods(MonoClass* klass) {
    if (!klass) {
        LOG_ERROR("Invalid class!");
        return;
    }
    
    const char* className = GetClassName(klass);
    const char* nameSpace = GetClassNamespace(klass);
    
    LOG_INFO("═══════════════════════════════════════════════════════");
    LOG_INFO("Methods in %s.%s:", nameSpace ? nameSpace : "", className ? className : "<unknown>");
    LOG_INFO("═══════════════════════════════════════════════════════");
    
    auto methods = GetMethods(klass);
    LOG_INFO("Total methods: %zu", methods.size());
    
    for (size_t i = 0; i < methods.size(); i++) {
        const char* methodName = GetMethodName(methods[i]);
        int paramCount = GetMethodParamCount(methods[i]);
        LOG_INFO("  [%zu] %s (params: %d)", i, methodName ? methodName : "<unknown>", paramCount);
    }
    
    LOG_INFO("═══════════════════════════════════════════════════════");
}

MonoClass* MonoHelper::GetObjectClass(MonoObject* obj) {
    if (!obj || !mono_object_get_class) return nullptr;
    return mono_object_get_class(obj);
}

void* MonoHelper::UnboxObject(MonoObject* obj) {
    if (!obj || !mono_object_unbox) return nullptr;
    return mono_object_unbox(obj);
}

const char* MonoHelper::MonoStringToUTF8(MonoString* monoStr) {
    if (!monoStr || !mono_string_to_utf8) return nullptr;
    return mono_string_to_utf8(monoStr);
}

} // namespace Mono
} // namespace ModLoader
