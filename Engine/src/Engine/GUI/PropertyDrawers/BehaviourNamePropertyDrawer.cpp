//
// Created by Monika on 04.05.2025.
//

#include <Engine/GUI/PropertyDrawers/BehaviourNamePropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PropertyDrawerUtils.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Base/ScriptSystem.h>

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

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetProperty().GetName().c_str());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetProperty().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }
            DrawTitleContextMenu(context, feedback);

            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

        auto&& pBehaviour = dynamic_cast<SR_SCRIPTING_NS::Behaviour*>(context.pOwner);
        SRAssert2(pBehaviour, "pOwner is not a Behaviour!");

        if (value.GetTypeInfo().detailedType == "StringAtom") {
            if (auto&& pStringAtom = value.Cast<SR_UTILS_NS::StringAtom>()) {
                const bool markAsInvalid = !pBehaviour->IsInstanceValid();
                if (markAsInvalid) {
                    SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f));
                }

                SR_UTILS_NS::Optional<uint32_t> selectedIndex = GetSelectedIndex(*pStringAtom);

                const char* pPrevValue = selectedIndex ? m_existingNames[selectedIndex.value()].c_str() : pStringAtom->c_str();
                if (SR_IMMEDIATE_GUI_NS::BeginCombo("##Combo", pPrevValue, SR_IMMEDIATE_GUI_NS::ComboFlags::NoArrowButton)) {
                    if (markAsInvalid) {
                        SR_IMMEDIATE_GUI_NS::PopStyleColor();
                    }

                    if (!m_comboOpened) {
                        ReInitNames();
                        selectedIndex = GetSelectedIndex(*pStringAtom);
                        SR_IMMEDIATE_GUI_NS::SetKeyboardFocusHere();
                        m_comboOpened = true;
                    }

                    if (SR_IMMEDIATE_GUI_NS::InputText("##Search", &m_searchBuffer)) {
                        SR_NOOP;
                    }

                    for (uint64_t i = 0; i < m_existingNames.size(); ++i) {
                        if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_existingNames[i])) {
                            continue;
                        }

                        bool isSelected = selectedIndex && selectedIndex.Value() == i;
                        if (SR_IMMEDIATE_GUI_NS::Selectable(m_existingNames[i].c_str(), isSelected)) {
                            selectedIndex = i;
                            m_searchBuffer = m_existingNames[i];
                            SR_IMMEDIATE_GUI_NS::CloseCurrentPopup();
                        }

                        if (isSelected) {
                            SR_IMMEDIATE_GUI_NS::SetItemDefaultFocus();
                        }
                    }
                    SR_IMMEDIATE_GUI_NS::EndCombo();
                }
                else {
                    if (markAsInvalid) {
                        SR_IMMEDIATE_GUI_NS::PopStyleColor();
                    }
                    m_comboOpened = false;
                    m_searchBuffer.clear();
                }

                if (selectedIndex && *pStringAtom != m_existingNames[selectedIndex.value()]) {
                    SetPropertyDrawerMappedValue(context, feedback, pStringAtom, m_existingNames[selectedIndex.value()]);
                }
            }
            else {
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map string atom value!");
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Invalid string type!");
        }

        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }

    void BehaviourNamePropertyDrawer::ReInitNames() {
        m_existingNames = SR_SCRIPTING_NS::ScriptSystem::Instance().GetBehaviourNames();
    }

    SR_UTILS_NS::Optional<uint32_t> BehaviourNamePropertyDrawer::GetSelectedIndex(SR_UTILS_NS::StringAtom name) const {
        for (uint32_t i = 0; i < m_existingNames.size(); ++i) {
            if (m_existingNames[i] == name) {
                return i;
            }
        }

        return {};
    }
}
