/**
 * IL2CPP Runtime API Implementation
 * 
 * Dynamically resolves IL2CPP function pointers from the runtime
 * This allows mods to interact with game objects and methods
 */

#include "il2cpp-api.h"
#include <Windows.h>
#include <cstring>

/* Function pointer declarations */
il2cpp_domain_get_t il2cpp_domain_get = nullptr;
il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies = nullptr;
il2cpp_assembly_get_image_t il2cpp_assembly_get_image = nullptr;
il2cpp_image_from_name_t il2cpp_image_from_name = nullptr;
il2cpp_class_from_name_t il2cpp_class_from_name = nullptr;
il2cpp_class_from_system_type_t il2cpp_class_from_system_type = nullptr;
il2cpp_class_get_name_t il2cpp_class_get_name = nullptr;
il2cpp_class_get_namespace_t il2cpp_class_get_namespace = nullptr;
il2cpp_class_get_parent_t il2cpp_class_get_parent = nullptr;
il2cpp_object_new_t il2cpp_object_new = nullptr;
il2cpp_object_get_size_t il2cpp_object_get_size = nullptr;
il2cpp_object_get_class_t il2cpp_object_get_class = nullptr;
il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = nullptr;
il2cpp_runtime_invoke_t il2cpp_runtime_invoke = nullptr;
il2cpp_method_get_name_t il2cpp_method_get_name = nullptr;
il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name = nullptr;
il2cpp_field_get_value_t il2cpp_field_get_value = nullptr;
il2cpp_field_set_value_t il2cpp_field_set_value = nullptr;
il2cpp_string_new_t il2cpp_string_new = nullptr;
il2cpp_string_new_utf16_t il2cpp_string_new_utf16 = nullptr;
il2cpp_array_new_t il2cpp_array_new = nullptr;
il2cpp_array_addr_with_size_t il2cpp_array_addr_with_size = nullptr;
il2cpp_class_get_type_t il2cpp_class_get_type = nullptr;

/**
 * Helper to resolve a function pointer from IL2CPP runtime
 * The il2cpp runtime is exported from il2cpp.dll or compiled into GameAssembly.dll
 */
static void* resolve_il2cpp_function(const char* function_name) {
    // Try il2cpp.dll first (common in many IL2CPP games)
    HMODULE il2cpp_module = GetModuleHandleA("il2cpp.dll");
    
    if (!il2cpp_module) {
        // Fallback: try GameAssembly.dll (for games where IL2CPP is compiled in)
        il2cpp_module = GetModuleHandleA("GameAssembly.dll");
    }
    
    if (il2cpp_module) {
        return GetProcAddress(il2cpp_module, function_name);
    }
    
    return nullptr;
}

/**
 * Initialize all IL2CPP function pointers
 * Must be called once after ModLoaderCore.dll is loaded into the game
 */
void il2cpp_api_init(void) {
    // Domain functions
    il2cpp_domain_get = (il2cpp_domain_get_t)resolve_il2cpp_function("il2cpp_domain_get");
    il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)resolve_il2cpp_function("il2cpp_domain_get_assemblies");
    
    // Assembly & Image functions
    il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)resolve_il2cpp_function("il2cpp_assembly_get_image");
    il2cpp_image_from_name = (il2cpp_image_from_name_t)resolve_il2cpp_function("il2cpp_image_from_name");
    
    // Class functions
    il2cpp_class_from_name = (il2cpp_class_from_name_t)resolve_il2cpp_function("il2cpp_class_from_name");
    il2cpp_class_from_system_type = (il2cpp_class_from_system_type_t)resolve_il2cpp_function("il2cpp_class_from_system_type");
    il2cpp_class_get_name = (il2cpp_class_get_name_t)resolve_il2cpp_function("il2cpp_class_get_name");
    il2cpp_class_get_namespace = (il2cpp_class_get_namespace_t)resolve_il2cpp_function("il2cpp_class_get_namespace");
    il2cpp_class_get_parent = (il2cpp_class_get_parent_t)resolve_il2cpp_function("il2cpp_class_get_parent");
    
    // Object functions
    il2cpp_object_new = (il2cpp_object_new_t)resolve_il2cpp_function("il2cpp_object_new");
    il2cpp_object_get_size = (il2cpp_object_get_size_t)resolve_il2cpp_function("il2cpp_object_get_size");
    il2cpp_object_get_class = (il2cpp_object_get_class_t)resolve_il2cpp_function("il2cpp_object_get_class");
    
    // Method functions
    il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)resolve_il2cpp_function("il2cpp_class_get_method_from_name");
    il2cpp_runtime_invoke = (il2cpp_runtime_invoke_t)resolve_il2cpp_function("il2cpp_runtime_invoke");
    il2cpp_method_get_name = (il2cpp_method_get_name_t)resolve_il2cpp_function("il2cpp_method_get_name");
    
    // Field functions
    il2cpp_class_get_field_from_name = (il2cpp_class_get_field_from_name_t)resolve_il2cpp_function("il2cpp_class_get_field_from_name");
    il2cpp_field_get_value = (il2cpp_field_get_value_t)resolve_il2cpp_function("il2cpp_field_get_value");
    il2cpp_field_set_value = (il2cpp_field_set_value_t)resolve_il2cpp_function("il2cpp_field_set_value");
    
    // String functions
    il2cpp_string_new = (il2cpp_string_new_t)resolve_il2cpp_function("il2cpp_string_new");
    il2cpp_string_new_utf16 = (il2cpp_string_new_utf16_t)resolve_il2cpp_function("il2cpp_string_new_utf16");
    
    // Array functions
    il2cpp_array_new = (il2cpp_array_new_t)resolve_il2cpp_function("il2cpp_array_new");
    il2cpp_array_addr_with_size = (il2cpp_array_addr_with_size_t)resolve_il2cpp_function("il2cpp_array_addr_with_size");
    
    // Type functions
    il2cpp_class_get_type = (il2cpp_class_get_type_t)resolve_il2cpp_function("il2cpp_class_get_type");
}
