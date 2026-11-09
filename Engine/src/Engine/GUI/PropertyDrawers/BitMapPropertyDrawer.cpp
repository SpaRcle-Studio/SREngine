//
// Created by Monika on 03.02.2025.
//

#include <Engine/GUI/PropertyDrawers/BitMapPropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Codegen/BitMapPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback BitMapPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

    #ifdef SR_COMMON_USE_ENTT
        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetProperty().GetName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetDisplayName();

        auto&& container = value.AsSequenceContainer();

        const SR_MATH_NS::FVector2 counterButtonWidth = { 40, context.fieldHeight };
        SR_MATH_NS::FVector2 buttonSize;

        auto&& pWindow = SR_IMMEDIATE_GUI_NS::GetCurrentWindow();
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_IMMEDIATE_GUI_NS::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_IMMEDIATE_GUI_NS::Direction::Down : SR_IMMEDIATE_GUI_NS::Direction::Right;

        if (context.pValue) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { (context.fieldWidth - (counterButtonWidth.x + mainButtonSize.x)) / 3, context.fieldHeight };
            if (SR_IMMEDIATE_GUI_NS::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }
        else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(0, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            const float_t arrowWidth = context.lineHeight * 0.75f;
            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));

            SR_IMMEDIATE_GUI_NS::SameLine();

            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth + counterButtonWidth.x;
            const float_t partItemWidth = ((context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth) / 3;
            buttonSize = { partItemWidth, context.fieldHeight };

            if (SR_IMMEDIATE_GUI_NS::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            DrawTitleContextMenu(context, feedback);
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::BeginDisabled();
        SR_IMMEDIATE_GUI_NS::Button("{}"_format(container.Size()).c_str(), counterButtonWidth);
        SR_IMMEDIATE_GUI_NS::EndDisabled();

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Add", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            container.Resize(container.Size() + 1);
            feedback.isChanged = true;
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Remove", buttonSize)) {
            if (!container.Empty()) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                container.Resize(container.Size() - 1);
                feedback.isChanged = true;
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Clear", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            container.Clear();
            feedback.isChanged = true;
        }

        if (m_isOpened) {
            constexpr uint64_t maxPartsInLine = 8;

            if (auto&& pBitMap = value.TryCast<SR_UTILS_NS::Vector<bool>>()) {
                for (uint64_t i = 0; i < pBitMap->size(); ++i) {
                    SR_IMMEDIATE_GUI_NS::PushID(i);

                    if (i % maxPartsInLine == 0) {
                        SR_MATH_NS::FVector2 itemButtonSize = { 40, context.fieldHeight };
                        SR_IMMEDIATE_GUI_NS::BeginDisabled();
                        SR_IMMEDIATE_GUI_NS::Button("[{}] "_format(static_cast<uint64_t>(i / maxPartsInLine)).c_str(), itemButtonSize);
                        SR_IMMEDIATE_GUI_NS::EndDisabled();
                        SR_IMMEDIATE_GUI_NS::SameLine();
                    }

                    bool bValue = (*pBitMap)[i];
                    if (SR_IMMEDIATE_GUI_NS::Checkbox("", &bValue)) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        pBitMap->at(i) = bValue;
                        feedback.isChanged = true;
                    }

                    if ((i + 1) % maxPartsInLine != 0) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                    }

                    SR_IMMEDIATE_GUI_NS::PopID();
                }
            }
            else {
                SRHalt("Failed to map bit map value!");
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);
    #endif

        return feedback;
    }
}
