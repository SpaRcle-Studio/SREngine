//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class MaterialDataPropertyDrawer final : public ObjectPropertyDrawer {
        SR_CLASS()
    public:
        PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) override;

    private:
        bool DrawShaderData(SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context);
        bool DrawShaderProperty(SR_GRAPH_NS::MaterialShaderData& shaderData, SR_GRAPH_NS::MaterialShaderProperty& property, const PropertyDrawerContext& context);

    private:
        std::map<SR_UTILS_NS::StringAtom, bool> m_shaderDataOpened;
        std::set<SR_UTILS_NS::StringAtom> m_stagesToRemove;

        MathVectorPropertyDrawer::Ptr m_vectorDrawer;

    };
}

#endif //SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
