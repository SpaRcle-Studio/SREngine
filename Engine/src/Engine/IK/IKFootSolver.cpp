//
// Created by Monika on 04.12.2025.
//

#include <Engine/IK/IKFootSolver.h>

#include <Physics/3D/Raycast3D.h>

#include <Utils/DebugDraw.h>
#include <Utils/Math/Curve.h>

#include <Codegen/IKFootSolver.generated.hpp>

namespace SR_CORE_NS {
    void IKFootSolver::OnDisable() {
        SR_UTILS_NS::DebugOverlayDraw::Instance().TryRemove(&m_debugHitId);
        Super::OnDisable();
    }

    void IKFootSolver::Update(float_t dt) {
        SR_TRACY_ZONE;

        if (!m_body || !m_footTarget) {
            return;
        }

        auto&& body = *m_body.Get()->GetTransform();
        auto&& target = *m_footTarget.Get()->GetTransform();

        const SR_MATH_NS::FVector3 origin = body.GetGlobalTranslation() + body.TransformDirection(m_rayOffset);

        if (auto&& hit = SR_PHYSICS_NS::Raycast3D::Instance().CastSingle(origin, -SR_MATH_NS::FVector3::Up(), m_maxRayDistance)) {
            m_debugHitId = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawLine(m_debugHitId,
                hit->position, hit->GetRayEndPoint(), SR_MATH_NS::FColor::Green(), SR_FLOAT_MAX
            );

            auto&& newPos = hit->position + target.TransformDirection(m_footOffset);
            const float_t distance = newPos.Distance(target.GetGlobalTranslation());

            const bool forceStepped = distance > m_forceStepDistance;
            if (auto&& pAnotherFoot = m_anotherFoot.Get()) {
                if (pAnotherFoot->IsStepping() && !forceStepped) {
                    Super::Update(dt);
                    return;
                }

                //if (pAnotherFoot->GetProgress() > m_stepProgress && forceStepped) {
                //    Super::Update(dt);
                //    return;
                //}
            }

            m_stepProgress = SR_MIN(1.f, m_stepProgress + dt * m_stepSpeed);

            if (!m_initialized || distance > m_distanceToStep) {
                if (!m_initialized) {
                    m_footCurrentPosition = target.GetGlobalTranslation();
                    m_footCurrentRotation = target.GetGlobalRotation();
                }
                else {
                    m_footCurrentPosition = m_footTargetPosition;
                    m_footCurrentRotation = m_footTargetRotation;
                }

                m_initialized = true;

                m_footTargetPosition = newPos;
                m_footTargetRotation = body.GetGlobalRotation() * SR_MATH_NS::Quaternion::AngleAxis(m_footXAngle, SR_MATH_NS::FVector3::Right());

                if (forceStepped) {
                    m_footCurrentPosition = m_footTargetPosition;
                    m_footCurrentRotation = m_footTargetRotation;
                }

                m_stepProgress = forceStepped ? 1.f : 0.f;
            }


            const float_t ease = SR_MATH_NS::Curve::SmoothStep(0.f, 1.f, m_stepProgress);
            const float_t hor = SR_MATH_NS::Curve::CubicEaseInOut(m_stepProgress);
            //SR_MATH_NS::FVector3 footPos = SR_MATH_NS::FVector3::Lerp(m_footCurrentPosition, m_footTargetPosition, ease);
            SR_MATH_NS::FVector3 footPos = SR_MATH_NS::FVector3::Lerp(m_footCurrentPosition, m_footTargetPosition, hor);

            if (IsStepping()) {
                //const float_t lift = SR_MATH_NS::Curve::SinusoidalEaseInOut(m_stepProgress) * m_stepHeight;
                //footPos.y += lift;

                const float_t ver = SR_MATH_NS::Sin(SR_PI * m_stepProgress);  // чистая синусоида
                footPos.y += ver * m_stepHeight;
            }

            target.SetGlobalTranslation(footPos);
            target.SetRotation(SR_MATH_NS::Quaternion::Slerp(m_footCurrentRotation, m_footTargetRotation, ease));
        }
        else {
            SR_UTILS_NS::DebugOverlayDraw::Instance().TryRemove(&m_debugHitId);
        }

        Super::Update(dt);
    }

    bool IKFootSolver::IsStepping() const noexcept {
        return m_stepProgress < 1.f;
    }

    float_t IKFootSolver::GetProgress() const noexcept {
        return m_stepProgress;
    }
}
