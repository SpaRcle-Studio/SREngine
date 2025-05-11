//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_ENUM_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_ENUM_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class EnumPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        std::string m_searchBuffer;
        bool m_comboOpened = false;

    };
}

#endif //SR_ENGINE_GUI_ENUM_PROPERTY_DRAWER_H
