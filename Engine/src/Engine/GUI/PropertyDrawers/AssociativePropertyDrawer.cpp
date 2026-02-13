//
// Created by Monika on 27.07.2025.
//

#include <Engine/GUI/PropertyDrawers/AssociativePropertyDrawer.h>

#include <Graphics/GUI/ImmediateGUI.h>

#include <Codegen/AssociativePropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    AssociativePropertyDrawer::AssociativePropertyDrawer()
        : Super()
    { }

    AssociativePropertyDrawer::~AssociativePropertyDrawer()
    {
        SR_SAFE_DELETE_PTR(m_keyValue);
    }

    PropertyDrawerFeedback AssociativePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        SR_TRACY_ZONE;

        if (!m_keyValue) {
            m_keyValue = new SR_UTILS_NS::Reflection::Value();
        }

        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();
        if (!value.IsAssociativeContainer()) {
            SRHalt("AssociativePropertyDrawer can only be used with associative containers!");
            return feedback;
        }

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().ToCStr());
        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& container = value.AsAssociativeContainer();
        SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetEditorParams().GetDisplayName();

        const SR_MATH_NS::FVector2 counterButtonWidth = { 40, context.fieldHeight };

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);
        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        if (context.pValue) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };
            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }
        else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
        SR_GRAPH_GUI_NS::Immediate::Button("{}"_format(container.Size()).c_str(), counterButtonWidth);
        SR_GRAPH_GUI_NS::Immediate::EndDisabled();

        if (!m_keyDrawer) {
            *m_keyValue = container.GetKeyType();
            SR_UTILS_NS::StringAtom inspectorName = GetValueInspector(*m_keyValue);
            m_keyDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspectorName);
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        const SR_MATH_NS::FVector2 buttonSize = { 50, context.fieldHeight };

        if (SR_GRAPH_GUI_NS::Immediate::Button("Add", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            feedback.isChanged = true;
            container.Insert(*m_keyValue, container.GetMappedType());
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        PropertyDrawerContext keyCtx = context;

        keyCtx.isEnumValueAvailableCheckFn = [&](SR_UTILS_NS::StringAtom enumValue) {
            if (!m_keyValue->IsEnum()) {
                SRHalt("AssociativePropertyDrawer::Draw() : key value is not an enum type!");
                return true;
            }

            SR_UTILS_NS::EnumReflector* pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(m_keyValue->GetEnumType());
            if (!pReflector) {
                SRHalt("AssociativePropertyDrawer::Draw() : key value enum reflector is not found!");
                return true;
            }

            const int64_t enumValueInt = pReflector->FromStringInternal(enumValue).value();

            for (auto&& pIt = container.begin(); pIt != container.end(); ++pIt) {
                void* pMappedRaw = pIt.First().Detach().Data();
                if (pReflector->ReadEnumValueFromPointerInternal(pMappedRaw) == enumValueInt) {
                    return false;
                }
            }
            return true;
        };

        keyCtx.pValue = m_keyValue;
        keyCtx.fieldTitleWidth = 0.f;
        keyCtx.noHeader = true;
        keyCtx.fieldWidth = context.fieldWidth - counterButtonWidth.x - buttonSize.x;
        m_keyDrawer->Draw(keyCtx);

        if (m_isOpened) {
            for (auto&& pIt = container.begin(); pIt != container.end(); ++pIt) {
                const uint64_t index = SR_UTILS_NS::Distance(container.begin(), pIt);
                SR_GRAPH_GUI_NS::Immediate::PushID(index);

                SR_UTILS_NS::Reflection::Value firstValue = pIt.First().Detach();
                SR_UTILS_NS::Reflection::Value secondValue = pIt.Second();
                const bool isSetLike = secondValue.SizeOf() == 0;

                SR_MATH_NS::FVector2 spaceSize = { 40, context.fieldHeight };
                if (isSetLike) {
                    spaceSize.x = context.fieldTitleWidth;
                }

                SR_GRAPH_GUI_NS::Immediate::Dummy(spaceSize);
                SR_GRAPH_GUI_NS::Immediate::SameLine();

                SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();

                m_keyDrawers.resize(SR_MAX(m_keyDrawers.size(), index + 1));
                if (!m_keyDrawers[index]) {
                    m_keyDrawers[index] = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(GetValueInspector(*m_keyValue));
                }

                PropertyDrawerContext keyContext = context;
                keyContext.pValue = &firstValue;
                if (isSetLike) {
                    keyContext.fieldWidth = context.fieldWidth;
                }
                else {
                    keyContext.fieldWidth = context.fieldTitleWidth - spaceSize.x;
                }
                keyContext.fieldTitleWidth = 0.f;
                keyContext.noHeader = false;
                m_keyDrawers[index]->Draw(keyContext);

                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
                SR_GRAPH_GUI_NS::Immediate::EndGroup();

                if (SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem("ElementContextMenu")) {
                    if (SR_GRAPH_GUI_NS::Immediate::MenuItem("Remove")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;
                        container.Erase(firstValue);
                        SR_GRAPH_GUI_NS::Immediate::EndPopup();
                        SR_GRAPH_GUI_NS::Immediate::PopID();
                        break;
                    }
                    SR_GRAPH_GUI_NS::Immediate::EndPopup();
                }

                if (!isSetLike) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();

                    SR_GRAPH_GUI_NS::Immediate::PushID("Value");

                    m_valueDrawers.resize(SR_MAX(m_valueDrawers.size(), index + 1));
                    if (!m_valueDrawers[index]) {
                        m_valueDrawers[index] = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(GetValueInspector(secondValue));
                    }

                    PropertyDrawerContext valueContext = context;
                    valueContext.pValue = &secondValue;
                    valueContext.fieldWidth = context.fieldWidth;
                    valueContext.fieldTitleWidth = 0.f;
                    valueContext.noHeader = true;
                    valueContext.openedByDefault = false;

                    SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                    PropertyDrawerFeedback elementFeedback = m_valueDrawers[index]->Draw(valueContext);
                    SR_GRAPH_GUI_NS::Immediate::EndGroup();

                    if (elementFeedback.isChanged) {
                        feedback.isChanged = true;
                    }

                    SR_GRAPH_GUI_NS::Immediate::PopID();
                }

                SR_GRAPH_GUI_NS::Immediate::PopID();
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();
        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        SetValue(context, feedback, value);
        return feedback;
    }
}