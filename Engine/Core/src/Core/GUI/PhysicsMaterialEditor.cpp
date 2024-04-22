//
// Created by innerviewer on 6/6/2023.
//

#include <Core/GUI/PhysicsMaterialEditor.h>

#include <Utils/Xml.h>
#include <Utils/Resources/IResourceReloader.h>

namespace SR_CORE_GUI_NS {
    PhysicsMaterialEditor::PhysicsMaterialEditor()
        : Super("Physics Material Editor")
    { }

    void PhysicsMaterialEditor::Draw() {
        if (m_materialPath.GetExtensionView() == "physmat") {
            if (ImGui::Button(m_materialPath.c_str())) {
                ChooseMaterial();
            }
        }
        else {
            if (ImGui::Button("Choose material.")) {
                ChooseMaterial();
            }

            return;
        }

        ImGui::Separator();

        if (ImGui::DragFloat("Dynamic Friction", &m_materialData.dynamicFriction, 0.01f)) {
            SetDynamicFriction(m_materialData.dynamicFriction);
        }

        if (ImGui::DragFloat("Static Friction", &m_materialData.staticFriction, 0.01f)) {
            SetStaticFriction(m_materialData.staticFriction);
        }

        if (ImGui::DragFloat("Bounciness", &m_materialData.bounciness, 0.01f)) {
            SetBounciness(m_materialData.bounciness);
        }

        if (ImGui::BeginCombo("Friction Combine",
                              SR_UTILS_NS::EnumReflector::ToStringAtom(m_materialData.frictionCombine).c_str())) {
            auto&& selectables = SR_UTILS_NS::EnumReflector::GetNames<SR_PHYSICS_NS::Combine>();
            for (auto&& selectable : selectables) {
                if (ImGui::Selectable(selectable.c_str())) {
                    ImGui::SetItemDefaultFocus();
                    SetFrictionCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(selectable));
                }
            }

            ImGui::EndCombo();
        }

        if (ImGui::BeginCombo("Bounce Combine", SR_UTILS_NS::EnumReflector::ToStringAtom(m_materialData.bounceCombine).c_str())) {
            auto&& selectables = SR_UTILS_NS::EnumReflector::GetNames<SR_PHYSICS_NS::Combine>();
            for (auto&& selectable : selectables) {
                if (ImGui::Selectable(selectable.c_str())) {
                    ImGui::SetItemDefaultFocus();
                    SetBounceCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(selectable));
                }
            }

            ImGui::EndCombo();
        }

        if (ImGui::Button("Save")) {
            SR_PTYPES_NS::PhysicsMaterial::Save(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(m_materialPath), m_materialData);
        }
    }

    void PhysicsMaterialEditor::ChooseMaterial() {
        if (auto&& pFileBrowser = GetManager()->GetWidget<FileBrowser>()) {
            pFileBrowser->Open();

            pFileBrowser->SetCallback([this](const SR_UTILS_NS::Path& path){
                this->SetMaterialPath(path);
            });
        }
    }

    void PhysicsMaterialEditor::ReadData() {
        auto&& document = SR_XML_NS::Document::Load(m_materialPath);
        if (!document.Valid()) {
            SR_ERROR("PhysicsMaterialEditor::Draw() : file is not found! \n\tPath: " + m_materialPath.ToString());
            return;
        }

        auto&& matXml = document.Root().GetNode("PhysicsMaterial");
        if (!matXml) {
            SR_ERROR("PhysicsMaterialEditor::Draw() : \"PhysicsMaterial\" node is not found! \n\tPath: " + m_materialPath.ToString());
            return;
        }

        SetDynamicFriction(matXml.TryGetNode("DynamicFriction").TryGetAttribute<float_t>(0.6f));
        SetStaticFriction(matXml.TryGetNode("StaticFriction").TryGetAttribute<float_t>(0.6f));
        SetBounciness(matXml.TryGetNode("Bounciness").TryGetAttribute<float_t>(0.6f));
        SetFrictionCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(matXml.TryGetNode("FrictionCombine").TryGetAttribute<std::string>("Average")));
        SetBounceCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(matXml.TryGetNode("BounceCombine").TryGetAttribute<std::string>("Average")));
    }

    bool PhysicsMaterialEditor::OpenFile(const SR_UTILS_NS::Path& path) {
        m_materialPath = path;
        ReadData();
        Super::Open();
        return true;
    }
}