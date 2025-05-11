

# File AnimationStateCondition.h

[**File List**](files.md) **>** [**Animations**](dir_f2b59a27925630266b6aa3e5cfad87aa.md) **>** [**AnimationStateCondition.h**](AnimationStateCondition_8h.md)

[Go to the documentation of this file](AnimationStateCondition_8h.md)


```C++
//
// Created by Monika on 06.05.2023.
//

#ifndef SR_ENGINE_ANIMATIONSTATECONDITION_H
#define SR_ENGINE_ANIMATIONSTATECONDITION_H

#include <Utils/Types/Time.h>
#include <Graphics/Animations/AnimationContext.h>

namespace SR_ANIMATIONS_NS {
    class AnimationStateTransition;

    class AnimationStateCondition : public SR_UTILS_NS::NonCopyable {
    using Super = SR_UTILS_NS::NonCopyable;
    public:
        SR_NODISCARD static AnimationStateCondition* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD virtual bool IsSuitable(const StateConditionContext& context) const noexcept = 0;
        SR_NODISCARD virtual bool IsFinished(const StateConditionContext& context) const noexcept {
            return IsSuitable(context);
        }

        SR_NODISCARD virtual bool IsNeedBreakUpdate() const noexcept { return false; }

        SR_NODISCARD virtual std::optional<float_t> GetProgress() const noexcept { return std::nullopt; }

        virtual void Reset() { }
        virtual void Update(const StateConditionContext& context) { }

    };


    class AnimationStateConditionTrue : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override { return true; }

    };


    class AnimationStateConditionAnd : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        ~AnimationStateConditionAnd() override;

    public:
        SR_NODISCARD static AnimationStateConditionAnd* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsNeedBreakUpdate() const noexcept override;
        SR_NODISCARD std::optional<float_t> GetProgress() const noexcept override;

        void Reset() override;
        void Update(const StateConditionContext& context) override;

    protected:
        std::vector<AnimationStateCondition*> m_conditions;

    };


    class AnimationStateConditionOr : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        ~AnimationStateConditionOr() override;

    public:
        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsNeedBreakUpdate() const noexcept override;
        SR_NODISCARD std::optional<float_t> GetProgress() const noexcept override;

        void Reset() override;

    protected:
        std::vector<AnimationStateCondition*> m_conditions;

    };


    class AnimationStateConditionNot : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        ~AnimationStateConditionNot() override;

    public:
        SR_NODISCARD static AnimationStateConditionNot* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsNeedBreakUpdate() const noexcept override;
        SR_NODISCARD std::optional<float_t> GetProgress() const noexcept override;

        void Update(const StateConditionContext& context) override;
        void Reset() override;

    protected:
        AnimationStateCondition* m_condition = nullptr;

    };


    class AnimationStateConditionExitTime : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        SR_NODISCARD static AnimationStateConditionExitTime* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD bool IsFinished(const StateConditionContext& context) const noexcept override;

        SR_NODISCARD std::optional<float_t> GetProgress() const noexcept override;

        void Reset() override;
        void Update(const StateConditionContext& context) override;

    protected:
        float_t m_dtCapacity = 0.f;
        float_t m_dtDuration = 0.f;
        float_t m_dtExitTime = 0.f;

        float_t m_duration = 0.25f;
        float_t m_exitTime = 0.75f;
        bool m_hasExitTime = true;

    };


    //class AnimationStateConditionOperationBase : public AnimationStateCondition {
    //    AnimationStateConditionOperationType m_type = AnimationStateConditionOperationType::Equals;

    //};


    class AnimationStateConditionBool : public AnimationStateCondition {
        using Super = AnimationStateCondition;
    public:
        SR_NODISCARD static AnimationStateConditionBool* Load(const SR_XML_NS::Node& nodeXml);

        SR_NODISCARD bool IsSuitable(const StateConditionContext& context) const noexcept override;
        SR_NODISCARD void Update(const StateConditionContext& context) override;
        SR_NODISCARD bool IsNeedBreakUpdate() const noexcept override { return !m_checked; }

        void Reset() override;

    private:
        SR_UTILS_NS::StringAtom m_variableName;
        bool m_value = false;
        bool m_checked = false;

    };
}

#endif //SR_ENGINE_ANIMATIONSTATECONDITION_H
```


