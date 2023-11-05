//
// Created by Monika on 08.05.2023.
//

#ifndef SRENGINE_ANIMATIONSTATE_H
#define SRENGINE_ANIMATIONSTATE_H

#include <Graphics/Animations/AnimationStateTransition.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph;
    class AnimationClip;
    class AnimationStateMachine;

    class AnimationState : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using Transitions = std::vector<AnimationStateTransition*>;
    public:
        explicit AnimationState(AnimationStateMachine* pMachine)
            : Super()
            , m_machine(pMachine)
        { }

        ~AnimationState() override;

    public:
        SR_NODISCARD AnimationStateMachine* GetMachine() const noexcept { return m_machine; }

        SR_NODISCARD SR_UTILS_NS::TimePointType GetStart() const noexcept { return m_startPoint; }
        SR_NODISCARD SR_UTILS_NS::TimePointType GetEnd() const noexcept { return m_endPoint; }
        SR_NODISCARD Transitions& GetTransitions() noexcept { return m_transitions; }
        SR_NODISCARD const Transitions& GetTransitions() const noexcept { return m_transitions; }

        virtual void OnTransitionBegin(const UpdateContext& context) { }
        virtual void OnTransitionEnd(const UpdateContext& context) { }
        virtual void Update(const UpdateContext& context) { }

        template<class T = AnimationStateTransition, typename ...Args> T* AddTransition(Args&& ...args) {
            auto&& pTransition = new T(this, std::forward<Args>(args)...);
            m_transitions.emplace_back(dynamic_cast<AnimationStateTransition*>(pTransition));
            return pTransition;
        }

    protected:
        Transitions m_transitions;

        SR_UTILS_NS::TimePointType m_startPoint;
        SR_UTILS_NS::TimePointType m_endPoint;

        AnimationStateMachine* m_machine = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class IAnimationClipState : public AnimationState {
        using Super = AnimationState;
    public:
        explicit IAnimationClipState(AnimationStateMachine* pMachine, AnimationClip* pClip);

        ~IAnimationClipState() override;

    public:
        void SetClip(AnimationClip* pClip);

    protected:
        AnimationClip* m_clip = nullptr;
        uint32_t m_maxKeyFrame = 0;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationClipState : public IAnimationClipState {
        using Super = IAnimationClipState;
    public:
        explicit AnimationClipState(AnimationStateMachine* pMachine, AnimationClip* pClip)
            : Super(pMachine, pClip)
        { }

    public:
        void Update(const UpdateContext& context) override;

    protected:
        std::map<AnimationChannel*, uint32_t> m_playState;
        float_t m_time = 0.f;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationSetPoseState : public IAnimationClipState {
        using Super = IAnimationClipState;
    public:
        explicit AnimationSetPoseState(AnimationStateMachine* pMachine, AnimationClip* pClip)
            : Super(pMachine, pClip)
        { }

    public:
        void OnTransitionBegin(const UpdateContext& context) override;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationEntryPointState : public AnimationState {
    public:
        using Super = AnimationState;
        using Ptr = std::shared_ptr<AnimationEntryPointState>;
    public:
        explicit AnimationEntryPointState(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

    };
}

#endif //SRENGINE_ANIMATIONSTATE_H
