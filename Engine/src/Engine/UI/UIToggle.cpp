//
// Created by Codex on 15.11.2026.
//

#include <Engine/UI/UIToggle.h>
#include <Codegen/UIToggle.generated.hpp>

namespace SR_CORE_UI_NS {
    void UIToggle::RefreshVisual() {
        if (auto pObject = m_checkmark.Get()) {
            pObject->SetEnabled(m_value);
        }
    }

    void UIToggle::SetValue(bool value) {
        if (m_value == value) {
            return;
        }
        m_value = value;
        RefreshVisual();
        InvokeEvents(m_onValueChanged);
    }

    void UIToggle::OnPostLoad() {
        UIButton::OnPostLoad();
        RefreshVisual();
    }

    void UIToggle::Submit() {
        if (IsActive() && IsInteractable()) {
            SetValue(!m_value);
            UIButton::Submit();
        }
    }
}
