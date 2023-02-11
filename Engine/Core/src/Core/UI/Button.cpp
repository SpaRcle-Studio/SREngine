//
// Created by Monika on 20.11.2022.
//

#include <Core/UI/Button.h>

namespace SR_CORE_UI_NS {
    Button::Button()
        : Super()
    { }

    SR_UTILS_NS::Component* Button::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        return new Button();
    }

    SR_HTYPES_NS::Marshal::Ptr Button::Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const {
        pMarshal = Super::Save(pMarshal, flags);
        return pMarshal;
    }
}
