//
// Created by innerviewer on 21.01.2023.
//

#ifndef SRENGINE_PHYSXSIMULATIONCALLBACK_H
#define SRENGINE_PHYSXSIMULATIONCALLBACK_H

#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PHYSICS_NS {
    class ContactReportCallback : public physx::PxSimulationEventCallback {
    public:
        void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override { };
        void onWake(physx::PxActor** actors, physx::PxU32 count) override { };
        void onSleep(physx::PxActor** actors, physx::PxU32 count) override { };
        void onContact(const physx::PxContactPairHeader &pairHeader, const physx::PxContactPair *pairs, physx::PxU32 nbPairs) override;
        void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) override { };
        void onAdvance(const physx::PxRigidBody*const* bodyBuffer, const physx::PxTransform* poseBuffer, const physx::PxU32 count) override { };
    };
}

#endif //SRENGINE_PHYSXSIMULATIONCALLBACK_H
