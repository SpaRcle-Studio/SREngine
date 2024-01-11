//
// Created by Monika on 20.11.2022.
//

#ifndef SR_ENGINE_UI_BUTTON_H
#define SR_ENGINE_UI_BUTTON_H

#include <Utils/ECS/Component.h>

namespace SR_CORE_UI_NS {
    class Button : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(Button);
        using Super = SR_UTILS_NS::Component;
    public:
        Button();

    protected:
        ~Button() override = default;

    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_UTILS_NS::SavableSaveData data) const override;

    };
}

#endif //SR_ENGINE_UI_BUTTON_H
