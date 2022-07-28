//
// Created by Monika on 28.07.2022.
//

#ifndef SRENGINE_RIGIDBODY_H
#define SRENGINE_RIGIDBODY_H

#include <Physics/PhysicsLib.h>
#include <Utils/ECS/Component.h>

namespace SR_PHYSICS_NS::Types {
    class Rigidbody : public SR_UTILS_NS::Component {
    public:
        Rigidbody();
        ~Rigidbody() override = default;

    protected:
        void OnAttached() override;

        void OnDestroy() override;

        void OnDisabled() override;
        void OnEnabled() override;

    private:
        btRigidBody* m_rigidbody = nullptr;

    };
}

#endif //SRENGINE_RIGIDBODY_H
