//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATETRANSITION_H
#define SR_ENGINE_ANIMATIONSTATETRANSITION_H

#include <Graphics/Animations/AnimationStateCondition.h>

#include <utility>

namespace SR_ANIMATIONS_NS {
    class AnimationState;
    class AnimationStateMachine;

    class AnimationStateTransition : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;

    public:
        AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination, AnimationStateCondition* pCondition);
        AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination);

        ~AnimationStateTransition() override;

    public:
        SR_NODISCARD virtual bool IsSuitable(const StateConditionContext& context) const noexcept;
        SR_NODISCARD virtual bool IsFinished(const StateConditionContext& context) const noexcept;

        SR_NODISCARD AnimationState* GetDestination() const noexcept { return m_destinationState; }

    protected:
        AnimationStateMachine* m_machine = nullptr;

        AnimationStateCondition* m_condition = nullptr;

        AnimationState* m_sourceState = nullptr;
        AnimationState* m_destinationState = nullptr;

    };
}

#endif //SR_ENGINE_ANIMATIONSTATETRANSITION_H
