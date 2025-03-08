//
// Created by Monika on 30.01.2025.
//

#include <Core/GUI/PropertyDrawers/EnumPropertyDrawer.h>

#include <Codegen/EnumPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback EnumPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_UTILS_NS::EnumReflector* pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(value.GetEnumType());
        if (!pReflector) {
            SR_GRAPH_GUI_NS::ColoredText("EnumReflector not found!", ImColor(255, 0, 0));
            return feedback;
        }

        if (pReflector->GetEnumVariantInternal() == SR_UTILS_NS::EnumVariant::Undefined) {
            SR_GRAPH_GUI_NS::ColoredText("EnumReflector variant is not defined!", ImColor(255, 0, 0));
            return feedback;
        }

        if (pReflector->GetEnumVariantInternal() == SR_UTILS_NS::EnumVariant::Flags) {
            SR_GRAPH_GUI_NS::ColoredText("Flags are not supported!", ImColor(255, 0, 0));
            return feedback;
        }

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
            }

            ImGui::SameLine();
        }

        void* pMappedRaw = value.Data();
        int64_t enumValue = pReflector->ReadEnumValueFromPointerInternal(pMappedRaw);
        auto&& names = pReflector->GetNamesInternal();

        std::optional<uint64_t> selectedIndex = pReflector->GetIndexInternal(enumValue);

        ImGui::PushItemWidth(context.fieldWidth);

        const char* pPrevValue = selectedIndex ? names[selectedIndex.value()].c_str() : "";
        if (ImGui::BeginCombo("##Combo", pPrevValue, ImGuiComboFlags_NoArrowButton)) {
            if (!m_comboOpened) {
                ImGui::SetKeyboardFocusHere();
                m_comboOpened = true;
            }

            if (ImGui::InputText("##Search", &m_searchBuffer)) {
                SR_NOOP;
            }

            for (uint64_t i = 0; i < names.size(); ++i) {
                if (!m_searchBuffer.empty() && !CheckSearchMatch(m_searchBuffer, names[i])) {
                    continue;
                }

                bool isSelected = (selectedIndex == i);
                if (ImGui::Selectable(names[i].c_str(), isSelected))
                {
                    selectedIndex = i;
                    m_searchBuffer = names[i];
                    ImGui::CloseCurrentPopup();
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        else {
            m_comboOpened = false;
            m_searchBuffer.clear();
        }

        ImGui::PopItemWidth();

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

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }
}
