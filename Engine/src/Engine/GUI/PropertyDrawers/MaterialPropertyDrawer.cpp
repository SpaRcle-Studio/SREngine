//
// Created by Monika on 17.02.2025.
//

#include <Engine/GUI/PropertyDrawers/MaterialPropertyDrawer.h>

#include <Graphics/Material/UniqueMaterial.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/FileSystem/FileDialog.h>
#include <Utils/Resources/ResourceManager.h>

#include <Codegen/MaterialPropertyDrawer.generated.hpp>
#include <Utils/Serialization/SRASerialization.h>

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

    void MaterialPropertyDrawer::CustomContextMenu(const PropertyDrawerContext& context, SR_UTILS_NS::SRClass* pClass) {
        if (!pClass) {
            return;
        }

        auto&& pMaterial = static_cast<SR_GRAPH_NS::BaseMaterial*>(pClass);
        if (pMaterial->GetMaterialType() != SR_GRAPH_NS::MaterialType::Unique) {
            return;
        }

        /// Export material
        if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Export material")) {
            auto&& resPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            if (auto&& path = SR_UTILS_NS::FileDialog::Instance().SaveDialog(resPath.ToString(), { { "Material", "mat" } }); !path.IsEmpty()) {
                path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetCachePath());
                path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
                static_cast<SR_GRAPH_NS::UniqueMaterial*>(pMaterial)->SaveAs(path);
            }
        }
    }
}
