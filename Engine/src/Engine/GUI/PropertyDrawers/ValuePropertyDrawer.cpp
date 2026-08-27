//
// Created by Monika on 03.02.2025.
//

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/EnumPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ValuePropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Serialization/Serializable.h>
#include <Utils/Platform/Platform.h>

#include <Codegen/ValuePropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ValuePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.HasExplicitSetter() ? context.GetValue().Copy() : context.GetValue();
        //if (value.GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
        //    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map value property!");
        //    return feedback;
        //}

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        if (!m_openedByDefault) {
            m_isOpened |= context.openedByDefault;
            m_openedByDefault = true;
        }

        m_isOpened |= context.noHeader;

        if (context.pValue && !context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetPropertyDisplayName();
            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }

        SR_UTILS_NS::Reflection::Value* pValue = value.Cast<SR_UTILS_NS::Reflection::Value>();
        if (value.GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            pValue = &value;
        }
        SR_UTILS_NS::Reflection::ReflectedCategoryType category = pValue->GetTypeInfo().category;

        if (m_isOpened) {
            if (!m_enumDrawer) {
                m_enumDrawer = MakeShared<EnumPropertyDrawer>();
            }

            PropertyDrawerContext enumContext = context;
            auto&& enumValue = SR_UTILS_NS::Reflection::Value::Create(category);
            enumContext.pValue = &enumValue;
            enumContext.pProperty = nullptr;
            enumContext.noHeader = false;
            enumContext.maxPartsInLine = 4;
            enumContext.fieldWidth += context.fieldTitleWidth;
            enumContext.fieldTitleWidth = 0.f;
            if (m_enumDrawer->Draw(enumContext).isChanged) {
                m_drawer = nullptr;
                m_typeNames.clear();
                m_detailedSizes.clear();
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                pTypeInfo->category = category;
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                *pValue = SR_UTILS_NS::Reflection::Value::CreateDefault(pTypeInfo);
                SR_UTILS_NS::Reflection::FreeTypeInfo(pTypeInfo);
                feedback.isChanged = true;
            }
        }

        if (m_lastCategoryType != category) {
            m_lastCategoryType = category;
            m_drawer = nullptr;
            m_typeNames.clear();
            m_detailedSizes.clear();
        }

        if (m_typeNames.empty()) {
            SR_UTILS_NS::Reflection::GetTypeNamesByCategory(category, m_typeNames);
        }

        if (m_lastDetailedType != pValue->GetTypeInfo().detailedType) {
            m_lastDetailedType = pValue->GetTypeInfo().detailedType;
            m_drawer = nullptr;
        }

        /// select detailed type
        if (m_isOpened && !m_typeNames.empty()) {
            SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>::iterator pTypeNameIt = m_typeNames.end();

            auto&& detailedType = pValue->GetTypeInfo().detailedType;
            pTypeNameIt = std::find(m_typeNames.begin(), m_typeNames.end(), detailedType);

            std::optional<uint64_t> selectedIndex = pTypeNameIt != m_typeNames.end() ? std::make_optional(m_typeNames.distance(pTypeNameIt)) : std::nullopt;
            const char* pPrevValue = selectedIndex.has_value() ? m_typeNames[selectedIndex.value()].data() : m_default.c_str();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth + context.fieldTitleWidth);

            if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Type##Combo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                if (!m_comboTypeOpened) {
                    SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                    m_comboTypeOpened = true;
                }

                if (SR_GRAPH_GUI_NS::Immediate::InputText("##Search", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < m_typeNames.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_typeNames[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(m_typeNames[i].data(), isSelected)) {
                        selectedIndex = i;
                        m_searchBuffer = m_typeNames[i];
                        SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::EndCombo();
            }
            else {
                m_comboTypeOpened = false;
                m_searchBuffer.clear();
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            if (selectedIndex && m_typeNames[*selectedIndex] != detailedType) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                pTypeInfo->category = category;
                pTypeInfo->detailedType = m_typeNames[*selectedIndex];
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                *pValue = SR_UTILS_NS::Reflection::Value::CreateDefault(pTypeInfo);
                SR_UTILS_NS::Reflection::FreeTypeInfo(pTypeInfo);
                feedback.isChanged = true;
                m_drawer = nullptr;
                m_detailedSizes.clear();
            }
        }

        if (m_detailedSizes.empty()) {
            SR_UTILS_NS::Reflection::GetTypeDetailedSizes(category, m_lastDetailedType, m_detailedSizes);
            m_detailedSizesStr.clear();
            for (auto&& size : m_detailedSizes) {
                m_detailedSizesStr.emplace_back(SR_FORMAT("{}", size));
            }
        }

        /// select detailed size
        if (m_isOpened && !m_detailedSizes.empty()) {
            SR_UTILS_NS::Vector<uint8_t>::iterator pSizeIt = m_detailedSizes.end();

            auto&& size = pValue->GetTypeInfo().detailedSize;
            pSizeIt = std::find(m_detailedSizes.begin(), m_detailedSizes.end(), size);

            std::optional<uint64_t> selectedIndex = pSizeIt != m_detailedSizes.end() ? std::make_optional(m_detailedSizes.distance(pSizeIt)) : std::nullopt;
            const char* pPrevValue = selectedIndex.has_value() ? m_detailedSizesStr[selectedIndex.value()].c_str() : m_default.c_str();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth + context.fieldTitleWidth);

            if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Size##SizeCombo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                if (!m_comboSizeOpened) {
                    SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                    m_comboSizeOpened = true;
                }

                if (SR_GRAPH_GUI_NS::Immediate::InputText("##SizeSearch", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < m_detailedSizes.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, m_detailedSizesStr[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(m_detailedSizesStr[i].c_str(), isSelected)) {
                        selectedIndex = i;
                        m_searchBuffer = m_detailedSizesStr[i];
                        SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::EndCombo();
            }
            else {
                m_comboSizeOpened = false;
                m_searchBuffer.clear();
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            if (selectedIndex && m_detailedSizes[*selectedIndex] != size) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                pTypeInfo->category = category;
                pTypeInfo->detailedType = m_lastDetailedType;
                pTypeInfo->detailedSize = m_detailedSizes[*selectedIndex];
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                *pValue = SR_UTILS_NS::Reflection::Value::CreateDefault(pTypeInfo);
                SR_UTILS_NS::Reflection::FreeTypeInfo(pTypeInfo);
                feedback.isChanged = true;
                m_drawer = nullptr;
            }
        }

        if (m_isOpened && !m_drawer) {
            SR_UTILS_NS::StringAtom inspector = SR_CORE_GUI_NS::GetValueInspector(*pValue);
            if (!inspector.Empty()) {
                m_drawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
            }
        }

        if (m_isOpened && m_drawer) {
            PropertyDrawerContext elementContext = context;
            if (category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
                elementContext.pValue = pValue->Cast<SR_UTILS_NS::Reflection::Value>();
            }
            else {
                elementContext.pValue = pValue;
            }
            elementContext.pProperty = nullptr;
            elementContext.fieldWidth += context.fieldTitleWidth;
            elementContext.fieldTitleWidth = 0.f;
            elementContext.noHeader = false;
            elementContext.openedByDefault = true;

            if (elementContext.pValue->IsValid()) {
                SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                SR_GRAPH_GUI_NS::Immediate::PushID("ValueDrawer");
                PropertyDrawerFeedback elementFeedback = m_drawer->Draw(elementContext);
                SR_GRAPH_GUI_NS::Immediate::PopID();
                SR_GRAPH_GUI_NS::Immediate::EndGroup();
                if (elementFeedback.isChanged) {
                    feedback.isChanged = true;
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        const bool needForceSet = context.pValue && feedback.isChanged && value.GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Value;
        if (needForceSet) {
            *context.pValue = value.Copy();
        }
        else {
            SetValue(context, feedback, value);
        }

        return feedback;
    }
}
