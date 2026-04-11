#pragma once

/**
 * IL2CPP Runtime API - Common functions for interacting with IL2CPP
 * 
 * This header declares the core IL2CPP API functions needed for:
 * - Class/method lookup
 * - Object creation and manipulation
 * - Method invocation
 * - Type introspection
 * 
 * Based on Il2CppVersions documentation and standard IL2CPP runtime
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========== Basic Type Definitions ========== */

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

/* Forward declarations for IL2CPP types */
typedef struct Il2CppDomain Il2CppDomain;
typedef struct Il2CppAssembly Il2CppAssembly;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppClass Il2CppClass;
typedef struct Il2CppObject Il2CppObject;
typedef struct Il2CppString Il2CppString;
typedef struct Il2CppArray Il2CppArray;
typedef struct Il2CppReflectionType Il2CppReflectionType;
typedef struct Il2CppMethod Il2CppMethod;
typedef struct Il2CppFieldInfo Il2CppFieldInfo;
typedef struct MethodInfo MethodInfo;

typedef void (*Il2CppMethodPointer)(void);

/* ========== Domain Functions ========== */

/**
 * Get the root domain of the IL2CPP runtime
 * Required before any assembly operations
 */
typedef Il2CppDomain* (*il2cpp_domain_get_t)(void);
extern il2cpp_domain_get_t il2cpp_domain_get;

/**
 * Get all assemblies in the domain
 */
typedef const Il2CppAssembly** (*il2cpp_domain_get_assemblies_t)(Il2CppDomain* domain, size_t* size);
extern il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;

/* ========== Assembly & Image Functions ========== */

/**
 * Get the image from an assembly
 * Images contain the actual type and method metadata
 */
typedef Il2CppImage* (*il2cpp_assembly_get_image_t)(const Il2CppAssembly* assembly);
extern il2cpp_assembly_get_image_t il2cpp_assembly_get_image;

/**
 * Get image by name
 * Common images: "UnityEngine.CoreModule", "Assembly-CSharp", "netstandard"
 */
typedef Il2CppImage* (*il2cpp_image_from_name_t)(const char* name);
extern il2cpp_image_from_name_t il2cpp_image_from_name;

/* ========== Class Functions ========== */

/**
 * Find a class by name in an image
 * Example: il2cpp_class_from_name(image, "UnityEngine", "GameObject")
 */
typedef Il2CppClass* (*il2cpp_class_from_name_t)(Il2CppImage* image, const char* namespaze, const char* name);
extern il2cpp_class_from_name_t il2cpp_class_from_name;

/**
 * Find a class in any assembly by full name
 * Searches across all loaded images
 */
typedef Il2CppClass* (*il2cpp_class_from_system_type_t)(Il2CppReflectionType* type);
extern il2cpp_class_from_system_type_t il2cpp_class_from_system_type;

/**
 * Get class name
 */
typedef const char* (*il2cpp_class_get_name_t)(Il2CppClass* klass);
extern il2cpp_class_get_name_t il2cpp_class_get_name;

/**
 * Get class namespace
 */
typedef const char* (*il2cpp_class_get_namespace_t)(Il2CppClass* klass);
extern il2cpp_class_get_namespace_t il2cpp_class_get_namespace;

/**
 * Get parent class
 */
typedef Il2CppClass* (*il2cpp_class_get_parent_t)(Il2CppClass* klass);
extern il2cpp_class_get_parent_t il2cpp_class_get_parent;

/* ========== Object Functions ========== */

/**
 * Create new instance of a class
 * Returns initialized object with fields set to default
 */
typedef Il2CppObject* (*il2cpp_object_new_t)(Il2CppClass* klass);
extern il2cpp_object_new_t il2cpp_object_new;

/**
 * Get object size in bytes
 */
typedef uint32 (*il2cpp_object_get_size_t)(Il2CppObject* obj);
extern il2cpp_object_get_size_t il2cpp_object_get_size;

/**
 * Get the class of an object instance
 */
typedef Il2CppClass* (*il2cpp_object_get_class_t)(Il2CppObject* obj);
extern il2cpp_object_get_class_t il2cpp_object_get_class;

/* ========== Method Functions ========== */

/**
 * Find a method in a class by name
 * Example: il2cpp_class_get_method_from_name(klass, "SetActive", 1)
 * The last parameter is parameter count (-1 for any)
 */
typedef const MethodInfo* (*il2cpp_class_get_method_from_name_t)(
    Il2CppClass* klass, 
    const char* name, 
    int argsCount
);
extern il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;

/**
 * Invoke a method on an object instance
 * Example for GameObject.SetActive(true):
 *   bool active = true;
 *   il2cpp_runtime_invoke(method, gameObject, &active, nullptr);
 */
typedef Il2CppObject* (*il2cpp_runtime_invoke_t)(
    const MethodInfo* method,
    void* obj,
    void** params,
    void** exc
);
extern il2cpp_runtime_invoke_t il2cpp_runtime_invoke;

/**
 * Get method name
 */
typedef const char* (*il2cpp_method_get_name_t)(const MethodInfo* method);
extern il2cpp_method_get_name_t il2cpp_method_get_name;

/* ========== Field Functions ========== */

/**
 * Get field by name from a class
 */
typedef Il2CppFieldInfo* (*il2cpp_class_get_field_from_name_t)(Il2CppClass* klass, const char* name);
extern il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name;

/**
 * Get field value from an object instance
 */
typedef void (*il2cpp_field_get_value_t)(Il2CppObject* obj, Il2CppFieldInfo* field, void* value);
extern il2cpp_field_get_value_t il2cpp_field_get_value;

/**
 * Set field value on an object instance
 */
typedef void (*il2cpp_field_set_value_t)(Il2CppObject* obj, Il2CppFieldInfo* field, void* value);
extern il2cpp_field_set_value_t il2cpp_field_set_value;

/* ========== String Functions ========== */

/**
 * Create a new IL2CPP string from UTF-8 C string
 */
typedef Il2CppString* (*il2cpp_string_new_t)(const char* str);
extern il2cpp_string_new_t il2cpp_string_new;

/**
 * Create a new IL2CPP string from UTF-16 wide string
 */
typedef Il2CppString* (*il2cpp_string_new_utf16_t)(const wchar_t* str, uint32 len);
extern il2cpp_string_new_utf16_t il2cpp_string_new_utf16;

/* ========== Array Functions ========== */

/**
 * Create a new array of a specific element type
 */
typedef Il2CppArray* (*il2cpp_array_new_t)(Il2CppClass* elementType, uint32 length);
extern il2cpp_array_new_t il2cpp_array_new;

/**
 * Get array element by index
 */
typedef void* (*il2cpp_array_addr_with_size_t)(Il2CppArray* array, uint32 elementSize, uint32 index);
extern il2cpp_array_addr_with_size_t il2cpp_array_addr_with_size;

/* ========== Type Functions ========== */

/**
 * Get type from a class
 */
typedef Il2CppReflectionType* (*il2cpp_class_get_type_t)(Il2CppClass* klass);
extern il2cpp_class_get_type_t il2cpp_class_get_type;

/* ========== Initialization ========== */

/**
 * Initialize IL2CPP function pointers from runtime
 * Call this once at startup to resolve all function addresses
 */
void il2cpp_api_init(void);

/* ========== Helper macros for common operations ========== */

#define IL2CPP_NULL_CHECK(ptr) if (!(ptr)) { return NULL; }
#define IL2CPP_VOID_CHECK(ptr) if (!(ptr)) { return; }

#ifdef __cplusplus
}
#endif
