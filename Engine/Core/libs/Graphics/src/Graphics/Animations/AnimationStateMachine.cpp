//
// Created by Monika on 08.05.2023.
//

#include <Graphics/Animations/AnimationStateMachine.h>

namespace SR_ANIMATIONS_NS {
    AnimationStateMachine::AnimationStateMachine(IAnimationDataSet* pParent)
        : Super(pParent)
    {
        AddState<AnimationEntryPointState>();
        m_activeStates.insert(GetEntryPoint());
    }

    AnimationStateMachine::~AnimationStateMachine() {
        for (auto&& pState : m_states) {
            delete pState;
        }
    }

    void AnimationStateMachine::Update(const UpdateContext& context) {
        SR_TRACY_ZONE;

        for (auto pIt = m_activeStates.begin(); pIt != m_activeStates.end(); ) {
            AnimationState* pState = *pIt;

            pState->Update(context);

            StateConditionContext stateConditionContext;
            stateConditionContext.pState = pState;
            stateConditionContext.pMachine = this;

            bool changed = false;

            for (auto&& pTransition : pState->GetTransitions()) {
                if (!pTransition->IsSuitable(stateConditionContext)) {
                    continue;
                }

                auto&& pDestinationState = pTransition->GetDestination();
                if (!pDestinationState) {
                    continue;
                }

                pDestinationState->OnTransitionBegin(context);

                if (pTransition->IsFinished(stateConditionContext)) {
                    pDestinationState->OnTransitionEnd(context);

                    if (m_activeStates.count(pState) == 1) {
                        pIt = m_activeStates.erase(pIt);
                    }

                    pIt = m_activeStates.insert(pIt, pDestinationState);

                    changed = true;
                }
            }

            if (!changed) {
                ++pIt;
            }
        }
    }

    AnimationEntryPointState* AnimationStateMachine::GetEntryPoint() const {
        if (auto&& pState = dynamic_cast<AnimationEntryPointState*>(m_states.front())) {
            return pState;
        }

        SRHalt("Failed to get entry point!");

        return nullptr;
    }
}