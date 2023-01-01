//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_BULLET3PHYSICSWORLD_H
#define SRENGINE_BULLET3PHYSICSWORLD_H

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

#endif //SRENGINE_BULLET3PHYSICSWORLD_H
