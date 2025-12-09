//
// Created by Monika on 04.12.2025.
//

#include <Engine/IK/IKBody.h>
#include <Engine/IK/IKFootSolver.h>

#include <Physics/3D/Rigidbody3D.h>

#include <Utils/DebugDraw.h>

#include <Codegen/IKBody.generated.hpp>

namespace SR_CORE_NS {
    void IKBody::Update(float_t dt) {
        SR_TRACY_ZONE;

        if (m_rotationSpeed > 0.f && m_doRotate) {
            GetTransform()->Rotate(SR_MATH_NS::Quaternion::AngleAxis(dt * m_rotationSpeed, SR_MATH_NS::FVector3::Up()));
        }

        if (m_walkSpeed > 0.f) {
            if (auto&& pRigidbody = GetSceneObject()->GetComponent<SR_PTYPES_NS::Rigidbody3D>(); pRigidbody && pRigidbody->IsActive()) {
                auto&& velocity = pRigidbody->GetLinearVelocity();
                const SR_MATH_NS::FVector3 dir = GetTransform()->GetQuaternion() * m_walkDirection;
                velocity.x = SR_CLAMP(velocity.x + dir.x * m_walkSpeed, -m_velocityLimit.x, m_velocityLimit.x);
                velocity.z = SR_CLAMP(velocity.z + dir.z * m_walkSpeed, -m_velocityLimit.y, m_velocityLimit.y);
                pRigidbody->SetLinearVelocity(velocity);
            }
            else {
                GetTransform()->Translate(m_walkDirection * dt * m_walkSpeed);
            }
        }

        if (m_walkResetDistance > 0.f) {
            const SR_MATH_NS::FVector3 bodyPosition = GetTransform()->GetTranslation();
            const float_t distance = (bodyPosition - m_walkResetPos).Length();
            if (distance >= m_walkResetDistance) {
                GetTransform()->SetTranslation(m_walkResetPos);
            }
        }




        auto&& pBodyShakeTarget = m_bodyShakeTarget.Get();
        if (m_yStepShakeOffset != 0.f && pBodyShakeTarget && !m_footSolvers.empty()) {
            float_t minStep = std::numeric_limits<float_t>::max();
            float_t maxStep = std::numeric_limits<float_t>::min();

            for (auto&& pFootSolverRef : m_footSolvers) {
                if (auto&& pFootSolver = pFootSolverRef.Get()) {
                    const float_t footStep = SR_MIN(1.f, pFootSolver->GetProgress());
                    minStep = SR_MIN(minStep, footStep);
                    maxStep = SR_MAX(maxStep, footStep);
                }
            }

            const float_t stepDelta = maxStep - minStep;

            const SR_MATH_NS::FVector3 bodyPosition = pBodyShakeTarget->GetTransform()->GetTranslation();
            const float_t yOffset = m_bodyYOffset + m_yStepShakeOffset * SR_SIN(stepDelta * static_cast<float_t>(SR_PI));
            const SR_MATH_NS::FVector3 newPosition = SR_MATH_NS::FVector3(bodyPosition.x, yOffset, bodyPosition.z);

            pBodyShakeTarget->GetTransform()->SetTranslation(bodyPosition.Lerp(newPosition, dt * m_yStepShakeSpeed));
        }

        Super::Update(dt);
    }
}
