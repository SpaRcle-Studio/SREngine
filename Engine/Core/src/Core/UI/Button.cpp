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
        m_properties.AddEntityRefProperty(SR_BUTTON_IDLE_PROP_NAME, GetThis()).SetWidth(260.f);
        m_properties.AddEntityRefProperty(SR_BUTTON_HOVERED_PROP_NAME, GetThis()).SetWidth(260.f);
        m_properties.AddEntityRefProperty(SR_BUTTON_PRESSED_PROP_NAME, GetThis()).SetWidth(260.f);

        return Super::InitializeEntity();
    }

    void Button::Update(float_t dt) {
        Super::Update(dt);

        if (auto&& pRef = GetComponentProperties().Find<SR_UTILS_NS::EntityRefProperty>(SR_BUTTON_IDLE_PROP_NAME)) {
            if (auto&& pGameObject = pRef->GetEntityRef().GetGameObject()) {
                pGameObject->SetEnabled(IsIdle());
            }
        }

        if (auto&& pRef = GetComponentProperties().Find<SR_UTILS_NS::EntityRefProperty>(SR_BUTTON_HOVERED_PROP_NAME)) {
            if (auto&& pGameObject = pRef->GetEntityRef().GetGameObject()) {
                pGameObject->SetEnabled(IsHovered());
            }
        }

        if (auto&& pRef = GetComponentProperties().Find<SR_UTILS_NS::EntityRefProperty>(SR_BUTTON_PRESSED_PROP_NAME)) {
            if (auto&& pGameObject = pRef->GetEntityRef().GetGameObject()) {
                pGameObject->SetEnabled(IsPressed());
            }
        }
    }
}