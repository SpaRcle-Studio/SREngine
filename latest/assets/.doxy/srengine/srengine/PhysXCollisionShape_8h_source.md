

# File PhysXCollisionShape.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Physics**](dir_519f717f3cdf5b5486fbfb20b03d90e0.md) **>** [**inc**](dir_caed82ebc61f04cfe4cf46381d77d744.md) **>** [**Physics**](dir_0ab9965f62ec4b8feb4217f1d72c6eed.md) **>** [**PhysX**](dir_ff2872f47b85400c7459df934950f633.md) **>** [**PhysXCollisionShape.h**](PhysXCollisionShape_8h.md)

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


