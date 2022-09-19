//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_COLLIDER_H
#define SRENGINE_COLLIDER_H

#include <Utils/ECS/Component.h>
#include <Physics/PhysicsLib.h>

namespace SR_PHYSICS_NS::Types {
    class Collider : public SR_UTILS_NS::Component {
        friend class SR_PHYSICS_NS::PhysicsScene;
        using PhysicsScenePtr = SR_HTYPES_NS::SafePtr<PhysicsScene>;
    public:
        ~Collider() override;

        void OnAttached() override;
        void OnDestroy() override;
        void OnMatrixDirty() override;

        PhysicsScenePtr GetPhysicsScene();

    private:
        PhysicsScenePtr m_physicsScene;

        btRigidBody* m_rigidbody = nullptr;
        btMotionState* m_motionState = nullptr;
        btCollisionShape* m_shape = nullptr;
        //btCollisionObject* m_collider = nullptr;

    };
}

#endif //SRENGINE_COLLIDER_H
