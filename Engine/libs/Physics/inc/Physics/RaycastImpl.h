//
// Created by innerviewer on 2/16/2023.
//

#ifndef SR_ENGINE_RAYCASTIMPL_H
#define SR_ENGINE_RAYCASTIMPL_H

#include <Physics/macros.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/RaycastHit.h>

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class RayCastImpl : public SR_UTILS_NS::NonCopyable {
    public:
        using RayCastHits = SR_UTILS_NS::Vector<SR_UTILS_NS::RayCastHit>;

    public:
        explicit RayCastImpl(SR_PHYSICS_NS::PhysicsWorld* world)
            : m_world(world)
        { }

        ~RayCastImpl() override = default;

    protected:
        SR_PHYSICS_NS::PhysicsWorld* m_world = nullptr;
    };
}

#endif //SR_ENGINE_RAYCASTIMPL_H
