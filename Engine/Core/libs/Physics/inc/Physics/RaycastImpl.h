//
// Created by innerviewer on 2/16/2023.
//

#ifndef SRENGINE_RAYCASTIMPL_H
#define SRENGINE_RAYCASTIMPL_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/RaycastHit.h>

namespace SR_PHYSICS_NS {
    class PhysicsWorld;

    class RaycastImpl : public SR_UTILS_NS::NonCopyable {
    public:
        using RaycastHits = std::vector<SR_UTILS_NS::RaycastHit>;

    public:
        explicit RaycastImpl(SR_PHYSICS_NS::PhysicsWorld* world)
            : m_world(world)
        { }

        ~RaycastImpl() override = default;

    protected:
        SR_PHYSICS_NS::PhysicsWorld* m_world = nullptr;
    };
}

#endif //SRENGINE_RAYCASTIMPL_H
