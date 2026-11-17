//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Engine/UI/UIControl.h>

namespace SR_CORE_UI_NS {
    /// @category(UI)
    class UIButton : public UIControl {
        SR_CLASS()
    public:
        bool AcceptsButton(SR_UTILS_NS::PointerButton button) const override;
        void PointerUp(const SR_UTILS_NS::PointerEvent& event, bool click) override;
        void Submit() override;
        /// @method
        void SetClickReceiver(const SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::Component>& pReceiver, SR_UTILS_NS::StringAtom method);

    private:
        /// @property
        SR_UTILS_NS::Vector<UIButtonEvent> m_onClickEvents;
        /// @property @group(Mouse Events)
        bool m_leftClick = true;
        /// @property @group(Mouse Events)
        bool m_rightClick = false;
        /// @property @group(Mouse Events)
        bool m_middleClick = false;
    };
}

#endif // SR_ENGINE_UI_BUTTON_H
