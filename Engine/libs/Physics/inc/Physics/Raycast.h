//
// Created by innerviewer on 2/15/2023.
//

#ifndef SR_ENGINE_RAYCAST_H
#define SR_ENGINE_RAYCAST_H

#include <Physics/stdInclude.h>

#include <Utils/Common/RaycastHit.h>
#include <Utils/Types/Vector.h>

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class RayCast {
    public:
    public:
        virtual ~RayCast() = default;

        void SwitchPhysics(SR_PHYSICS_NS::PhysicsWorld* pWorld) { m_world = pWorld; }

    protected:
        SR_PHYSICS_NS::PhysicsWorld* m_world = nullptr;
    };
}

#endif //SR_ENGINE_RAYCAST_H
