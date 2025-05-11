

# File PhysXCollisionShape.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Physics**](dir_b6093f632646a02ac714961018ea77eb.md) **>** [**inc**](dir_c3db09d6a2a4255c529e8dd3a426d758.md) **>** [**Physics**](dir_d2d325d8d5dbff54ef03880cbcd3bb2d.md) **>** [**PhysX**](dir_3ad88c97ba0c5fb710f861c6ad44644a.md) **>** [**PhysXCollisionShape.h**](PhysXCollisionShape_8h.md)

[Go to the documentation of this file](PhysXCollisionShape_8h.md)


```C++
//
// Created by Monika on 25.11.2022.
//

#ifndef SR_ENGINE_PHYSX_COLLISION_SHAPE_H
#define SR_ENGINE_PHYSX_COLLISION_SHAPE_H

#include <Physics/CollisionShape.h>

#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PTYPES_NS {
    class PhysXCollisionShape : public CollisionShapeImpl {
        using Super = CollisionShape;
    public:
        ~PhysXCollisionShape() override;

    public:
        bool UpdateShape() override;
        bool UpdateMatrix() override;

        SR_NODISCARD physx::PxMaterial* GetMaterial() const;

        SR_NODISCARD physx::PxConvexMesh* CreateConvexMesh(SR_HTYPES_NS::RawMesh* pRawMesh);
        SR_NODISCARD physx::PxTriangleMesh* CreateTriangleMesh(SR_HTYPES_NS::RawMesh* pRawMesh);

        SR_NODISCARD void* GetHandle() const noexcept override { return m_shape; }

    private:
        physx::PxShape* m_shape = nullptr;

    };
}

#endif //SR_ENGINE_PHYSX_COLLISION_SHAPE_H
```


