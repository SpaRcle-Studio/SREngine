//
// Created by Monika on 20.11.2022.
//

#include <Core/UI/Button.h>

namespace SR_CORE_UI_NS {
    void Button::OnDestroy() {
        Super::OnDestroy();

        AutoFree([](auto&& pData) {
            delete pData;
        });
    }

    bool Button::InitializeEntity() noexcept {
        return Super::InitializeEntity();
    }
}