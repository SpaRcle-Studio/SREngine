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
    public:
        bool InitializeEntity() noexcept override;
        void OnDestroy() override;

    };
}

#endif //SR_ENGINE_UI_BUTTON_H
