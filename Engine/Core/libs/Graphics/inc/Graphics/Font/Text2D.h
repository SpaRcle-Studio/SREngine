//
// Created by Monika on 21.10.2023.
//

#ifndef SRENGINE_TEXT2D_H
#define SRENGINE_TEXT2D_H

#include <Graphics/Font/ITextComponent.h>

namespace SR_GTYPES_NS {
    class Text2D : public ITextComponent {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Text2D);
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD bool IsFlatMesh() const noexcept override { return true; }
        SR_NODISCARD Component* CopyComponent() const override;

    };
}

#endif //SRENGINE_TEXT2D_H
