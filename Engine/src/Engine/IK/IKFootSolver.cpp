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

        if (!m_body || !m_footTarget || !m_config) {
            return;
        }

        auto&& body = *m_body.Get()->GetTransform();
        auto&& target = *m_footTarget.Get()->GetTransform();
        auto&& config = *m_config.Get();

        const SR_MATH_NS::FVector3 currentBodyPosition = body.GetGlobalTranslation();
        const SR_MATH_NS::FVector3 bodyMovement = currentBodyPosition - m_lastBodyPosition;
        m_lastBodyPosition = currentBodyPosition;

        m_bodyVelocity = m_bodyVelocity * (1.f - dt * config.bodyVelocityLerpSpeed);
        m_bodyVelocity += bodyMovement * 10.f * dt * config.bodyVelocityLerpSpeed;
        m_bodyVelocity = m_bodyVelocity.Clamp(-config.bodyVelocityLimit, config.bodyVelocityLimit);

        const float_t distanceToStep = config.distanceToStep * (1.f + m_bodyVelocity.Length() * config.distanceToStepSpeedFactor);

        const SR_MATH_NS::FVector3 origin = m_lastBodyPosition + body.TransformDirection(m_rayOffset);

        SR_UTILS_NS::LayerMask layerMask;
        layerMask.mask &= ~SR_UTILS_NS::TagManager::Instance().TagToMask("Player");

        if (auto&& hit = SR_PHYSICS_NS::Raycast3D::Instance().CastSingle(origin, -SR_MATH_NS::FVector3::Up(), config.maxRayDistance, layerMask)) {
            m_debugHitId = SR_UTILS_NS::DebugOverlayDraw::Instance().DrawLine(m_debugHitId,
                hit->position, hit->GetRayEndPoint(), SR_MATH_NS::FColor::Green(), SR_FLOAT_MAX
            );

            auto&& newPos = hit->position + target.TransformDirection(m_footOffset);
            const float_t distance = newPos.Distance(target.GetGlobalTranslation());

            const bool forceStepped = distance > config.forceStepDistance;
            if (auto&& pAnotherFoot = m_anotherFoot.Get()) {
                const bool isStepping = pAnotherFoot->GetProgress() < config.minProgressToAllowStep;
                if (isStepping && !pAnotherFoot->IsForceStepped() && !forceStepped && m_anotherFootWaitingTime < config.maxWaitingTimeAnotherFoot) {
                    m_anotherFootWaitingTime += dt;
                    Super::Update(dt);
                    return;
                }
                pAnotherFoot->m_anotherFootWaitingTime = 0.f;
            }

            m_forceStepped = forceStepped;

            m_stepProgress += dt * config.stepSpeed;
            if (m_stepProgress >= 1.f + config.stepRelaxTime) {
                m_anotherFootWaitingTime = 0.f;
                m_stepProgress = 1.f + config.stepRelaxTime;
            }

            if (!m_initialized || distance > SR_MIN(config.forceStepDistance, distanceToStep)) {
                //if (!m_initialized) {
                    m_footCurrentPosition = target.GetGlobalTranslation();
                    m_footCurrentRotation = target.GetGlobalRotation();
                //}
                //else {
                //    m_footCurrentPosition = m_footTargetPosition;
                //    m_footCurrentRotation = m_footTargetRotation;
                //}

                m_initialized = true;

                m_footTargetPosition = newPos - m_lastSideWayOffset;
                m_footTargetRotation = body.GetGlobalRotation() * SR_MATH_NS::Quaternion::AngleAxis(config.footXAngle, SR_MATH_NS::FVector3::Right());

                if (forceStepped) {
                    m_footCurrentPosition = m_footTargetPosition;
                    m_footCurrentRotation = m_footTargetRotation;
                }

                m_stepProgress = forceStepped ? 1.f : (m_stepProgress > config.uncompletedStepResetProgress ? 0.f : m_stepProgress);
            }


            const float_t ease = SR_MATH_NS::Curve::SmoothStep(0.f, 1.f, SR_MIN(m_stepProgress, 1.f));
            const float_t hor = SR_MATH_NS::Curve::CubicEaseInOut(SR_MIN(m_stepProgress, 1.f));
            //SR_MATH_NS::FVector3 footPos = SR_MATH_NS::FVector3::Lerp(m_footCurrentPosition, m_footTargetPosition, ease);
            SR_MATH_NS::FVector3 footPos = SR_MATH_NS::FVector3::Lerp(m_footCurrentPosition, m_footTargetPosition, hor);

            if (IsStepping()) {
                //const float_t lift = SR_MATH_NS::Curve::SinusoidalEaseInOut(m_stepProgress) * m_stepHeight;
                //footPos.y += lift;

                const float_t ver = SR_MATH_NS::Sin(SR_PI * SR_MIN(m_stepProgress, 1.f));  // чистая синусоида
                footPos.y += ver * config.stepHeight;

                const float_t sideways = SR_MATH_NS::Curve::CubicEaseInOut(SR_MIN(m_stepProgress, 1.f));
                m_lastSideWayOffset = SR_MATH_NS::FVector3(m_bodyVelocity.x, 0.f, m_bodyVelocity.z) * sideways * config.walkDirPredictionFactor;
                footPos += m_lastSideWayOffset;
            }
            else {
                m_lastSideWayOffset = SR_MATH_NS::FVector3();
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
