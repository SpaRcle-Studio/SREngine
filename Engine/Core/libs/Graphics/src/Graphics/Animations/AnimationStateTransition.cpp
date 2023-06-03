//
// Created by Monika on 06.05.2023.
//

#include <Graphics/Animations/AnimationStateTransition.h>

namespace SR_ANIMATIONS_NS {
    AnimationStateTransition::AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination, AnimationStateCondition* pCondition)
        : Super()
        , m_machine(pSource->GetMachine())
        , m_condition(pCondition)
        , m_sourceState(pSource)
        , m_destinationState(pDestination)
    { 
        SRAssert(m_destinationState != m_sourceState);
    }

    AnimationStateTransition::AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination)
        : Super()
        , m_machine(pSource->GetMachine())
        , m_sourceState(pSource)
        , m_destinationState(pDestination)
    { 
        SRAssert(m_destinationState != m_sourceState);
    }

    AnimationStateTransition::~AnimationStateTransition() {
        SR_SAFE_DELETE_PTR(m_condition);
        m_machine = nullptr;
        m_sourceState = nullptr;
        m_destinationState = nullptr;
    }

    bool AnimationStateTransition::IsSuitable(const StateConditionContext& context) const noexcept {
        if (m_condition) {
            return m_condition->IsSuitable(context);
        }

        return true;
    }

    bool AnimationStateTransition::IsFinished(const StateConditionContext& context) const noexcept {
        if (m_condition) {
            return m_condition->IsFinished(context);
        }

        return true;
    }
}