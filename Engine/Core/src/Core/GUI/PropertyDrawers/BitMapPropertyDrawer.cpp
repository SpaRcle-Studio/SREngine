//
// Created by Monika on 03.02.2025.
//

#include <Core/GUI/PropertyDrawers/BitMapPropertyDrawer.h>

#include <Codegen/BitMapPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback BitMapPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetEditorParams().GetDisplayName();

        auto&& container = value.AsSequenceContainer();

        const ImVec2 counterButtonWidth = { 40, context.fieldHeight };
        ImVec2 buttonSize;

        auto&& pWindow = ImGui::GetCurrentWindow();
        const ImGuiDir_ dir = m_isOpened ? ImGuiDir_Down : ImGuiDir_Right;

        if (context.pValue) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(5, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const ImVec2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { (context.fieldWidth - (counterButtonWidth.x + mainButtonSize.x)) / 3, context.fieldHeight };
            if (ImGui::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }
        else {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(0, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const float_t arrowWidth = context.lineHeight * 0.75f;
            ImGui::Dummy(ImVec2(arrowWidth, 0));

            ImGui::SameLine();

            const ImVec2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth + counterButtonWidth.x;
            const float_t partItemWidth = ((context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth) / 3;
            buttonSize = { partItemWidth, context.fieldHeight };

            if (ImGui::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }

        ImGui::SameLine();

        ImGui::BeginDisabled();
        ImGui::Button("{}"_format(container.Size()).c_str(), counterButtonWidth);
        ImGui::EndDisabled();

        ImGui::SameLine();

        if (ImGui::Button("Add", buttonSize)) {
            container.Resize(container.Size() + 1);
            feedback.isChanged = true;
        }

        ImGui::SameLine();

        if (ImGui::Button("Remove", buttonSize)) {
            if (!container.Empty()) {
                container.Resize(container.Size() - 1);
                feedback.isChanged = true;
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Clear", buttonSize)) {
            container.Clear();
            feedback.isChanged = true;
        }

        if (m_isOpened) {
            constexpr uint64_t maxPartsInLine = 8;

            if (std::vector<bool>* pBitMap = value.TryCast<std::vector<bool>>()) {
                for (uint64_t i = 0; i < pBitMap->size(); ++i) {
                    ImGui::PushID(i);

                    if (i % maxPartsInLine == 0) {
                        ImVec2 itemButtonSize = { 40, context.fieldHeight };
                        ImGui::BeginDisabled();
                        ImGui::Button("[{}] "_format(static_cast<uint64_t>(i / maxPartsInLine)).c_str(), itemButtonSize);
                        ImGui::EndDisabled();
                        ImGui::SameLine();
                    }

                    bool bValue = (*pBitMap)[i];
                    if (ImGui::Checkbox("", &bValue)) {
                        pBitMap->at(i) = bValue;
                        feedback.isChanged = true;
                    }

                    if ((i + 1) % maxPartsInLine != 0) {
                        ImGui::SameLine();
                    }

                    ImGui::PopID();
                }
            }
            else {
                SRHalt("Failed to map bit map value!");
            }
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        if (!context.pValue && feedback.isChanged && !value.IsRef()) {
            context.GetProperty().Set(context.pOwner, value);
        }

        return feedback;
    }
}
