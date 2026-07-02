//
// Created by Monika on 18.06.2026.
//

#ifndef SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H
#define SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H

#include <Engine/stdInclude.h>

#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/Retarget/RetargetReferencePoseDeltaAlgorithm.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>

namespace SR_CORE_NS {
    class EditorRetargetTool : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

        void TwoBoneIK(SR_ANIMATIONS_NS::Skeleton* pSkeleton);

    private:
        SR_ANIMATIONS_NS::RetargetReferencePoseDeltaAlgorithmState::RotationFollowStateMap m_retargetState;

    private:
        /// @property @group(Offsets)
        float_t m_scaleFactor = 1.f;
        /// @property @group(Offsets)
        SR_MATH_NS::FVector3 m_targetHipsOffset;
        /// @property @group(Offsets)
        SR_MATH_NS::FVector3 m_IKLeftHandOffset;
        /// @property @group(Offsets)
        SR_MATH_NS::FVector3 m_IKRightHandOffset;
        /// @property @group(Offsets)
        SR_MATH_NS::FVector3 m_IKLeftFootOffset;
        /// @property @group(Offsets)
        SR_MATH_NS::FVector3 m_IKRightFootOffset;

        /// @property
        float m_smoothing = 10.f;
        /// @property
        float m_twoBoneWeight = 1.f;
        /// @property
        uint8_t m_twoBoneIterations = 32;
        /// @property
        float m_ccdWeight = 0.35f;
        /// @property
        uint8_t m_ccdIterations = 6;
        /// @property
        bool m_twoBoneIKEnabled = true;
        /// @property
        bool m_handTipRotationFromTarget = false;
        /// @property
        bool m_footTipRotationFromTarget = true;
        /// @property
        SR_UTILS_NS::EntityRef<SR_ANIMATIONS_NS::Skeleton> m_sourceSkeleton;
        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<SR_ANIMATIONS_NS::Skeleton>> m_targetSkeletons;

    };
}

#endif //SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H
