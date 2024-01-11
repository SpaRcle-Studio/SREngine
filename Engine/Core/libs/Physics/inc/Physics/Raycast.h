//
// Created by innerviewer on 2/15/2023.
//

#ifndef SR_ENGINE_RAYCAST_H
#define SR_ENGINE_RAYCAST_H

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

#endif //SR_ENGINE_RAYCAST_H
