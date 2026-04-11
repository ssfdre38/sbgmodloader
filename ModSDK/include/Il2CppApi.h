#pragma once
#include <cstdint>
#include <string>

namespace ModSDK {

/// IL2CPP object pointers (opaque handles)
typedef void* Il2CppObject;
typedef void* Il2CppClass;
typedef void* Il2CppImage;
typedef void* Il2CppMethod;
typedef void* Il2CppString;

/// Common IL2CPP game types
class GameObject;
class Transform;
class Component;
class Renderer;
class TextMeshProUGUI;
class Canvas;
class RectTransform;

/// Wrapper around IL2CPP UnityEngine functions
namespace IL2CPP {
    
    // Class/Type operations
    Il2CppClass* ClassFromName(const char* imageName, const char* namespaceName, const char* className);
    Il2CppImage* ImageFromName(const char* imageName);
    
    // GameObject operations
    GameObject* CreateGameObject(const char* name);
    void DestroyGameObject(GameObject* go);
    Transform* GetTransform(GameObject* go);
    
    // Component operations
    Component* GetComponent(GameObject* go, Il2CppClass* componentClass);
    Component* AddComponent(GameObject* go, Il2CppClass* componentClass);
    
    // Method invocation
    Il2CppObject* InvokeMethod(Il2CppMethod* method, Il2CppObject* instance, void** params, int paramCount);
    
    // String operations
    Il2CppString* CreateString(const char* text);
    std::string StringToStd(Il2CppString* str);
    
}  // namespace IL2CPP

}  // namespace ModSDK
