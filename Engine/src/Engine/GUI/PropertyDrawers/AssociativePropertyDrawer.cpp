//
// Created by Monika on 27.07.2025.
//

#include <Engine/GUI/PropertyDrawers/AssociativePropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Codegen/AssociativePropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    AssociativePropertyDrawer::AssociativePropertyDrawer()
        : Super()
    { }

    AssociativePropertyDrawer::~AssociativePropertyDrawer() {
        SR_SAFE_DELETE_PTR(m_keyValue);
    }

    PropertyDrawerFeedback AssociativePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        SR_TRACY_ZONE;

        if (!m_keyValue) {
            m_keyValue = new SR_UTILS_NS::Reflection::Value();
        }

        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();
        SR_UTILS_NS::Reflection::AssociativeContainerValueRef container = value.AsAssociativeContainer();

        const bool isSetLike = value.GetTypeInfo().detailedType == "Set" || value.GetTypeInfo().detailedType == "FlatHashSet";

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyDisplayName().ToCStr());
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        SR_UTILS_NS::StringAtom displayName = context.GetPropertyDisplayName();

        const SR_MATH_NS::FVector2 counterButtonWidth = { 40, context.fieldHeight };

        auto&& pWindow = SR_IMMEDIATE_GUI_NS::GetCurrentWindow();
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_IMMEDIATE_GUI_NS::GetWindowCursorPos(pWindow);
        const auto dir = m_isOpened ? SR_IMMEDIATE_GUI_NS::Direction::Down : SR_IMMEDIATE_GUI_NS::Direction::Right;

        if (context.pValue) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };
            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
        }
        else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };

            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::BeginDisabled();
        m_tmpBuffer.clear();
        SR_UTILS_NS::FormatTo(m_tmpBuffer, "{}", container.Size());
        SR_IMMEDIATE_GUI_NS::Button(m_tmpBuffer.c_str(), counterButtonWidth);
        SR_IMMEDIATE_GUI_NS::EndDisabled();

        if (!m_keyDrawer && value.GetTypeInfo().pNext[0]) {
            if (isSetLike) {
                *m_keyValue = SR_UTILS_NS::Reflection::Value::CreateDefault(value.GetTypeInfo().pNext[0]);
            }
            else {
                *m_keyValue = SR_UTILS_NS::Reflection::Value::CreateDefault(value.GetTypeInfo().pNext[0]->pNext[0]);
            }
            SR_UTILS_NS::StringAtom inspectorName = GetValueInspector(*m_keyValue);
            if (!inspectorName.empty()) {
                m_keyDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspectorName);
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        const SR_MATH_NS::FVector2 buttonSize = { 50, context.fieldHeight };

        if (SR_IMMEDIATE_GUI_NS::Button("Add", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            feedback.isChanged = true;
            if (isSetLike) {
                container.Insert(m_keyValue->Copy(), SR_UTILS_NS::Reflection::Value());
            }
            else {
                container.Insert(m_keyValue->Copy(), SR_UTILS_NS::Reflection::Value::CreateDefault(value.GetTypeInfo().pNext[1]));
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        PropertyDrawerContext keyCtx = context;

        keyCtx.isEnumValueAvailableCheckFn = [&](SR_UTILS_NS::StringAtom enumValue) {
            if (m_keyValue->GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum) {
                SRHalt("AssociativePropertyDrawer::Draw() : key value is not an enum type!");
                return true;
            }

            SR_UTILS_NS::EnumReflector* pReflector = SR_UTILS_NS::EnumReflectorManager::Instance().GetReflector(m_keyValue->GetEnumType());
            if (!pReflector) {
                SRHalt("AssociativePropertyDrawer::Draw() : key value enum reflector is not found!");
                return true;
            }

            const int64_t enumValueInt = pReflector->FromStringInternal(enumValue).value();

            for (auto&& pIt = container.Begin(); pIt != container.End(); ++pIt) {
                void* pMappedRaw = pIt.First().Data();
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
        if (m_keyDrawer) {
            m_keyDrawer->Draw(keyCtx);
        }

        if (m_isOpened) {
            for (auto&& pIt = container.Begin(); pIt != container.End(); ++pIt) {
                const uint64_t index = SR_UTILS_NS::Distance(container.Begin(), pIt);
                SR_IMMEDIATE_GUI_NS::PushID(static_cast<int32_t>(index));

                SR_UTILS_NS::Reflection::Value firstValue = pIt.First().Copy();

                SR_MATH_NS::FVector2 spaceSize = { 40, context.fieldHeight };
                if (isSetLike) {
                    spaceSize.x = context.fieldTitleWidth;
                }

                SR_IMMEDIATE_GUI_NS::Dummy(spaceSize);
                SR_IMMEDIATE_GUI_NS::SameLine();

                SR_IMMEDIATE_GUI_NS::BeginGroup();
                SR_IMMEDIATE_GUI_NS::BeginDisabled();

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

                SR_IMMEDIATE_GUI_NS::EndDisabled();
                SR_IMMEDIATE_GUI_NS::EndGroup();

                if (SR_IMMEDIATE_GUI_NS::BeginPopupContextItem("ElementContextMenu")) {
                    if (SR_IMMEDIATE_GUI_NS::MenuItem("Remove")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;
                        container.Erase(pIt);
                        SR_IMMEDIATE_GUI_NS::EndPopup();
                        SR_IMMEDIATE_GUI_NS::PopID();
                        break;
                    }
                    SR_IMMEDIATE_GUI_NS::EndPopup();
                }

                if (!isSetLike) {
                    SR_UTILS_NS::Reflection::Value secondValue = pIt.Second();

                    SR_IMMEDIATE_GUI_NS::SameLine();

                    SR_IMMEDIATE_GUI_NS::PushID("Value");

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

                    SR_IMMEDIATE_GUI_NS::BeginGroup();
                    PropertyDrawerFeedback elementFeedback = m_valueDrawers[index]->Draw(valueContext);
                     SR_IMMEDIATE_GUI_NS::EndGroup();

                    if (elementFeedback.isChanged) {
                        feedback.isChanged = true;
                    }

                    SR_IMMEDIATE_GUI_NS::PopID();
                }

                SR_IMMEDIATE_GUI_NS::PopID();
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();
        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }
}