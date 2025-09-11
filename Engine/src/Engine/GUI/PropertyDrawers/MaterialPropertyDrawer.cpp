//
// Created by Monika on 17.02.2025.
//

#include <Engine/GUI/PropertyDrawers/MaterialPropertyDrawer.h>

#include <Codegen/MaterialPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    void MaterialPropertyDrawer::OnObjectReplaced(SRClass* pOld, SRClass* pNew) {
        if (!pOld || !pNew) {
            return;
        }

        auto&& pOldBaseMaterial = static_cast<SR_GRAPH_NS::BaseMaterial*>(pOld);
        auto&& pNewBaseMaterial = static_cast<SR_GRAPH_NS::BaseMaterial*>(pNew);

        if (pOldBaseMaterial->GetMaterialType() != SR_GRAPH_NS::MaterialType::File) {
            return;
        }

        if (pNewBaseMaterial->GetMaterialType() != SR_GRAPH_NS::MaterialType::Unique) {
            return;
        }

        auto&& pOldMaterialData = pOldBaseMaterial->GetMaterialData();
        auto&& pNewMaterialData = pNewBaseMaterial->GetMaterialData();

        if (!pOldMaterialData || !pNewMaterialData) {
            return;
        }

        /// copy data from old to new material

        auto&& defaultData = pOldMaterialData->GetDefaultShaderData();
        if (auto&& pDefaultShader = defaultData.pShader) {
            pNewMaterialData->GetDefaultShaderData().SetShader(pDefaultShader);
            defaultData.ForEachProperty([&](const SR_GRAPH_NS::MaterialShaderProperty& property) {
                pNewMaterialData->GetDefaultShaderData().SetData(property.id, *property.data, property.type);
            });
        }
    }
}
