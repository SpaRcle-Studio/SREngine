//
// Created by Monika on 04.05.2025.
//

#include <Core/GUI/PropertyDrawers/BehaviourNamePropertyDrawer.h>

#include <Utils/Events/Broadcaster.h>

#include <Codegen/BehaviourNamePropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    BehaviourNamePropertyDrawer::BehaviourNamePropertyDrawer() {
        ReInitNames();
        m_moduleReloadSubscription = SR_UTILS_NS::Broadcaster::Instance().Subscribe(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID, [this](auto&& msg) {
            ReInitNames();
        });
    }

    PropertyDrawerFeedback BehaviourNamePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().c_str());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }

            ImGui::SameLine();
        }

        ImGui::PushItemWidth(context.fieldWidth);

        auto&& pBehaviour = dynamic_cast<SR_SCRIPTING_NS::Behaviour*>(context.pOwner);
        SRAssert2(pBehaviour, "pOwner is not a Behaviour!");

        if (value.IsStringAtom()) {
            if (auto&& pStringAtom = value.TryCast<SR_UTILS_NS::StringAtom>()) {
                const bool markAsInvalid = !pBehaviour->IsInstanceValid();
                if (markAsInvalid) {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 0.f, 0.f, 1.f));
                }

                std::optional<uint64_t> selectedIndex = GetSelectedIndex(*pStringAtom);

                const char* pPrevValue = selectedIndex ? m_existingNames[selectedIndex.value()].c_str() : pStringAtom->c_str();
                if (ImGui::BeginCombo("##Combo", pPrevValue, ImGuiComboFlags_NoArrowButton)) {
                    if (markAsInvalid) {
                        ImGui::PopStyleColor();
                    }

                    if (!m_comboOpened) {
                        ImGui::SetKeyboardFocusHere();
                        m_comboOpened = true;
                    }

                    if (ImGui::InputText("##Search", &m_searchBuffer)) {
                        SR_NOOP;
                    }

                    for (uint64_t i = 0; i < m_existingNames.size(); ++i) {
                        if (!m_searchBuffer.empty() && !CheckSearchMatch(m_searchBuffer, m_existingNames[i])) {
                            continue;
                        }

                        bool isSelected = (selectedIndex == i);
                        if (ImGui::Selectable(m_existingNames[i].c_str(), isSelected)) {
                            selectedIndex = i;
                            m_searchBuffer = m_existingNames[i];
                            ImGui::CloseCurrentPopup();
                        }

                        if (isSelected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }
                else {
                    if (markAsInvalid) {
                        ImGui::PopStyleColor();
                    }
                    m_comboOpened = false;
                    m_searchBuffer.clear();
                }

                if (selectedIndex && *pStringAtom != m_existingNames[selectedIndex.value()]) {
                    SetMappedValue(context, feedback, pStringAtom, m_existingNames[selectedIndex.value()]);
                }
            }
            else {
                SR_GRAPH_GUI_NS::ColoredText("Failed to map string atom value!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
        }
        else {
            SR_GRAPH_GUI_NS::ColoredText("Invalid string type!", ImColor(1.f, 0.f, 0.f, 1.f));
        }

        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }

    void BehaviourNamePropertyDrawer::ReInitNames() {
        static const SR_UTILS_NS::StringAtom cppBehaviourName = SR_SCRIPTING_NS::CppBehaviour::GetClassStaticName();
        auto&& factory = SR_UTILS_NS::Factory::Instance();

        m_existingNames = factory.GetInheritances(cppBehaviourName);

        std::erase_if(m_existingNames, [factory](const auto& name) {
            return factory.IsAbstract(name);
        });
    }

    std::optional<uint32_t> BehaviourNamePropertyDrawer::GetSelectedIndex(SR_UTILS_NS::StringAtom name) const {
        for (uint32_t i = 0; i < m_existingNames.size(); ++i) {
            if (m_existingNames[i] == name) {
                return i;
            }
        }

        return std::nullopt;
    }
}
