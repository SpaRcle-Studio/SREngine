//
// Created by Monika on 21.10.2023.
//

#include <Graphics/Font/Text3D.h>

namespace SR_GTYPES_NS {
    SR_REGISTER_COMPONENT(Text3D);

    SR_UTILS_NS::Component* Text3D::CopyComponent() const {
        auto&& pComponent = new Text3D();
        pComponent->SetText(m_text);
        pComponent->SetDebug(m_debug);
        pComponent->SetFont(m_font);
        pComponent->SetFontSize(m_fontSize);
        pComponent->SetKerning(m_kerning);
        return pComponent;
    }

    SR_UTILS_NS::Component* Text3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
        auto&& pComponent = new Text3D();
        if (!ITextComponent::LoadComponent(pComponent, marshal, dataStorage)) {
            pComponent->AutoFree([](auto&& pData) {
                delete pData;
            });
            return nullptr;
        }

        return pComponent;
    }
}