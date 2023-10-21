//
// Created by Monika on 21.10.2023.
//

#ifndef SRENGINE_TEXT3D_H
#define SRENGINE_TEXT3D_H

#include <Graphics/Font/ITextComponent.h>

namespace SR_GTYPES_NS {
    class Text3D : public ITextComponent {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Text3D);
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD Component* CopyComponent() const override;

    };
}

#endif //SRENGINE_TEXT3D_H
