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
} // namespace SR_PTYPES_NS

#endif // SR_ENGINE_PHYSX_COLLISION_SHAPE_H
