//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_LIBRARYIMPL_H
#define SRENGINE_LIBRARYIMPL_H

#include <Physics/Utils/Utils.h>

namespace SR_PTYPES_NS {
    class Rigidbody3D;
    class CollisionShape;
}

namespace SR_PHYSICS_NS {
    class PhysicsWorld;
}

namespace SR_PHYSICS_NS {
    class LibraryImpl : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        LibraryImpl();
        ~LibraryImpl() override = default;

    public:
        SR_NODISCARD virtual bool IsShapeSupported(ShapeType type) const { return false; }
        SR_NODISCARD virtual ShapeType GetDefaultShape() const { return ShapeType::Unknown; }

        SR_NODISCARD virtual SR_PTYPES_NS::CollisionShape* CreateCollisionShape(ShapeType type) { return nullptr; }
        SR_NODISCARD virtual SR_PTYPES_NS::Rigidbody3D* CreateRigidbody3D(ShapeType type) { return nullptr; }

        SR_NODISCARD virtual SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld() { return nullptr; }

    };
}

#endif //SRENGINE_LIBRARYIMPL_H
