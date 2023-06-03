//
// Created by Monika on 24.11.2022.
//

#ifndef SRENGINE_PHYSXLIBRARYIMPL_H
#define SRENGINE_PHYSXLIBRARYIMPL_H

#include <Physics/LibraryImpl.h>
#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PHYSICS_NS {
    class PhysXLibraryImpl : public SR_PHYSICS_NS::LibraryImpl {
        using Super = SR_PHYSICS_NS::LibraryImpl;
    public:
        PhysXLibraryImpl() = default;
        ~PhysXLibraryImpl() override;

    public:
        SR_NODISCARD bool Initialize() override;

        SR_NODISCARD bool IsShapeSupported(ShapeType type) const override;
        SR_NODISCARD ShapeType GetDefaultShape() const override { return ShapeType::Box3D; }

        SR_NODISCARD SR_PTYPES_NS::CollisionShape* CreateCollisionShape() override;
        SR_NODISCARD SR_PTYPES_NS::Rigidbody3D* CreateRigidbody3D() override;
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) override;

        SR_NODISCARD virtual SR_PTYPES_NS::Vehicle4W3D* CreateVehicle4W3D() override;

        SR_NODISCARD SR_PTYPES_NS::PhysicsMaterialImpl* CreatePhysicsMaterial() override;

    public:
        SR_NODISCARD physx::PxPhysics* GetPxPhysics() const { return m_physics; }

    private:
        physx::PxErrorCallback* m_errorCallback = nullptr;
        physx::PxAllocatorCallback* m_allocatorCallback = nullptr;

        physx::PxPhysics* m_physics = nullptr;
        physx::PxFoundation* m_foundation = nullptr;

        PhysXPvdConnection* m_pvd = nullptr;
        physx::PxPvdTransport* m_pvdTransport = nullptr;

    };
}

#endif //SRENGINE_PHYSXLIBRARYIMPL_H
