//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Engine/UI/IButton.h>

namespace SR_CORE_UI_NS {
    class Button : public IButton {
        using Super = IButton;
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_IDLE_PROP_NAME = "Idle";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_HOVERED_PROP_NAME = "Hovered";
        SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_BUTTON_PRESSED_PROP_NAME = "Pressed";

    public:
        void OnDestroy() override;
        void Update(float_t dt) override;
    };
} // namespace SR_CORE_UI_NS

#endif // SR_ENGINE_UI_BUTTON_H
