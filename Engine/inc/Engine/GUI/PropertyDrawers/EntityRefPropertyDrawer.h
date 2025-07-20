//
// Created by Monika on 19.07.2025.
//

#ifndef SR_ENGINE_GUI_ENTITY_REF_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_ENTITY_REF_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class EntityRefPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<EntityRefPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    };
}

#endif //SR_ENGINE_GUI_ENTITY_REF_PROPERTY_DRAWER_H
