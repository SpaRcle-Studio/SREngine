

# File PhysXLibraryImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXLibraryImpl.h**](PhysXLibraryImpl_8h.md)

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


