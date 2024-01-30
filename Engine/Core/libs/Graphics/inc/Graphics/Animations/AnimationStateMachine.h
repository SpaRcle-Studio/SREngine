//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATEMACHINE_H
#define SR_ENGINE_ANIMATIONSTATEMACHINE_H

#include <Graphics/Animations/AnimationState.h>

namespace SR_ANIMATIONS_NS {
    class AnimationStateMachine : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
        using Super = IAnimationDataSet;
    public:
        explicit AnimationStateMachine(IAnimationDataSet* pParent);
        ~AnimationStateMachine() override;

    public:
        virtual void Update(const UpdateContext& context);

        SR_NODISCARD AnimationEntryPointState* GetEntryPoint() const;

        template<class T, typename... Args> T* AddState(Args&& ...args) {
            auto&& pState = new T(this, std::forward<Args>(args)...);
            m_states.emplace_back(dynamic_cast<AnimationState*>(pState));
            return pState;
        }

    private:
        /// первый стейт это всегда EntryPoint
        std::vector<AnimationState*> m_states;

        std::set<AnimationState*> m_activeStates;

    };
}

#endif //SR_ENGINE_ANIMATIONSTATEMACHINE_H
