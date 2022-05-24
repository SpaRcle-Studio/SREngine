//
// Created by Monika on 23.05.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
#define EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H

#include "NonCopyable.h"

#define REGISTER_BEHAVIOUR(className)               \
    Behaviour* g_codegen_behaviour_ptr;             \
    EXTERN void InitBehaviour() {                   \
        g_codegen_behaviour_ptr = new className();  \
    }                                               \
                                                    \
    EXTERN void ReleaseBehaviour() {                \
        delete g_codegen_behaviour_ptr;             \
    }                                               \
                                                    \
    EXTERN void Awake() {                           \
        g_codegen_behaviour_ptr->Awake();           \
    }                                               \
                                                    \
    EXTERN void Start() {                           \
        g_codegen_behaviour_ptr->Start();           \
    }                                               \
                                                    \
    EXTERN void Update(float_t dt) {                \
        g_codegen_behaviour_ptr->Update(dt);        \
    }                                               \
                                                    \
    EXTERN void Close() {                           \
        g_codegen_behaviour_ptr->Close();           \
    }                                               \

#endif //EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
