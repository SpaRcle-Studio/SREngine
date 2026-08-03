//
// Created by Monika on 13.02.2025.
//

#include <Engine/GUI/PropertyDrawers/StringPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PropertyDrawerUtils.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Localization/LocalizationManager.h>
#include <Utils/Localization/Encoding.h>

#include <Codegen/StringPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback StringPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetProperty().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        const bool isTextBox = context.pProperty && context.pProperty->GetEditorParams().GetCustomArg("text-box") == "enabled";

        if (value.GetTypeInfo().detailedType == "String") {
            if (auto&& pString = value.Cast<SR_UTILS_NS::String>()) {
                m_buffer = *pString;

                if (isTextBox) {
                    SR_GRAPH_GUI_NS::Immediate::InputTextMultiline("##Input", &m_buffer, SR_MATH_NS::FVector2(context.fieldWidth, 100));
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &m_buffer);
                }

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    SetPropertyDrawerMappedValue(context, feedback, pString, SR_UTILS_NS::String(m_buffer));
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string value!");
            }
        }
        else if (value.GetTypeInfo().detailedType == "StringView") {
            if (auto&& pStringView = value.Cast<SR_UTILS_NS::StringView>()) {
                /// read only
                if (pStringView->empty()) {
                    static std::string emptyString = " "; /// imgui will assert if empty string is passed
                    SR_GRAPH_GUI_NS::Immediate::InputText("##Input", emptyString.data(), emptyString.size(), SR_GRAPH_GUI_NS::Immediate::InputTextFlags::ReadOnly);
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::InputText("##Input", const_cast<char*>(pStringView->data()), pStringView->size(), SR_GRAPH_GUI_NS::Immediate::InputTextFlags::ReadOnly);
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string view value!");
            }
        }
        else if (value.GetTypeInfo().detailedType == "StringAtom") {
            if (auto&& pStringAtom = value.Cast<SR_UTILS_NS::StringAtom>()) {
                m_buffer = pStringAtom->ToStringRef();
                SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &m_buffer);

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    SetPropertyDrawerMappedValue(context, feedback, pStringAtom, SR_UTILS_NS::StringAtom(m_buffer));
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string atom value!");
            }
        }
        else if (value.GetTypeInfo().detailedType == "UnicodeString") {
            if (auto&& pUnicodeString = value.Cast<SR_UTILS_NS::UnicodeString>()) {
                m_buffer.clear();
                SR_UTILS_NS::Localization::UtfToUtf<char, char32_t>(m_buffer, pUnicodeString->View());

                if (isTextBox) {
                    SR_GRAPH_GUI_NS::Immediate::InputTextMultiline("##Input", &m_buffer, SR_MATH_NS::FVector2(context.fieldWidth, 100));
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &m_buffer);
                }

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    std::u32string unicodeText;
                    SR_UTILS_NS::Localization::UtfToUtf<char32_t, char>(unicodeText, m_buffer);
                    SetPropertyDrawerMappedValue(context, feedback, pUnicodeString, SR_UTILS_NS::UnicodeString(unicodeText));
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string atom value!");
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Invalid string type!");
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
