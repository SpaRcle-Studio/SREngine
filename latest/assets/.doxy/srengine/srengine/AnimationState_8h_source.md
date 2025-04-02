

# File AnimationState.h

[**File List**](files.md) **>** [**Animations**](dir_417ea13389e3cbd1256e515e0204a036.md) **>** [**AnimationState.h**](AnimationState_8h.md)

[Go to the documentation of this file](AnimationState_8h.md)


```C++
//
// Created by Monika on 08.05.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATE_H
#define SR_ENGINE_ANIMATIONSTATE_H

#include <Graphics/Animations/AnimationStateTransition.h>

namespace SR_ANIMATIONS_NS {
    class AnimationGraph;
    class AnimationClip;
    class AnimationStateMachine;

    class AnimationState : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using Transitions = std::vector<AnimationStateTransition*>;
    public:
        explicit AnimationState()
            : Super()
        { }

        ~AnimationState() override;

    public:
        SR_NODISCARD static AnimationState* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD AnimationStateMachine* GetMachine() const noexcept { return m_machine; }

        SR_NODISCARD virtual SR_UTILS_NS::StringAtom GetName() const noexcept = 0;
        SR_NODISCARD virtual float_t GetProgress() const noexcept { return 1.f; }
        SR_NODISCARD virtual float_t GetDuration() const noexcept { return 0.f; }
        SR_NODISCARD virtual float_t GetTime() const noexcept { return 0.f; }

        SR_NODISCARD AnimationStateTransition* GetActiveTransition() const noexcept { return m_activeTransition; }

        SR_NODISCARD Transitions& GetTransitions() noexcept { return m_transitions; }
        SR_NODISCARD const Transitions& GetTransitions() const noexcept { return m_transitions; }
        SR_NODISCARD bool IsResetOnPlay() const noexcept { return m_resetOnPlay; }

        void OnTransitionBegin(AnimationStateTransition* pTransition);
        void OnTransitionDone();
        virtual void Update(const UpdateContext& context) { }

        void SetMachine(AnimationStateMachine* pMachine) { m_machine = pMachine; }
        void SetResetOnPlay(bool reset) { m_resetOnPlay = reset; }

        virtual void Reset() { }

        virtual void Update(UpdateContext& context) { }
        virtual bool Compile(CompileContext& context) { return true; }

        template<class T = AnimationStateTransition, typename ...Args> T* AddTransition(Args&& ...args) {
            return AddTransition(new T(this, std::forward<Args>(args)...));
        }

        template<class T> T* AddTransition(T* pTransition) {
            m_transitions.emplace_back(dynamic_cast<AnimationStateTransition*>(pTransition));
            return pTransition;
        }

    protected:
        bool m_resetOnPlay = false;
        Transitions m_transitions;
        AnimationStateTransition* m_activeTransition = nullptr;
        AnimationStateMachine* m_machine = nullptr;

    };


    class AnimationNoneState : public AnimationState {
        using Super = AnimationState;
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept override { return "None"; }

    };


    class AnimationClipState : public AnimationState {
        using Super = AnimationState;
    public:
        ~AnimationClipState() override;

        SR_NODISCARD static AnimationClipState* Load(const SR_XML_NS::Node& nodeXml);

        void Update(UpdateContext& context) override;
        bool Compile(CompileContext& context) override;
        void Reset() override;
        void SetClip(AnimationClip* pClip);

        SR_NODISCARD float_t GetProgress() const noexcept override;
        SR_NODISCARD float_t GetDuration() const noexcept override { return m_duration; }
        SR_NODISCARD float_t GetTime() const noexcept override { return m_time; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept override;

    protected:
        std::vector<ChannelUpdateContext> m_channelContexts;
        AnimationClip* m_clip = nullptr;
        uint32_t m_maxKeyFrame = 0;
        float_t m_duration = 0.f;
        float_t m_time = 0.f;
        std::vector<uint32_t> m_channelPlayState;
    };


    class AnimationEntryPointState : public AnimationState {
        using Super = AnimationState;
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetName() const noexcept override { return "SR_ENGINE_ENTRY_POINT"; }

    };
}

#endif //SR_ENGINE_ANIMATIONSTATE_H
```


