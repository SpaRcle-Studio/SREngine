//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXCollisionShape.h>
#include <Physics/PhysX/PhysXRigidbody3D.h>

#include <Utils/Types/RawMesh.h>

#include <Enum/ShapeType.hpp>

namespace SR_PTYPES_NS {
    PhysXCollisionShape::~PhysXCollisionShape() {
        if (m_shape) {
            m_shape->userData = nullptr;
            m_shape->release();
            m_shape = nullptr;
        }
    }

    bool PhysXCollisionShape::UpdateShape() {
        SR_TRACY_ZONE;

        if (!GetShape()->GetRigidbody()->IsUpdatable()) {
            return false;
        }

        auto&& pPhysics = GetShape()->GetRigidbody()->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

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

        switch (GetShape()->GetType()) {
            case ShapeType::Plane3D: {
                auto&& size = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize());
                size.y = 0.01f;
                m_shape = pPhysics->createShape(physx::PxBoxGeometry(size), *pMaterial, true);
                break;
            }
            case ShapeType::Box3D: {
                m_shape = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize())), *pMaterial, true);
                break;
            }
            case ShapeType::Sphere3D: {
                m_shape = pPhysics->createShape(physx::PxSphereGeometry(GetShape()->GetRadius()), *pMaterial, true);
                break;
            }
            case ShapeType::Capsule3D: {
                m_shape = pPhysics->createShape(physx::PxCapsuleGeometry(GetShape()->GetRadius(), GetShape()->GetHeight()), *pMaterial, true);
                break;
            }
            case ShapeType::Convex3D: {
                SR_HTYPES_NS::RawMesh::Ptr pRawMesh = GetShape()->GetRawMesh();

                if (!pRawMesh) {
                    SR_WARN("PhysXCollisionShape::UpdateShape() : mesh is not set!");
                    m_shape = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize())), *pMaterial, true);
                    break;
                }

                physx::PxConvexMesh* convexMesh = CreateConvexMesh(pRawMesh.Get());

                if (!convexMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create convex mesh!");
                    return false;
                }

                m_shape = pPhysics->createShape(physx::PxConvexMeshGeometry(convexMesh), *pMaterial, true);
                break;
            }
            case ShapeType::TriangleMesh3D: {
                SR_HTYPES_NS::RawMesh::Ptr pRawMesh = GetShape()->GetRawMesh();

                if (!pRawMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : mesh is nullptr!");
                    return false;
                }

                physx::PxTriangleMesh* triangleMesh = CreateTriangleMesh(pRawMesh.Get());

                if (!triangleMesh) {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create triangle mesh!");
                    return false;
                }

                m_shape = pPhysics->createShape(physx::PxTriangleMeshGeometry(triangleMesh), *pMaterial);
                break;
            }
            default: {
                SR_ERROR("PhysXCollisionShape::UpdateShape() : unsupported shape! Type: {}"_format(GetShape()->GetType()));
                if (isDefaultMaterial) {
                    pMaterial->release();
                }
                return false;
            }
        }

        SRAssert(m_shape);

        if (m_shape) {
            m_shape->userData = static_cast<void*>(GetShape());
        }

        UpdateMatrix();

        if (GetShape()->GetRigidbody()->IsTrigger()) {
            m_shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
            m_shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
        }

        return true;
    }

    bool PhysXCollisionShape::UpdateMatrix() {
        SR_TRACY_ZONE;

        if (!m_shape) {
            return false;
        }

        auto&& scale = GetShape()->GetScale();

        const SR_MATH_NS::Matrix4x4 localToRigidBody = GetShape()->GetRigidbody()->GetTransform()->GetMatrix().Inverse() * GetShape()->GetTransform()->GetMatrix();
        physx::PxVec3 translation = SR_PHYSICS_UTILS_NS::FV3ToPxV3((localToRigidBody.GetTranslate() + GetShape()->GetCenter()));
        physx::PxQuat rotation = SR_PHYSICS_UTILS_NS::QuatToPxQuat(localToRigidBody.GetQuat());

        switch (GetShape()->GetType()) {
            case ShapeType::Plane3D: {
                auto&& size = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize() * scale);
                size.y = 0.01f;
                m_shape->setGeometry(physx::PxBoxGeometry(size));
                break;
            }
            case ShapeType::Box3D:
                m_shape->setGeometry(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize() * scale)));
                break;
            case ShapeType::Capsule3D: {
                auto&& maxXZ = SR_MAX(scale.x, scale.z);
                m_shape->setGeometry(physx::PxCapsuleGeometry(GetShape()->GetRadius() * maxXZ, GetShape()->GetHeight() * scale.y));
                rotation = physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)) * rotation; /// капсула в PhysX ориентирована вдоль оси Z, а в SR - вдоль Y
                break;
            }
            case ShapeType::Sphere3D:
                m_shape->setGeometry(physx::PxSphereGeometry(GetShape()->GetRadius() * scale.Max()));
                break;
            case ShapeType::Convex3D: /// кейс не нужен, геометрия обновляется при создании меша в UpdateShape()
            default:
                break;
        }

        physx::PxTransform localPose(translation, rotation);
        m_shape->setLocalPose(localPose);

        GetShape()->GetRigidbody()->UpdateInertia();

        return true;
    }

    physx::PxConvexMesh* PhysXCollisionShape::CreateConvexMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        SR_TRACY_ZONE;

        SRAssert(pRawMesh);

        const uint32_t meshId = GetShape()->GetMeshId();
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

        auto&& pPhysics = GetShape()->GetRigidbody()->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        const physx::PxTolerancesScale scale = pPhysics->getTolerancesScale();
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
        SR_TRACY_ZONE;

        SRAssert(pRawMesh);

        const uint32_t meshId = GetShape()->GetMeshId();
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

        auto&& pPhysics = GetShape()->GetRigidbody()->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

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
        if (auto&& pMaterial = GetShape()->GetPhysicsMaterial()) {
            if (auto&& pMaterialImpl = pMaterial->GetMaterialImpl(LibraryType::PhysX)) {
                if (auto&& pPxMaterial = pMaterialImpl->GetHandle()) {
                    return (physx::PxMaterial*)pPxMaterial;
                }
            }
        }
        if (auto&& pDefaultMat = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetDefaultMaterial()) {
            if (auto&& pMaterialImpl = pDefaultMat->GetMaterialImpl(LibraryType::PhysX)) {
                if (auto&& pPxMaterial = pMaterialImpl->GetHandle()) {
                    return (physx::PxMaterial*)pPxMaterial;
                }
            }
        }
        return nullptr;
    }
}
