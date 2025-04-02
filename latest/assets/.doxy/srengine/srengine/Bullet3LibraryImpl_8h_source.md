

# File Bullet3LibraryImpl.h

[**File List**](files.md) **>** [**Bullet3**](dir_d808912b90bd0713ac82f52ede71578e.md) **>** [**Bullet3LibraryImpl.h**](Bullet3LibraryImpl_8h.md)

[Go to the documentation of this file](Bullet3LibraryImpl_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_BULLET3LIBRARYIMPL_H
#define SR_ENGINE_BULLET3LIBRARYIMPL_H

#include <Physics/LibraryImpl.h>

namespace SR_PHYSICS_NS {
    class Bullet3LibraryImpl : public SR_PHYSICS_NS::LibraryImpl {
        using Super = SR_PHYSICS_NS::LibraryImpl;
    public:
        Bullet3LibraryImpl() = default;
        ~Bullet3LibraryImpl() override = default;

    public:
        SR_NODISCARD bool Initialize() override { return true; }

        SR_NODISCARD bool IsShapeSupported(ShapeType type) const override;
        SR_NODISCARD ShapeType GetDefaultShape() const override { return ShapeType::Box3D; }

        SR_NODISCARD SR_PTYPES_NS::CollisionShape* CreateCollisionShape() override;
        SR_NODISCARD SR_PTYPES_NS::Rigidbody3D* CreateRigidbody3D() override;
        SR_NODISCARD SR_PHYSICS_NS::PhysicsWorld* CreatePhysicsWorld(Space space) override;

    };
}

#endif //SR_ENGINE_BULLET3LIBRARYIMPL_H
```


