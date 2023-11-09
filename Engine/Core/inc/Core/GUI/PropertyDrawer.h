//
// Created by Monika on 09.11.2023.
//

#ifndef SR_ENGINE_CORE_PROPERTY_DRAWER_H
#define SR_ENGINE_CORE_PROPERTY_DRAWER_H

#include <Graphics/Types/Material.h>

namespace SR_CORE_GUI_NS {
    class EditorGUI;

    struct DrawPropertyContext {
        EditorGUI* pEditor = nullptr;
    };

    SR_MAYBE_UNUSED bool DrawProperty(const DrawPropertyContext& context, SR_UTILS_NS::Property* pProperty);
    SR_MAYBE_UNUSED bool DrawStandardProperty(const DrawPropertyContext& context, SR_UTILS_NS::StandardProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawPathProperty(const DrawPropertyContext& context, SR_UTILS_NS::PathProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawPropertyContainer(const DrawPropertyContext& context, const SR_UTILS_NS::PropertyContainer* pProperties);
    SR_MAYBE_UNUSED bool DrawLabelProperty(const DrawPropertyContext& context, SR_UTILS_NS::LabelProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MaterialProperty* pProperty);
}

#endif //SR_ENGINE_CORE_PROPERTY_DRAWER_H
