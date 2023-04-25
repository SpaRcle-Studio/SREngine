//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONSTATETRANSITION_H
#define SRENGINE_ANIMATIONSTATETRANSITION_H

#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    SR_ENUM_NS_CLASS_T(AnimationStateConditionOperationType, uint8_t,
        Equals, Less, More, NotEquals
    );

    class AnimationStateCondition : public SR_UTILS_NS::NonCopyable {
    protected:
        using Hash = uint64_t;

    public:
        virtual bool Evaluate(IAnimationDataSet* pDataSet) const noexcept = 0;

    };

    class AnimationStateConditionAnd : public AnimationStateCondition {

    };

    class AnimationStateConditionOr : public AnimationStateCondition {

    };

    class AnimationStateConditionNot : public AnimationStateCondition {

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionOperationBase : public AnimationStateCondition {
        AnimationStateConditionOperationType m_type = AnimationStateConditionOperationType::Equals;

    };

    class AnimationStateConditionBool : public AnimationStateConditionOperationBase {
    private:
        struct BoolVariable {
            bool m_useConst = true;
            bool m_const = false;
            Hash m_variable = 0;
        } m_data;
    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateTransition : public SR_UTILS_NS::NonCopyable {
        AnimationStateCondition* m_condition = nullptr;
    };
}

#endif //SRENGINE_ANIMATIONSTATETRANSITION_H
