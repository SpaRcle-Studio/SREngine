//
// Created by Monika on 22.11.2022.
//

#ifndef SRENGINE_LIBRARYIMPL_H
#define SRENGINE_LIBRARYIMPL_H

#include <Physics/Utils/Utils.h>

namespace SR_PTYPES_NS {
    class Rigidbody2D;
    class Rigidbody3D;
    class CollisionShape;
    class PhysicsMaterialImpl;
}

namespace SR_PHYSICS_NS {
    class PhysicsWorld;
}

namespace SR_PHYSICS_NS {
    class LibraryImpl : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using Space = SR_UTILS_NS::Measurement;
    public:
        LibraryImpl();
        ~LibraryImpl() override = default;

    public:
        SR_NODISCARD virtual bool Initialize();

        SR_NODISCARD virtual bool IsShapeSupported(ShapeType type) const { return false; }
        SR_NODISCARD virtual ShapeType GetDefaultShape() const { return ShapeType::Unknown; }

        SR_NODISCARD virtual SR_PTYPES_NS::CollisionShape* CreateCollisionShape() { return nullptr; }

        SR_NODISCARD virtual SR_PTYPES_NS::Rigidbody2D* CreateRigidbody2D() { return nullptr; }
        SR_NODISCARD virtual SR_PTYPES_NS::Rigidbody3D* CreateRigidbody3D() { return nullptr; }

        SR_NODISCARD virtual SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) { return nullptr; }

        SR_NODISCARD virtual SR_PTYPES_NS::PhysicsMaterialImpl* CreatePhysicsMaterial() { return nullptr; }

        SR_NODISCARD bool IsVehicleSupported() const noexcept { return m_isVehicleSupported; }

    private:
        bool m_isVehicleSupported = false;
    };
}

#endif //SRENGINE_LIBRARYIMPL_H
