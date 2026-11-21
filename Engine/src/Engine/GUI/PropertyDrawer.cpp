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
#include <Utils/Types/FlatHashMap.h>

#include <Codegen/PropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    SR_HTYPES_NS::FlatHashMap<const SR_UTILS_NS::Reflection::TypeInfo*, SR_UTILS_NS::StringAtom>& GetTypePropertyDrawers() {
        static SR_HTYPES_NS::FlatHashMap<const SR_UTILS_NS::Reflection::TypeInfo*, SR_UTILS_NS::StringAtom> drawers = []() {
            SR_HTYPES_NS::FlatHashMap<const SR_UTILS_NS::Reflection::TypeInfo*, SR_UTILS_NS::StringAtom> result;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::Quaternion>()] = "QuaternionPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::FColor>()] = "FColorPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::AABB>()] = "AABBPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::FRect>()] = "RectPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::IRect>()] = "RectPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::URect>()] = "RectPropertyDrawer"_atom;
            result[SR_UTILS_NS::Reflection::TypeOf<SR_MATH_NS::USRect>()] = "RectPropertyDrawer"_atom;
            return result;
        }();
        return drawers;
    }

    void RegisterTypePropertyDrawer(const SR_UTILS_NS::Reflection::TypeInfo* pType, SR_UTILS_NS::StringAtom drawer) {
        GetTypePropertyDrawers()[pType] = drawer;
    }

    SR_UTILS_NS::Reflection::Value PropertyDrawerContext::GetValue() const {
        if (pValue) {
            return pValue->Ref();
        }
        return pProperty->Get(pOwner);
    }

    SR_UTILS_NS::StringAtom GetValueInspectorInternal(const SR_UTILS_NS::Reflection::Value& value) {
        SR_TRACY_ZONE;

        auto&& typeInfo = value.GetTypeInfo();
        auto&& drawers = GetTypePropertyDrawers();
        if (auto&& pDrawer = drawers.find(&typeInfo); pDrawer != drawers.end()) {
            return pDrawer->second;
        }
        if (typeInfo.fieldsCount > 0 || typeInfo.vtable.pFieldCount) {
            return "StructPropertyDrawer"_atom;
        }
        if (typeInfo.vtable.pEnumCount && typeInfo.vtable.pEnumValue) {
            return "EnumPropertyDrawer"_atom;
        }
        if (typeInfo.IsArithmetic()) {
            return typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::Bool ? "BoolPropertyDrawer"_atom : "NumericPropertyDrawer"_atom;
        }
        if (typeInfo.IsString()) {
            return typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::Path ? "PathPropertyDrawer"_atom : "StringPropertyDrawer"_atom;
        }

        switch (typeInfo.kind) {
            case SR_UTILS_NS::Reflection::TypeKind::Value: return "ValuePropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::Object: return "ObjectPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::NativeHandle: return "ObjectPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::Enum: return "EnumPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::Optional: return "OptionalPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::SharedPtr: return "PointerPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::EntityRef: return "EntityRefPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::ResourceRef: return "ResourceRefPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::Vector:
                if (typeInfo.pNext[0] && typeInfo.pNext[0]->kind == SR_UTILS_NS::Reflection::TypeKind::Bool) {
                    return "BitMapPropertyDrawer"_atom;
                }
                return "VectorPropertyDrawer"_atom;
            case SR_UTILS_NS::Reflection::TypeKind::Map:
            case SR_UTILS_NS::Reflection::TypeKind::FlatHashMap:
            case SR_UTILS_NS::Reflection::TypeKind::Set:
            case SR_UTILS_NS::Reflection::TypeKind::FlatHashSet:
                return "AssociativePropertyDrawer"_atom;
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
        if (typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::SharedPtr || typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::NativeHandle ||
            typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptHandle || typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptObject ||
            typeInfo.kind == SR_UTILS_NS::Reflection::TypeKind::ScriptEnum) {
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
            context.pValue->AsRef().Assign(value.AsRef());
        }
    }

    SR_UTILS_NS::Optional<uint64_t> PropertyDrawerBase::SearchComboBox(const PropertyDrawerContext& context, const SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& types, bool& comboOpened,
                                            SR_UTILS_NS::Optional<SR_UTILS_NS::StringAtom> activeType, SR_UTILS_NS::StringView defaultValue
    ) {
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>::const_iterator pTypeIt = types.end();

        if (activeType) {
            pTypeIt = std::find(types.begin(), types.end(), activeType);
        }

        SR_UTILS_NS::Optional<uint64_t> selectedIndex;
        if (pTypeIt != types.end()) {
            selectedIndex = static_cast<uint64_t>(std::distance(types.begin(), pTypeIt));
        }
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

                bool isSelected = selectedIndex && *selectedIndex == i;
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

        if (!SR_UTILS_NS::Reflection::IsTypeKindArithmetic(value.GetTypeInfo().kind)) {
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
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown data type! Value type: %s", value.GetTypeInfo().name.c_str());
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

        if (value.GetTypeInfo().kind != SR_UTILS_NS::Reflection::TypeKind::AABB) {
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

    PropertyDrawerFeedback StructPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        SR_TRACY_ZONE;
        const auto kind = context.GetValue().GetTypeInfo().kind;
        if (kind == SR_UTILS_NS::Reflection::TypeKind::MathVector || kind == SR_UTILS_NS::Reflection::TypeKind::MathSize) {
            return DrawMath(context);
        }
        PropertyDrawerFeedback feedback;
        auto value = context.GetValue();
        auto&& info = value.GetTypeInfo();
        const auto fieldCount = value.AsRef().FieldCount();
        if (m_pType != &info || m_drawers.size() != fieldCount) {
            m_drawers.clear();
            m_drawers.resize(fieldCount);
            m_drawerTypes.clear();
            m_drawerTypes.resize(fieldCount);
            m_pType = &info;
        }

        const SR_UTILS_NS::StringAtom displayName = context.pValue ? context.customDisplayName : context.GetPropertyDisplayName();
        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(displayName.c_str());
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());
        if (info.vtable.pFieldCount) {
            if (!m_openedByDefault) {
                m_isOpened |= context.openedByDefault;
                m_openedByDefault = true;
            }
            const bool nullable = info.vtable.pIsNull && info.vtable.pCreate;
            const bool isNull = nullable && info.vtable.pIsNull(info, value.Data());
            if (!context.noHeader || nullable) {
                const float_t totalWidth = context.fieldTitleWidth + context.fieldWidth;
                const float_t titleWidth = context.noHeader ? 0.f :
                    SR_MIN(context.fieldTitleWidth > 0.f ? context.fieldTitleWidth : 30.f, totalWidth);
                float_t valueWidth = SR_MAX(totalWidth - titleWidth, 1.f);
                if (!context.noHeader) {
                    auto&& pWindow = SR_IMMEDIATE_GUI_NS::GetCurrentWindow();
                    auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList(pWindow);
                    const auto arrowPos = SR_IMMEDIATE_GUI_NS::GetWindowCursorPos(pWindow) + SR_MATH_NS::FVector2(1.f, 5.f);
                    const auto direction = m_isOpened ? SR_IMMEDIATE_GUI_NS::Direction::Down : SR_IMMEDIATE_GUI_NS::Direction::Right;
                    SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), direction, 1.f);
                    const auto enabledState = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
                    if (SR_IMMEDIATE_GUI_NS::Button(context.fieldTitleWidth > 0.f && !displayName.empty() ? displayName.c_str() : "##Expand",
                        { titleWidth, context.fieldHeight })) {
                        m_isOpened = !m_isOpened;
                    }
                    SR_IMMEDIATE_GUI_NS::EndForceEnabled(enabledState);
                    DrawTitleContextMenu(context, feedback);
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
                const float_t actionWidth = nullable ? SR_MIN(SR_IMMEDIATE_GUI_NS::CalcTextSize("Create").x + context.spaceWidth * 2.f, valueWidth * 0.4f) : 0.f;
                const auto typeName = info.vtable.displayName.empty() ? info.name : info.vtable.displayName;
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
                SR_IMMEDIATE_GUI_NS::Button(isNull ? "null" : typeName.c_str(), { SR_MAX(valueWidth - actionWidth, 1.f), context.fieldHeight });
                SR_IMMEDIATE_GUI_NS::EndDisabled();
                if (nullable) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                    SR_IMMEDIATE_GUI_NS::BeginDisabled(value.IsConst());
                    if (SR_IMMEDIATE_GUI_NS::Button(isNull ? "Create" : "Reset", { actionWidth, context.fieldHeight })) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        if (isNull) {
                            info.vtable.pCreate(info, value.Data());
                            m_isOpened = true;
                        }
                        else {
                            info.DestructAt(value.Data());
                            info.ConstructAt(value.Data());
                        }
                        SetReflectedValue(context, feedback, value);
                    }
                    SR_IMMEDIATE_GUI_NS::EndDisabled();
                }
            }
            if ((!m_isOpened && !context.noHeader) || (info.vtable.pIsNull && info.vtable.pIsNull(info, value.Data()))) {
                SR_IMMEDIATE_GUI_NS::PopStyleVar();
                SR_IMMEDIATE_GUI_NS::PopID();
                SR_IMMEDIATE_GUI_NS::PopID();
                return feedback;
            }
        }
        SR_UTILS_NS::Reflection::Value reset;
        if (context.pProperty && !context.pValue) {
            reset = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
        }
        if (!info.vtable.pFieldCount && !context.noHeader && !displayName.empty()) {
            if (SR_IMMEDIATE_GUI_NS::Button(displayName.c_str(),
                { context.fieldTitleWidth + context.fieldWidth, context.fieldHeight }) && reset && !value.IsConst()) {
                value = reset.Copy();
                SetReflectedValue(context, feedback, value);
            }
            DrawTitleContextMenu(context, feedback);
            value = context.GetValue();
        }

        auto copy = value.Copy();
        if (!copy) {
            SR_IMMEDIATE_GUI_NS::PopStyleVar();
            SR_IMMEDIATE_GUI_NS::PopID();
            SR_IMMEDIATE_GUI_NS::PopID();
            return feedback;
        }
        SR_IMMEDIATE_GUI_NS::BeginDisabled(value.IsConst());
        for (uint32_t i = 0; i < fieldCount; ++i) {
            auto child = copy.AsRef().Field(i).ToValue();
            if (!child) {
                continue;
            }
            const auto fieldName = copy.AsRef().FieldName(i);
            auto&& fieldType = child.GetTypeInfo();
            if (m_drawerTypes[i] != &fieldType) {
                m_drawers[i] = {};
                m_drawerTypes[i] = &fieldType;
            }
            if (!m_drawers[i]) {
                const auto inspector = GetValueInspector(child);
                if (!inspector.empty()) {
                    m_drawers[i] = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                }
            }
            if (!m_drawers[i]) {
                continue;
            }

            SR_IMMEDIATE_GUI_NS::PushID(i);
            auto childContext = context;
            childContext.pValue = &child;
            childContext.pProperty = nullptr;
            childContext.customDisplayName = fieldName;
            childContext.editorPropertyParams = context.GetEditorParams();
            childContext.pUID = m_drawers[i].Get();
            childContext.propertyPath.emplace_back(fieldName);
            childContext.noHeader = false;
            const bool isNestedStruct = m_drawers[i]->GetMeta()->GetFactoryName() == "StructPropertyDrawer"_atom &&
                fieldType.kind != SR_UTILS_NS::Reflection::TypeKind::MathVector &&
                fieldType.kind != SR_UTILS_NS::Reflection::TypeKind::MathSize;
            const float_t totalWidth = context.fieldTitleWidth + context.fieldWidth;
            const float_t titleWidth = SR_MIN(context.fieldTitleWidth > 0.f ? context.fieldTitleWidth : totalWidth * 0.3f, totalWidth * 0.4f);
            if (isNestedStruct) {
                const float_t indent = SR_MIN(context.GetArrowWidth(), totalWidth * 0.1f);
                SR_IMMEDIATE_GUI_NS::Dummy({ indent, context.fieldHeight });
                SR_IMMEDIATE_GUI_NS::SameLine();
                childContext.fieldTitleWidth = titleWidth;
                childContext.fieldWidth = SR_MAX(totalWidth - indent - titleWidth, 1.f);
            }
            else {
                if (SR_IMMEDIATE_GUI_NS::Button(fieldName.c_str(), { titleWidth, context.fieldHeight })) {
                    auto resetChild = reset && &reset.GetTypeInfo() == &info ?
                        reset.AsRef().Field(i).ToValue() : SR_UTILS_NS::Reflection::Value::CreateDefault(&fieldType);
                    if (resetChild && child.AsRef().Assign(resetChild.AsRef())) {
                        SetReflectedValue(context, feedback, copy);
                    }
                }
                SR_IMMEDIATE_GUI_NS::SameLine();
                childContext.fieldTitleWidth = 0.f;
                childContext.fieldWidth = SR_MAX(totalWidth - titleWidth, 1.f);
                childContext.customDisplayName = SR_UTILS_NS::StringAtom();
                childContext.noHeader = true;
                if (fieldType.IsContainer() || fieldType.kind == SR_UTILS_NS::Reflection::TypeKind::Object ||
                    fieldType.kind == SR_UTILS_NS::Reflection::TypeKind::Value) {
                    childContext.fieldTitleWidth = childContext.fieldWidth * 0.3f;
                    childContext.fieldWidth -= childContext.fieldTitleWidth;
                }
            }
            bool childDrag = false;
            bool notified = false;
            childContext.onBeforeChangeCallback = [&childDrag, &notified, &info, &context](bool drag) {
                childDrag |= drag;
                if (info.vtable.pFieldCount && !notified && context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(drag);
                    notified = true;
                }
            };
            SR_IMMEDIATE_GUI_NS::BeginGroup();
            const auto childFeedback = m_drawers[i]->Draw(childContext);
            SR_IMMEDIATE_GUI_NS::EndGroup();
            if (childFeedback.isChanged) {
                childDrag |= childFeedback.isDrag;
                feedback.isDrag |= childDrag;
                auto writeContext = context;
                if (notified) {
                    writeContext.onBeforeChangeCallback = {};
                }
                SetReflectedValue(writeContext, feedback, copy, childDrag);
            }
            SR_IMMEDIATE_GUI_NS::PopID();
        }
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        SR_IMMEDIATE_GUI_NS::PopStyleVar();
        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();
        return feedback;
    }

    PropertyDrawerFeedback StructPropertyDrawer::DrawMath(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;
        auto value = context.GetValue();
        auto copy = value.Copy();
        auto&& info = value.GetTypeInfo();
        const bool isSize = info.kind == SR_UTILS_NS::Reflection::TypeKind::MathSize;
        const uint32_t dimension = isSize ? info.detailedSize : info.fieldsCount;
        const float_t fieldWidth = SR_MAX(context.fieldWidth, 1.f);
        const uint32_t availableParts = SR_MAX(static_cast<uint32_t>(fieldWidth / (context.axisButtonWidth + 2.f * SR_IMMEDIATE_GUI_NS::GetFrameHeight())), 1u);
        const uint32_t partsInLine = SR_MIN(SR_MAX(context.maxPartsInLine, 1u), availableParts);
        const float_t partWidth = fieldWidth / static_cast<float_t>(partsInLine);
        const float_t axisWidth = SR_MIN(context.axisButtonWidth, partWidth * 0.4f);
        const SR_MATH_NS::FVector2 buttonSize(axisWidth, context.fieldHeight);
        static const SR_MATH_NS::FColor colors[] = {
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.f),
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.f),
            SR_MATH_NS::FColor(0.1f, 0.25f, 0.8f, 1.f)
        };
        const char* pLabels[] = { "X", "Y", "Z", "W", "V", "U" };
        SR_UTILS_NS::Reflection::Value reset;
        if (context.pProperty) {
            reset = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
        }

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyDisplayName().c_str());
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());
        SR_IMMEDIATE_GUI_NS::BeginDisabled(value.IsConst());
        if (!context.pValue) {
            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(),
                { context.fieldTitleWidth, context.fieldHeight * (isSize ? 2.f : 1.f) }) && reset) {
                copy = reset.Copy();
                feedback.isChanged = true;
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        SR_IMMEDIATE_GUI_NS::BeginGroup();
        for (uint32_t i = 0; i < dimension; ++i) {
            auto&& field = info.pFields[isSize && dimension == 1 ? 0 : i];
            auto&& component = isSize && dimension > 1 ? field.pType->pFields[0] : field;
            const uint32_t offset = isSize && dimension > 1 ? field.offset + component.offset : field.offset;
            auto&& pData = static_cast<uint8_t*>(copy.Data()) + offset;
            auto&& pType = component.pType;
            const auto dataType = SR_IMMEDIATE_GUI_NS::GetDataType(pType->GetScalarSize(), pType->IsSigned(), pType->IsIntegral());

            SR_IMMEDIATE_GUI_NS::PushID(i);
            const auto color = colors[i % 3];
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Button, color);
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonHovered, color + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.f));
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::ButtonActive, color + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.f));
            if (SR_IMMEDIATE_GUI_NS::Button(pLabels[i], buttonSize)) {
                if (reset && &reset.GetTypeInfo() == &info) {
                    pType->CopyAssign(pData, static_cast<const uint8_t*>(reset.Data()) + offset);
                }
                else {
                    auto zero = SR_UTILS_NS::Reflection::Value::CreateDefault(pType);
                    pType->CopyAssign(pData, zero.Data());
                }
                feedback.isChanged = true;
            }
            SR_IMMEDIATE_GUI_NS::PopStyleColor(3);
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::PushItemWidth(partWidth - axisWidth);
            if (pType->kind == SR_UTILS_NS::Reflection::TypeKind::Bool) {
                if (SR_IMMEDIATE_GUI_NS::Checkbox("##Value", static_cast<bool*>(static_cast<void*>(pData)))) {
                    feedback.isChanged = true;
                }
                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::Dummy({ SR_MAX(partWidth - axisWidth - SR_IMMEDIATE_GUI_NS::GetFrameHeight(), 0.f), 0.f });
            }
            else if (SR_IMMEDIATE_GUI_NS::DragScalar("##Value", dataType, pData, context.GetEditorParams().GetDragSpeed())) {
                feedback.isChanged = true;
                feedback.isDrag = true;
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
            SR_IMMEDIATE_GUI_NS::PopID();
            if (i + 1 < dimension && (i + 1) % partsInLine != 0) {
                SR_IMMEDIATE_GUI_NS::SameLine();
            }
        }

        if (isSize) {
            for (uint32_t i = 0; i < dimension; ++i) {
                auto&& field = info.pFields[dimension == 1 ? 1 : i];
                auto&& metricField = dimension == 1 ? field : field.pType->pFields[1];
                const uint32_t offset = dimension == 1 ? metricField.offset : field.offset + metricField.offset;
                auto&& pMetric = reinterpret_cast<SR_MATH_NS::SizeMetric*>(static_cast<uint8_t*>(copy.Data()) + offset);
                SR_IMMEDIATE_GUI_NS::PushID(i);
                SR_IMMEDIATE_GUI_NS::PushItemWidth(partWidth);
                if (SR_IMMEDIATE_GUI_NS::BeginCombo("##Metric", SR_UTILS_NS::EnumReflector::ToStringAtom(*pMetric).c_str())) {
                    for (auto&& name : SR_UTILS_NS::EnumReflector::GetNames<SR_MATH_NS::SizeMetric>()) {
                        if (SR_IMMEDIATE_GUI_NS::Selectable(name.c_str())) {
                            *pMetric = SR_UTILS_NS::EnumReflector::FromString<SR_MATH_NS::SizeMetric>(name);
                            feedback.isChanged = true;
                        }
                    }
                    SR_IMMEDIATE_GUI_NS::EndCombo();
                }
                SR_IMMEDIATE_GUI_NS::PopItemWidth();
                SR_IMMEDIATE_GUI_NS::PopID();
                if (i + 1 < dimension && (i + 1) % partsInLine != 0) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
            }
        }
        SR_IMMEDIATE_GUI_NS::EndGroup();
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        SR_IMMEDIATE_GUI_NS::PopStyleVar();
        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();
        if (feedback.isChanged) {
            SetReflectedValue(context, feedback, copy, feedback.isDrag);
        }
        return feedback;
    }

    PropertyDrawerFeedback QuaternionPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;
        auto value = context.GetValue();
        auto angles = value.Cast<SR_MATH_NS::Quaternion>()->EulerAngle();
        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());
        SR_IMMEDIATE_GUI_NS::BeginDisabled(value.IsConst());
        if (!context.pValue) {
            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), { context.fieldTitleWidth, context.fieldHeight })) {
                auto reset = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                if (reset) {
                    SetReflectedValue(context, feedback, reset);
                    angles = reset.Cast<SR_MATH_NS::Quaternion>()->EulerAngle();
                }
            }
            DrawTitleContextMenu(context, feedback);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }
        if (!m_anglesDrawer) {
            m_anglesDrawer = SRNew<StructPropertyDrawer>();
        }
        auto anglesValue = SR_UTILS_NS::Reflection::Value::CreateRef(angles);
        auto anglesContext = context;
        anglesContext.pValue = &anglesValue;
        anglesContext.onBeforeChangeCallback = nullptr;
        const auto anglesFeedback = m_anglesDrawer->Draw(anglesContext);
        if (anglesFeedback.isChanged) {
            auto rotation = SR_UTILS_NS::Reflection::Value::Create(SR_MATH_NS::Quaternion::FromEuler(angles));
            SetReflectedValue(context, feedback, rotation, anglesFeedback.isDrag);
            feedback.isDrag = anglesFeedback.isDrag;
        }
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        SR_IMMEDIATE_GUI_NS::PopStyleVar();
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

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);
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

        SR_IMMEDIATE_GUI_NS::PopItemWidth();
        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }

}
