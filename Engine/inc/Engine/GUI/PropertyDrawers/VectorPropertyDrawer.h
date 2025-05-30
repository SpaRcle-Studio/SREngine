//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class VectorPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        bool m_isOpened = false;
        std::vector<PropertyDrawerBase::Ptr> m_drawers;
    };
} // namespace SR_CORE_GUI_NS

#endif // SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H
