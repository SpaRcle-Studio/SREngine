

# File PhysXLibraryImpl.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXLibraryImpl.h**](PhysXLibraryImpl_8h.md)

[Go to the documentation of this file](PhysXLibraryImpl_8h.md)


```C++
//
// Created by Monika on 24.11.2022.
//

#ifndef SR_ENGINE_PHYSXLIBRARYIMPL_H
#define SR_ENGINE_PHYSXLIBRARYIMPL_H

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

        void ConnectPVD() override;

        SR_NODISCARD bool IsShapeSupported(ShapeType type) const override;
        SR_NODISCARD ShapeType GetDefaultShape() const override { return ShapeType::Box3D; }

        SR_NODISCARD SR_PTYPES_NS::CollisionShapeImpl* CreateCollisionShapeImpl() override;
        SR_NODISCARD SR_PTYPES_NS::Rigidbody3DImpl* CreateRigidbody3DImpl() override;
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) override;

        SR_NODISCARD SR_PTYPES_NS::Vehicle4W3D* CreateVehicle4W3D() override;

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

#endif //SR_ENGINE_PHYSXLIBRARYIMPL_H
```


