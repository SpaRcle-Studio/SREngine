//
// Created by Monika on 25.11.2022.
//

#include <Physics/PhysX/PhysXCollisionShape.h>
#include <Physics/PhysX/PhysXRigidbody3D.h>

#include <Utils/Types/RawMesh.h>

#include <Enum/ShapeType.hpp>

namespace SR_PTYPES_NS {
    PhysXCollisionShape::~PhysXCollisionShape() {
        ReleaseShapes();
    }

    std::optional<bool> PhysXCollisionShape::UpdateShape() {
        SR_TRACY_ZONE;

        if (!GetShape()->GetRigidbody()->IsUpdatable()) {
            return false;
        }

        auto&& pPhysics = GetShape()->GetRigidbody()->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        const bool isNeedReCreate = m_shapes.empty()
                || GetShape()->GetType() != m_currentShapeType
                || GetShape()->GetBounds() != m_currentBounds
                || GetShape()->GetType() == ShapeType::Convex3D || GetShape()->GetType() == ShapeType::TriangleMesh3D;

        m_currentShapeType = GetShape()->GetType();
        m_currentBounds = GetShape()->GetBounds();

        if (isNeedReCreate) {
            ReleaseShapes();
        }

        if (m_shapes.empty()) {
            auto&& pMaterial = GetMaterial();
            bool isDefaultMaterial = false;

            if (!pMaterial) {
                pMaterial = pPhysics->createMaterial(1.0f, 1.0f, 0.0f);
                isDefaultMaterial = true;
            }

            switch (m_currentShapeType) {
                case ShapeType::Plane3D: {
                    auto&& size = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize());
                    size.y = 0.01f;
                    m_shapes.resize(1);
                    m_shapes[0] = pPhysics->createShape(physx::PxBoxGeometry(size), *pMaterial, true);
                    break;
                }
                case ShapeType::Box3D: {
                    m_shapes.resize(1);
                    m_shapes[0] = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize())), *pMaterial, true);
                    break;
                }
                case ShapeType::Sphere3D: {
                    m_shapes.resize(1);
                    m_shapes[0] = pPhysics->createShape(physx::PxSphereGeometry(GetShape()->GetRadius()), *pMaterial, true);
                    break;
                }
                case ShapeType::Capsule3D: {
                    m_shapes.resize(1);
                    m_shapes[0] = pPhysics->createShape(physx::PxCapsuleGeometry(GetShape()->GetRadius(), GetShape()->GetHeight()), *pMaterial, true);
                    break;
                }
                case ShapeType::Convex3D: {
                    m_shapes.resize(1);
                    SR_HTYPES_NS::RawMesh::Ptr pRawMesh = GetShape()->GetRawMesh();

                    if (!pRawMesh) {
                        SR_WARN("PhysXCollisionShape::UpdateShape() : mesh is not set!");
                        m_shapes[0] = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize())), *pMaterial, true);
                        break;
                    }

                    physx::PxConvexMesh* convexMesh = CreateConvexMesh(pRawMesh.Get());

                    if (!convexMesh) {
                        SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create convex mesh!");
                        return false;
                    }

                    m_shapes[0] = pPhysics->createShape(physx::PxConvexMeshGeometry(convexMesh), *pMaterial, true);
                    break;
                }
                case ShapeType::Boxes3D: {
                    auto&& boxes = GetShape()->GetBoxes();
                    m_shapes.resize(boxes.size());
                    for (size_t i = 0; i < boxes.size(); ++i) {
                        m_shapes[i] = pPhysics->createShape(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(boxes[i].GetSize())), *pMaterial, true);
                    }
                    break;
                }
                case ShapeType::TriangleMesh3D: {
                    m_shapes.resize(1);

                    auto&& customTriangleMesh = GetShape()->GetCustomTriangleMeshData();
                    if (!customTriangleMesh.vertices.empty() && !customTriangleMesh.indices.empty()) {
                        physx::PxTriangleMesh* pTriangleMesh = CreateTriangleMesh(customTriangleMesh.vertices, customTriangleMesh.indices);

                        if (!pTriangleMesh) {
                            SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create triangle mesh from custom data!");
                            return false;
                        }

                        m_shapes[0] = pPhysics->createShape(physx::PxTriangleMeshGeometry(pTriangleMesh), *pMaterial);
                        break;
                    }

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

                    m_shapes[0] = pPhysics->createShape(physx::PxTriangleMeshGeometry(triangleMesh), *pMaterial);
                    break;
                }
                default: {
                    SR_ERROR("PhysXCollisionShape::UpdateShape() : unsupported shape! Type: {}"_format(m_currentShapeType));
                    if (isDefaultMaterial) {
                        pMaterial->release();
                    }
                    return false;
                }
            }
        }

        const bool isTrigger = GetShape()->GetRigidbody()->IsTrigger();
        const bool needUpdateTriggerFlag = isTrigger != m_isTrigger || isNeedReCreate || GetShape()->GetType() == ShapeType::Boxes3D;
        m_isTrigger = isTrigger;

        for (auto&& pShape : m_shapes) {
            if (pShape) {
                pShape->userData = static_cast<void*>(GetShape());
                if (needUpdateTriggerFlag) {
                    pShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, !m_isTrigger);
                    pShape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, m_isTrigger);
                }
            }
            else {
                SR_ERROR("PhysXCollisionShape::UpdateShape() : failed to create shape!");
                return false;
            }
        }

        //m_shape->setContactOffset(0.05f);
        //m_shape->setRestOffset(0.0f);

        UpdateMatrix();

        return isNeedReCreate ? std::optional<bool>(true) : std::nullopt;
    }

    bool PhysXCollisionShape::UpdateMatrix() {
        SR_TRACY_ZONE;

        if (m_shapes.empty()) {
            return false;
        }

        auto&& scale = GetShape()->GetScale();
        const auto rigidbodySize = GetShape()->GetRigidbody() ? GetShape()->GetRigidbody()->GetScale() : SR_MATH_NS::FVector3::One();

        const SR_MATH_NS::Matrix4x4 localToRigidBody = GetShape()->GetRigidbody()->GetTransform()->GetMatrix().Inverse() * GetShape()->GetTransform()->GetMatrix();
        physx::PxVec3 translation = SR_PHYSICS_UTILS_NS::FV3ToPxV3(((localToRigidBody.GetTranslate() + GetShape()->GetCenter())) * rigidbodySize);
        physx::PxQuat rotation = SR_PHYSICS_UTILS_NS::QuatToPxQuat(localToRigidBody.GetQuat());

        const ShapeType type = GetShape()->GetType();
        switch (type) {
            case ShapeType::Plane3D: {
                auto&& size = SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize() * scale);
                size.y = 0.01f;
                m_shapes[0]->setGeometry(physx::PxBoxGeometry(size));
                break;
            }
            case ShapeType::Box3D:
                m_shapes[0]->setGeometry(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(GetShape()->GetSize() * scale)));
                break;
            case ShapeType::Capsule3D: {
                auto&& maxXZ = SR_MAX(scale.x, scale.z);
                m_shapes[0]->setGeometry(physx::PxCapsuleGeometry(GetShape()->GetRadius() * maxXZ, GetShape()->GetHeight() * scale.y));
                rotation = physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)) * rotation; /// капсула в PhysX ориентирована вдоль оси Z, а в SR - вдоль Y
                break;
            }
            case ShapeType::Boxes3D: {
                auto&& boxes = GetShape()->GetBoxes();
                for (size_t i = 0; i < boxes.size(); ++i) {
                    if (i >= m_shapes.size()) {
                        SR_ERROR("PhysXCollisionShape::UpdateMatrix() : shape index out of range! Index: {}, Shapes count: {}"_format(i, m_shapes.size()));
                        break;
                    }
                    physx::PxTransform localPose(translation + SR_PHYSICS_UTILS_NS::FV3ToPxV3(boxes[i].GetPosition()), rotation);
                    m_shapes[i]->setLocalPose(localPose);
                    m_shapes[i]->setGeometry(physx::PxBoxGeometry(SR_PHYSICS_UTILS_NS::FV3ToPxV3(boxes[i].GetSize())));
                }
                break;
            }
            case ShapeType::Sphere3D:
                m_shapes[0]->setGeometry(physx::PxSphereGeometry(GetShape()->GetRadius() * scale.Max()));
                break;
            case ShapeType::Convex3D: /// кейс не нужен, геометрия обновляется при создании меша в UpdateShape()
            default:
                break;
        }

        if (type != ShapeType::Boxes3D && type != ShapeType::TriangleMesh3D) {
            physx::PxTransform localPose(translation, rotation);
            for (auto&& pShape : m_shapes) {
                if (pShape) {
                    pShape->setLocalPose(localPose);
                }
            }
        }

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

        const SR_UTILS_NS::VertexDataBuffer& buffer = pRawMesh->GetVertexBuffer(meshId,
            SR_UTILS_NS::VertexLayoutDescription().AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
        );

        auto&& indices = pRawMesh->GetIndices(meshId);
        std::vector<physx::PxVec3> pxVertices;
        pxVertices.resize(indices.size());

        for (uint32_t i = 0; i < indices.size(); ++i) {
            const uint64_t vertexIndex = indices[i];
            const SR_MATH_NS::FVector3* vertices = static_cast<const SR_MATH_NS::FVector3*>(buffer.GetRawData());
            pxVertices[i] = *reinterpret_cast<const physx::PxVec3*>(&vertices[vertexIndex]);
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

    SR_NODISCARD physx::PxTriangleMesh* PhysXCollisionShape::CreateTriangleMesh(
        const SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3>& vertices,
        const SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices
    ) {
        SR_TRACY_ZONE;

        if (vertices.empty() || indices.empty()) {
            SR_ERROR("PhysXCollisionShape::CreateTriangleMesh() : vertices or indices are empty!");
            return nullptr;
        }

        auto&& pPhysics = GetShape()->GetRigidbody()->GetLibrary<PhysXLibraryImpl>()->GetPxPhysics();

        physx::PxTriangleMeshDesc meshDesc = {};

        meshDesc.points.count  = static_cast<physx::PxU32>(vertices.size());
        meshDesc.points.stride = sizeof(float_t) * 3;
        meshDesc.points.data   = vertices.data();

        meshDesc.triangles.count  = static_cast<physx::PxU32>(indices.size() / 3);
        meshDesc.triangles.stride = sizeof(uint32_t) * 3;
        meshDesc.triangles.data   = indices.data();

        //meshDesc.flags |= physx::PxMeshFlag::eDISABLE_CLEAN_MESH;
        //meshDesc.flags |= physx::PxMeshFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
        //meshDesc.flags |= physx::PxMeshFlag::ePREFER_FAST_COOKING;

        physx::PxCookingParams params(pPhysics->getTolerancesScale());
        params.meshPreprocessParams =
                static_cast<physx::PxMeshPreprocessingFlag::Enum>(physx::PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH |
                                                                  physx::PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE);

        //params.meshCookingHint = physx::PxMeshCookingHint::eCOOKING_PERFORMANCE;

        physx::PxTriangleMesh* triangleMesh = nullptr;
        physx::PxDefaultMemoryOutputStream writeBuffer;

        physx::PxCooking* cooking = PxCreateCooking(0, pPhysics->getFoundation(), params);

        {
            SR_TRACY_ZONE_N("cookTriangleMesh");
            if (cooking->cookTriangleMesh(meshDesc, writeBuffer)) {
                physx::PxDefaultMemoryInputData id(writeBuffer.getData(), writeBuffer.getSize());
                SR_TRACY_ZONE_N("createTriangleMesh");
                triangleMesh = pPhysics->createTriangleMesh(id);
            }
        }

        {
            SR_TRACY_ZONE_N("releaseCooking");
            cooking->release();
        }

        return triangleMesh;
    }

    physx::PxTriangleMesh* PhysXCollisionShape::CreateTriangleMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        SR_TRACY_ZONE;

        SRAssert(pRawMesh);

        const uint32_t meshId = GetShape()->GetMeshId();
        if (meshId >= pRawMesh->GetMeshesCount()) {
            return nullptr;
        }

        const SR_UTILS_NS::VertexDataBuffer& buffer = pRawMesh->GetVertexBuffer(meshId,
            SR_UTILS_NS::VertexLayoutDescription().AddAttribute(SR_UTILS_NS::VertexAttribute::Position, SR_UTILS_NS::VertexAttributeFormat::Float32, 3)
        );

        auto&& indices = pRawMesh->GetIndices(meshId);
        std::vector<physx::PxVec3> pxVertices;
        pxVertices.resize(indices.size());

        for (uint32_t i = 0; i < indices.size(); ++i) {
            const uint64_t vertexIndex = indices[i];
            const SR_MATH_NS::FVector3* vertices = static_cast<const SR_MATH_NS::FVector3*>(buffer.GetRawData());
            pxVertices[i] = *reinterpret_cast<const physx::PxVec3*>(&vertices[vertexIndex]);
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

    const std::vector<void*>& PhysXCollisionShape::GetHandles() const noexcept {
        SR_TRACY_ZONE;
        m_handles.resize(m_shapes.size());
        std::ranges::transform(m_shapes, m_handles.begin(), [](physx::PxShape* pShape) { return static_cast<void*>(pShape); });
        return m_handles;
    }

    void PhysXCollisionShape::ReleaseShapes() {
        for (auto&& pShape : m_shapes) {
            if (pShape) {
                pShape->userData = nullptr;
                pShape->release();
            }
        }
        m_shapes.clear();
    }
}
