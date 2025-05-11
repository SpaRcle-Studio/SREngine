

# File MaterialDataPropertyDrawer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**PropertyDrawers**](dir_30dc1e095f689d337a3714af764d731f.md) **>** [**MaterialDataPropertyDrawer.h**](MaterialDataPropertyDrawer_8h.md)

[Go to the documentation of this file](MaterialDataPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_DATA_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

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


