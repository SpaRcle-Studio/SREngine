//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/EnumPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class MaterialDataPropertyDrawer final : public ObjectPropertyDrawer {
        using Super = ObjectPropertyDrawer;
        SR_CLASS()
    public:
        MaterialDataPropertyDrawer();

        PropertyDrawerFeedback DrawCustomProperties(const PropertyDrawerContext& context) override;

    private:
        bool DrawShaderData(bool isDefault, SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context);
        bool DrawShaderPath(SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context);
        bool DrawUseTypeEnum(SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context);
        bool DrawShaderProperty(SR_GRAPH_NS::MaterialShaderData& shaderData, SR_GRAPH_NS::MaterialShaderProperty& property, const PropertyDrawerContext& context);

    private:
        std::map<SR_UTILS_NS::StringAtom, bool> m_shaderDataOpened;
        std::set<SR_UTILS_NS::StringAtom> m_stagesToRemove;
        std::string m_newStageName = "New Stage";

        MathVectorPropertyDrawer::Ptr m_vectorDrawer;
        NumericPropertyDrawer::Ptr m_numericDrawer;
        BoolPropertyDrawer::Ptr m_boolDrawer;
        PathPropertyDrawer::Ptr m_pathDrawer;
        EnumPropertyDrawer::Ptr m_enumPropertyDrawer;

    };
}

#endif //SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
