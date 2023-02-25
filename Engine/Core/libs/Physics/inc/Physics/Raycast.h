//
// Created by innerviewer on 2/15/2023.
//

#ifndef SRENGINE_RAYCAST_H
#define SRENGINE_RAYCAST_H

#include <Utils/Common/RaycastHit.h>

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class Raycast {
    public:
        using RaycastHits = std::vector<SR_UTILS_NS::RaycastHit>;

    public:
        virtual ~Raycast() = default;

        void SwitchPhysics(SR_PHYSICS_NS::PhysicsWorld* pWorld) { m_world = pWorld; }

    protected:
        SR_PHYSICS_NS::PhysicsWorld* m_world = nullptr;
    };
}

#endif //SRENGINE_RAYCAST_H
