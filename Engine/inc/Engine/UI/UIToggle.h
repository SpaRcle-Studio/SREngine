//
// Created by Codex on 15.11.2026.
//

#ifndef SR_ENGINE_UI_TOGGLE_H
#define SR_ENGINE_UI_TOGGLE_H

#include <Engine/UI/UIButton.h>

namespace SR_CORE_UI_NS {
    /// @category(UI)
    class UIToggle : public UIButton {
        SR_CLASS()
    public:
        /// @method
        void SetValue(bool value);
        /// @method @evaluate
        bool GetValue() const noexcept { return m_value; }
        void Submit() override;
        void OnPostLoad() override;

    private:
        void RefreshVisual();
        /// @property @setter(SetValue)
        bool m_value = false;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_checkmark;
        /// @property
        SR_UTILS_NS::Vector<UIButtonEvent> m_onValueChanged;
    };
}

#endif // SR_ENGINE_UI_TOGGLE_H
