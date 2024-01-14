//
// Created by Monika on 20.11.2022.
//

#include <Core/UI/Button.h>

namespace SR_CORE_UI_NS {
    SR_REGISTER_COMPONENT(Button);

    SR_UTILS_NS::Component* Button::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return new Button();
    }

    SR_HTYPES_NS::Marshal::Ptr Button::Save(SR_UTILS_NS::SavableContext data) const {
        auto&& pMarshal = Super::Save(data);
        return pMarshal;
    }

    void Button::OnDestroy() {
        Super::OnDestroy();

        GetThis().AutoFree([](auto&& pData) {
            delete pData;
        });
    }
}