

# File LibraryImpl.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**LibraryImpl.h**](LibraryImpl_8h.md)

[Go to the documentation of this file](LibraryImpl_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_LIBRARYIMPL_H
#define SR_ENGINE_LIBRARYIMPL_H

#include <Physics/macros.h>

#include <Physics/Utils/Utils.h>

namespace SR_PTYPES_NS {
    class Rigidbody2DImpl;
    class Rigidbody3DImpl;
    class CollisionShapeImpl;
    class PhysicsMaterialImpl;
    class Vehicle4W3D;
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

        virtual void ConnectPVD() { }

        SR_NODISCARD virtual bool IsShapeSupported(ShapeType type) const { return false; }
        SR_NODISCARD virtual ShapeType GetDefaultShape() const { return ShapeType::Unknown; }

        SR_NODISCARD virtual SR_PTYPES_NS::CollisionShapeImpl* CreateCollisionShapeImpl() { return nullptr; }

        SR_NODISCARD virtual SR_PTYPES_NS::Rigidbody2DImpl* CreateRigidbody2DImpl() { SRHalt("Not implemented!"); return nullptr; }
        SR_NODISCARD virtual SR_PTYPES_NS::Rigidbody3DImpl* CreateRigidbody3DImpl() { SRHalt("Not implemented!"); return nullptr; }

        SR_NODISCARD virtual SR_PTYPES_NS::Vehicle4W3D* CreateVehicle4W3D() { return nullptr; }

        SR_NODISCARD virtual SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) { return nullptr; }

        SR_NODISCARD virtual SR_PTYPES_NS::PhysicsMaterialImpl* CreatePhysicsMaterial() { return nullptr; }

        SR_NODISCARD bool IsVehicleSupported() const noexcept { return m_isVehicleSupported; }

    private:
        bool m_isVehicleSupported = false;
    };
}

#endif //SR_ENGINE_LIBRARYIMPL_H
```


