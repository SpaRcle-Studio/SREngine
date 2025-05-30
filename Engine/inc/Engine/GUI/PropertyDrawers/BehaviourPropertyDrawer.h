//
// Created by Monika on 04.05.2025.
//

#ifndef SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class BehaviourPropertyDrawer : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        BehaviourPropertyDrawer();

    public:
        PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) override;

    private:
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;
        std::string m_searchBuffer;
        bool m_comboOpened = false;
        ObjectPropertyDrawer::Ptr m_pObjectPropertyDrawer;
    };
} // namespace SR_CORE_GUI_NS

#endif // SR_ENGINE_GUI_BEHAVIOUR_PROPERTY_DRAWER_H
