//
// Created by Monika on 09.11.2023.
//

#include <Core/GUI/PropertyDrawer.h>
#include <Graphics/Material/UniqueMaterial.h>

#include <Codegen/PropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    bool DrawMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MaterialProperty* pProperty) {
        return true;
    }

    bool DrawMeshMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MeshMaterialProperty* pProperty) {
        return true;
    }

    bool DrawLabelProperty(const DrawPropertyContext& context, SR_UTILS_NS::LabelProperty* pProperty) {
        return true;
    }

    bool DrawPathProperty(const DrawPropertyContext& context, SR_UTILS_NS::PathProperty* pProperty) {
        return true;
    }

    bool DrawEnumProperty(const DrawPropertyContext& context, SR_UTILS_NS::EnumProperty* pProperty) {
        return true;
    }

    bool DrawStandardProperty(const DrawPropertyContext& context, SR_UTILS_NS::StandardProperty* pProperty) {
        return true;
    }

    SR_UTILS_NS::StringAtom GetValueInspector(const SR_UTILS_NS::Reflection::Value& value) {
        if (value.IsBitMap()) {
            return "BitMapPropertyDrawer";
        }

        if (value.IsBool()) {
            return "BoolPropertyDrawer";
        }

        if (value.IsArithmetic()) {
            return "NumericPropertyDrawer";
        }

        if (value.IsSequenceContainer()) {
            return "VectorPropertyDrawer";
        }

        if (value.IsMathSize()) {
            return "MathSizePropertyDrawer";
        }

        if (value.IsMathVector()) {
            return "MathVectorPropertyDrawer";
        }

        if (value.IsEnum()) {
            return "EnumPropertyDrawer";
        }

        if (value.IsSmartPtr()) {
            return "PointerPropertyDrawer";
        }

        if (value.IsString() || value.IsStringView() || value.IsStringAtom() || value.IsUnicodeString()) {
            return "StringPropertyDrawer";
        }

        if (value.IsPath()) {
            return "PathPropertyDrawer";
        }

        if (value.IsClass()) {
            return "ObjectPropertyDrawer";
        }

        return SR_UTILS_NS::StringAtom();
    }

    bool DrawProperty(const DrawPropertyContext& context, SR_UTILS_NS::Property* pProperty) {
        return false;
    }

    bool DrawPropertyContainer(const DrawPropertyContext& context, const SR_UTILS_NS::PropertyContainer* pProperties) {
        bool isRendered = false;
        for (auto&& propertyInfo : pProperties->GetProperties()) {
            isRendered |= DrawProperty(context, propertyInfo.pProperty);
        }
        return isRendered;
    }

    SR_GRAPH_NS::RenderContext::Ptr PropertyDrawerBase::GetRenderContext() const {
        if (m_context) {
            return m_context;
        }
        m_context = SR_THIS_THREAD->GetContext()->GetValue<SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext>>();
        SRAssert2(m_context, "Failed to get render context!");
        return m_context;
    }

    PropertyDrawerFeedback BoolPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetPropertyName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
            }

            ImGui::SameLine();
        }

        if (auto&& bValue = value.TryCast<bool>()) {
            bool isChecked = *bValue;
            if (ImGui::Checkbox("##Checkbox", &isChecked)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                *bValue = isChecked;
                feedback.isChanged = true;
            }
        }
        else {
            SR_GRAPH_GUI_NS::ColoredText("Failed to map bool value!", ImColor(1.f, 0.f, 0.f, 1.f));
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    PropertyDrawerFeedback NumericPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        if (!value.IsArithmetic()) {
            SR_GRAPH_GUI_NS::ColoredText("Property is not numeric!", ImColor(1.f, 0.f, 0.f, 1.f));
            return feedback;
        }

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetPropertyName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        const ImVec2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

        if (!context.pValue && ImGui::Button(context.GetEditorParams().GetDisplayName().c_str(), buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            feedback.isChanged = true;
            value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
            value = value.DetachIfConst();
        }

        ImGui::SameLine();

        ImGui::PushItemWidth(context.fieldWidth);

        const float_t drag = context.GetEditorParams().GetDragSpeed();
        const ImGuiDataType_ dataType = SR_GRAPH_GUI_NS::GetImGuiDataType(value.SizeOf(), value.IsSigned(), value.IsIntegral());
        if (dataType == ImGuiDataType_COUNT) {
            SR_GRAPH_GUI_NS::ColoredText("Unknown data type!", ImColor(1.f, 0.f, 0.f, 1.f));
            return feedback;
        }

        if (void* pValue = value.Data()) {
            SR_GRAPH_GUI_NS::ImGuiDataTypeUnion dataTypeUnion = SR_GRAPH_GUI_NS::ReadImGuiDataType(pValue, dataType);
            if (ImGui::DragScalar("", dataType, &dataTypeUnion, drag)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(true);
                }
                SR_GRAPH_GUI_NS::WriteImGuiDataType(pValue, dataType, dataTypeUnion);
                feedback.isChanged = true;
            }
        }
        else {
            SR_GRAPH_GUI_NS::ColoredText("Failed to map numeric value!", ImColor(1.f, 0.f, 0.f, 1.f));
        }

        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    PropertyDrawerFeedback MathVectorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        std::string_view vectorType = value.GetTypeName();
        if (size_t pos = vectorType.rfind(':'); pos != std::string_view::npos) {
            vectorType.remove_prefix(pos + 1);
        }
        std::string_view vectorPartType = SR_UTILS_NS::StringUtils::GetBetween(vectorType, '<', '>');
        const uint8_t dimension = SR_UTILS_NS::CharToInt(vectorType[sizeof("Vector") - 1]);

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetPropertyName().ToCStr());

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        if (!context.pValue) {
            const ImVec2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (ImGui::Button(context.GetPropertyDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }
        }

        ImGui::SameLine();

        const float_t partItemWidth = (context.fieldWidth / static_cast<float_t>(context.maxPartsInLine)) - context.axisButtonWidth;

        const ImVec2 buttonSize = { context.axisButtonWidth, context.fieldHeight };
        const float_t drag = context.GetEditorParams().GetDragSpeed();
        ImGuiDataType_ partType = SR_GRAPH_GUI_NS::GetImGuiDataType(vectorPartType);

        constexpr std::array<const char*, 6> labels = { "X", "Y", "Z", "W", "V", "U" };
        constexpr std::array<ImVec4, 6> colors = {
            ImVec4(0.8f, 0.1f, 0.15f, 1.0f), /// red
            ImVec4(0.2f, 0.7f, 0.2f, 1.0f), /// green
            ImVec4(0.1f, 0.25f, 0.8f, 1.0f), /// blue
            ImVec4(0.8f, 0.1f, 0.15f, 1.0f), /// red
            ImVec4(0.2f, 0.7f, 0.2f, 1.0f), /// green
            ImVec4(0.1f, 0.25f, 0.8f, 1.0f), /// blue
            //ImVec4(0.8f, 0.8f, 0.2f, 1.0f), /// yellow
            //ImVec4(0.2f, 0.7f, 0.7f, 1.0f), /// cyan
            //ImVec4(0.7f, 0.2f, 0.7f, 1.0f) /// magenta
        };

        for (uint8_t i = 0; i < dimension; ++i) {
            ImGui::PushID(i);

            ImGui::PushStyleColor(ImGuiCol_Button, colors[i]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i] + ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i] + ImVec4(0.2f, 0.2f, 0.2f, 0.0f));

            const uint64_t partSize = value.SizeOf() / dimension;
            const uint64_t offset = partSize * i;

            if (ImGui::Button(labels[i], buttonSize)) {
                SR_UTILS_NS::Reflection::Value copy = value.Detach();
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

            ImGui::PopStyleColor(3);

            ImGui::SameLine();

            ImGui::PushItemWidth(partItemWidth);

            if (partSize == 1) {
                ImGui::PopItemWidth();
                SR_UTILS_NS::Reflection::Value copy = value.Detach();
                bool* pTemp = reinterpret_cast<bool*>(&((char*)(copy.Data()))[offset]);
                if (ImGui::Checkbox("", pTemp)) {
                    SetReflectedValue(context, feedback, copy, false);
                }
                ImGui::SameLine();
                ImGui::Dummy(ImVec2(partItemWidth - ImGui::GetFrameHeight(), 0.0f));
                ImGui::PushItemWidth(partItemWidth);
            }
            else if (partType == ImGuiDataType_COUNT) {
                SR_GRAPH_GUI_NS::ColoredText("Unknown part type!", ImColor(1.f, 0.f, 0.f, 1.f));
            }
            else {
                SR_UTILS_NS::Reflection::Value copy = value.Detach();
                if (ImGui::DragScalar("", partType, (char*)copy.Data() + offset, drag)) {
                    SetReflectedValue(context, feedback, copy, true);
                }
            }

            ImGui::PopItemWidth();
            ImGui::PopID();

            if (i + 1 < dimension) {
                if ((i + 1) % context.maxPartsInLine == 0) {
                    ImGui::Dummy(ImVec2(context.fieldTitleWidth, 0.0f));
                    ImGui::SameLine();
                }
                else {
                    ImGui::SameLine();
                }
            }
        }

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }

    PropertyDrawerFeedback MathSizePropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        std::string_view vectorType = value.GetTypeName();
        if (size_t pos = vectorType.rfind(':'); pos != std::string_view::npos) {
            vectorType.remove_prefix(pos + 1);
        }
        std::string_view vectorPartType = SR_UTILS_NS::StringUtils::GetBetween(vectorType, '<', '>');
        const uint8_t dimension = vectorType.find("Size2") != std::string_view::npos ? 2 : 1;

        ImGuiDataType_ partType = SR_GRAPH_GUI_NS::GetImGuiDataType(vectorPartType);
        if (partType == ImGuiDataType_COUNT) {
            SR_GRAPH_GUI_NS::ColoredText("Unknown part type!", ImColor(1.f, 0.f, 0.f, 1.f));
            return feedback;
        }

        ImGui::PushID(context.pOwner);
        ImGui::PushID(context.GetProperty().GetName().ToCStr());

        if (!context.pValue) {
            const ImVec2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight * 2.f };
            if (ImGui::Button(context.GetProperty().GetEditorParams().GetDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }
        }

        SRAssert(value);

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        constexpr uint32_t maxPartsInLine = 3;
        const float_t partItemWidth = (context.fieldWidth) / maxPartsInLine - context.axisButtonWidth;

        const ImVec2 buttonSize = { context.axisButtonWidth, context.fieldHeight };
        const float_t drag = context.GetProperty().GetEditorParams().GetDragSpeed();

        constexpr std::array<const char*, 2> labels = { "X", "Y" };
        constexpr std::array<ImVec4, 2> colors = {
            ImVec4(0.8f, 0.1f, 0.15f, 1.0f),
            ImVec4(0.2f, 0.7f, 0.2f, 1.0f),
        };

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            SR_UTILS_NS::Reflection::Value copy = value.Detach();

            for (uint8_t i = 0; i < dimension; ++i) {
                ImGui::PushID(i);

                ImGui::PushStyleColor(ImGuiCol_Button, colors[i]);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors[i] + ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors[i] + ImVec4(0.2f, 0.2f, 0.2f, 0.0f));

                auto&& pFSize = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::FSize)]);
                auto&& pISize = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::ISize)]);
                auto&& pUSize = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::USize)]);

                if (ImGui::Button(labels[i], buttonSize)) {
                    feedback.isChanged = true;
                    if (value.SizeOf() == context.GetProperty().GetResetValue().SizeOf()) {
                        auto&& pMapped = context.GetProperty().GetResetValue().Data();
                        switch (partType) {
                            case ImGuiDataType_Float: pFSize->v = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::FSize)])->v; break;
                            case ImGuiDataType_S32: pISize->v = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::ISize)])->v; break;
                            case ImGuiDataType_U32: pUSize->v = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(pMapped))[i * sizeof(SR_MATH_NS::USize)])->v; break;
                            default:
                                SRHalt("Unknown part type!");
                                break;
                        }
                    }
                    else {
                        switch (partType) {
                            case ImGuiDataType_Float: pFSize->v = 0.f; break;
                            case ImGuiDataType_S32: pISize->v = 0; break;
                            case ImGuiDataType_U32: pUSize->v = 0; break;
                            default:
                                SRHalt("Unknown part type!");
                                break;
                        }
                    }
                }

                ImGui::PopStyleColor(3);
                ImGui::PushItemWidth(partItemWidth);

                ImGui::SameLine();

                switch (partType) {
                    case ImGuiDataType_Float: {
                        float_t temp = pFSize->v;
                        if (ImGui::DragScalar("", ImGuiDataType_Float, &temp, drag)) {
                            pFSize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    case ImGuiDataType_S32: {
                        int32_t temp = pISize->v;
                        if (ImGui::DragScalar("", ImGuiDataType_S32, &temp, drag)) {
                            pISize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    case ImGuiDataType_U32: {
                        uint32_t temp = pUSize->v;
                        if (ImGui::DragScalar("", ImGuiDataType_U32, &temp, drag)) {
                            pUSize->v = temp;
                            feedback.isChanged = true;
                            feedback.isDrag = true;
                        }
                        break;
                    }
                    default:
                        SR_GRAPH_GUI_NS::ColoredText("Unknown part type!", ImColor(1.f, 0.f, 0.f, 1.f));
                        break;
                }

                ImGui::PopItemWidth();

                ImGui::PopID();

                if (i + 1 < dimension) {
                    ImGui::SameLine();
                }
            }

            ImGui::PushID("Metric");

            ImGui::PushItemWidth(context.fieldWidth / maxPartsInLine);

            for (uint8_t i = 0; i < dimension; ++i) {
                ImGui::PushID(i);

                auto&& pFSize = reinterpret_cast<SR_MATH_NS::FSize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::FSize)]);
                auto&& pISize = reinterpret_cast<SR_MATH_NS::ISize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::ISize)]);
                auto&& pUSize = reinterpret_cast<SR_MATH_NS::USize*>(&((char*)(copy.Data()))[i * sizeof(SR_MATH_NS::USize)]);

                SR_MATH_NS::SizeMetric* pSize = nullptr;
                switch (partType) {
                    case ImGuiDataType_Float: pSize = &pFSize->metric; break;
                    case ImGuiDataType_S32: pSize = &pISize->metric; break;
                    case ImGuiDataType_U32: pSize = &pUSize->metric; break;
                    default:
                        SR_GRAPH_GUI_NS::ColoredText("Unknown part type!", ImColor(1.f, 0.f, 0.f, 1.f));
                        break;
                }

                if (pSize && ImGui::BeginCombo("", SR_UTILS_NS::EnumReflector::ToStringAtom(*pSize).c_str())) {
                    auto&& names = SR_UTILS_NS::EnumReflector::GetNames<SR_MATH_NS::SizeMetric>();
                    for (auto&& name : names) {
                        if (ImGui::Selectable(name.c_str())) {
                            ImGui::SetItemDefaultFocus();
                            *pSize = SR_UTILS_NS::EnumReflector::FromString<SR_MATH_NS::SizeMetric>(name);
                            feedback.isChanged = true;
                        }
                    }

                    ImGui::EndCombo();
                }

                ImGui::PopID();

                if (i + 1 < dimension) {
                    ImGui::SameLine();
                }
            }
            ImGui::PopItemWidth();
            ImGui::EndGroup();

            if (feedback.isChanged) {
                SetReflectedValue(context, feedback, copy, feedback.isDrag);
            }
        }

        ImGui::PopID();

        ImGui::PopStyleVar();

        ImGui::PopID();
        ImGui::PopID();

        return feedback;
    }
}
