

# File PhysXPhysicsWorld.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXPhysicsWorld.h**](PhysXPhysicsWorld_8h.md)

[Go to the documentation of this file](PhysXPhysicsWorld_8h.md)


```C++
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
```


