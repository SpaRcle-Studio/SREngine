//
// Created by Monika on 06.05.2023.
//

#ifndef SRENGINE_ANIMATIONSTATECONDITION_H
#define SRENGINE_ANIMATIONSTATECONDITION_H

#include <Utils/Types/Time.h>
#include <Graphics/Animations/AnimationCommon.h>

namespace SR_ANIMATIONS_NS {
    class AnimationStateCondition : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using Hash = uint64_t;
    public:
        explicit AnimationStateCondition(AnimationStateMachine* pMachine)
            : Super()
            , m_machine(pMachine)
        { }

    public:
        SR_NODISCARD AnimationStateMachine* GetMachine() const noexcept { return m_machine; }

        SR_NODISCARD virtual bool IsSuitable(const StateConditionContext& context) const noexcept = 0;

        SR_NODISCARD virtual bool IsFinished(const StateConditionContext& context) const noexcept {
            return IsSuitable(context);
        }

        virtual void Reset() { }

    protected:
        AnimationStateMachine* m_machine = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionTrue : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        explicit AnimationStateConditionTrue(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override { return true; }

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionAnd : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        explicit AnimationStateConditionAnd(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

        ~AnimationStateConditionAnd() override;

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;

        void Reset() override;

    protected:
        std::vector<AnimationStateCondition*> m_conditions;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionOr : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        explicit AnimationStateConditionOr(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

        ~AnimationStateConditionOr() override;

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;

        void Reset() override;

    protected:
        std::vector<AnimationStateCondition*> m_conditions;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionNot : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        explicit AnimationStateConditionNot(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

        ~AnimationStateConditionNot() override;

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;

        void Reset() override;

    protected:
        AnimationStateCondition* m_condition = nullptr;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    class AnimationStateConditionExitTime : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        explicit AnimationStateConditionExitTime(AnimationStateMachine* pMachine)
            : Super(pMachine)
        { }

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;

    protected:
        float_t duration = 0.25f;
        float_t exitTime = 0.75f;
        bool hasExitTime = true;

    };

    /// ----------------------------------------------------------------------------------------------------------------

    //class AnimationStateConditionOperationBase : public AnimationStateCondition {
    //    AnimationStateConditionOperationType m_type = AnimationStateConditionOperationType::Equals;

    //};

    /// ----------------------------------------------------------------------------------------------------------------

    //class AnimationStateConditionBool : public AnimationStateConditionOperationBase {
    //private:
    //    struct BoolVariable {
    //        bool m_useConst = true;
    //        bool m_const = false;
    //        Hash m_variable = 0;
    //    } m_data;
    //};
}

#endif //SRENGINE_ANIMATIONSTATECONDITION_H
