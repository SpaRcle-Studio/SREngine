//
// Created by Monika on 04.05.2025.
//

#include <Engine/GUI/PropertyDrawers/BehaviourNamePropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PropertyDrawerUtils.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Scripting/Base/Behaviour.h>

#include <Utils/Events/Broadcaster.h>
#include <Utils/Common/StringUtils.h>

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

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetProperty().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        auto&& pBehaviour = dynamic_cast<SR_SCRIPTING_NS::Behaviour*>(context.pOwner);
        SRAssert2(pBehaviour, "pOwner is not a Behaviour!");

        if (value.GetTypeInfo().detailedType == "StringAtom") {
            if (auto&& pStringAtom = value.Cast<SR_UTILS_NS::StringAtom>()) {
                const bool markAsInvalid = !pBehaviour->IsInstanceValid();
                if (markAsInvalid) {
                    SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f));
                }

                std::optional<uint64_t> selectedIndex = GetSelectedIndex(*pStringAtom);

                const char* pPrevValue = selectedIndex ? m_existingNames[selectedIndex.value()].c_str() : pStringAtom->c_str();
                if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("##Combo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                    if (markAsInvalid) {
                        SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
                    }

                    if (!m_comboOpened) {
                        SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                        m_comboOpened = true;
                    }

                    if (SR_GRAPH_GUI_NS::Immediate::InputText("##Search", &m_searchBuffer)) {
                        SR_NOOP;
                    }

                    for (uint64_t i = 0; i < m_existingNames.size(); ++i) {
                        if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_existingNames[i])) {
                            continue;
                        }

                        bool isSelected = (selectedIndex == i);
                        if (SR_GRAPH_GUI_NS::Immediate::Selectable(m_existingNames[i].c_str(), isSelected)) {
                            selectedIndex = i;
                            m_searchBuffer = m_existingNames[i];
                            SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                        }

                        if (isSelected) {
                            SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                        }
                    }
                    SR_GRAPH_GUI_NS::Immediate::EndCombo();
                }
                else {
                    if (markAsInvalid) {
                        SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
                    }
                    m_comboOpened = false;
                    m_searchBuffer.clear();
                }

                if (selectedIndex && *pStringAtom != m_existingNames[selectedIndex.value()]) {
                    SetPropertyDrawerMappedValue(context, feedback, pStringAtom, m_existingNames[selectedIndex.value()]);
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
