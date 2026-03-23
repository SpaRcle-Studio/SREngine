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
        std::optional<bool> UpdateShape() override;
        bool UpdateMatrix() override;

        SR_NODISCARD physx::PxMaterial* GetMaterial() const;

        SR_NODISCARD physx::PxConvexMesh* CreateConvexMesh(SR_HTYPES_NS::RawMesh* pRawMesh);
        SR_NODISCARD physx::PxTriangleMesh* CreateTriangleMesh(SR_HTYPES_NS::RawMesh* pRawMesh);

        SR_NODISCARD const std::vector<void*>& GetHandles() const noexcept override;

    private:
        void ReleaseShapes();

    private:
        mutable std::vector<void*> m_handles;
        std::vector<physx::PxShape*> m_shapes;
        ShapeType m_currentShapeType = ShapeType::Unknown;
        SR_MATH_NS::FVector3 m_currentBounds;
        bool m_isTrigger = false;

    };
}

#endif //SR_ENGINE_PHYSX_COLLISION_SHAPE_H
