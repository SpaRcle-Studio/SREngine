//
// Created by Monika on 20.11.2022.
//

#include <Engine/UI/UIButton.h>
#include <Codegen/UIButton.generated.hpp>

namespace SR_CORE_UI_NS {
    bool UIButton::AcceptsButton(SR_UTILS_NS::PointerButton button) const {
        return (m_leftClick && button == SR_UTILS_NS::PointerButton::Primary)
            || (m_rightClick && button == SR_UTILS_NS::PointerButton::Secondary)
            || (m_middleClick && button == SR_UTILS_NS::PointerButton::Middle);
    }

    void UIButton::PointerUp(const SR_UTILS_NS::PointerEvent& event, bool click) {
        if (click) {
            Submit();
        }
    }

    void UIButton::Submit() {
        if (IsActive() && IsInteractable()) {
            InvokeEvents(m_onClickEvents);
        }
    }
}
