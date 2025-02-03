//
// Created by Monika on 03.02.2025.
//

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

#include <Codegen/ObjectPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ObjectPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        auto&& pWindow = ImGui::GetCurrentWindow();
        const ImGuiDir_ dir = m_isOpened ? ImGuiDir_Down : ImGuiDir_Right;

        std::string_view typeName = value.GetTypeName();
        if (size_t pos = typeName.rfind(':'); pos != std::string_view::npos) {
            typeName.remove_prefix(pos + 1);
        }

        ImVec2 buttonSize;

        if (context.pValue) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(5, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const ImVec2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { context.fieldWidth - mainButtonSize.x, context.fieldHeight };

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
            const float_t titleTotalWidth = context.fieldTitleWidth;
            buttonSize = { (context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth, context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetEditorParams().GetDisplayName();
            if (ImGui::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }

        ImGui::SameLine();

        ImGui::BeginDisabled();
        ImGui::Button("{}"_format(typeName).c_str(), buttonSize);
        ImGui::EndDisabled();

        if (m_isOpened) {
            const SR_UTILS_NS::SRClassMeta* pMeta = SR_UTILS_NS::Factory::Instance().GetType(typeName);

            if (pMeta) {
                auto&& properties = pMeta->GetProperties();

                if (m_drawers.empty()) {
                    for (auto&& property : properties) {
                        SR_UTILS_NS::StringAtom inspector = property.GetEditorParams().GetInspector();

                        if (inspector.Empty()) {
                            inspector = GetValueInspector(property.Get(value.Data()));
                        }

                        if (inspector.Empty()) {
                            m_drawers.emplace_back();
                            continue;
                        }

                        PropertyDrawerBase::Ptr pDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                        if (!pDrawer) {
                            m_drawers.emplace_back();
                            continue;
                        }

                        m_drawers.emplace_back(pDrawer);
                    }
                }

                for (uint64_t i = 0; i < properties.size(); ++i) {
                    if (!m_drawers[i]) {
                        SR_GRAPH_GUI_NS::ColoredText("Missing inspector for element!", ImColor(255, 0, 0));
                        ImGui::PopID();
                        continue;
                    }

                    ImGui::Dummy(ImVec2(context.lineHeight, 5.0f));

                    ImGui::SameLine();

                    PropertyDrawerContext propertyContext = context;
                    propertyContext.pValue = nullptr;
                    float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth) - context.lineHeight;
                    propertyContext.fieldWidth = totalWidth * 0.7;
                    propertyContext.fieldTitleWidth = totalWidth * 0.3;
                    propertyContext.pProperty = &properties[i];
                    propertyContext.pOwner = value.Data();

                    ImGui::BeginGroup();
                    PropertyDrawerFeedback propertyFeedback = m_drawers[i]->Draw(propertyContext);
                    ImGui::EndGroup();

                    if (propertyFeedback.isChanged) {
                        feedback.isChanged = true;
                    }
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to get meta for object!", ImColor(255, 0, 0));
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