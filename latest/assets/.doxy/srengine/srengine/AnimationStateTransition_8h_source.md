

# File AnimationStateTransition.h

[**File List**](files.md) **>** [**Animations**](dir_417ea13389e3cbd1256e515e0204a036.md) **>** [**AnimationStateTransition.h**](AnimationStateTransition_8h.md)

[Go to the documentation of this file](AnimationStateTransition_8h.md)


```C++
//
// Created by Monika on 23.04.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATETRANSITION_H
#define SR_ENGINE_ANIMATIONSTATETRANSITION_H

#include <Graphics/Animations/AnimationStateCondition.h>

namespace SR_ANIMATIONS_NS {
    class AnimationState;
    class AnimationStateMachine;

    class AnimationStateTransition : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;

    public:
        SR_NODISCARD static AnimationStateTransition* Load(AnimationState* pSource, AnimationState* pDestination, const SR_XML_NS::Node& nodeXml);

        AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination, AnimationStateCondition* pCondition);
        AnimationStateTransition(AnimationState* pSource, AnimationState* pDestination);

        ~AnimationStateTransition() override;

    public:
        SR_NODISCARD virtual bool IsSuitable(const StateConditionContext& context) const noexcept;
        SR_NODISCARD virtual bool IsFinished(const StateConditionContext& context) const noexcept;

        void OnTransitionBegin(const StateConditionContext& context);

        SR_NODISCARD AnimationState* GetDestination() const noexcept { return m_destinationState; }
        SR_NODISCARD AnimationState* GetSource() const noexcept { return m_sourceState; }

        SR_NODISCARD bool IsActive() const noexcept { return m_isActive; }

        SR_NODISCARD float_t GetProgress() const noexcept { return m_condition ? m_condition->GetProgress().value_or(1.f) : 1.f; }

        virtual void Reset();
        virtual void Update(const StateConditionContext& context);

    protected:
        bool m_isActive = false;
        AnimationStateCondition* m_condition = nullptr;
        AnimationState* m_sourceState = nullptr;
        AnimationState* m_destinationState = nullptr;

    };
}

#endif //SR_ENGINE_ANIMATIONSTATETRANSITION_H
```


