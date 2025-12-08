//
// Created by Monika on 04.12.2025.
//

#include <Engine/IK/IKBody.h>
#include <Engine/IK/IKFootSolver.h>

#include <Utils/DebugDraw.h>

#include <Codegen/IKBody.generated.hpp>

namespace SR_CORE_NS {
    void IKBody::Update(float_t dt) {
        SR_TRACY_ZONE;

        if (m_rotationSpeed > 0.f && m_doRotate) {
            GetTransform()->Rotate(SR_MATH_NS::Quaternion::AngleAxis(dt * m_rotationSpeed, SR_MATH_NS::FVector3::Up()));
        }

        if (m_walkSpeed > 0.f) {
            GetTransform()->Translate(m_walkDirection * dt * m_walkSpeed);
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

            for (auto&& pFootSolverRef : m_footSolvers) {
                if (auto&& pFootSolver = pFootSolverRef.Get()) {
                    const float_t footStep = pFootSolver->GetProgress();
                    minStep = SR_MIN(minStep, footStep);
                }
            }

            const SR_MATH_NS::FVector3 bodyPosition = GetTransform()->GetTranslation();
            const float_t yOffset = m_yStepShakeOffset * SR_SIN(minStep * static_cast<float_t>(SR_PI));
            const SR_MATH_NS::FVector3 newPosition = SR_MATH_NS::FVector3(bodyPosition.x, yOffset, bodyPosition.z);

            GetTransform()->SetTranslation(bodyPosition.Lerp(newPosition, dt * m_yStepShakeSpeed));
        }

        Super::Update(dt);
    }
}
