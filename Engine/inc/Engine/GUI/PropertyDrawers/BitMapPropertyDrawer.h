//
// Created by Monika on 03.02.2025.
//

#ifndef SR_ENGINE_GUI_BIT_MAP_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_BIT_MAP_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class BitMapPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        bool m_isOpened = false;

    };
}

#endif //SR_ENGINE_GUI_BIT_MAP_PROPERTY_DRAWER_H
