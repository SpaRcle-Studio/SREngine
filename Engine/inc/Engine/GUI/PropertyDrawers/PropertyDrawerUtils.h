//
// Created by Monika on 30.11.2025.
//

#ifndef SR_ENGINE_PROPERTY_DRAWER_UTILS_H
#define SR_ENGINE_PROPERTY_DRAWER_UTILS_H

#include <Engine/GUI/PropertyDrawer.h>

#include <Utils/Reflection/Value.h>

namespace SR_CORE_GUI_NS {
    struct PropertyDrawerFeedback;
    struct PropertyDrawerContext;

    template<typename MappedVal, typename NewVal> static void SetPropertyDrawerMappedValue(const PropertyDrawerContext& context, PropertyDrawerFeedback& feedback, MappedVal pMapped, NewVal value, bool drag = false) {
        if (context.onBeforeChangeCallback) {
            context.onBeforeChangeCallback(drag);
        }

        feedback.isChanged = true;

        if (!context.pValue) {
            context.GetProperty().Set(context.pOwner, SR_UTILS_NS::Reflection::Value::Create(value));
        }
        else {
            *pMapped = value;
        }
    }
}

#endif //SR_ENGINE_PROPERTY_DRAWER_UTILS_H
