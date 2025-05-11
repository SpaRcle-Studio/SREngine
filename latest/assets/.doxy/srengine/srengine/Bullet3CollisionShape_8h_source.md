

# File Bullet3CollisionShape.h

[**File List**](files.md) **>** [**Bullet3**](dir_b49b257c816fcf8e49fc788b011f4b07.md) **>** [**Bullet3CollisionShape.h**](Bullet3CollisionShape_8h.md)

[Go to the documentation of this file](Bullet3CollisionShape_8h.md)


```C++
//
// Created by Monika on 22.11.2022.
//

#ifndef SR_ENGINE_BULLET3COLLISIONSHAPE_H
#define SR_ENGINE_BULLET3COLLISIONSHAPE_H

#include <Physics/CollisionShape.h>

#include <Physics/Bullet3/Bullet3PhysicsLib.h>

namespace SR_PTYPES_NS {
    class Bullet3CollisionShape : public CollisionShape {
        using Super = CollisionShape;
    public:
        Bullet3CollisionShape(LibraryPtr pLibrary);
        ~Bullet3CollisionShape() override;

    public:
        SR_NODISCARD void* GetHandle() const noexcept override { return m_shape; }

        bool UpdateShape() override;
        bool UpdateMatrix() override;

        SR_NODISCARD SR_MATH_NS::FVector3 CalculateLocalInertia(float_t mass) const override;

    private:
        btCollisionShape* m_shape = nullptr;

    };
}

#endif //SR_ENGINE_BULLET3COLLISIONSHAPE_H
```


