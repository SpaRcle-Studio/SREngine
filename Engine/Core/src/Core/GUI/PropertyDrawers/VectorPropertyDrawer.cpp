//
// Created by Monika on 01.02.2025.
//

#include <Core/GUI/PropertyDrawers/VectorPropertyDrawer.h>

#include <Codegen/VectorPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback VectorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        if (!value.IsSequenceContainer()) {
            SRHalt("VectorPropertyDrawer can only be used with sequence containers!");
            return feedback;
        }

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.property.GetName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        SR_UTILS_NS::StringAtom displayName = context.property.GetEditorParams().GetDisplayName();

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

        if (container.Size() < m_drawers.size()) {
            m_drawers.resize(container.Size());
        }

        if (m_isOpened) {
            for (auto&& pIt = container.begin(); pIt != container.end(); ++pIt) {
                SR_UTILS_NS::Reflection::Value element = *pIt;
                uint64_t index = std::distance(container.begin(), pIt);
                ImGui::PushID(index);

                ImVec2 itemButtonSize = { 40, context.fieldHeight };
                ImGui::BeginDisabled();
                ImGui::Button("[{}] "_format(index).c_str(), itemButtonSize);
                ImGui::EndDisabled();

                ImGui::SameLine();

                if (index >= m_drawers.size()) {
                    m_drawers.emplace_back();

                    SR_UTILS_NS::StringAtom inspector = SR_CORE_GUI_NS::GetValueInspector(element);
                    if (inspector.Empty()) {
                        SR_GRAPH_GUI_NS::ColoredText("Missing inspector for element!", ImColor(255, 0, 0));
                    }
                    else {
                        auto&& pDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                        m_drawers.back() = pDrawer;
                    }
                }

                if (!m_drawers[index]) {
                    SR_GRAPH_GUI_NS::ColoredText("Missing inspector for element!", ImColor(255, 0, 0));
                    ImGui::PopID();
                    continue;
                }

                PropertyDrawerContext elementContext = context;
                elementContext.pValue = &element;
                elementContext.fieldWidth += context.fieldTitleWidth;
                elementContext.fieldWidth -= itemButtonSize.x;
                elementContext.fieldTitleWidth = 0.f;

                ImGui::BeginGroup();
                PropertyDrawerFeedback elementFeedback = m_drawers[index]->Draw(elementContext);
                ImGui::EndGroup();

                if (elementFeedback.isChanged) {
                    feedback.isChanged = true;
                }

                ImGui::PopID();
            }
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        if (!context.pValue && feedback.isChanged && !value.IsRef()) {
            context.property.Set(context.pOwner, value);
        }

        return feedback;
    }
}
