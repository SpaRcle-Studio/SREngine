

# File PhysXSimulationCallback.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXSimulationCallback.h**](PhysXSimulationCallback_8h.md)

[Go to the documentation of this file](PhysXSimulationCallback_8h.md)


```C++
//
// Created by innerviewer on 21.01.2023.
//

#ifndef SR_ENGINE_PHYSXSIMULATIONCALLBACK_H
#define SR_ENGINE_PHYSXSIMULATIONCALLBACK_H

#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PHYSICS_NS {
    class ContactReportCallback : public physx::PxSimulationEventCallback {
    public:
        void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override { };
        void onWake(physx::PxActor** actors, physx::PxU32 count) override { };
        void onSleep(physx::PxActor** actors, physx::PxU32 count) override { };
        void onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs, physx::PxU32 nbPairs) override;
        void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override;
        void onAdvance(const physx::PxRigidBody*const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override { };
    };
}

#endif //SR_ENGINE_PHYSXSIMULATIONCALLBACK_H
```


