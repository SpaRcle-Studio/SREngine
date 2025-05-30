//
// Created by Monika on 30.01.2025.
//

#include <Engine/GUI/PropertyDrawers/EnumPropertyDrawer.h>

#include <Codegen/EnumPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback EnumPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_UTILS_NS::EnumReflector* pReflector =
            SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(value.GetEnumType());
        if (!pReflector) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "EnumReflector not found!");
            return feedback;
        }

        if (pReflector->GetEnumVariantInternal() == SR_UTILS_NS::EnumVariant::Undefined) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(
                SR_MATH_NS::FColor(1.f, 0.f, 0.f), "EnumReflector variant is not defined!"
            );
            return feedback;
        }

        if (pReflector->GetEnumVariantInternal() == SR_UTILS_NS::EnumVariant::Flags) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Flags are not supported!");
            return feedback;
        }

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(
            SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2()
        );

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = {context.fieldTitleWidth, context.fieldHeight};

            if (SR_GRAPH_GUI_NS::Immediate::Button(
                    context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize
                )) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue()
                                                              : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        void* pMappedRaw = value.Data();
        int64_t enumValue = pReflector->ReadEnumValueFromPointerInternal(pMappedRaw);
        auto&& names = pReflector->GetNamesInternal();

        std::optional<uint64_t> selectedIndex = pReflector->GetIndexInternal(enumValue);

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        const char* pPrevValue = selectedIndex ? names[selectedIndex.value()].c_str() : "";
        if (SR_GRAPH_GUI_NS::Immediate::BeginCombo(
                "##Combo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton
            )) {
            if (!m_comboOpened) {
                SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                m_comboOpened = true;
            }

            if (SR_GRAPH_GUI_NS::Immediate::InputText("##Search", &m_searchBuffer)) {
                SR_NOOP;
            }

            for (uint64_t i = 0; i < names.size(); ++i) {
                if (!m_searchBuffer.empty() && !CheckSearchMatch(m_searchBuffer, names[i])) {
                    continue;
                }

                bool isSelected = (selectedIndex == i);
                if (SR_GRAPH_GUI_NS::Immediate::Selectable(names[i].c_str(), isSelected)) {
                    selectedIndex = i;
                    m_searchBuffer = names[i];
                    SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                }

                if (isSelected)
                    SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
            }
            SR_GRAPH_GUI_NS::Immediate::EndCombo();
        } else {
            m_comboOpened = false;
            m_searchBuffer.clear();
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        if (selectedIndex) {
            int64_t newEnumValue = pReflector->AtInternal(selectedIndex.value()).value();
            if (newEnumValue != enumValue) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                pReflector->WriteEnumValueToPointerInternal(pMappedRaw, newEnumValue);
                feedback.isChanged = true;
            }
        }

        SetValue(context, feedback, value);

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
} // namespace SR_CORE_GUI_NS
