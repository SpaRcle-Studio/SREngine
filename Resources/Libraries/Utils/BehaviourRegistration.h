//
// Created by Monika on 23.05.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
#define EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H

#include "NonCopyable.h"

#pragma warning (disable: 4190)

#ifndef EXTERN
    #define EXTERN extern "C" __declspec(dllexport)
#endif

#define REGISTER_BEHAVIOUR_BASE                                           \
    EXTERN void Awake() {                                                 \
        g_codegen_behaviour_ptr->Awake();                                 \
    }                                                                     \
                                                                          \
    EXTERN void Start() {                                                 \
        g_codegen_behaviour_ptr->Start();                                 \
    }                                                                     \
                                                                          \
    EXTERN void OnDisable() {                                             \
        g_codegen_behaviour_ptr->OnDisable();                             \
    }                                                                     \
                                                                          \
    EXTERN void OnEnable() {                                              \
        g_codegen_behaviour_ptr->OnEnable();                              \
    }                                                                     \
                                                                          \
    EXTERN void Update(float_t dt) {                                      \
        g_codegen_behaviour_ptr->Update(dt);                              \
    }                                                                     \
                                                                          \
    EXTERN void Close() {                                                 \
        g_codegen_behaviour_ptr->Close();                                 \
    }                                                                     \

#define REGISTER_BEHAVIOUR_PROPERTIES                                     \
    EXTERN std::any GetProperty(const std::string& id) {                  \
        if (!g_codegen_behaviour_ptr->HasProperty(id)) {                  \
            return std::any();                                            \
        }                                                                 \
        return g_codegen_behaviour_ptr->GetProperty(id);                  \
    }                                                                     \
                                                                          \
    EXTERN void SetProperty(const std::string& id, const std::any& val) { \
        if (!g_codegen_behaviour_ptr->HasProperty(id)) {                  \
            return;                                                       \
        }                                                                 \
        return g_codegen_behaviour_ptr->SetProperty(id, val);             \
    }                                                                     \
                                                                          \
    EXTERN std::vector<std::string> GetProperties() {                     \
        return g_codegen_behaviour_ptr->GetProperties();                  \
    }                                                                     \

#define REGISTER_BEHAVIOUR(className)                                     \
    Behaviour* g_codegen_behaviour_ptr;                                   \
    EXTERN void InitBehaviour() {                                         \
        g_codegen_behaviour_ptr = new className();                        \
    }                                                                     \
                                                                          \
    EXTERN void ReleaseBehaviour() {                                      \
        delete g_codegen_behaviour_ptr;                                   \
    }                                                                     \
                                                                          \
    REGISTER_BEHAVIOUR_BASE                                               \
    REGISTER_BEHAVIOUR_PROPERTIES                                         \



#endif //EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
