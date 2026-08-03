//
// Created by Monika on 04.05.2025.
//

#ifndef SR_ENGINE_GUI_BEHAVIOUR_NAME_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_BEHAVIOUR_NAME_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

#include <Utils/Common/SubscriptionHolder.h>

namespace SR_CORE_GUI_NS {
    class BehaviourNamePropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        BehaviourNamePropertyDrawer();

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        void ReInitNames();

        SR_NODISCARD std::optional<uint32_t> GetSelectedIndex(SR_UTILS_NS::StringAtom name) const;

    private:
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> m_existingNames;
        std::string m_searchBuffer;
        bool m_comboOpened = false;

    };
}

#endif //SR_ENGINE_GUI_BEHAVIOUR_NAME_PROPERTY_DRAWER_H
