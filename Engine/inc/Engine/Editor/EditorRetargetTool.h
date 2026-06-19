//
// Created by Monika on 18.06.2026.
//

#ifndef SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H
#define SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H

#include <Engine/stdInclude.h>

#include <Graphics/Animations/Skeleton.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(EditorRetargetToolTestMode, uint8_t,
        V1,
        V2
    );

    class EditorRetargetTool : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

        void TestV1(SR_ANIMATIONS_NS::Skeleton* pSkeleton);
        void TestV2(SR_ANIMATIONS_NS::Skeleton* pSkeleton);

    private:
        /// @property
        EditorRetargetToolTestMode m_testMode = EditorRetargetToolTestMode::V2;
        /// @property
        SR_UTILS_NS::EntityRef<SR_ANIMATIONS_NS::Skeleton> m_sourceSkeleton;
        /// @property
        SR_UTILS_NS::Vector<SR_UTILS_NS::EntityRef<SR_ANIMATIONS_NS::Skeleton>> m_targetSkeletons;

    };
}

#endif //SR_ENGINE_CORE_EDITOR_EDITOR_RETARGET_TOOL_H
