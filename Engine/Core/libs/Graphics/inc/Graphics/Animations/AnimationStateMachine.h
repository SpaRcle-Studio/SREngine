//
// Created by Monika on 23.04.2023.
//

#ifndef SRENGINE_ANIMATIONSTATEMACHINE_H
#define SRENGINE_ANIMATIONSTATEMACHINE_H

#include <Graphics/Animations/AnimationStateTransition.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph;

    class AnimationState : public SR_UTILS_NS::NonCopyable {

    };

    class AnimationStateMachine : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
    private:
        std::vector<AnimationState*> m_states;
        std::vector<AnimationStateTransition*> m_transitions;

    };
}

#endif //SRENGINE_ANIMATIONSTATEMACHINE_H
