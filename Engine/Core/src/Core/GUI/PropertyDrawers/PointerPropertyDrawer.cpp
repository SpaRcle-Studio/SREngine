//
// Created by Monika on 03.02.2025.
//

#include <Core/GUI/PropertyDrawers/PointerPropertyDrawer.h>

#include <Codegen/PointerPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PointerPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        auto&& editorParams = context.GetEditorParams();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        auto&& pWindow = ImGui::GetCurrentWindow();
        const ImGuiDir_ dir = m_isOpened ? ImGuiDir_Down : ImGuiDir_Right;

        std::string_view typeName = value.GetSharedPtrType();
        if (size_t pos = typeName.rfind(':'); pos != std::string_view::npos) {
            typeName.remove_prefix(pos + 1);
        }

        m_isOpened |= context.noHeader;

        if (context.pValue && !context.noHeader) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(5, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const ImVec2 mainButtonSize = { 30, context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::BeginForceEnabled();
            if (ImGui::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(0, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            const float_t arrowWidth = context.lineHeight * 0.75f;
            ImGui::Dummy(ImVec2(arrowWidth, 0));

            ImGui::SameLine();

            const ImVec2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = editorParams.GetDisplayName();
            auto&& stackSize = SR_GRAPH_GUI_NS::BeginForceEnabled();
            if (ImGui::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::EndForceEnabled(stackSize);
        }

        SR_UTILS_NS::SRClass* pClassValue = value.GetSRClass();

        if (!context.noHeader) {
            ImGui::SameLine();

            if (m_default.empty()) {
                m_default = "{} (nullptr)"_format(typeName);
            }

            if (m_typeNames.empty()) {
                if (!editorParams.IsNotNull()) {
                    m_typeNames.emplace_back("(nullptr)");
                }

                auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(typeName);
                if (pMeta && !pMeta->IsAbstract()) {
                    m_typeNames.emplace_back(pMeta->GetFactoryName());
                }

                for (auto&& type : SR_UTILS_NS::Factory::Instance().GetInheritances(typeName)) {
                    m_typeNames.emplace_back(type);
                }
            }

            std::vector<std::string>::iterator pTypeNameIt = m_typeNames.end();

            if (pClassValue) {
                const SR_UTILS_NS::SRClassMeta* pMeta = pClassValue->GetMeta();
                SRAssert(pMeta);
                pTypeNameIt = std::find(m_typeNames.begin(), m_typeNames.end(), pMeta->GetFactoryName());
            }

            std::optional<uint64_t> selectedIndex = pTypeNameIt != m_typeNames.end() ? std::make_optional(std::distance(m_typeNames.begin(), pTypeNameIt)) : std::nullopt;

            const char* pPrevValue = selectedIndex.has_value() ? m_typeNames[selectedIndex.value()].data() : m_default.c_str();

            ImGui::PushItemWidth(context.fieldWidth);

            if (m_typeNames.size() <= 1) {
                ImGui::BeginDisabled();
            }

            if (ImGui::BeginCombo("##Combo", pPrevValue, ImGuiComboFlags_NoArrowButton)) {
                if (!m_comboOpened) {
                    ImGui::SetKeyboardFocusHere();
                    m_comboOpened = true;
                }

                if (ImGui::InputText("##Search", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < m_typeNames.size(); ++i) {
                    if (!m_searchBuffer.empty() && !CheckSearchMatch(m_searchBuffer, m_typeNames[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (ImGui::Selectable(m_typeNames[i].data(), isSelected))
                    {
                        selectedIndex = i;
                        m_searchBuffer = m_typeNames[i];
                        ImGui::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        ImGui::SetItemDefaultFocus();
                    }
                }
                ImGui::EndCombo();
            }
            else {
                m_comboOpened = false;
                m_searchBuffer.clear();
            }

            if (m_typeNames.size() <= 1) {
                ImGui::EndDisabled();
            }

            ImGui::PopItemWidth();

            if (selectedIndex) {
                if (m_typeNames[selectedIndex.value()] == "(nullptr)") {
                    OnObjectReplaced(pClassValue, nullptr);
                    value.SetSRClass(nullptr);
                    feedback.isChanged = true;
                }
                else if (pClassValue) {
                    if (m_typeNames[selectedIndex.value()] != pClassValue->GetMeta()->GetFactoryName()) {
                        SRClass* pNew = SR_UTILS_NS::Factory::Instance().CreateBase(m_typeNames[selectedIndex.value()]);
                        OnObjectReplaced(pClassValue, pNew);
                        value.SetSRClass(pNew);
                        feedback.isChanged = true;
                    }
                }
                else {
                    SRClass* pNew = SR_UTILS_NS::Factory::Instance().CreateBase(m_typeNames[selectedIndex.value()]);
                    OnObjectReplaced(pClassValue, pNew);
                    value.SetSRClass(pNew);
                    feedback.isChanged = true;
                }

                pClassValue = value.GetSRClass();
            }
        }

        if (m_isOpened && pClassValue) {
            if (m_lastTypeName != pClassValue->GetMeta()->GetFactoryName()) {
                m_lastTypeName = pClassValue->GetMeta()->GetFactoryName();

                if (auto&& inspectorName = pClassValue->GetMeta()->GetInspectorName(); !inspectorName.empty()) {
                    m_objectDrawer = SR_UTILS_NS::Factory::Instance().Create<ObjectPropertyDrawer>(inspectorName);
                }
                if (!m_objectDrawer) {
                    m_objectDrawer = SRNew<ObjectPropertyDrawer>();
                }
            }

            if (!context.pValue && !context.noHeader) {
                ImGui::Dummy(ImVec2(context.GetArrowWidth(), 5.0f));
                ImGui::SameLine();
            }

            PropertyDrawerContext propertyContext = context;
            auto&& valueRef = SR_UTILS_NS::Reflection::Value::CreateRef(*pClassValue);
            propertyContext.pValue = &valueRef;
            float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
            totalWidth -= ((!context.pValue && !context.noHeader) ? context.GetArrowWidth() : 0.f);
            propertyContext.fieldWidth = totalWidth * 0.7f;
            propertyContext.fieldTitleWidth = totalWidth * 0.3f;
            propertyContext.pProperty = nullptr;
            propertyContext.pOwner = pClassValue;
            propertyContext.noHeader = true;

            ImGui::BeginGroup();
            PropertyDrawerFeedback propertyFeedback = m_objectDrawer->Draw(propertyContext);
            ImGui::EndGroup();

            if (propertyFeedback.isChanged) {
                feedback.isChanged = true;
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