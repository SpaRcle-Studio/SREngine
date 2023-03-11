//
// Created by Monika on 23.05.2022.
//

#ifndef EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
#define EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H

#include <Libraries/Utils/ModuleCore.h>

#define REGISTER_BEHAVIOUR_METHOD(className, methodName)                                                                \
   EXTERN void methodName() {                                                                                           \
        if (auto&& ptr = gBehaviourContext->pBehaviour.ReinterpretCast<className*>()) {                                 \
            ptr->methodName();                                                                                          \
        }                                                                                                               \
    }                                                                                                                   \

#define REGISTER_BEHAVIOUR_METHOD_ARGS(className, methodName, argA, argB)                                               \
   EXTERN void methodName(argA) {                                                                                       \
        if (auto&& ptr = gBehaviourContext->pBehaviour.ReinterpretCast<className*>()) {                                 \
            ptr->methodName(argB);                                                                                      \
        }                                                                                                               \
    }                                                                                                                   \

#define REGISTER_BEHAVIOUR_BASE(className)                                                                              \
    REGISTER_BEHAVIOUR_METHOD(className, Awake)                                                                         \
    REGISTER_BEHAVIOUR_METHOD(className, Start)                                                                         \
    REGISTER_BEHAVIOUR_METHOD(className, OnEnable)                                                                      \
    REGISTER_BEHAVIOUR_METHOD(className, OnDisable)                                                                     \
    REGISTER_BEHAVIOUR_METHOD(className, FixedUpdate)                                                                   \
    REGISTER_BEHAVIOUR_METHOD(className, Close)                                                                         \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, Update, ESArg1(float_t dt), ESArg1(dt))                                   \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, SetGameObject, ESArg1(Behaviour::GameObjectPtr gm), ESArg1(gm))           \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, SetScene, ESArg1(Behaviour::ScenePtr scene), ESArg1(scene))               \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnCollisionEnter, ESArg1(const CollisionData& data), ESArg1(data))        \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnCollisionStay, ESArg1(const CollisionData& data), ESArg1(data))         \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnCollisionExit, ESArg1(const CollisionData& data), ESArg1(data))         \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnTriggerEnter, ESArg1(const CollisionData& data), ESArg1(data))          \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnTriggerStay, ESArg1(const CollisionData& data), ESArg1(data))           \
    REGISTER_BEHAVIOUR_METHOD_ARGS(className, OnTriggerExit, ESArg1(const CollisionData& data), ESArg1(data))           \

#define REGISTER_BEHAVIOUR_PROPERTIES(className)                                                                        \
    EXTERN std::any GetProperty(const std::string& id) {                                                                \
        auto&& ptr = gBehaviourContext->pBehaviour.ReinterpretCast<className*>();                                       \
                                                                                                                        \
        if (!ptr) {                                                                                                     \
            return std::any();                                                                                          \
        }                                                                                                               \
                                                                                                                        \
        if (!ptr->HasProperty(id)) {                                                                                    \
            return std::any();                                                                                          \
        }                                                                                                               \
        return ptr->GetProperty(id);                                                                                    \
    }                                                                                                                   \
                                                                                                                        \
    EXTERN void SetProperty(const std::string& id, const std::any& val) {                                               \
        auto&& ptr = gBehaviourContext->pBehaviour.ReinterpretCast<className*>();                                       \
                                                                                                                        \
        if (!ptr) {                                                                                                     \
            return;                                                                                                     \
        }                                                                                                               \
                                                                                                                        \
        if (!ptr->HasProperty(id)) {                                                                                    \
            return;                                                                                                     \
        }                                                                                                               \
        return ptr->SetProperty(id, val);                                                                               \
    }                                                                                                                   \
                                                                                                                        \
    EXTERN std::vector<std::string> GetProperties() {                                                                   \
        if (auto&& ptr = gBehaviourContext->pBehaviour.ReinterpretCast<className*>()) {                                 \
            return ptr->GetProperties();                                                                                \
        }                                                                                                               \
        return {};                                                                                                      \
    }                                                                                                                   \

#define REGISTER_BEHAVIOUR(className)                                                                                   \
    EXTERN void* InitBehaviour() {                                                                                      \
        if (!gBehaviourContext) {                                                                                       \
            gBehaviourContext = new BehaviourContext();                                                                 \
            ++gBehavioursCount;                                                                                         \
            gBehaviourContext->pBehaviour = new className();                                                            \
            return (void*)gBehaviourContext;                                                                            \
        }                                                                                                               \
                                                                                                                        \
        return nullptr;                                                                                                 \
    }                                                                                                                   \
                                                                                                                        \
    EXTERN void SwitchContext(void* pContext) {                                                                         \
        gBehaviourContext = (BehaviourContext*)pContext;                                                                \
    }                                                                                                                   \
                                                                                                                        \
    EXTERN void ReleaseBehaviour() {                                                                                    \
        if (gBehaviourContext) {                                                                                        \
            gBehaviourContext->pBehaviour.AutoFree([](void* ptr) {                                                      \
				delete reinterpret_cast<className*>(ptr);                                                               \
			});                                                                                                         \
                                                                                                                        \
            if (gBehaviourContext->pBehaviour.Valid()) {                                                                \
                Debug::Halt("pBehaviour is valid!");                                                                    \
            }                                                                                                           \
                                                                                                                        \
            delete gBehaviourContext;                                                                                   \
            gBehaviourContext = nullptr;                                                                                \
                                                                                                                        \
            --gBehavioursCount;                                                                                         \
        }                                                                                                               \
    }                                                                                                                   \
                                                                                                                        \
    EXTERN SharedPtr<void> GetBehaviourPtr() {                                                                          \
        return gBehaviourContext ? gBehaviourContext->pBehaviour : SharedPtr<void>(nullptr);                            \
    }                                                                                                                   \
                                                                                                                        \
    REGISTER_BEHAVIOUR_BASE(className)                                                                                  \
    REGISTER_BEHAVIOUR_PROPERTIES(className)                                                                            \



#endif //EVOSCRIPTLIB_BEHAVIOURREGISTRATION_H
