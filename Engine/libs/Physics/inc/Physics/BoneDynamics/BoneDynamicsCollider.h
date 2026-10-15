//
// Created by Monika on 15.10.2026.
//

#ifndef SR_ENGINE_PHYSICS_BONE_DYNAMICS_COLLIDER_H
#define SR_ENGINE_PHYSICS_BONE_DYNAMICS_COLLIDER_H

#include <Physics/BoneDynamics/XPBDSolver.h>

#include <Utils/ECS/Component.h>

namespace SR_PHYSICS_NS {
    SR_ENUM_NS_CLASS_T(BoneDynamicsColliderType, uint8_t,
        Sphere,
        Capsule,
        Plane
    )

    /// Лёгкий коллайдер для BoneDynamicsSystem, в физическую сцену не регистрируется.
    /// Capsule ориентирована вдоль локальной оси Y, Plane - нормаль вдоль локальной оси Y.
    /// @category(Physics)
    class BoneDynamicsCollider : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<BoneDynamicsCollider>;

    public:
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        void LateUpdate() override;
        void OnDisable() override;
        void OnDestroy() override;

        SR_NODISCARD XPBDCollisionShape GetCollisionShape() const;
        SR_NODISCARD BoneDynamicsColliderType GetColliderType() const noexcept { return m_type; }

        /// Отладку включает BoneDynamicsSystem с включённым Debug, запрос нужно повторять каждый кадр
        void RequestDebug() noexcept { m_debugRequestFrames = 2; }

    private:
        void UpdateDebug(bool enabled);

    private:
        uint64_t m_debugId = SR_UINT64_MAX;
        uint8_t m_debugRequestFrames = 0;

        /// @property
        bool m_debug = false;

        /// @property
        BoneDynamicsColliderType m_type = BoneDynamicsColliderType::Sphere;
        /// @property @drag(0.01f)
        SR_MATH_NS::FVector3 m_center;
        /// @property @drag(0.01f) @condition(This.GetColliderType() != SR_PHYSICS_NS::BoneDynamicsColliderType::Plane)
        float_t m_radius = 0.1f;
        /// @property @drag(0.01f) @tooltip(Полная высота капсулы без полусфер) @condition(This.GetColliderType() == SR_PHYSICS_NS::BoneDynamicsColliderType::Capsule)
        float_t m_height = 0.2f;

    };
}

#endif //SR_ENGINE_PHYSICS_BONE_DYNAMICS_COLLIDER_H
