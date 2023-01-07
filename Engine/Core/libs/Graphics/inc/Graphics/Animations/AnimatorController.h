//
// Created by Monika on 07.01.2023.
//

#ifndef SRENGINE_ANIMATORCONTROLLER_H
#define SRENGINE_ANIMATORCONTROLLER_H

#include <Utils/ECS/Component.h>

namespace SR_ANIMATIONS_NS {
    class AnimatorController : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
        SR_INITIALIZE_COMPONENT(AnimatorController);
        using Super = SR_UTILS_NS::Component;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage);

    public:
        SR_NODISCARD Component* CopyComponent() const override;
        SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr Save(SR_HTYPES_NS::Marshal::Ptr pMarshal, SR_UTILS_NS::SavableFlags flags) const override;

        void OnAttached() override;
        void OnDestroy() override;
        void OnEnable() override;
        void OnDisable() override;

    };
}

#endif //SRENGINE_ANIMATORCONTROLLER_H
