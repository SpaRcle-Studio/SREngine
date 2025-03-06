//
// Created by Monika on 13.02.2025.
//

#include <Core/GUI/PropertyDrawers/StringPropertyDrawer.h>

#include <Codegen/StringPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback StringPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
            }

            ImGui::SameLine();
        }

        ImGui::PushItemWidth(context.fieldWidth);

        if (value.IsString()) {
            if (auto&& pString = value.TryCast<std::string>()) {
                if (ImGui::InputText("##Input", pString, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    feedback.isChanged = true;
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to map string value!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
        }
        else if (value.IsStringView()) {
            if (auto&& pStringView = value.TryCast<std::string_view>()) {
                /// read only
                if (pStringView->empty()) {
                    static std::string emptyString = " "; /// imgui will assert if empty string is passed
                    ImGui::InputText("##Input", emptyString.data(), emptyString.size(), ImGuiInputTextFlags_ReadOnly);
                }
                else {
                    ImGui::InputText("##Input", const_cast<char*>(pStringView->data()), pStringView->size(), ImGuiInputTextFlags_ReadOnly);
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to map string view value!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
        }
        else if (value.IsStringAtom()) {
            if (auto&& pStringAtom = value.TryCast<SR_UTILS_NS::StringAtom>()) {
                std::string str = pStringAtom->ToString();
                if (ImGui::InputText("##Input", str.data(), str.size(), ImGuiInputTextFlags_EnterReturnsTrue)) {
                    feedback.isChanged = true;
                    *pStringAtom = str;
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

        SetValue(context, feedback, value);

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }
}
