

# File AnimationStateMachine.h

[**File List**](files.md) **>** [**Animations**](dir_417ea13389e3cbd1256e515e0204a036.md) **>** [**AnimationStateMachine.h**](AnimationStateMachine_8h.md)

[Go to the documentation of this file](AnimationStateMachine_8h.md)


```C++
//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATEMACHINE_H
#define SR_ENGINE_ANIMATIONSTATEMACHINE_H

#include <Graphics/Animations/AnimationState.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph;

    class AnimationStateMachine : public IAnimationDataSet, public SR_UTILS_NS::NonCopyable {
        using Super = IAnimationDataSet;
    public:
        AnimationStateMachine();
        ~AnimationStateMachine() override;

    public:
        SR_NODISCARD static AnimationStateMachine* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD bool IsStateActive(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD AnimationEntryPointState* GetEntryPoint() const;
        SR_NODISCARD AnimationState* FindState(SR_UTILS_NS::StringAtom name) const;
        SR_NODISCARD AnimationState* GetState(uint32_t index) const;
        SR_NODISCARD const std::vector<AnimationState*>& GetStates() const noexcept { return m_states; }

        void Compile(CompileContext& context);
        void Update(UpdateContext& context);

        template<class T, typename... Args> T* CreateState(Args&& ...args) {
            return AddState(new T(std::forward<Args>(args)...));
        }

        template<class T> T* AddState(T* pState) {
            SR_STATIC_ASSERT2((std::is_base_of_v<AnimationState, T>), "T must be derived from AnimationState");
            m_states.emplace_back(dynamic_cast<AnimationState*>(pState));
            pState->SetMachine(this);
            return pState;
        }

        void SetNode(AnimationGraphNode* pNode) { m_node = pNode; }

    private:
        bool UpdateTransition(UpdateContext& context, AnimationStateTransition* pTransition, bool& hasActiveTransitions);

    private:
        AnimationGraphNode* m_node = nullptr;

        std::vector<AnimationState*> m_states;

        std::set<AnimationState*> m_activeStates;

    };
}

#endif //SR_ENGINE_ANIMATIONSTATEMACHINE_H
```


