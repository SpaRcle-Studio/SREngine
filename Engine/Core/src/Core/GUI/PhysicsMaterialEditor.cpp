//
// Created by innerviewer on 6/6/2023.
//

#include <Core/GUI/PhysicsMaterialEditor.h>

#include <Utils/GUI.h>
#include <Utils/Xml.h>
#include <Utils/ResourceManager/IResourceReloader.h>

namespace SR_CORE_GUI_NS {
    PhysicsMaterialEditor::PhysicsMaterialEditor()
        : Super("Physics Material Editor")
    { }

    void PhysicsMaterialEditor::Draw() {
        ImGui::Text("test");

        if (ImGui::DragFloat(SR_FORMAT_C("Dynamic Friction##rgbd%i"), &m_materialData.dynamicFriction, 0.01f)) {
            SetDynamicFriction(m_materialData.dynamicFriction);
        }

        if (ImGui::DragFloat(SR_FORMAT_C("Static Friction##rgbd%i"), &m_materialData.staticFriction, 0.01f)) {
            SetStaticFriction(m_materialData.staticFriction);
        }

        if (ImGui::DragFloat(SR_FORMAT_C("Bounciness##rgbd%i"), &m_materialData.bounciness, 0.01f)) {
            SetBounciness(m_materialData.bounciness);
        }

        if (ImGui::Button("Save")) {
            SR_PTYPES_NS::PhysicsMaterial::Save(m_materialPath, m_materialData);
        }
    }

    void PhysicsMaterialEditor:: Edit(const SR_UTILS_NS::Path& path) {
        m_materialPath = path;

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

        SetDynamicFriction(matXml.TryGetNode("DynamicFriction").TryGetAttribute("Value").ToFloat(0.6f));
        SetStaticFriction(matXml.TryGetNode("StaticFriction").TryGetAttribute("Value").ToFloat(0.6f));
        SetBounciness(matXml.TryGetNode("Bounciness").TryGetAttribute("Value").ToFloat(0.0f));
        SetFrictionCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(matXml.TryGetNode("FrictionCombine").TryGetAttribute("Value").ToString("Average")));
        SetBounceCombine(SR_UTILS_NS::EnumReflector::FromString<SR_PHYSICS_NS::Combine>(matXml.TryGetNode("BounceCombine").TryGetAttribute("Value").ToString("Average")));

        Super::Open();
    }
}