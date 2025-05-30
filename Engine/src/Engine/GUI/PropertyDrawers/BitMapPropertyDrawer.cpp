//
// Created by Monika on 03.02.2025.
//

#include <Engine/GUI/PropertyDrawers/BitMapPropertyDrawer.h>

#include <Codegen/BitMapPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback BitMapPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(
            SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2()
        );

        SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetEditorParams().GetDisplayName();

        auto&& container = value.AsSequenceContainer();

        const SR_MATH_NS::FVector2 counterButtonWidth = {40, context.fieldHeight};
        SR_MATH_NS::FVector2 buttonSize;

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

        const auto dir =
            m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        if (context.pValue) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(
                pDrawList, arrowPos,
                SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f
            );

            const SR_MATH_NS::FVector2 mainButtonSize = {30, context.fieldHeight};
            buttonSize = {(context.fieldWidth - (counterButtonWidth.x + mainButtonSize.x)) / 3, context.fieldHeight};
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        } else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(0, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(
                pDrawList, arrowPos,
                SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f
            );

            const float_t arrowWidth = context.lineHeight * 0.75f;
            SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            const SR_MATH_NS::FVector2 mainButtonSize = {
                SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight
            };
            const float_t titleTotalWidth = context.fieldTitleWidth + counterButtonWidth.x;
            const float_t partItemWidth = ((context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth) / 3;
            buttonSize = {partItemWidth, context.fieldHeight};

            if (SR_GRAPH_GUI_NS::Immediate::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
        SR_GRAPH_GUI_NS::Immediate::Button("{}"_format(container.Size()).c_str(), counterButtonWidth);
        SR_GRAPH_GUI_NS::Immediate::EndDisabled();

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Add", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            container.Resize(container.Size() + 1);
            feedback.isChanged = true;
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Remove", buttonSize)) {
            if (!container.Empty()) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                container.Resize(container.Size() - 1);
                feedback.isChanged = true;
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Clear", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            container.Clear();
            feedback.isChanged = true;
        }

        if (m_isOpened) {
            constexpr uint64_t maxPartsInLine = 8;

            if (std::vector<bool>* pBitMap = value.TryCast<std::vector<bool>>()) {
                for (uint64_t i = 0; i < pBitMap->size(); ++i) {
                    SR_GRAPH_GUI_NS::Immediate::PushID(i);

                    if (i % maxPartsInLine == 0) {
                        SR_MATH_NS::FVector2 itemButtonSize = {40, context.fieldHeight};
                        SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                        SR_GRAPH_GUI_NS::Immediate::Button(
                            "[{}] "_format(static_cast<uint64_t>(i / maxPartsInLine)).c_str(), itemButtonSize
                        );
                        SR_GRAPH_GUI_NS::Immediate::EndDisabled();
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                    }

                    bool bValue = (*pBitMap)[i];
                    if (SR_GRAPH_GUI_NS::Immediate::Checkbox("", &bValue)) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        pBitMap->at(i) = bValue;
                        feedback.isChanged = true;
                    }

                    if ((i + 1) % maxPartsInLine != 0) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                    }

                    SR_GRAPH_GUI_NS::Immediate::PopID();
                }
            } else {
                SRHalt("Failed to map bit map value!");
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }
} // namespace SR_CORE_GUI_NS
