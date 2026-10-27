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
            DrawTitleContextMenu(context, feedback);
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }

        SR_UTILS_NS::Reflection::Value* pValue = value.Cast<SR_UTILS_NS::Reflection::Value>();
        if (value.GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
            pValue = &value;
        }

        if (m_isOpened) {
            uint32_t index = 0;
            if (auto&& pTypeInfo = DrawTypeInfo(index, pValue->GetTypeInfo(), context)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                *pValue = SR_UTILS_NS::Reflection::Value::CreateDefault(pTypeInfo);
                SR_UTILS_NS::Reflection::FreeTypeInfo(pTypeInfo);
                feedback.isChanged = true;
            }
        }

        if (m_lastTypeInfoHash != pValue->GetTypeInfo().GetHash()) {
            m_drawer = nullptr;
            m_lastTypeInfoHash = pValue->GetTypeInfo().GetHash();
        }

        if (m_isOpened && !m_drawer) {
            SR_UTILS_NS::StringAtom inspector = SR_CORE_GUI_NS::GetValueInspector(*pValue);
            if (!inspector.Empty()) {
                m_drawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
            }
        }

        if (m_isOpened && m_drawer) {
            PropertyDrawerContext elementContext = context;
            if (pValue->GetTypeInfo().category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Value) {
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

    SR_UTILS_NS::Reflection::TypeInfo* ValuePropertyDrawer::DrawTypeInfo(uint32_t& index, const SR_UTILS_NS::Reflection::TypeInfo& typeInfo, const PropertyDrawerContext& context) {
        SR_TRACY_ZONE;

        ++index;
        m_comboTypeOpenedStack.resize(SR_MAX(m_comboTypeOpenedStack.size(), index));
        m_comboSizeOpenedStack.resize(SR_MAX(m_comboSizeOpenedStack.size(), index));
        m_enumDrawers.resize(SR_MAX(m_enumDrawers.size(), index));

        SR_IMMEDIATE_GUI_NS::PushID(index);

        auto&& pEnumDrawer = m_enumDrawers[index - 1];

        if (!pEnumDrawer) {
            pEnumDrawer = MakeShared<EnumPropertyDrawer>();
        }

        PropertyDrawerContext enumContext = context;
        auto&& enumValue = SR_UTILS_NS::Reflection::Value::Create(typeInfo.category);
        enumContext.pValue = &enumValue;
        enumContext.pProperty = nullptr;
        enumContext.noHeader = false;
        enumContext.maxPartsInLine = 4;
        enumContext.fieldWidth += context.fieldTitleWidth;
        enumContext.fieldTitleWidth = 0.f;

        if (pEnumDrawer->Draw(enumContext).isChanged) {
            auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
            pTypeInfo->category = typeInfo.category;
            SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
            SR_IMMEDIATE_GUI_NS::PopID();
            return pTypeInfo;
        }

        auto&& typeNames = m_typeNames;
        auto&& detailedSizes = m_detailedSizes;
        auto&& detailedSizesStr = m_detailedSizesStr;

        SR_UTILS_NS::Reflection::GetTypeNamesByCategory(typeInfo.category, typeNames);

        SR_UTILS_NS::Reflection::GetTypeDetailedSizes(typeInfo.category, typeInfo.detailedType, detailedSizes);
        detailedSizesStr.resize(SR_MAX(detailedSizesStr.size(), detailedSizes.size()));
        for (uint64_t i = 0; i < detailedSizes.size(); i++) {
            detailedSizesStr[i].clear();
            SR_UTILS_NS::FormatTo(detailedSizesStr[i], "{}", detailedSizes[i]);
        }

         /// select category type
        if (!typeNames.empty()) {
            auto&& detailedType = typeInfo.detailedType;
            auto pTypeNameIt = std::find(typeNames.begin(), typeNames.end(), detailedType);

            std::optional<uint64_t> selectedIndex = pTypeNameIt != typeNames.end() ? std::make_optional(typeNames.distance(pTypeNameIt)) : std::nullopt;
            const char* pPrevValue = selectedIndex.has_value() ? typeNames[selectedIndex.value()].data() : m_default.c_str();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth + context.fieldTitleWidth);

            bool& comboTypeOpened = m_comboTypeOpenedStack.at(index - 1);
            if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Type##Combo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                if (!comboTypeOpened) {
                    SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                    comboTypeOpened = true;
                }

                if (SR_GRAPH_GUI_NS::Immediate::InputText("##Search", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < typeNames.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, typeNames[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(typeNames[i].data(), isSelected)) {
                        selectedIndex = i;
                        m_searchBuffer = typeNames[i];
                        SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::EndCombo();
            }
            else {
                comboTypeOpened = false;
                m_searchBuffer.clear();
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            if (selectedIndex && typeNames[*selectedIndex] != detailedType) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                pTypeInfo->category = typeInfo.category;
                pTypeInfo->detailedType = typeNames[*selectedIndex];
                uint8_t nextInfosCount = SR_UTILS_NS::Reflection::GetReflectedTypeNextCount(typeInfo.category, pTypeInfo->detailedType);
                for (uint8_t i = 0; i < nextInfosCount; ++i) {
                    pTypeInfo->pNext[i] = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                }
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                SR_IMMEDIATE_GUI_NS::PopID();
                return pTypeInfo;
            }
        }

        /// select detailed size
        if (!detailedSizes.empty()) {
            auto&& size = typeInfo.detailedSize;
            auto pSizeIt = std::find(detailedSizes.begin(), detailedSizes.end(), size);

            std::optional<uint64_t> selectedIndex = pSizeIt != detailedSizes.end() ? std::make_optional(detailedSizes.distance(pSizeIt)) : std::nullopt;
            const char* pPrevValue = selectedIndex.has_value() ? detailedSizesStr[selectedIndex.value()].c_str() : m_default.c_str();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth + context.fieldTitleWidth);

            bool& comboSizeOpened = m_comboSizeOpenedStack.at(index - 1);
            if (SR_GRAPH_GUI_NS::Immediate::BeginCombo("Size##SizeCombo", pPrevValue, SR_GRAPH_GUI_NS::Immediate::ComboFlags::NoArrowButton)) {
                if (!comboSizeOpened) {
                    SR_GRAPH_GUI_NS::Immediate::SetKeyboardFocusHere();
                    comboSizeOpened = true;
                }

                if (SR_GRAPH_GUI_NS::Immediate::InputText("##SizeSearch", &m_searchBuffer)) {
                    SR_NOOP;
                }

                for (uint64_t i = 0; i < detailedSizes.size(); ++i) {
                    if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, detailedSizesStr[i])) {
                        continue;
                    }

                    bool isSelected = (selectedIndex == i);
                    if (SR_GRAPH_GUI_NS::Immediate::Selectable(detailedSizesStr[i].c_str(), isSelected)) {
                        selectedIndex = i;
                        m_searchBuffer = detailedSizesStr[i];
                        SR_GRAPH_GUI_NS::Immediate::CloseCurrentPopup();
                    }

                    if (isSelected) {
                        SR_GRAPH_GUI_NS::Immediate::SetItemDefaultFocus();
                    }
                }
                SR_GRAPH_GUI_NS::Immediate::EndCombo();
            }
            else {
                comboSizeOpened = false;
                m_searchBuffer.clear();
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            if (selectedIndex && detailedSizes[*selectedIndex] != size) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                pTypeInfo->category = typeInfo.category;
                pTypeInfo->detailedType = typeInfo.detailedType;
                pTypeInfo->detailedSize = detailedSizes[*selectedIndex];
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                SR_IMMEDIATE_GUI_NS::PopID();
                return pTypeInfo;
            }
        }

        uint8_t nextInfosCount = SR_UTILS_NS::Reflection::GetReflectedTypeNextCount(typeInfo.category, typeInfo.detailedType);
        for (uint8_t i = 0; i < nextInfosCount; i++) {
            if (!typeInfo.pNext[i]) {
                continue;
            }
            if (auto&& pNext = DrawTypeInfo(index, *typeInfo.pNext[i], context)) {
                auto&& pTypeInfo = SR_UTILS_NS::Reflection::AllocateTypeInfo();
                *pTypeInfo = typeInfo;
                pTypeInfo->vtable = {};
                for (uint8_t j = 0; j < nextInfosCount; j++) {
                    if (j != i) {
                        pTypeInfo->pNext[j] = SR_UTILS_NS::Reflection::CopyTypeInfo(typeInfo.pNext[j]);
                    }
                    else {
                        pTypeInfo->pNext[j] = pNext;
                    }
                }
                SR_UTILS_NS::Reflection::FindVTable(*pTypeInfo);
                SR_IMMEDIATE_GUI_NS::PopID();
                return pTypeInfo;
            }
        }

        SR_IMMEDIATE_GUI_NS::PopID();
        return nullptr;
    }
}
