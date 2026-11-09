//
// Created by Monika on 09.11.2023.
//

#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/EntityRefPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ResourceRefPropertyDrawer.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/EditorGizmo.h>
#include <Engine/GUI/SceneViewer.h>

#include <Graphics/Material/UniqueMaterial.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Render/RenderContext.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Utils/Common/LexicalCast.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/PropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    SR_UTILS_NS::Reflection::Value PropertyDrawerContext::GetValue() const {
        if (pValue) {
            return pValue->Ref();
        }
        return pProperty->Get(pOwner);
    }

    SR_UTILS_NS::StringAtom GetValueInspectorInternal(const SR_UTILS_NS::Reflection::Value& value) {
        SR_TRACY_ZONE;

        auto&& typeInfo = value.GetTypeInfo();
        switch (typeInfo.category) {
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Value:
                return "ValuePropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Object:
                return "ObjectPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::String:
                if (typeInfo.detailedType == "Path") {
                    return "PathPropertyDrawer"_atom;
                }
                return "StringPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic:
                if (typeInfo.detailedType == "bool") {
                    return "BoolPropertyDrawer"_atom;
                }
                return "NumericPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Enum:
                return "EnumPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathObject:
                if (typeInfo.detailedType == "Quaternion") {
                    return "MathVectorPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "Color") {
                    return "FColorPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "AABB") {
                    return "AABBPropertyDrawer"_atom;
                }
                return SR_UTILS_NS::StringAtom();
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathSize:
                return "MathSizePropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathVector:
                return "MathVectorPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::MathRect:
                return "RectPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::ReflectedCategoryType::Container:
                if (typeInfo.detailedType == "Optional") {
                    return "OptionalPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "SharedPtr") {
                    return "PointerPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "Pair") {
                    return "PairPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "EntityRef") {
                    return "EntityRefPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "ResourceRef") {
                    return "ResourceRefPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "Vector") {
                    if (typeInfo.pNext[0] && typeInfo.pNext[0]->detailedType == "bool") {
                        return "BitMapPropertyDrawer"_atom;
                    }
                    return "VectorPropertyDrawer"_atom;
                }
                if (typeInfo.detailedType == "FlatHashMap" || typeInfo.detailedType == "FlatHashSet" || typeInfo.detailedType == "Map" || typeInfo.detailedType == "Set") {
                    return "AssociativePropertyDrawer"_atom;
                }
                return SR_UTILS_NS::StringAtom();
            default:
                return SR_UTILS_NS::StringAtom();
        }
    }

    SR_UTILS_NS::StringAtom GetValueInspector(const SR_UTILS_NS::Reflection::Value& value) {
        SR_TRACY_ZONE;
        SR_UTILS_NS::StringAtom inspector = GetValueInspectorInternal(value);
        if (inspector == ObjectPropertyDrawer::GetClassStaticName()) {
            /// возможно, это не безопасно, и может привести к UB
            if (SR_UTILS_NS::SRClass* pValueClass = value.GetSRClass()) {
                inspector = pValueClass->GetMeta()->GetInspectorName();
            }
        }
        return inspector;
    }

    const SR_GRAPH_NS::RenderContext::Ptr& PropertyDrawerBase::GetRenderContext() const {
        if (m_context) {
            return m_context;
        }
        m_context = (SR_GRAPH_NS::RenderContext*)SR_UTILS_NS::StoreUtils::Temp::GetPointer("RenderContext");
        SRAssert2(m_context, "Failed to get render context!");
        return m_context;
    }

    void PropertyDrawerBase::SetValue(const PropertyDrawerContext& context, const PropertyDrawerFeedback& feedback, const SR_UTILS_NS::Reflection::Value& value) {
        if (!context.pValue && feedback.isChanged && (!value.IsRef() || context.HasExplicitSetter())) {
            context.GetProperty().Set(context.pOwner, value);
        }
    }

    static bool IsClipboardSupported(const SR_UTILS_NS::Reflection::TypeInfo& typeInfo) {
        if (typeInfo.category == SR_UTILS_NS::Reflection::ReflectedCategoryType::Container && typeInfo.detailedType == "SharedPtr") {
            return false;
        }
        for (auto&& pNext : typeInfo.pNext) {
            if (pNext && !IsClipboardSupported(*pNext)) {
                return false;
            }
        }
        return true;
    }

    void PropertyDrawerBase::DrawTitleContextMenu(const PropertyDrawerContext& context, PropertyDrawerFeedback& feedback) {
        if (context.pValue || !context.pProperty || !context.pOwner || !context.pEditor) {
            return;
        }

        if (!SR_IMMEDIATE_GUI_NS::BeginPopupContextItem("PropertyTitleContextMenu")) {
            return;
        }

        const bool isOverridden = context.isPropertyOverriddenCallback &&
            context.isPropertyOverriddenCallback(context.pOwner, *context.pProperty, context.propertyPath);
        if (isOverridden && context.revertPropertyCallback && SR_IMMEDIATE_GUI_NS::MenuItem("Revert prefab override")) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            context.revertPropertyCallback(context.pOwner, *context.pProperty, context.propertyPath);
            feedback.isOverrideReverted = true;
        }

        CustomTitleContextMenu(context, feedback);

        const SR_UTILS_NS::Reflection::Value value = context.GetValue();
        const bool isSupported = value.IsValid() && IsClipboardSupported(value.GetTypeInfo());

        SR_UTILS_NS::Reflection::Value& clipboard = context.pEditor->GetPropertyClipboard();

        const bool canPaste = isSupported && clipboard.IsValid()
            && clipboard.GetTypeInfo() == value.GetTypeInfo()
            && !context.GetProperty().IsReadOnly();

        bool isCopyClicked = false;
        bool isPasteClicked = false;
        {
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(!isSupported);
            isCopyClicked = SR_IMMEDIATE_GUI_NS::MenuItem("Copy");
        }
        {
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(!canPaste);
            isPasteClicked = SR_IMMEDIATE_GUI_NS::MenuItem("Paste");
        }

        if (isCopyClicked && isSupported) {
            clipboard = value.Copy();
        }

        if (isPasteClicked && canPaste) {
            SetReflectedValue(context, feedback, clipboard.Copy());
        }

        SR_IMMEDIATE_GUI_NS::EndPopup();
    }

    void PropertyDrawerBase::SetReflectedValue(const PropertyDrawerContext& context, PropertyDrawerFeedback& feedback, const SR_UTILS_NS::Reflection::Value& value, bool drag) {
        if (context.onBeforeChangeCallback) {
            context.onBeforeChangeCallback(drag);
        }

        feedback.isChanged = true;

        if (!context.pValue) {
            context.GetProperty().Set(context.pOwner, value);
        }
        else {
            SRAssert2(value.SizeOf() == context.pValue->SizeOf(), "PropertyDrawerBase::SetReflectedValue() : size mismatch!");
            std::memcpy(context.pValue->Data(), value.Data(), value.SizeOf());
        }
    }

    std::optional<uint64_t> PropertyDrawerBase::SearchComboBox(const PropertyDrawerContext& context, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& types, bool& comboOpened,
                                            std::optional<SR_UTILS_NS::StringAtom> activeType, SR_UTILS_NS::StringView defaultValue
    ) {
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>::const_iterator pTypeIt = types.end();

        if (activeType) {
            pTypeIt = std::find(types.begin(), types.end(), activeType);
        }

        std::optional<uint64_t> selectedIndex = pTypeIt != types.end() ? std::make_optional(std::distance(types.begin(), pTypeIt)) : std::nullopt;
        const char* pPrevValue = selectedIndex.has_value() ? types[selectedIndex.value()].data() : defaultValue.c_str();

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

        if (types.size() < 1) {
            SR_IMMEDIATE_GUI_NS::BeginDisabled();
        }

        if (SR_IMMEDIATE_GUI_NS::BeginCombo("##Combo", pPrevValue, SR_IMMEDIATE_GUI_NS::ComboFlags::NoArrowButton)) {
            if (!comboOpened) {
                SR_IMMEDIATE_GUI_NS::SetKeyboardFocusHere();
                comboOpened = true;
            }

            if (SR_IMMEDIATE_GUI_NS::InputText("##Search", &m_searchBuffer)) {
                SR_NOOP;
            }

            for (uint64_t i = 0; i < types.size(); ++i) {
                if (!m_searchBuffer.empty() && !SR_UTILS_NS::StringUtils::CheckSearchMatch(m_searchBuffer, types[i])) {
                    continue;
                }

                bool isSelected = (selectedIndex == i);
                if (SR_IMMEDIATE_GUI_NS::Selectable(types[i].data(), isSelected))
                {
                    selectedIndex = i;
                    m_searchBuffer = types[i];
                    SR_IMMEDIATE_GUI_NS::CloseCurrentPopup();
                }

                if (isSelected) {
                    SR_IMMEDIATE_GUI_NS::SetItemDefaultFocus();
                }
            }
            SR_IMMEDIATE_GUI_NS::EndCombo();
        }
        else {
            comboOpened = false;
            m_searchBuffer.clear();
        }

        if (types.size() < 1) {
            SR_IMMEDIATE_GUI_NS::EndDisabled();
        }

        return selectedIndex;
    }

    PropertyDrawerFeedback BoolPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
            }
            DrawTitleContextMenu(context, feedback);

            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        if (auto&& bValue = value.Cast<bool>()) {
            bool isChecked = *bValue;
            if (SR_IMMEDIATE_GUI_NS::Checkbox("##Checkbox", &isChecked)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                *bValue = isChecked;
                feedback.isChanged = true;
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map bool value!");
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    OptionalPropertyDrawer::~OptionalPropertyDrawer() = default;

    PropertyDrawerFeedback OptionalPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
            }
            DrawTitleContextMenu(context, feedback);

            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        auto&& pOptionalBase = value.GetOptionalBase();
        if (pOptionalBase) {
            if (!m_valueDrawer) {
                SR_UTILS_NS::Reflection::Value optionalValue = pOptionalBase->GetReflectionValue();
                SR_UTILS_NS::StringAtom inspector = GetValueInspector(optionalValue);
                m_valueDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
            }

            if (m_valueDrawer) {
                bool hasValue = pOptionalBase->HasValue();
                if (SR_IMMEDIATE_GUI_NS::Checkbox("##Checkbox", &hasValue)) {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    if (!hasValue) {
                        pOptionalBase->Reset();
                    }
                    else {
                        pOptionalBase->SetValue(pOptionalBase->GetReflectionValue());
                    }
                    feedback.isChanged = true;
                }

                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::PushID("Value");

                SR_UTILS_NS::Reflection::Value optionalValue = pOptionalBase->GetReflectionValue();

                SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard lock(!hasValue);
                PropertyDrawerContext valueContext = context;
                valueContext.pValue = &optionalValue;
                valueContext.fieldWidth = context.fieldWidth - SR_IMMEDIATE_GUI_NS::GetFrameHeight();
                valueContext.fieldTitleWidth = 0.f;
                valueContext.noHeader = true;
                valueContext.openedByDefault = false;

                SR_IMMEDIATE_GUI_NS::BeginGroup();
                PropertyDrawerFeedback elementFeedback = m_valueDrawer->Draw(valueContext);
                SR_IMMEDIATE_GUI_NS::EndGroup();

                if (elementFeedback.isChanged) {
                    feedback.isChanged = true;
                    pOptionalBase->SetValue(optionalValue);
                }

                SR_IMMEDIATE_GUI_NS::PopID();
            }
            else {
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unsupported optional type!");
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map optional value!");
        }

        //const float checkBoxSize = SR_IMMEDIATE_GUI_NS::GetFrameHeight();

        /*if (auto&& pValue = value.TryCast<std::optional<float>>()) {
            bool hasValue = pValue->has_value();
            if (SR_IMMEDIATE_GUI_NS::Checkbox("##Checkbox", &hasValue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                if (hasValue) {
                    *pValue = float();
                }
                else {
                    pValue->reset();
                }
                feedback.isChanged = true;
            }

            float dataValue = pValue->value_or(0.f);
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard lock(!hasValue);
            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth - checkBoxSize);

            if (SR_IMMEDIATE_GUI_NS::DragFloat("##Value", &dataValue, context.GetEditorParams().GetDragSpeed())) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                *pValue = dataValue;
                feedback.isChanged = true;
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }
        else if (auto&& pValue = value.TryCast<std::optional<bool>>()) {
            bool hasValue = pValue->has_value();
            if (SR_IMMEDIATE_GUI_NS::Checkbox("##Checkbox", &hasValue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                if (hasValue) {
                    *pValue = false;
                }
                else {
                    pValue->reset();
                }
                feedback.isChanged = true;
            }

            bool dataValue = pValue->value_or(false);
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard lock(!hasValue);
            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth - checkBoxSize);

            if (SR_IMMEDIATE_GUI_NS::Checkbox("Value", &dataValue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                *pValue = dataValue;
                feedback.isChanged = true;
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }
        else if (auto&& pValue = value.TryCast<std::optional<SR_UTILS_NS::StringAtom>>()) {
            bool hasValue = pValue->has_value();
            if (SR_IMMEDIATE_GUI_NS::Checkbox("##Checkbox", &hasValue)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                if (hasValue) {
                    *pValue = SR_UTILS_NS::StringAtom();
                }
                else {
                    pValue->reset();
                }
                feedback.isChanged = true;
            }

            SR_UTILS_NS::StringAtom dataValue = pValue->value_or(SR_UTILS_NS::StringAtom());
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard lock(!hasValue);
            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth - checkBoxSize);

            char buffer[256] = { 0 };
            std::strncpy(buffer, dataValue.c_str(), sizeof(buffer) - 1);
            if (SR_IMMEDIATE_GUI_NS::InputText("##Value", buffer, sizeof(buffer))) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                *pValue = SR_UTILS_NS::StringAtom(buffer);
                feedback.isChanged = true;
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unsupported optional type!");
        }*/

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    PropertyDrawerFeedback NumericPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        if (value.GetTypeInfo().category != SR_UTILS_NS::Reflection::ReflectedCategoryType::Arithmetic) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Property is not numeric!");
            return feedback;
        }

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

        if (!context.pValue) {
            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

        const float_t drag = context.GetEditorParams().GetDragSpeed();
        auto&& range = context.GetEditorParams().GetRange();
        const auto dataType = SR_IMMEDIATE_GUI_NS::GetDataType(value.SizeOf(), value.IsSigned(), value.IsIntegral());
        if (dataType == SR_IMMEDIATE_GUI_NS::ImmediateDataType::COUNT) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown data type! Value detailed type: %s", value.GetTypeInfo().detailedType.c_str());
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
            SR_IMMEDIATE_GUI_NS::PopStyleVar();
            SR_IMMEDIATE_GUI_NS::PopID();
            SR_IMMEDIATE_GUI_NS::PopID();
            return feedback;
        }

        if (void* pValue = value.Data()) {
            SR_IMMEDIATE_GUI_NS::ImmediateDataTypeUnion dataTypeUnion = SR_IMMEDIATE_GUI_NS::ReadDataType(pValue, dataType);
            SR_IMMEDIATE_GUI_NS::ImmediateDataTypeUnion minValue;
            SR_IMMEDIATE_GUI_NS::ImmediateDataTypeUnion maxValue;
            void* pMin = nullptr;
            void* pMax = nullptr;

            if (range) {
                minValue = SR_IMMEDIATE_GUI_NS::FloatToDataType(range.value().first, dataType);
                maxValue = SR_IMMEDIATE_GUI_NS::FloatToDataType(range.value().second, dataType);
                pMin = &minValue;
                pMax = &maxValue;
            }

            if (SR_IMMEDIATE_GUI_NS::DragScalar("", dataType, &dataTypeUnion, drag, pMin, pMax)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                SR_IMMEDIATE_GUI_NS::WriteDataType(pValue, dataType, dataTypeUnion);
                feedback.isChanged = true;
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map numeric value!");
        }

        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    PropertyDrawerFeedback AABBPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        if (value.GetTypeInfo().detailedType != "AABB") {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Property is not AABB!");
            return feedback;
        }

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

        if (!context.pValue && SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            feedback.isChanged = true;
            value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
            value = value.Copy();
        }
        DrawTitleContextMenu(context, feedback);

        const float_t drag = context.GetEditorParams().GetDragSpeed();

        if (auto&& pAABB = value.Cast<SR_MATH_NS::AABB>()) {
            SR_MATH_NS::FVector3 min = pAABB->Min();
            SR_MATH_NS::FVector3 max = pAABB->Max();

            const float_t labelWidth = SR_IMMEDIATE_GUI_NS::CalcTextSize("Max").x;
            SR_IMMEDIATE_GUI_NS::PushItemWidth(SR_MAX(context.fieldWidth - labelWidth, 1.f));

            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (SR_IMMEDIATE_GUI_NS::DragFloat3("Min", &min.x, drag)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                pAABB->SetMin(min);
                feedback.isChanged = true;
            }

            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (SR_IMMEDIATE_GUI_NS::DragFloat3("Max", &max.x, drag)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                pAABB->SetMax(max);
                feedback.isChanged = true;
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map AABB value!");
        }

        DrawEditBoundsButton(context);

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    void AABBPropertyDrawer::DrawEditBoundsButton(const PropertyDrawerContext& context) {
        if (context.pValue || !context.pProperty || !context.pEditor || !context.pComponent) {
            return;
        }

        if (context.pOwner != context.pComponent.Get() || context.GetProperty().IsReadOnly()) {
            return;
        }

        auto&& pViewer = context.pEditor->GetWidget<SceneViewer>();
        auto&& pGizmoObject = pViewer ? pViewer->GetGizmo() : SR_UTILS_NS::GameObject::Ptr();
        auto&& pGizmo = pGizmoObject ? pGizmoObject->GetComponent<EditorGizmo>() : SR_HTYPES_NS::SharedPtr<EditorGizmo>();
        if (!pGizmo) {
            return;
        }

        const bool isEditing = pGizmo->IsBoundsEdit(context.pComponent.Get(), context.pProperty);

        SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
        SR_IMMEDIATE_GUI_NS::SameLine();

        const SR_MATH_NS::FColor color = isEditing ? SR_MATH_NS::FColor(0.2f, 0.6f, 0.2f, 1.f) : SR_MATH_NS::FColor(0.3f, 0.3f, 0.3f, 1.f);
        if (SR_IMMEDIATE_GUI_NS::ButtonColored("Edit Bounds", color, SR_MATH_NS::FVector2(context.fieldWidth, context.fieldHeight))) {
            if (isEditing) {
                pGizmo->StopBoundsEdit();
            }
            else {
                pGizmo->BeginBoundsEdit(context.pComponent, context.pProperty);
            }
        }
    }

    PropertyDrawerFeedback MathVectorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        const bool isQuaternion = value.GetTypeInfo().detailedType == "Quaternion";
        SR_UTILS_NS::StringView vectorPartType = isQuaternion ? "float" : value.GetTypeInfo().detailedType;
        const uint8_t dimension = isQuaternion ? 4 : value.GetTypeInfo().detailedSize;

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        const float_t partItemWidth = (context.fieldWidth / static_cast<float_t>(context.maxPartsInLine)) - context.axisButtonWidth;

        const SR_MATH_NS::FVector2 buttonSize = { context.axisButtonWidth, context.fieldHeight };
        const float_t drag = context.GetEditorParams().GetDragSpeed();
        auto partType = SR_IMMEDIATE_GUI_NS::GetDataType(vectorPartType);

        constexpr std::array<const char*, 6> labels = { "X", "Y", "Z", "W", "V", "U" };
        static const std::array<SR_MATH_NS::FColor, 6> colors = {
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), /// red
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), /// green
            SR_MATH_NS::FColor(0.1f, 0.25f, 0.8f, 1.0f), /// blue
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), /// red
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), /// green
            SR_MATH_NS::FColor(0.1f, 0.25f, 0.8f, 1.0f), /// blue
            //SR_MATH_NS::FColor(0.8f, 0.8f, 0.2f, 1.0f), /// yellow
            //SR_MATH_NS::FColor(0.2f, 0.7f, 0.7f, 1.0f), /// cyan
            //SR_MATH_NS::FColor(0.7f, 0.2f, 0.7f, 1.0f) /// magenta
        };

        for (uint8_t i = 0; i < dimension; ++i) {
            SR_IMMEDIATE_GUI_NS::PushID(i);

            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, colors[i]);
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

            const uint64_t partSize = value.SizeOf() / dimension;
            const uint64_t offset = partSize * i;

            if (SR_IMMEDIATE_GUI_NS::Button(labels[i], buttonSize)) {
                SR_UTILS_NS::Reflection::Value copy = value.Copy();
                if (context.pProperty && context.GetProperty().GetResetValue().SizeOf() == value.SizeOf()) {
                    if (auto&& pResetData = (char*)context.GetProperty().GetResetValue().Data()) {
                        std::memcpy((char*)copy.Data() + offset, pResetData + offset, partSize);
                    }
                }
                if (!feedback.isChanged) {
                    std::memset((char*)copy.Data() + offset, 0, partSize);
                    feedback.isChanged = true;
                }
                SetReflectedValue(context, feedback, copy);
            }

            SR_IMMEDIATE_GUI_NS::PopStyleColor(3);

            SR_IMMEDIATE_GUI_NS::SameLine();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(partItemWidth);

            if (partSize == 1) {
                SR_IMMEDIATE_GUI_NS::PopItemWidth();
                SR_UTILS_NS::Reflection::Value copy = value.Copy();
                bool* pTemp = reinterpret_cast<bool*>(&((char*)(copy.Data()))[offset]);
                if (SR_IMMEDIATE_GUI_NS::Checkbox("", pTemp)) {
                    SetReflectedValue(context, feedback, copy, false);
                }
                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(partItemWidth - SR_IMMEDIATE_GUI_NS::GetFrameHeight(), 0.0f));
                SR_IMMEDIATE_GUI_NS::PushItemWidth(partItemWidth);
            }
            else if (partType == SR_IMMEDIATE_GUI_NS::ImmediateDataType::COUNT) {
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown part type!");
            }
            else {
                SR_UTILS_NS::Reflection::Value copy = value.Copy();
                if (SR_IMMEDIATE_GUI_NS::DragScalar("", partType, (char*)copy.Data() + offset, drag)) {
                    SetReflectedValue(context, feedback, copy, true);
                }
            }

            SR_IMMEDIATE_GUI_NS::PopItemWidth();
            SR_IMMEDIATE_GUI_NS::PopID();

            if (i + 1 < dimension) {
                if ((i + 1) % context.maxPartsInLine == 0) {
                    SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
                else {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }

    PropertyDrawerFeedback FColorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        if (SR_MATH_NS::FColor* pColor = value.Cast<SR_MATH_NS::FColor>()) {
            if (SR_IMMEDIATE_GUI_NS::ColorEditAlpha("##ColorPicker", *pColor, SR_IMMEDIATE_GUI_NS::ColorEditFlags::DefaultOptions)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                feedback.isChanged = true;
            }
        }
        else {
            SRHalt("FColorPropertyDrawer can only be used with FColor type!");
        }

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }

    PropertyDrawerFeedback MathSizePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_UTILS_NS::StringView vectorPartType = value.GetTypeInfo().detailedType;
        const uint8_t dimension = value.GetTypeInfo().detailedSize;

        const auto partType = SR_IMMEDIATE_GUI_NS::GetDataType(vectorPartType);
        if (partType == SR_IMMEDIATE_GUI_NS::ImmediateDataType::COUNT) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown part type!");
            return feedback;
        }

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetProperty().GetName().ToCStr());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight * 2.f };
            if (SR_IMMEDIATE_GUI_NS::Button(context.GetProperty().GetDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }
            DrawTitleContextMenu(context, feedback);
        }

        SRAssert(value);

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        constexpr uint32_t maxPartsInLine = 3;
        const float_t partItemWidth = (context.fieldWidth) / maxPartsInLine - context.axisButtonWidth;

        const SR_MATH_NS::FVector2 buttonSize = { context.axisButtonWidth, context.fieldHeight };
        const float_t drag = context.GetProperty().GetEditorParams().GetDragSpeed();

        constexpr std::array<const char*, 2> labels = { "X", "Y" };
        static const std::array<SR_MATH_NS::FColor, 2> colors = {
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f),
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f),
        };

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::BeginGroup();
        {
            SR_UTILS_NS::Reflection::Value copy = value.Copy();

            for (uint8_t i = 0; i < dimension; ++i) {
                SR_IMMEDIATE_GUI_NS::PushID(i);

                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, colors[i]);
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

                auto&& pFSize = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::FSize)]);
                auto&& pISize = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::ISize)]);
                auto&& pUSize = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::USize)]);

                if (SR_IMMEDIATE_GUI_NS::Button(labels[i], buttonSize)) {
                    feedback.isChanged = true;
                    if (value.SizeOf() == context.GetProperty().GetResetValue().SizeOf()) {
                        auto&& pMapped = context.GetProperty().GetResetValue().Data();
                        switch (partType) {
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float: pFSize->v = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::FSize)])->v; break;
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Int32: pISize->v = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::ISize)])->v; break;
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::UInt32: pUSize->v = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::USize)])->v; break;
                            default:
                                SRHalt("Unknown part type!");
                                break;
                        }
                    }
                    else {
                        switch (partType) {
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float:  pFSize->v = 0.f; break;
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Int32:  pISize->v = 0; break;
                            case SR_IMMEDIATE_GUI_NS::ImmediateDataType::UInt32: pUSize->v = 0; break;
                            default:
                                SRHalt("Unknown part type!");
                                break;
                        }
                    }
                }

                SR_IMMEDIATE_GUI_NS::PopStyleColor(3);
                SR_IMMEDIATE_GUI_NS::PushItemWidth(partItemWidth);

                SR_IMMEDIATE_GUI_NS::SameLine();

                switch (partType) {
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float: {
                        float_t temp = pFSize->v;
                        if (SR_IMMEDIATE_GUI_NS::DragScalar("", partType, &temp, drag)) {
                            pFSize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Int32: {
                        int32_t temp = pISize->v;
                        if (SR_IMMEDIATE_GUI_NS::DragScalar("", partType, &temp, drag)) {
                            pISize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::UInt32: {
                        uint32_t temp = pUSize->v;
                        if (SR_IMMEDIATE_GUI_NS::DragScalar("", partType, &temp, drag)) {
                            pUSize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    default:
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown part type!");
                        break;
                }

                SR_IMMEDIATE_GUI_NS::PopItemWidth();

                SR_IMMEDIATE_GUI_NS::PopID();

                if (i + 1 < dimension) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
            }

            SR_IMMEDIATE_GUI_NS::PushID("Metric");

            SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth / maxPartsInLine);

            for (uint8_t i = 0; i < dimension; ++i) {
                SR_IMMEDIATE_GUI_NS::PushID(i);

                auto&& pFSize = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::FSize)]);
                auto&& pISize = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::ISize)]);
                auto&& pUSize = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::USize)]);

                SR_MATH_NS::SizeMetric* pSize = nullptr;
                switch (partType) {
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float: pSize = &pFSize->metric; break;
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::Int32: pSize = &pISize->metric; break;
                    case SR_IMMEDIATE_GUI_NS::ImmediateDataType::UInt32: pSize = &pUSize->metric; break;
                    default:
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown part type!");
                        break;
                }

                if (pSize && SR_IMMEDIATE_GUI_NS::BeginCombo("", SR_UTILS_NS::EnumReflector::ToStringAtom(*pSize).c_str())) {
                    auto&& names = SR_UTILS_NS::EnumReflector::GetNames<SR_MATH_NS::SizeMetric>();
                    for (auto&& name : names) {
                        if (SR_IMMEDIATE_GUI_NS::Selectable(name.c_str())) {
                            SR_IMMEDIATE_GUI_NS::SetItemDefaultFocus();
                            *pSize = SR_UTILS_NS::EnumReflector::FromString<SR_MATH_NS::SizeMetric>(name);
                            feedback.isChanged = true;
                        }
                    }

                    SR_IMMEDIATE_GUI_NS::EndCombo();
                }

                SR_IMMEDIATE_GUI_NS::PopID();

                if (i + 1 < dimension) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
            SR_IMMEDIATE_GUI_NS::EndGroup();

            if (feedback.isChanged) {
                SetReflectedValue(context, feedback, copy, feedback.isDrag);
            }
        }

        SR_IMMEDIATE_GUI_NS::PopID();

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }
}
