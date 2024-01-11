//
// Created by Monika on 24.11.2022.
//

#ifndef SR_ENGINE_PHYSXPHYSICSWORLD_H
#define SR_ENGINE_PHYSXPHYSICSWORLD_H

#include <Physics/PhysX/PhysXUtils.h>
#include <Physics/PhysicsWorld.h>

namespace SR_PTYPES_NS {
    class Rigidbody;
}

namespace SR_PHYSICS_NS {
    class ContactReportCallback;
    class PhysXPhysicsWorld : public PhysicsWorld {
        using Super = PhysicsWorld;
    public:
        explicit PhysXPhysicsWorld(LibraryPtr pLibrary, Space space);
        ~PhysXPhysicsWorld() override;

    public:
        bool Initialize() override;
        bool ClearForces() override;
        bool Synchronize() override;

        bool StepSimulation(float_t step) override;

        bool AddRigidbody(RigidbodyPtr pRigidbody) override;
        bool RemoveRigidbody(RigidbodyPtr pRigidbody) override;

        void ForEachRigidbody3D(const SR_HTYPES_NS::Function<void(SR_PTYPES_NS::Rigidbody3D *)> &fun) override;

        void Flush() override;

    private:
        bool SynchronizeStatic();
        bool SynchronizeDynamic();

    private:
        physx::PxScene* m_scene = nullptr;
        physx::PxDefaultCpuDispatcher* m_cpuDispatcher = nullptr;
        ContactReportCallback* m_contactCallback = nullptr;

        std::vector<physx::PxActor*> m_dynamicActors;
        std::vector<physx::PxActor*> m_staticActors;
        std::vector<physx::PxActor*> m_actors;

    };
}

#endif //SR_ENGINE_PHYSXPHYSICSWORLD_H
