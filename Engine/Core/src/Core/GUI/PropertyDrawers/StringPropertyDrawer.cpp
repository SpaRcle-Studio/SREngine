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
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }

            ImGui::SameLine();
        }

        ImGui::PushItemWidth(context.fieldWidth);

        const bool isTextBox = context.pProperty && context.pProperty->GetEditorParams().GetCustomArg("text-box") == "enabled";

        if (value.IsString()) {
            if (auto&& pString = value.TryCast<std::string>()) {
                std::string copy = *pString;
                ImGui::InputText("##Input", &copy);

                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pString, copy);
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
                ImGui::InputText("##Input", str.data(), str.size());

                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pStringAtom, SR_UTILS_NS::StringAtom(str));
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to map string atom value!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
        }
        else if (value.IsUnicodeString()) {
            if (auto&& pUnicodeString = value.TryCast<SR_HTYPES_NS::UnicodeString>()) {
                std::string text = SR_UTILS_NS::Localization::UtfToUtf<char, char32_t>(pUnicodeString->View());

                if (isTextBox) {
                    ImGui::InputTextMultiline("##Input", &text, ImVec2(context.fieldWidth, 100));
                }
                else {
                    ImGui::InputText("##Input", &text);
                }

                if (ImGui::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pUnicodeString, SR_HTYPES_NS::UnicodeString(SR_UTILS_NS::Localization::UtfToUtf<char32_t, char>(text)));
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
}
