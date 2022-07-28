//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_PHYSICSSCENE_H
#define SRENGINE_PHYSICSSCENE_H

#include <Physics/PhysicsLib.h>
#include <Utils/Types/SafePointer.h>

namespace SR_PHYSICS_NS {
    class PhysicsScene : public SR_HTYPES_NS::SafePtr<PhysicsScene> {
        friend class SR_HTYPES_NS::SafePtr<PhysicsScene>;
        using Super = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        PhysicsScene();
        ~PhysicsScene();

    public:
        bool Init();
        void Close();

    private:
        bool CreateDynamicWorld();

    private:
        btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
        btBroadphaseInterface* m_broadphase = nullptr;
        btCollisionDispatcher* m_dispatcher = nullptr;
        btConstraintSolver* m_solver = nullptr;
        btDefaultCollisionConfiguration* m_collisionConfiguration = nullptr;
        btDiscreteDynamicsWorld* m_dynamicsWorld = nullptr;

    };
}

#endif //SRENGINE_PHYSICSSCENE_H
