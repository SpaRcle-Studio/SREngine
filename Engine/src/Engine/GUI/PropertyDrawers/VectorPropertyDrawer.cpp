//
// Created by Monika on 01.02.2025.
//

#include <Engine/GUI/PropertyDrawers/VectorPropertyDrawer.h>

#include <Codegen/VectorPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback VectorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        if (!value.IsSequenceContainer()) {
            SRHalt("VectorPropertyDrawer can only be used with sequence containers!");
            return feedback;
        }

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        SR_UTILS_NS::StringAtom displayName = context.GetProperty().GetEditorParams().GetDisplayName();

        auto&& container = value.AsSequenceContainer();

        const SR_MATH_NS::FVector2 counterButtonWidth = { 40, context.fieldHeight };
        SR_MATH_NS::FVector2 buttonSize;

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        if (context.pValue) {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { (context.fieldWidth - (counterButtonWidth.x + mainButtonSize.x)) / 3, context.fieldHeight };
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
        }
        else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            //const float_t arrowWidth = context.lineHeight * 0.75f;
            //SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));
            //SR_GRAPH_GUI_NS::Immediate::SameLine();

            //const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth + counterButtonWidth.x;
            const float_t partItemWidth = ((context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth) / 3;
            buttonSize = { partItemWidth, context.fieldHeight };

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

        if (container.Size() < m_drawers.size()) {
            m_drawers.resize(container.Size());
        }

        if (m_isOpened) {
            for (auto pIt = container.begin(); pIt != container.end();) {
                SR_UTILS_NS::Reflection::Value element = *pIt;
                uint64_t index = SR_UTILS_NS::Distance(container.begin(), pIt);
                SR_GRAPH_GUI_NS::Immediate::PushID(index);

                SR_MATH_NS::FVector2 itemButtonSize = { 40, context.fieldHeight };

                SR_GRAPH_GUI_NS::Immediate::Button("{}"_format(index).c_str(), itemButtonSize);

                if (SR_GRAPH_GUI_NS::Immediate::BeginPopupContextItem("ElementContextMenu")) {
                    bool copy = false; //SR_GRAPH_GUI_NS::Immediate::MenuItem("Copy");
                    bool removed = SR_GRAPH_GUI_NS::Immediate::MenuItem("Remove");
                    bool cut = false; //SR_GRAPH_GUI_NS::Immediate::MenuItem("Cut");

                    if (copy || cut) {
                        //SR_UTILS_NS::SRASerializer serializer;
                        //SR_UTILS_NS::Serialization::Save(serializer, SR_HTYPES_NS::SharedPtr(pComponent), serializeId);
                        //std::string encoded = SR_UTILS_NS::StringUtils::Base64Encode(serializer.ToString());
                        //SR_PLATFORM_NS::TextToClipboard(serializeId.GetName() + encoded);
                    }

                    if (removed || cut) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        pIt = container.Erase(pIt);
                        feedback.isChanged = true;
                        removed = true;
                    }

                    if (index > 0 && SR_GRAPH_GUI_NS::Immediate::MenuItem("Move up")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = pIt->Detach();
                        pIt = container.Erase(pIt);
                        container.Insert(--SR_UTILS_NS::Reflection::ValueSequenceContainerIterator(pIt), temp);

                        feedback.isChanged = true;
                        SR_GRAPH_GUI_NS::Immediate::EndPopup();
                        SR_GRAPH_GUI_NS::Immediate::PopID();
                        break;
                    }

                    if (index + 1 < container.Size() && SR_GRAPH_GUI_NS::Immediate::MenuItem("Move down")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = pIt->Detach();
                        pIt = container.Erase(pIt);
                        container.Insert(++SR_UTILS_NS::Reflection::ValueSequenceContainerIterator(pIt), temp);

                        feedback.isChanged = true;
                        SR_GRAPH_GUI_NS::Immediate::EndPopup();
                        SR_GRAPH_GUI_NS::Immediate::PopID();
                        break;
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndPopup();
                    if (removed) {
                        SR_GRAPH_GUI_NS::Immediate::PopID();
                        continue;
                    }
                }

                SR_GRAPH_GUI_NS::Immediate::SameLine();

                if (index >= m_drawers.size()) {
                    m_drawers.emplace_back();

                    SR_UTILS_NS::StringAtom inspector = SR_CORE_GUI_NS::GetValueInspector(element);
                    if (!inspector.Empty()) {
                        auto&& pDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                        m_drawers.back() = pDrawer;
                    }
                }

                if (!m_drawers[index]) {
                    SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Missing inspector for element!");
                    SR_GRAPH_GUI_NS::Immediate::PopID();
                    ++pIt;
                    continue;
                }

                PropertyDrawerContext elementContext = context;
                elementContext.pValue = &element;
                elementContext.fieldWidth += context.fieldTitleWidth;
                elementContext.fieldWidth -= itemButtonSize.x;
                elementContext.fieldTitleWidth = 0.f;
                elementContext.noHeader = false;
                elementContext.openedByDefault = false;

                SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                PropertyDrawerFeedback elementFeedback = m_drawers[index]->Draw(elementContext);
                SR_GRAPH_GUI_NS::Immediate::EndGroup();

                if (elementFeedback.isChanged) {
                    feedback.isChanged = true;
                }

                SR_GRAPH_GUI_NS::Immediate::PopID();

                ++pIt;
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }
}
