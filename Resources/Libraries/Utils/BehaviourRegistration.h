//
// Created by Monika on 23.05.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
#define EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Utils/NonCopyable.h>
#include <Libraries/Types/SharedPtr.h>

#include <Libraries/GameObject.h>

#pragma warning (disable: 4190)

#ifndef EXTERN
    #define EXTERN extern "C" __declspec(dllexport)
#endif

#define REGISTER_BEHAVIOUR_BASE(className)                                          \
    EXTERN void Awake() {                                                           \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->Awake();                                                           \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void Start() {                                                           \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->Start();                                                           \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void OnDisable() {                                                       \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->OnDisable();                                                       \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void OnEnable() {                                                        \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->OnEnable();                                                        \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void Update(float_t dt) {                                                \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->Update(dt);                                                        \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void FixedUpdate() {                                                     \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->FixedUpdate();                                                     \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void Close() {                                                           \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->Close();                                                           \
        }                                                                           \
    }                                                                               \
                                                                                    \
    EXTERN void SetGameObject(Behaviour::GameObjectPtr gameObject) {                \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            ptr->SetGameObject(gameObject);                                         \
        }                                                                           \
    }                                                                               \

#define REGISTER_BEHAVIOUR_PROPERTIES(className)                                    \
    EXTERN std::any GetProperty(const std::string& id) {                            \
        auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>();         \
                                                                                    \
        if (!ptr) {                                                                 \
            return std::any();                                                      \
        }                                                                           \
                                                                                    \
        if (!ptr->HasProperty(id)) {                                                \
            return std::any();                                                      \
        }                                                                           \
        return ptr->GetProperty(id);                                                \
    }                                                                               \
                                                                                    \
    EXTERN void SetProperty(const std::string& id, const std::any& val) {           \
        auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>();         \
                                                                                    \
        if (!ptr) {                                                                 \
            return;                                                                 \
        }                                                                           \
                                                                                    \
        if (!ptr->HasProperty(id)) {                                                \
            return;                                                                 \
        }                                                                           \
        return ptr->SetProperty(id, val);                                           \
    }                                                                               \
                                                                                    \
    EXTERN std::vector<std::string> GetProperties() {                               \
        if (auto&& ptr = g_codegen_behaviour_ptr.ReinterpretCast<className*>()) {   \
            return ptr->GetProperties();                                            \
        }                                                                           \
        return {};                                                                  \
    }                                                                               \

#define REGISTER_BEHAVIOUR(className)                                               \
    SharedPtr<void> g_codegen_behaviour_ptr;                                        \
    EXTERN void InitBehaviour() {                                                   \
        g_codegen_behaviour_ptr = (void*)(new className());                         \
    }                                                                               \
                                                                                    \
    EXTERN void ReleaseBehaviour() {                                                \
        g_codegen_behaviour_ptr.AutoFree([](void* ptr) {                            \
            delete reinterpret_cast<className*>(ptr);                               \
        });                                                                         \
    }                                                                               \
                                                                                    \
    EXTERN SharedPtr<void> GetBehaviourPtr() {                                      \
        return g_codegen_behaviour_ptr;                                             \
    }                                                                               \
                                                                                    \
    REGISTER_BEHAVIOUR_BASE(className)                                              \
    REGISTER_BEHAVIOUR_PROPERTIES(className)                                        \



#endif //EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
