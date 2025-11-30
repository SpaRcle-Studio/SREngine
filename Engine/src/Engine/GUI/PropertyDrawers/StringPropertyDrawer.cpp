//
// Created by Monika on 13.02.2025.
//

#include <Engine/GUI/PropertyDrawers/StringPropertyDrawer.h>

#include <Graphics/GUI/ImmediateGUI.h>

#include <Utils/Localization/LocalizationManager.h>
#include <Utils/Localization/Encoding.h>

#include <Codegen/StringPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback StringPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        const bool isTextBox = context.pProperty && context.pProperty->GetEditorParams().GetCustomArg("text-box") == "enabled";

        if (value.IsString()) {
            if (auto&& pString = value.TryCast<std::string>()) {
                std::string copy = *pString;
                SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &copy);

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pString, copy);
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string value!");
            }
        }
        else if (value.IsStringView()) {
            if (auto&& pStringView = value.TryCast<std::string_view>()) {
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
        else if (value.IsStringAtom()) {
            if (auto&& pStringAtom = value.TryCast<SR_UTILS_NS::StringAtom>()) {
                std::string str = pStringAtom->ToString();
                SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &str);

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pStringAtom, SR_UTILS_NS::StringAtom(str));
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string atom value!");
            }
        }
        else if (value.IsUnicodeString()) {
            if (auto&& pUnicodeString = value.TryCast<SR_HTYPES_NS::UnicodeString>()) {
                std::string text = SR_UTILS_NS::Localization::UtfToUtf<char, char32_t>(pUnicodeString->View());

                if (isTextBox) {
                    SR_GRAPH_GUI_NS::Immediate::InputTextMultiline("##Input", &text, SR_MATH_NS::FVector2(context.fieldWidth, 100));
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::InputText("##Input", &text);
                }

                if (SR_GRAPH_GUI_NS::Immediate::IsItemDeactivatedAfterEdit()) {
                    SetMappedValue(context, feedback, pUnicodeString, SR_HTYPES_NS::UnicodeString(SR_UTILS_NS::Localization::UtfToUtf<char32_t, char>(text)));
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
