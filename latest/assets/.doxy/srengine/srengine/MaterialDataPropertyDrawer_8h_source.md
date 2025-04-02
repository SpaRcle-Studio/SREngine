

# File MaterialDataPropertyDrawer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**PropertyDrawers**](dir_4cfb8686e051f64f158d683134748f22.md) **>** [**MaterialDataPropertyDrawer.h**](MaterialDataPropertyDrawer_8h.md)

[Go to the documentation of this file](MaterialDataPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

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
        bool DrawShaderProperty(SR_GRAPH_NS::MaterialShaderData& shaderData, SR_GRAPH_NS::MaterialShaderProperty& property, const PropertyDrawerContext& context);

    private:
        std::map<SR_UTILS_NS::StringAtom, bool> m_shaderDataOpened;
        std::set<SR_UTILS_NS::StringAtom> m_stagesToRemove;

        MathVectorPropertyDrawer::Ptr m_vectorDrawer;
        NumericPropertyDrawer::Ptr m_numericDrawer;
        BoolPropertyDrawer::Ptr m_boolDrawer;
        PathPropertyDrawer::Ptr m_pathDrawer;

    };
}

#endif //SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
```


