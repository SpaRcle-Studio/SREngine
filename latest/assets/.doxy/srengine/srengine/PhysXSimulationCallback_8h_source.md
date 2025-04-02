

# File PhysXSimulationCallback.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXSimulationCallback.h**](PhysXSimulationCallback_8h.md)

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


