//
// Created by Monika on 28.09.2022.
//

#include <Physics/CollisionShape.h>
#include <Physics/LibraryImpl.h>

namespace SR_PTYPES_NS {
    CollisionShape::CollisionShape(LibraryPtr pLibrary)
        : Super()
        , m_library(pLibrary)
        , m_scale(SR_MATH_NS::FVector3::One())
        , m_bounds(SR_MATH_NS::FVector3::One())
    { }

    CollisionShape::~CollisionShape() = default;

    void CollisionShape::UpdateDebugShape() {
        auto&& pRigidbody = GetRigidbody();
        if (!pRigidbody || !pRigidbody->IsComponentLoaded()) {
            return;
        }

        if (SR_PHYSICS_UTILS_NS::IsBox(GetType())) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    m_rigidbody->GetScale() * GetSize(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsSphere(GetType())) {
            m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawSphere(
                    m_debugId,
                    m_rigidbody->GetTranslation() + m_rigidbody->GetCenterDirection(),
                    m_rigidbody->GetRotation(),
                    (m_rigidbody->GetScale() * GetSize()).Max3(),
                    SR_MATH_NS::FColor(0, 255, 200, 255),
                    SR_FLOAT_MAX
            );
        }
        else if (SR_PHYSICS_UTILS_NS::IsCapsule(GetType())) {
            SR_MATH_NS::Unit width = (m_rigidbody->GetScale() * GetRadius()).ZeroAxis(SR_MATH_NS::AXIS_Y).Max();
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
    }



    void CollisionShape::SetHeight(float_t height) {
        m_bounds.y = height;
        UpdateDebugShape();
        UpdateMatrix();
    }

    void CollisionShape::SetRadius(float_t radius) {
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
        else if (SR_PHYSICS_UTILS_NS::IsSphere(m_type)) {
            return m_bounds.x;
        }

        return 0.f;
    }

    SR_MATH_NS::FVector3 CollisionShape::GetSize() const {
        if (SR_PHYSICS_UTILS_NS::IsShapeHasSize(m_type)) {
            return m_bounds;
        }
        else {
            return SR_MATH_NS::FVector3::One();
        }
    }

    SR_MATH_NS::FVector3 CollisionShape::GetScale() const {
        return m_scale;
    }

    Rigidbody * CollisionShape::GetRigidbody() const {
        return m_rigidbody;
    }

    ShapeType CollisionShape::GetType() const noexcept {
        return m_type;
    }

    void CollisionShape::SetScale(const SR_MATH_NS::FVector3 &scale) {
        m_scale = scale;
    }

    SR_MATH_NS::FVector3 CollisionShape::CalculateLocalInertia(float_t mass) const {
        return SR_MATH_NS::FVector3();
    }

    bool CollisionShape::Valid() const noexcept {
        return m_library->IsShapeSupported(m_type);
    }

    void CollisionShape::SetType(ShapeType type) {
        m_type = type;
    }

    void CollisionShape::RemoveDebugShape() {
        if (m_debugId != SR_ID_INVALID) {
            SR_UTILS_NS::DebugDraw::Instance().Remove(m_debugId);
            m_debugId = SR_ID_INVALID;
        }
    }
}