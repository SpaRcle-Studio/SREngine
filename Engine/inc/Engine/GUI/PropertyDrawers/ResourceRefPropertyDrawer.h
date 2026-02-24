//
// Created by Monika on 19.02.2026.
//

#ifndef SR_ENGINE_GUI_RESOURCE_REF_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_RESOURCE_REF_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class ResourceRefPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ResourceRefPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        bool m_isOpened = false;
        SR_UTILS_NS::StringAtom m_lastTypeName;
        ObjectPropertyDrawer::Ptr m_objectDrawer = nullptr;

    };
}

#endif //SR_ENGINE_GUI_RESOURCE_REF_PROPERTY_DRAWER_H
