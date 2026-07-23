//
// Created by Monika on 05.12.2025.
//

#ifndef SR_ENGINE_CORE_IK_BODY_H
#define SR_ENGINE_CORE_IK_BODY_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/GameObject.h>

namespace SR_CORE_NS {
    class IKFootSolver;

    /// @category(Animations)
    class IKBody : public SR_UTILS_NS::Component {
        using Super = Component;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IKBody>;

    public:
        void Update(float_t dt) override;

    private:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::GameObject> m_bodyShakeTarget;
        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<IKFootSolver>> m_footSolvers;

        // FOR DEBUGGING

        /// @property
        bool m_doRotate = false;
        /// @property
        float_t m_rotationSpeed = 0.1f;
        /// @property
        float_t m_walkSpeed = 0.1f;
        /// @property
        SR_MATH_NS::FVector3 m_walkDirection = SR_MATH_NS::FVector3::Forward();
        /// @property
        SR_MATH_NS::FVector2 m_velocityLimit = SR_MATH_NS::FVector2(1.f, 1.f);
        /// @property
        SR_MATH_NS::FVector3 m_walkResetPos;
        /// @property
        float_t m_walkResetDistance = 5.f;

        /// @property
        float_t m_colliderCenterYOffset = 0.f;
        /// @property
        float_t m_colliderYPosLerpSpeed = 5.f;
        /// @property
        float_t m_bodyYOffset = 0.1f;
        /// @property
        float_t m_yStepShakeOffset = 0.3f;
        /// @property
        float_t m_yStepShakeSpeed = 0.25f;

    };
}

#endif //SR_ENGINE_CORE_IK_BODY_H
