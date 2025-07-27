//
// Created by Monika on 27.07.2025.
//

#ifndef SR_ENGINE_GUI_ASSOCIATIVE_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_ASSOCIATIVE_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class AssociativePropertyDrawer : public PropertyDrawerBase {
        using Super = PropertyDrawerBase;
        SR_CLASS()
    public:
        AssociativePropertyDrawer();

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        SR_UTILS_NS::Reflection::Value m_keyValue;
        bool m_isOpened = false;
        PropertyDrawerBase::Ptr m_keyDrawer;
        std::vector<PropertyDrawerBase::Ptr> m_keyDrawers;
        std::vector<PropertyDrawerBase::Ptr> m_valueDrawers;

    };
}

#endif //SR_ENGINE_GUI_ASSOCIATIVE_PROPERTY_DRAWER_H
