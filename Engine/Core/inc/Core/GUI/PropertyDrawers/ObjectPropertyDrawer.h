//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class ObjectPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ObjectPropertyDrawer>;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

        virtual PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) { return PropertyDrawerFeedback(); }

    private:
        bool m_isOpened = false;
        std::vector<PropertyDrawerBase::Ptr> m_drawers;

    };
}

#endif //SR_ENGINE_GUI_OBJECT_PROPERTY_DRAWER_H

