

# File PhysXPhysicsWorld.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXPhysicsWorld.h**](PhysXPhysicsWorld_8h.md)

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


