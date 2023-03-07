//
// Created by Monika on 05.03.2023.
//

#ifndef EVOSCRIPTLIB_MODULECORE_H
#define EVOSCRIPTLIB_MODULECORE_H

#pragma warning (disable: 4190)

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Utils/NonCopyable.h>
#include <Libraries/Types/SharedPtr.h>
#include <Libraries/Utils/Args.h>

#include <Libraries/GameObject.h>

#ifndef EXTERN
    #define EXTERN extern "C" __declspec(dllexport)
#endif

struct CollisionData {
    void* pHandler = nullptr;
    FVector3 point;
    FVector3 impulse;
};

struct RaycastHit {
    void* pHandler = nullptr;
    FVector3 position;
    FVector3 normal;
    float_t distance;
};

class Behaviour;

struct BehaviourContext {
    SharedPtr<void> pBehaviour;
    std::vector<std::function<void()>> propertiesRegistrations;
};

uint64_t gBehavioursCount = 0;
BehaviourContext* gBehaviourContext = nullptr;

EXTERN void InitModule() {

}

EXTERN void DeInitModule() {

}

#endif //EVOSCRIPTLIB_MODULECORE_H
