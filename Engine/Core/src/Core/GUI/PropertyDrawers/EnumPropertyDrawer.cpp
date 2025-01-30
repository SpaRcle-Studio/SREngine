//
// Created by Monika on 30.01.2025.
//

#include <Core/GUI/PropertyDrawers/EnumPropertyDrawer.h>

#include <Codegen/EnumPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback EnumPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.property.Get(context.pOwner);

        SR_UTILS_NS::EnumReflector* pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(context.property.GetEditorParams().GetEnumReflector());
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
        ImGui::PushID(context.property.GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

        if (ImGui::Button(context.property.GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
            feedback.isChanged = true;
            value = context.property.GetResetValue() ? context.property.GetResetValue() : context.property.GetDefaultValue();
        }

        ImGui::SameLine();

        void* pMappedRaw = value.MapString();
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
                bool found = m_searchBuffer.empty();
                for (uint64_t j = 0; j < m_searchBuffer.size() && j < names[i].size(); j++) {
                    if (std::tolower(m_searchBuffer[j]) != std::tolower(names[i][j])) {
                        found = false;
                        break;
                    }
                    found = true;
                }

                if (!found) {
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
                pReflector->WriteEnumValueToPointerInternal(pMappedRaw, newEnumValue);
                feedback.isChanged = true;
            }
        }

        if (feedback.isChanged) {
            context.property.Set(context.pOwner, value);
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }
}
