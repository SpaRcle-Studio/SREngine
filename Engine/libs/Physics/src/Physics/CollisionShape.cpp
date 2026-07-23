//
// Created by Monika on 28.09.2022.
//

#include <Physics/CollisionShape.h>
#include <Physics/LibraryImpl.h>
#include <Physics/Rigidbody.h>

#include <Utils/ECS/Transform.h>
#include <Utils/DebugDraw.h>
#include <Utils/FileSystem/PathDataAccessor.h>

#include <Codegen/CollisionShape.generated.hpp>
#include "../../../../../Resources/API/Engine/libs/Physics/inc/Physics/CollisionShape.h"

namespace SR_PTYPES_NS {
    CollisionShape::~CollisionShape() {
        RemoveDebugShape();
        if (m_materialData) {
            m_materialData->RemoveUsePoint();
            m_materialData = nullptr;
        }
        SR_SAFE_DELETE_PTR(m_impl);
    }

    void CollisionShape::OnMatrixDirty() {
        SR_TRACY_ZONE;

        if (auto&& pTransform = GetTransform()) {
            pTransform->GetMatrix().Decompose(
                m_translation,
                m_rotation,
                m_scale
            );
        }

        m_isShapeDirty = true;
        Super::OnMatrixDirty();
    }

    void CollisionShape::UpdateDebugShape() {
        SR_TRACY_ZONE;

        auto&& pRigidbody = GetRigidbody();

        if (!pRigidbody || !pRigidbody->IsDebugEnabled()) {
            return;
        }

        if (!pRigidbody->IsAttached() || !pRigidbody->IsActive()) {
            return;
        }

        m_isShapeDirty = false;

        const ShapeType type = GetType();

        if (SR_PHYSICS_UTILS_NS::IsBox(type)) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                m_scale * GetSize(),
                SR_MATH_NS::FColor(0, 255, 200, 255),
                SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsPlane(type)) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawPlane(
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                m_scale * SR_MATH_NS::FVector3(GetPlaneSize().x, 0.f, GetPlaneSize().y),
                SR_MATH_NS::FColor(0, 255, 200, 255),
                SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsSphere(type)) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawSphere(
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                (m_scale * GetRadius()).Max3(),
                SR_MATH_NS::FColor(0, 255, 200, 255),
                SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsCapsule(type)) {
            SR_MATH_NS::Unit width = (m_scale * GetRadius()).ZeroAxis(SR_MATH_NS::Axis::Y).Max();
            SR_MATH_NS::FVector3 size = SR_MATH_NS::FVector3(width, GetHeight() * m_scale.y, width);
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCapsule(
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                size,
                SR_MATH_NS::FColor(0, 255, 200, 255),
                SR_FLOAT_MAX
            );
        }
        else if (HasGeometry()) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawMesh(
                const_cast<SR_HTYPES_NS::RawMesh*>(GetRawMesh().Get()), GetMeshId(),
                m_debugId,
                m_translation + GetCenterDirection(),
                m_rotation,
                m_scale * GetSize(),
                SR_MATH_NS::FColor(0, 255, 200, 255),
                SR_FLOAT_MAX
            );
        }
    }

    void CollisionShape::SetHeight(const float_t height) {
        m_bounds.y = height;
        OnShapeDirty();
        UpdateMatrix();
    }

    void CollisionShape::SetRadius(const float_t radius) {
        if (SR_PHYSICS_UTILS_NS::IsCylinder(m_type) || SR_PHYSICS_UTILS_NS::IsCapsule(m_type)) {
            m_bounds.x = radius;
            m_bounds.z = radius;
        }
        else if (SR_PHYSICS_UTILS_NS::IsSphere(m_type)) {
            m_bounds = SR_MATH_NS::FVector3(radius);
        }

        OnShapeDirty();
        UpdateMatrix();
    }

    void CollisionShape::SetSize(const SR_MATH_NS::FVector3& size) {
        m_bounds = SR_MATH_NS::FVector3(size.x, size.y, size.z);
        OnShapeDirty();
        UpdateMatrix();
    }

    float_t CollisionShape::GetHeight() const {
        return m_bounds.y;
    }

    float_t CollisionShape::GetRadius() const {
        if (SR_PHYSICS_UTILS_NS::IsCylinder(m_type) || SR_PHYSICS_UTILS_NS::IsCapsule(m_type)) {
            return m_bounds.x;
        }
        if (SR_PHYSICS_UTILS_NS::IsSphere(m_type)) {
            return m_bounds.x;
        }

        return 0.f;
    }

    SR_MATH_NS::FVector3 CollisionShape::GetSize() const {
        if (SR_PHYSICS_UTILS_NS::IsShapeHasSize(m_type)) {
            return m_bounds;
        }
        return SR_MATH_NS::FVector3::One();
    }

    Rigidbody* CollisionShape::GetRigidbody() const {
        return m_rigidbody.Get().Get();
    }

    bool CollisionShape::HasGeometry() const noexcept {
        return SR_PHYSICS_UTILS_NS::IsShapeHasGeometry(m_type);
    }

    void CollisionShape::OnDisable() {
        if (m_currentRigidbody) {
            m_currentRigidbody->DetachShape(this);
        }
        Super::OnDisable();
    }

    void CollisionShape::OnEnable() {
        ReInitRigidbody();
        Super::OnEnable();
    }

    void CollisionShape::OnDetached() {
        if (m_currentRigidbody) {
            m_currentRigidbody->DetachShape(this);
        }
        Super::OnDetached();
    }

    void CollisionShape::OnRigidbodyDetached() {
        RemoveDebugShape();
        m_currentRigidbody = nullptr;
    }

    void CollisionShape::SetMaterial(const SR_UTILS_NS::Path& path) {
        if (m_material == path) {
            return;
        }

        m_material = path;

        if (m_materialData) {
            m_materialData->RemoveUsePoint();
            m_materialData = nullptr;
        }

        if (!m_material.IsEmpty()) {
            if ((m_materialData = SR_UTILS_NS::Asset::Load<PhysicsMaterial>(m_material))) {
                m_materialData->AddUsePoint();
            }
        }
    }

    void CollisionShape::OnShapeDirty() {
        if (m_currentRigidbody) {
            m_currentRigidbody->SetShapeDirty(true);
        }
        m_isShapeDirty = true;
    }

    void CollisionShape::ReInitRigidbody() {
        SR_TRACY_ZONE;

        if (m_currentRigidbody) {
            m_currentRigidbody->DetachShape(this);
            m_currentRigidbody = nullptr;
        }

        if (auto&& pRigidbody = GetRigidbody()) {
            pRigidbody->AttachShape(this);
            m_currentRigidbody = pRigidbody;
        }

        OnShapeDirty();
    }

    ShapeType CollisionShape::GetType() const noexcept {
        return m_type;
    }

    const std::vector<void*>& CollisionShape::GetHandles() const noexcept {
        static std::vector<void*> emptyHandles;
        return m_impl ? m_impl->GetHandles() : emptyHandles;
    }

    void CollisionShape::SetCenter(const SR_MATH_NS::FVector3& center) {
        if (m_center == center) {
            return;
        }
        m_center = center;
        OnShapeDirty();
    }

    /*void CollisionShape::SetType(ShapeType type) {
        if (GetType() == type) {
            return;
        }

        if (m_library && !m_library->IsShapeSupported(type)) {
            SR_ERROR("Rigidbody::SetType() : shape \"" + SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToStringRef() + "\" unsupported!");
            return;
        }

        GetCollisionShape()->SetType(type);

        SetShapeDirty(true);
       }*/

    SR_MATH_NS::FVector3 CollisionShape::CalculateLocalInertia(float_t mass) const {
        if (m_impl) {
            return m_impl->CalculateLocalInertia(mass);
        }
        return SR_MATH_NS::FVector3::Zero();
    }

    bool CollisionShape::IsShapeValid() const noexcept {
        return GetRigidbody()->GetLibrary()->IsShapeSupported(m_type);
    }

    void CollisionShape::SetRigidbody(Rigidbody* pRigidbody) {
        if (!pRigidbody) {
            m_rigidbody = SR_UTILS_NS::EntityRef<Rigidbody>();
        }
        else {
            m_rigidbody.SetEntityId(pRigidbody->GetEntityId());
        }
        ReInitRigidbody();
    }

    void CollisionShape::SetType(const ShapeType type) {
        m_type = type;
        m_bounds = SR_MATH_NS::FVector3(1.f);
        OnShapeDirty();
    }

    void CollisionShape::RemoveDebugShape() {
        SR_TRACY_ZONE;

        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }
    }

    void CollisionShape::SetBounds(const SR_MATH_NS::FVector3& bounds) {
        m_bounds = bounds;
        OnShapeDirty();
        UpdateMatrix();
    }

    SR_MATH_NS::FVector3 CollisionShape::GetCenterDirection() const noexcept {
        return m_rotation * (m_scale * m_center);
    }

    void CollisionShape::SetPlaneSize(const SR_MATH_NS::FVector2& size) {
        m_bounds = SR_MATH_NS::FVector3(size.x, 0.f, size.y);
        OnShapeDirty();
        UpdateMatrix();
    }

    void CollisionShape::SetCustomTriangleMeshIndices(const SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices) {
        SR_TRACY_ZONE;
        m_customTriangleMeshData.indices.resize(indices.size());
        SRAssert(!m_customTriangleMeshData.indices.empty());
        std::memcpy(m_customTriangleMeshData.indices.data(), indices.data(), indices.size() * sizeof(uint32_t));
        OnShapeDirty();
    }

    void CollisionShape::SwapCustomTriangleMeshVertices(SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::FVector3>& vertices) {
        SR_TRACY_ZONE;
        std::swap(m_customTriangleMeshData.vertices, vertices);
        SRAssert(!m_customTriangleMeshData.vertices.empty());
        OnShapeDirty();
    }

    void CollisionShape::SwapCustomTriangleMeshIndices(SR_HTYPES_NS::FastMemoryArray<uint32_t>& indices) {
        SR_TRACY_ZONE;
        std::swap(m_customTriangleMeshData.indices, indices);
        SRAssert(!m_customTriangleMeshData.indices.empty());
        OnShapeDirty();
    }

    void CollisionShape::Update(float_t dt) {
        if (m_impl) {
            m_impl->Update(dt);
        }

        auto&& pRigidbody = GetRigidbody();
        if (!pRigidbody) {
            RemoveDebugShape();
            return;
        }

        const bool isDebugEnabled = pRigidbody->IsDebugEnabled();

        if (isDebugEnabled && (m_debugId == SR_ID_INVALID || m_isShapeDirty)) {
            UpdateDebugShape();
        }
        else if (!isDebugEnabled && m_debugId != SR_ID_INVALID) {
            RemoveDebugShape();
        }
    }

    void CollisionShape::OnRawMeshChanged() {
        IRawMeshHolder::OnRawMeshChanged();

        if (!HasGeometry()) {
            return;
        }

        OnShapeDirty();
    }

    std::optional<bool> CollisionShape::UpdateShape() {
        if (!m_impl) {
            if (m_type == ShapeType::Unknown) {
                SetType(GetRigidbody()->GetLibrary()->GetDefaultShape());
            }

            m_impl = GetRigidbody()->GetLibrary()->CreateCollisionShapeImpl();
            if (!m_impl) {
                return false;
            }

            m_impl->SetShape(this);
        }

        return m_impl->UpdateShape();
    }

    bool CollisionShape::UpdateMatrix() {
        return m_impl && m_impl->UpdateMatrix();
    }

    void CollisionShape::SwapBoxes(SR_HTYPES_NS::FastMemoryArray<SR_MATH_NS::AABB>& boxes) {
        std::swap(m_boxes, boxes);
        OnShapeDirty();
    }
}
