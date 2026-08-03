//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_PAIR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_PAIR_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class PairPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        SR_HTYPES_NS::RawPointerHolder<SR_UTILS_NS::Reflection::Value> m_firstValue;
        SR_HTYPES_NS::RawPointerHolder<SR_UTILS_NS::Reflection::Value> m_secondValue;
        PropertyDrawerBase::Ptr m_firstDrawer;
        PropertyDrawerBase::Ptr m_secondDrawer;

    };
}

#endif //SR_ENGINE_GUI_PAIR_PROPERTY_DRAWER_H
