//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Core/UI/IButton.h>

namespace SR_CORE_UI_NS {
    class Button : public IButton {
        SR_REGISTER_NEW_COMPONENT(Button, 1001);
        using Super = IButton;
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_IDLE_PROP_NAME = "Idle";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_HOVERED_PROP_NAME = "Hovered";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_PRESSED_PROP_NAME = "Pressed";
    public:
        bool InitializeEntity() noexcept override;
        void OnDestroy() override;
        void Update(float_t dt) override;

    };
}

#endif //SR_ENGINE_UI_BUTTON_H
