//
// Created by Monika on 04.12.2025.
//

#ifndef SR_ENGINE_CORE_IK_FOOT_SOLVER_H
#define SR_ENGINE_CORE_IK_FOOT_SOLVER_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/GameObject.h>

namespace SR_CORE_NS {
    /// @category(Animations)
    class IKFootSolver : public SR_UTILS_NS::Component {
        using Super = Component;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IKFootSolver>;

    public:
        void OnDisable() override;
        void Update(float_t dt) override;

        SR_NODISCARD bool IsStepping() const noexcept;
        SR_NODISCARD float_t GetProgress() const noexcept;

    private:
        /// @property
        SR_UTILS_NS::EntityRef<IKFootSolver> m_anotherFoot;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> m_body;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> m_footTarget;
        /// @property
        float_t m_maxRayDistance = 2.0f;
        /// @property
        SR_MATH_NS::FVector3 m_rayOffset;
        /// @property
        SR_MATH_NS::FVector3 m_footOffset;
        /// @property
        float_t m_distanceToStep = 0.1f;
        /// @property
        float_t m_forceStepDistance = 1.5f;
        /// @property
        float_t m_footXAngle = 0.f;
        /// @property
        float_t m_stepSpeed = 1.f;
        /// @property
        float_t m_stepHeight = 0.2f;

        /// @property @readOnly @dontSave
        float_t m_stepProgress = 1.f;

        bool m_initialized = false;
        uint64_t m_debugHitId = SR_UINT64_MAX;

        SR_MATH_NS::Quaternion m_footTargetRotation;
        SR_MATH_NS::FVector3 m_footTargetPosition;

        SR_MATH_NS::Quaternion m_footCurrentRotation;
        SR_MATH_NS::FVector3 m_footCurrentPosition;

    };
}

#endif //SR_ENGINE_CORE_IK_FOOT_SOLVER_H
