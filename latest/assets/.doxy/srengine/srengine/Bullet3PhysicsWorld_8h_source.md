

# File Bullet3PhysicsWorld.h

[**File List**](files.md) **>** [**Bullet3**](dir_b49b257c816fcf8e49fc788b011f4b07.md) **>** [**Bullet3PhysicsWorld.h**](Bullet3PhysicsWorld_8h.md)

[Go to the documentation of this file](Bullet3PhysicsWorld_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_BULLET3PHYSICSWORLD_H
#define SR_ENGINE_BULLET3PHYSICSWORLD_H

#include <Physics/Bullet3/Bullet3PhysicsLib.h>
#include <Physics/PhysicsWorld.h>

namespace SR_PHYSICS_NS {
    class Bullet3PhysicsWorld : public PhysicsWorld {
        using Super = PhysicsWorld;
    public:
        explicit Bullet3PhysicsWorld(LibraryPtr pLibrary, Space space);
        ~Bullet3PhysicsWorld() override;

    public:
        bool Initialize() override;
        bool ClearForces() override;
        bool Synchronize() override;

        bool StepSimulation(float_t step) override;

        bool AddRigidbody(RigidbodyPtr pRigidbody) override;
        bool RemoveRigidbody(RigidbodyPtr pRigidbody) override;

    private:
        btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
        btBroadphaseInterface* m_broadPhase = nullptr;
        btCollisionDispatcher* m_dispatcher = nullptr;
        btConstraintSolver* m_solver = nullptr;
        btDefaultCollisionConfiguration* m_collisionConfiguration = nullptr;
        btDiscreteDynamicsWorld* m_dynamicsWorld = nullptr;

    };
}

#endif //SR_ENGINE_BULLET3PHYSICSWORLD_H
```


