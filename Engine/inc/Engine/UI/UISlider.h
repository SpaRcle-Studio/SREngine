//
// Created by Codex on 15.11.2026.
//

#ifndef SR_ENGINE_UI_SLIDER_H
#define SR_ENGINE_UI_SLIDER_H

#include <Engine/UI/UIControl.h>

namespace SR_CORE_UI_NS {
    /// @category(UI)
    class UISlider : public UIControl {
        SR_CLASS()
    public:
        /// @method
        void SetValue(float_t value);
        /// @method @evaluate
        float_t GetValue() const noexcept { return m_value; }
        void PointerDown(const SR_UTILS_NS::PointerEvent& event) override;
        bool CanDrag() const override { return true; }
        void PointerDrag(const SR_UTILS_NS::PointerEvent& event) override;
        bool Navigate(int32_t direction) override;
        void OnPostLoad() override;

    private:
        void RefreshVisual();
        void OnRangeChanged();
        /// @property @setter(SetValue)
        float_t m_value = 0.f;
        /// @property @onChanged(OnRangeChanged)
        float_t m_minValue = 0.f;
        /// @property @onChanged(OnRangeChanged)
        float_t m_maxValue = 1.f;
        /// @property
        float_t m_keyboardStep = 0.05f;
        /// @property @onChanged(OnRangeChanged)
        bool m_wholeNumbers = false;
        /// @property @onChanged(RefreshVisual)
        bool m_vertical = false;
        /// @property @onChanged(RefreshVisual)
        bool m_reverse = false;
        /// @property @onChanged(RefreshVisual)
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_handle;
        /// @property
        SR_UTILS_NS::Vector<UIButtonEvent> m_onValueChanged;
    };
}

#endif // SR_ENGINE_UI_SLIDER_H
