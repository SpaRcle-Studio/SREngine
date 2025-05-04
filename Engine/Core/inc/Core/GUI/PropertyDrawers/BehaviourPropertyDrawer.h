//
// Created by Monika on 04.05.2025.
//

#ifndef SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class BehaviourPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) override;

    private:
        std::string m_searchBuffer;
        bool m_comboOpened = false;

    };
}

#endif //SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
