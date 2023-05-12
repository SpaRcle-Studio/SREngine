//
// Created by Monika on 06.05.2023.
//

#include <Graphics/Animations/AnimationStateCondition.h>

namespace SR_ANIMATIONS_NS {
    bool AnimationStateConditionAnd::IsSuitable(const StateConditionContext& context) const noexcept {
        for (auto&& pCondition : m_conditions) {
            if (!pCondition->IsSuitable(context)) {
                return false;
            }
        }

        return false;
    }

    void AnimationStateConditionAnd::Reset() {
        for (auto&& pCondition : m_conditions) {
            pCondition->Reset();
        }
        Super::Reset();
    }

    AnimationStateConditionAnd::~AnimationStateConditionAnd() {
        for (auto&& pCondition : m_conditions) {
            delete pCondition;
        }
    }

    bool AnimationStateConditionAnd::IsFinished(const StateConditionContext &context) const noexcept {
        for (auto&& pCondition : m_conditions) {
            if (!pCondition->IsFinished(context)) {
                return false;
            }
        }

        return true;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    AnimationStateConditionOr::~AnimationStateConditionOr() {
        for (auto&& pCondition : m_conditions) {
            delete pCondition;
        }
    }

    bool AnimationStateConditionOr::IsSuitable(const StateConditionContext& context) const noexcept {
        for (auto&& pCondition : m_conditions) {
            if (pCondition->IsSuitable(context)) {
                return true;
            }
        }

        return false;
    }

    void AnimationStateConditionOr::Reset() {
        for (auto&& pCondition : m_conditions) {
            pCondition->Reset();
        }
        Super::Reset();
    }

    bool AnimationStateConditionOr::IsFinished(const StateConditionContext &context) const noexcept {
        for (auto&& pCondition : m_conditions) {
            if (pCondition->IsFinished(context)) {
                return true;
            }
        }

        return false;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    bool AnimationStateConditionNot::IsSuitable(const StateConditionContext& context) const noexcept {
        if (!m_condition) {
            return false;
        }

        return !m_condition->IsSuitable(context);
    }

    bool AnimationStateConditionNot::IsFinished(const StateConditionContext& context) const noexcept {
        if (!m_condition) {
            return false;
        }

        return !m_condition->IsFinished(context);
    }

    void AnimationStateConditionNot::Reset() {
        if (m_condition) {
            m_condition->Reset();
        }

        Super::Reset();
    }

    AnimationStateConditionNot::~AnimationStateConditionNot() {
        SR_SAFE_DELETE_PTR(m_condition);
    }

    /// ----------------------------------------------------------------------------------------------------------------

    bool AnimationStateConditionExitTime::IsSuitable(const StateConditionContext& context) const noexcept {
        if (!context.pState) {
            return false;
        }

        return false;
    }

    bool AnimationStateConditionExitTime::IsFinished(const StateConditionContext& context) const noexcept {
        if (!context.pState) {
            return false;
        }

        return false;
    }
}