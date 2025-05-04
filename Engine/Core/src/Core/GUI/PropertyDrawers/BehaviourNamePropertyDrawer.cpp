//
// Created by Monika on 04.05.2025.
//

#include <Core/GUI/PropertyDrawers/BehaviourNamePropertyDrawer.h>

#include <Codegen/BehaviourNamePropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback BehaviourNamePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }

            ImGui::SameLine();
        }

        ImGui::PushItemWidth(context.fieldWidth);

        auto&& pBehaviour = dynamic_cast<SR_SCRIPTING_NS::Behaviour*>(context.pOwner);
        SRAssert2(pBehaviour, "pOwner is not a Behaviour!");

        if (value.IsStringAtom()) {
            if (auto&& pStringAtom = value.TryCast<SR_UTILS_NS::StringAtom>()) {
                std::string str = pStringAtom->ToString();
                const bool isValid = pBehaviour->IsInstanceValid();
                if (!isValid) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
                }

                ImGui::InputText("##Input", &str);

                if (!isValid) {
                    ImGui::PopStyleColor();
                }

                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pStringAtom, SR_UTILS_NS::StringAtom(str));
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to map string atom value!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
        }
        else {
            SR_GRAPH_GUI_NS::ColoredText("Invalid string type!", ImColor(1.f, 0.f, 0.f, 1.f));
        }

        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }

    void BehaviourNamePropertyDrawer::ReInitNames() {
        static const SR_UTILS_NS::StringAtom cppBehaviourName = SR_SCRIPTING_NS::CppBehaviour::GetClassStaticName();
        auto&& factory = SR_UTILS_NS::Factory::Instance();

        m_existingNames = factory.GetInheritances(cppBehaviourName);

        std::erase_if(m_existingNames, [factory](const auto& name) {
            return factory.IsAbstract(name);
        });
    }
}
