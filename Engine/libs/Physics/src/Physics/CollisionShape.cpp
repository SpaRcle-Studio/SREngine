//
// Created by Monika on 28.09.2022.
//

#include <Physics/CollisionShape.h>
#include <Physics/LibraryImpl.h>

#include <Codegen/CollisionShape.generated.hpp>

namespace SR_PTYPES_NS {
    CollisionShape::CollisionShape()
        : SR_HTYPES_NS::SharedPtr<CollisionShape>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    CollisionShape::~CollisionShape() {
        RemoveDebugShape();
        SR_SAFE_DELETE_PTR(m_impl);
    }

    void CollisionShape::UpdateDebugShape() {
        SR_TRACY_ZONE;

        if (!m_rigidbody || !m_rigidbody->IsDebugEnabled()) {
            return;
        }

        if (!m_rigidbody->IsAttached() || !m_rigidbody->IsActive()) {
            return;
        }

        const ShapeType type = GetType();

        if (SR_PHYSICS_UTILS_NS::IsBox(type)) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    m_rigidbody->GetScale() * GetSize(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsPlane(type)) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawPlane(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    m_rigidbody->GetScale() * SR_MATH_NS::FVector3(GetPlaneSize().x, 0.f, GetPlaneSize().y),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsSphere(type)) {
                    m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawSphere(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    (m_rigidbody->GetScale() * GetRadius()).Max3(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsCapsule(type)) {
            SR_MATH_NS::Unit width = (m_rigidbody->GetScale() * GetRadius()).ZeroAxis(SR_MATH_NS::Axis::Y).Max();
            SR_MATH_NS::FVector3 size = SR_MATH_NS::FVector3(width, GetHeight() * m_rigidbody->GetScale().y, width);
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCapsule(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    size,
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (HasGeometry()) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawMesh(
                    const_cast<SR_HTYPES_NS::RawMesh*>(GetRawMesh().Get()), GetMeshId(),
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    m_rigidbody->GetScale() * GetSize(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
    }

    void CollisionShape::SetHeight(const float_t height) {
        m_bounds.y = height;
        UpdateDebugShape();
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

        UpdateDebugShape();
        UpdateMatrix();
    }

    void CollisionShape::SetSize(const SR_MATH_NS::FVector3& size) {
        m_bounds = SR_MATH_NS::FVector3(size.x, size.y, size.z);
        UpdateDebugShape();
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
        return m_rigidbody;
    }

    bool CollisionShape::HasGeometry() const noexcept {
        return SR_PHYSICS_UTILS_NS::IsShapeHasGeometry(m_type);
    }

    ShapeType CollisionShape::GetType() const noexcept {
        return m_type;
    }

    void* CollisionShape::GetHandle() const noexcept {
        return m_impl ? m_impl->GetHandle() : nullptr;
    }

    SR_MATH_NS::FVector3 CollisionShape::CalculateLocalInertia(float_t mass) const {
        if (m_impl) {
            return m_impl->CalculateLocalInertia(mass);
        }
        return SR_MATH_NS::FVector3::Zero();
    }

    bool CollisionShape::IsShapeValid() const noexcept {
        return GetRigidbody()->GetLibrary()->IsShapeSupported(m_type);
    }

    void CollisionShape::SetType(const ShapeType type) {
        m_type = type;
        m_bounds = SR_MATH_NS::FVector3(1.f);

        ReInitDebugShape();

        if (m_rigidbody) {
            m_rigidbody->SetShapeDirty(true);
        }
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
        UpdateDebugShape();
        UpdateMatrix();
    }

    void CollisionShape::SetPlaneSize(const SR_MATH_NS::FVector2& size) {
        m_bounds = SR_MATH_NS::FVector3(size.x, 0.f, size.y);
        UpdateDebugShape();
        UpdateMatrix();
    }

    void CollisionShape::Update(float_t dt) {
        if (m_impl) {
            m_impl->Update(dt);
        }

        const bool isDebugEnabled = m_rigidbody->IsDebugEnabled();

        if (isDebugEnabled && m_debugId == SR_ID_INVALID) {
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

        if (m_rigidbody) {
            m_rigidbody->SetShapeDirty(true);
        }

        ReInitDebugShape();
    }

    bool CollisionShape::UpdateShape() {
        if (!m_impl) {
            if (m_type == ShapeType::Unknown) {
                SetType(GetRigidbody()->GetLibrary()->GetDefaultShape());
            }

            m_impl = GetRigidbody()->GetLibrary()->CreateCollisionShapeImpl();
            m_impl->SetShape(this);
        }

        return m_impl && m_impl->UpdateShape();
    }

    bool CollisionShape::UpdateMatrix() {
        return m_impl && m_impl->UpdateMatrix();
    }

    void CollisionShape::ReInitDebugShape() {
        RemoveDebugShape();
        UpdateDebugShape();
    }
}