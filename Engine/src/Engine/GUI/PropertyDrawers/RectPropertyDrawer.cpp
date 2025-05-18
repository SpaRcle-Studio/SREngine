//
// Created by Monika on 18.05.2025.
//

#include <Engine/GUI/PropertyDrawers/RectPropertyDrawer.h>

#include <Codegen/RectPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback RectPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        std::string_view rectType = value.GetTypeName();
        if (size_t pos = rectType.rfind(':'); pos != std::string_view::npos) {
            rectType.remove_prefix(pos + 1);
        }
        std::string_view rectPartType = SR_UTILS_NS::StringUtils::GetBetween(rectType, '<', '>');

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 mainButtonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetPropertyDisplayName().c_str(), mainButtonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.DetachIfConst();
                SetReflectedValue(context, feedback, value);
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        const float_t partItemWidth = (context.fieldWidth / static_cast<float_t>(context.maxPartsInLine)) - context.axisButtonWidth;

        const SR_MATH_NS::FVector2 buttonSize = { context.axisButtonWidth, context.fieldHeight };
        const float_t drag = context.GetEditorParams().GetDragSpeed();
        auto partType = SR_GRAPH_GUI_NS::Immediate::GetDataType(rectPartType);

        constexpr std::array<const char*, 4> labels = { "X", "Y", "W", "H" };
        static const std::array<SR_MATH_NS::FColor, 4> colors = {
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), /// red
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), /// green
            SR_MATH_NS::FColor(0.8f, 0.1f, 0.15f, 1.0f), /// red
            SR_MATH_NS::FColor(0.2f, 0.7f, 0.2f, 1.0f), /// green
        };

        for (uint8_t i = 0; i < 4; ++i) {
            SR_GRAPH_GUI_NS::Immediate::PushID(i);

            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Button, colors[i]);
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonHovered, colors[i] + SR_MATH_NS::FColor(0.1f, 0.1f, 0.1f, 0.0f));
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::ButtonActive, colors[i] + SR_MATH_NS::FColor(0.2f, 0.2f, 0.2f, 0.0f));

            const uint64_t partSize = value.SizeOf() / 4;
            const uint64_t offset = partSize * i;

            if (SR_GRAPH_GUI_NS::Immediate::Button(labels[i], buttonSize)) {
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

            SR_GRAPH_GUI_NS::Immediate::PopStyleColor(3);

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(partItemWidth);

            if (partSize == 1) {
                SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
                SR_UTILS_NS::Reflection::Value copy = value.Detach();
                bool* pTemp = reinterpret_cast<bool*>(&((char*)(copy.Data()))[offset]);
                if (SR_GRAPH_GUI_NS::Immediate::Checkbox("", pTemp)) {
                    SetReflectedValue(context, feedback, copy, false);
                }
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(partItemWidth - SR_GRAPH_GUI_NS::Immediate::GetFrameHeight(), 0.0f));
                SR_GRAPH_GUI_NS::Immediate::PushItemWidth(partItemWidth);
            }
            else if (partType == SR_GRAPH_GUI_NS::Immediate::ImmediateDataType::COUNT) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Unknown part type!");
            }
            else {
                SR_UTILS_NS::Reflection::Value copy = value.Detach();
                if (SR_GRAPH_GUI_NS::Immediate::DragScalar("", partType, (char*)copy.Data() + offset, drag)) {
                    SetReflectedValue(context, feedback, copy, true);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
            SR_GRAPH_GUI_NS::Immediate::PopID();

            if (i + 1 < 4) {
                if ((i + 1) % 2 == 0) {
                    SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.fieldTitleWidth, 0.0f));
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}