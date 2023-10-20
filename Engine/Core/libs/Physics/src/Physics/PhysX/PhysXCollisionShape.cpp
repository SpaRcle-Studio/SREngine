//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXCollisionShape.h>
#include <Physics/PhysX/PhysXRigidbody3D.h>

namespace SR_PTYPES_NS {
    PhysXCollisionShape::PhysXCollisionShape(Super::LibraryPtr pLibrary)
        : Super(pLibrary)
    { }

    PhysXCollisionShape::~PhysXCollisionShape() {
        if (m_shape) {
            m_shape->userData = nullptr;
            m_shape->release();
            m_shape = nullptr;
        }
    }

    bool PhysXCollisionShape::UpdateShape() {
        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        if (m_shape) {
            m_shape->release();
            m_shape = nullptr;
        }

        auto&& pMaterial = GetMaterial();
        bool isDefaultMaterial = false;

        if (!pMaterial) {
            pMaterial = pPhysics->createMaterial(1.0f, 1.0f, 0.0f);
            isDefaultMaterial = true;
        }

        switch (m_type) {
            case ShapeType::Box3D: {
                m_shape = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetSize())), *pMaterial, true);
                break;
            }
            case ShapeType::Sphere3D: {
                m_shape = pPhysics->createShape(physx::PxSphereGeometry(GetRadius()), *pMaterial, true);
                break;
            }
            case ShapeType::Capsule3D: {
                m_shape = pPhysics->createShape(physx::PxCapsuleGeometry(GetRadius(), GetHeight()), *pMaterial, true);
                break;
            }
            case ShapeType::Convex3D: {
                SR_HTYPES_NS::RawMesh* rawMesh = GetRigidbody()->GetRawMesh();

                if (!rawMesh) {
                    SR_WARN("PhysXCollisionShape::UpdateShape() : mesh is not set!");
                    m_shape = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetSize())), *pMaterial, true);
                    break;
                }

                physx::PxConvexMesh* convexMesh = CreateConvexMesh(rawMesh);

                if (!convexMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create convex mesh!");
                    return false;
                }

                m_shape = pPhysics->createShape(physx::PxConvexMeshGeometry(convexMesh), *pMaterial);
                break;
            }
            case ShapeType::TriangleMesh3D: {
                SR_HTYPES_NS::RawMesh* rawMesh = GetRigidbody()->GetRawMesh();

                if (!rawMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : mesh is nullptr!");
                    return false;
                }

                physx::PxTriangleMesh* triangleMesh = CreateTriangleMesh(rawMesh);

                if (!triangleMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create triangle mesh!");
                    return false;
                }

                m_shape = pPhysics->createShape(physx::PxTriangleMeshGeometry(triangleMesh), *pMaterial);
                break;
            }
            default:
                SR_ERROR("PhysXCollisionShape::UpdateShape() : unsupported shape! Type: " + SR_UTILS_NS::EnumReflector::ToString(m_type));

                if (isDefaultMaterial) {
                    pMaterial->release();
                }
                
                return false;
        }

        SRAssert(m_shape);

        if (m_shape) {
            m_shape->userData = (void*)dynamic_cast<CollisionShape*>(this);
        }

        if (m_rigidbody->IsTrigger()){
            m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
            m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
        }

        return true;
    }

    bool PhysXCollisionShape::UpdateMatrix() {
        if (!m_shape) {
            return false;
        }

        switch (m_type) {
            case ShapeType::Box3D:
                m_shape->setGeometry(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetSize() * GetScale())));
                break;
            case ShapeType::Capsule3D: {
                auto&& maxXZ = SR_MAX(GetScale().x, GetScale().z);
                m_shape->setGeometry(physx::PxCapsuleGeometry(GetRadius() * maxXZ, GetHeight() * GetScale().y));
                break;
            }
            case ShapeType::Sphere3D:
                m_shape->setGeometry(physx::PxSphereGeometry(GetRadius() * GetScale().Max()));
                break;
            case ShapeType::Convex3D: /// кейс не нужен, геометрия обновляется при создании меша в UpdateShape()
            default:
                break;
        }

        return true;
    }

    physx::PxConvexMesh* PhysXCollisionShape::CreateConvexMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        SRAssert(pRawMesh);

        const uint32_t meshId = GetRigidbody()->GetMeshId();
        if (meshId >= pRawMesh->GetMeshesCount()) {
            return nullptr;
        }

        auto&& vertices = pRawMesh->GetVertices(meshId);
        auto&& indices = pRawMesh->GetIndices(meshId);
        std::vector<physx::PxVec3> pxVertices;
        pxVertices.resize(indices.size());

        for (uint32_t i = 0; i < indices.size(); ++i) {
            const uint64_t vertexIndex = indices[i];
            pxVertices[i] = *reinterpret_cast<physx::PxVec3*>(&vertices[vertexIndex].position);
        }

        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        physx::PxTolerancesScale scale = pPhysics->getTolerancesScale();
        physx::PxCooking* cooking = PxCreateCooking(0, pPhysics->getFoundation(), physx::PxCookingParams(scale)); /// PxU32 /*version*/

        physx::PxConvexMeshDesc convexDesc;
        convexDesc.points.count = pRawMesh->GetIndicesCount(meshId);
        convexDesc.points.stride = sizeof(physx::PxVec3);
        convexDesc.points.data = &pxVertices[0];
        convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

        physx::PxConvexMesh* convexMesh = nullptr;
        physx::PxDefaultMemoryOutputStream buf;
        if (cooking->cookConvexMesh(convexDesc, buf))
        {
            physx::PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
            convexMesh = pPhysics->createConvexMesh(id);
        }

        cooking->release();

        return convexMesh;
    }

    physx::PxTriangleMesh* PhysXCollisionShape::CreateTriangleMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        SRAssert(pRawMesh);

        const uint32_t meshId = GetRigidbody()->GetMeshId();
        if (meshId >= pRawMesh->GetMeshesCount()) {
            return nullptr;
        }

        auto&& vertices = pRawMesh->GetVertices(meshId);
        auto&& indices = pRawMesh->GetIndices(meshId);
        std::vector<physx::PxVec3> pxVertices;
        pxVertices.resize(indices.size());

        for (uint32_t i = 0; i < indices.size(); ++i) {
            const uint64_t vertexIndex = indices[i];
            pxVertices[i] = *reinterpret_cast<physx::PxVec3*>(&vertices[vertexIndex].position);
        }

        physx::PxTriangleMeshDesc meshDesc;
        meshDesc.points.count = pRawMesh->GetIndicesCount(meshId);
        meshDesc.points.stride = sizeof(physx::PxVec3);
        meshDesc.points.data = &pxVertices[0];

        meshDesc.triangles.count = pRawMesh->GetIndicesCount(meshId) / 3;
        meshDesc.triangles.stride = 3 * sizeof(uint32_t);
        meshDesc.triangles.data = &indices[0];

        auto&& pPhysics = GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        physx::PxTriangleMesh* triangleMesh = nullptr;
        physx::PxDefaultMemoryOutputStream writeBuffer;

        physx::PxTolerancesScale scale = pPhysics->getTolerancesScale();
        physx::PxCooking* cooking = PxCreateCooking(0, pPhysics->getFoundation(), physx::PxCookingParams(scale));

        if (cooking->cookTriangleMesh(meshDesc, writeBuffer))
        {
            physx::PxDefaultMemoryInputData id(writeBuffer.getData(), writeBuffer.getSize());
            triangleMesh = pPhysics->createTriangleMesh(id);
        }

        cooking->release();

        return triangleMesh;
    }

    physx::PxMaterial* PhysXCollisionShape::GetMaterial() const {
        auto&& pMaterial = GetRigidbody()->GetPhysicsMaterial();
        if (!pMaterial) {
            return nullptr;
        }

        auto&& pMaterialImpl = pMaterial->GetMaterialImpl(LibraryType::PhysX);
        if (!pMaterialImpl) {
            return nullptr;
        }

        auto&& pPxMaterial = pMaterialImpl->GetHandle();
        if (!pPxMaterial) {
            return nullptr;
        }

        return (physx::PxMaterial*)pPxMaterial;
    }
}
