//
// Created by Monika on 09.12.2025.
//


#ifndef SR_ENGINE_CORE_IK_FOOT_SOLVER_CONFIG_H
#define SR_ENGINE_CORE_IK_FOOT_SOLVER_CONFIG_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>

namespace SR_CORE_NS {
    /// @category(Animations)
    class IKFootSolverConfig : public SR_UTILS_NS::Component {
        using Super = Component;
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<IKFootSolverConfig>;

    public:
        /// @property
        float_t maxRayDistance = 2.0f;
        /// @property
        float_t distanceToStep = 0.1f;
        /// @property
        float_t forceStepDistance = 1.5f;
        /// @property
        float_t footXAngle = 0.f;
        /// @property
        float_t stepSpeed = 1.f;
        /// @property
        float_t stepRelaxTime = 0.1f;
        /// @property
        float_t stepHeight = 0.2f;
        /// @property
        float_t walkDirPredictionFactor = 1.0f;
        /// @property
        float_t bodyVelocityLimit = 2.0f;
        /// @property
        float_t bodyVelocityLerpSpeed = 1.0f;
        /// @property
        float_t distanceToStepSpeedFactor = 1.0f;
        /// @property
        float_t maxWaitingTimeAnotherFoot = 0.3f;
        /// @property
        float_t uncompletedStepResetProgress = 0.5f;
        /// @property
        float_t minProgressToAllowStep = 0.7f;

    };
}

#endif //SR_ENGINE_CORE_IK_FOOT_SOLVER_CONFIG_H
