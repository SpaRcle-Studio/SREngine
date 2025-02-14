//
// Created by Monika on 03.02.2025.
//

#include <Core/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Graphics/GUI/Utils.h>

#include <Codegen/ObjectPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ObjectPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetPropertyName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        auto&& pWindow = ImGui::GetCurrentWindow();

        m_isOpened |= context.noHeader;
        const ImGuiDir_ dir = m_isOpened ? ImGuiDir_Down : ImGuiDir_Right;

        const SR_UTILS_NS::SRClass& classValue = *static_cast<SR_UTILS_NS::SRClass*>(value.Data());

        ImVec2 buttonSize;

        if (context.pValue && !context.noHeader) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(5, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const ImVec2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { context.fieldWidth - mainButtonSize.x, context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::BeginForceEnabled();
            if (ImGui::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(0, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            ImGui::Dummy(ImVec2(context.GetArrowWidth(), 0));

            ImGui::SameLine();

            const ImVec2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - context.GetArrowWidth(), 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth;
            buttonSize = { (context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth, context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetEditorParams().GetDisplayName();
            auto&& stackSize = SR_GRAPH_GUI_NS::BeginForceEnabled();
            if (ImGui::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::EndForceEnabled(stackSize);
        }

        if (!context.noHeader) {
            ImGui::SameLine();

            ImGui::BeginDisabled();
            ImGui::Button("{}"_format(classValue.GetMeta()->GetFactoryName()).c_str(), buttonSize);
            ImGui::EndDisabled();
        }

        if (m_isOpened) {
            if (const SR_UTILS_NS::SRClassMeta* pMeta = classValue.GetMeta()) {
                if (m_drawers.empty()) {
                    pMeta->ForEachProperty([&](auto&& property, uint64_t index) {
                        SR_UTILS_NS::StringAtom inspector = property.GetEditorParams().GetInspector();

                        if (inspector.Empty()) {
                            inspector = GetValueInspector(property.Get(value.Data()));
                        }

                        if (inspector.Empty()) {
                            m_drawers.emplace_back();
                            return;
                        }

                        PropertyDrawerBase::Ptr pDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                        if (!pDrawer) {
                            m_drawers.emplace_back();
                            return;
                        }

                        m_drawers.emplace_back(pDrawer);
                    });
                }

                PropertyDrawerContext propertyContext = context;
                propertyContext.pValue = nullptr;
                float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
                totalWidth -= ((!context.pValue && !context.noHeader) ? context.GetArrowWidth() : 0.f);
                propertyContext.fieldWidth = totalWidth * 0.7f;
                propertyContext.fieldTitleWidth = totalWidth * 0.3f;
                propertyContext.pOwner = value.Data();
                propertyContext.noHeader = false;

                pMeta->ForEachProperty([&](auto&& property, uint64_t index) {
                    if (property.IsHidden()) {
                        return;
                    }

                    if (!m_drawers[index]) {
                        SR_GRAPH_GUI_NS::ColoredText("Missing inspector for element!", ImColor(255, 0, 0));
                        return;
                    }

                    if (!context.pValue && !context.noHeader) {
                        ImGui::Dummy(ImVec2(context.GetArrowWidth(), 5.0f));
                        ImGui::SameLine();
                    }

                    propertyContext.noHeader = property.GetEditorParams().IsNoHeader();
                    propertyContext.pProperty = &property;

                    SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(property.IsReadOnly());

                    ImGui::BeginGroup();
                    PropertyDrawerFeedback propertyFeedback = m_drawers[index]->Draw(propertyContext);
                    ImGui::EndGroup();

                    if (propertyFeedback.isChanged) {
                        property.OnChanged(context.pOwner);
                        feedback.isChanged = true;
                    }
                });

                propertyContext.noHeader = false;

                PropertyDrawerFeedback customFeedback = DrawCustomProperties(context);
                if (customFeedback.isChanged) {
                    feedback.isChanged = true;
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
