//
// Created by Monika on 25.11.2022.
//

#ifndef SRENGINE_PHYSXCOLLISIONSHAPE_H
#define SRENGINE_PHYSXCOLLISIONSHAPE_H

#include <Physics/CollisionShape.h>

#include <Physics/PhysX/PhysXUtils.h>

namespace SR_PTYPES_NS {
    class PhysXCollisionShape : public CollisionShape {
        using Super = CollisionShape;
    public:
        explicit PhysXCollisionShape(LibraryPtr pLibrary);
        ~PhysXCollisionShape() override;

    public:
        bool UpdateShape() override;
        bool UpdateMatrix() override;

        physx::PxConvexMesh* CreateConvexMesh(SR_HTYPES_NS::RawMesh* pRawMesh);
        physx::PxTriangleMesh* CreateTriangleMesh(SR_HTYPES_NS::RawMesh* pRawMesh);

        SR_NODISCARD void* GetHandle() const noexcept override { return m_shape; }

    private:
        physx::PxShape* m_shape = nullptr;
    };
}

#endif //SRENGINE_PHYSXCOLLISIONSHAPE_H
