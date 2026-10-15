//
// Created by Monika on 15.10.2026.
//

#include <Physics/BoneDynamics/BoneDynamicsCollider.h>

#include <Utils/ECS/Transform.h>
#include <Utils/DebugDraw.h>

#include <Codegen/BoneDynamicsCollider.generated.hpp>

namespace SR_PHYSICS_NS {
    void BoneDynamicsCollider::LateUpdate() {
        /// Система обновляется в LateUpdate раньше или позже коллайдера, поэтому запрос живёт два кадра,
        /// иначе отладка мигала бы через кадр
        UpdateDebug(m_debug || m_debugRequestFrames > 0);
        if (m_debugRequestFrames > 0) {
            --m_debugRequestFrames;
        }
        Super::LateUpdate();
    }

    void BoneDynamicsCollider::OnDisable() {
        UpdateDebug(false);
        Super::OnDisable();
    }

    void BoneDynamicsCollider::OnDestroy() {
        UpdateDebug(false);
        Super::OnDestroy();
    }

    XPBDCollisionShape BoneDynamicsCollider::GetCollisionShape() const {
        XPBDCollisionShape shape;

        auto&& pTransform = GetTransform();
        if (!pTransform) {
            return shape;
        }

        SR_MATH_NS::FVector3 translation;
        SR_MATH_NS::Quaternion rotation;
        SR_MATH_NS::FVector3 scale;
        pTransform->GetMatrix().Decompose(translation, rotation, scale);

        const SR_MATH_NS::FVector3 center = translation + rotation * (scale * m_center);
        const SR_MATH_NS::FVector3 up = rotation * SR_MATH_NS::FVector3::Up();

        switch (m_type) {
            case BoneDynamicsColliderType::Sphere:
                shape.type = XPBDCollisionShapeType::Sphere;
                shape.a = center;
                shape.radius = m_radius * scale.Max();
                break;
            case BoneDynamicsColliderType::Capsule: {
                const float_t halfHeight = m_height * 0.5f * scale.y;
                shape.type = XPBDCollisionShapeType::Capsule;
                shape.a = center - up * halfHeight;
                shape.b = center + up * halfHeight;
                shape.radius = m_radius * SR_MAX(scale.x, scale.z);
                break;
            }
            case BoneDynamicsColliderType::Plane:
                shape.type = XPBDCollisionShapeType::Plane;
                shape.a = center;
                shape.b = up;
                break;
            default:
                break;
        }

        return shape;
    }

    void BoneDynamicsCollider::UpdateDebug(const bool enabled) {
        if (!enabled) {
            SR_UTILS_NS::DebugDraw::Instance().TryRemove(&m_debugId);
            return;
        }

        auto&& pTransform = GetTransform();
        if (!pTransform) {
            return;
        }

        SR_MATH_NS::FVector3 translation;
        SR_MATH_NS::Quaternion rotation;
        SR_MATH_NS::FVector3 scale;
        pTransform->GetMatrix().Decompose(translation, rotation, scale);

        const SR_MATH_NS::FVector3 center = translation + rotation * (scale * m_center);
        const SR_MATH_NS::FColor color = SR_MATH_NS::FColor(255, 200, 0, 255) / 255.f;

        switch (m_type) {
            case BoneDynamicsColliderType::Sphere:
                m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawSphere(m_debugId, center, rotation,
                    SR_MATH_NS::FVector3(m_radius * scale.Max()), color, SR_FLOAT_MAX
                );
                break;
            case BoneDynamicsColliderType::Capsule: {
                const float_t radius = m_radius * SR_MAX(scale.x, scale.z);
                m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCapsule(m_debugId, center, rotation,
                    SR_MATH_NS::FVector3(radius, m_height * scale.y, radius), color, SR_FLOAT_MAX
                );
                break;
            }
            case BoneDynamicsColliderType::Plane:
                m_debugId = SR_UTILS_NS::DebugDraw::Instance().DrawPlane(m_debugId, center, rotation,
                    SR_MATH_NS::FVector3(1.f, 0.f, 1.f), color, SR_FLOAT_MAX
                );
                break;
            default:
                break;
        }
    }
}
