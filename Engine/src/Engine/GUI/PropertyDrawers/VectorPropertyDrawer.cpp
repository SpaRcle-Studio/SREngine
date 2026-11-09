//
// Created by Monika on 01.02.2025.
//

#include <Engine/GUI/PropertyDrawers/VectorPropertyDrawer.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Codegen/VectorPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback VectorPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();
        auto&& container = value.AsSequenceContainer();
        if (!value.GetTypeInfo().vtable.containerVTable.pSize) {
            return feedback;
        }

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().ToCStr());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        SR_UTILS_NS::StringAtom displayName = context.GetPropertyDisplayName();

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

            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
        }
        else {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            //const float_t arrowWidth = context.lineHeight * 0.75f;
            //SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(arrowWidth, 0));
            //SR_IMMEDIATE_GUI_NS::SameLine();

            //const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - arrowWidth, 0), context.fieldHeight };
            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth + counterButtonWidth.x;
            const float_t partItemWidth = ((context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth) / 3;
            buttonSize = { partItemWidth, context.fieldHeight };

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

        SR_IMMEDIATE_GUI_NS::SameLine();

        if (SR_IMMEDIATE_GUI_NS::Button("Add", buttonSize)) {
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            container.Resize(container.Size() + 1);
            if (context.GetEditorParams().IsNotNull()) {
                if (auto&& newElementValue = container.Back(); newElementValue.IsSharedPtr()) {
                    if (auto&& pSharedPtrBase = newElementValue.GetSharedPtrBase()) {
                        SR_UTILS_NS::StringAtom typeName = newElementValue.GetTypeInfo().pNext[0]->detailedType;
                        if (SR_UTILS_NS::Factory::Instance().IsAbstract(typeName)) {
                            auto&& inheritances = SR_UTILS_NS::Factory::Instance().GetInheritances(typeName);
                            for (auto&& inheritance : inheritances) {
                                if (!SR_UTILS_NS::Factory::Instance().IsAbstract(inheritance)) {
                                    typeName = inheritance;
                                    break;
                                }
                            }
                        }

                        if (SR_UTILS_NS::Factory::Instance().IsAbstract(typeName)) {
                            SRHalt("VectorPropertyDrawer::Draw() : failed to find concrete type for abstract type {}!", typeName);
                        }
                        else {
                            if (auto&& pInstance = SR_UTILS_NS::Factory::Instance().CreateBase(typeName)) {
                                pSharedPtrBase->SetPointerFromBase(dynamic_cast<SR_HTYPES_NS::SharedPtrBase*>(pInstance));
                            }
                            else {
                                SRHalt("VectorPropertyDrawer::Draw() : failed to create instance of type {}!", typeName);
                            }
                        }
                    }
                    else {
                        SRHalt("VectorPropertyDrawer::Draw() : new element is smart pointer, but GetSharedPtrBase() returned nullptr!");
                    }
                }
            }
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

        if (container.Size() < m_drawers.size()) {
            m_drawers.resize(container.Size());
        }

        if (m_isOpened) {
            for (auto pIt = container.Begin(); pIt != container.End();) {
                uint64_t index = SR_UTILS_NS::Distance(container.Begin(), pIt);
                SR_IMMEDIATE_GUI_NS::PushID(static_cast<int32_t>(index));
                SR_UTILS_NS::Reflection::Value element = *pIt;

                SR_MATH_NS::FVector2 itemButtonSize = { 40, context.fieldHeight };

                SR_IMMEDIATE_GUI_NS::Button("{}"_format(index).c_str(), itemButtonSize);

                if (SR_IMMEDIATE_GUI_NS::BeginPopupContextItem("ElementContextMenu")) {
                    bool copy = false; //SR_IMMEDIATE_GUI_NS::MenuItem("Copy");
                    bool removed = SR_IMMEDIATE_GUI_NS::MenuItem("Remove");
                    bool cut = false; //SR_IMMEDIATE_GUI_NS::MenuItem("Cut");

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

                    if (index > 0 && SR_IMMEDIATE_GUI_NS::MenuItem("Move up")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = (*pIt).Copy();
                        pIt = container.Erase(pIt);
                        container.Insert(--pIt, temp);

                        feedback.isChanged = true;
                        SR_IMMEDIATE_GUI_NS::EndPopup();
                        SR_IMMEDIATE_GUI_NS::PopID();
                        break;
                    }

                    if (index + 1 < container.Size() && SR_IMMEDIATE_GUI_NS::MenuItem("Move down")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = (*pIt).Copy();
                        pIt = container.Erase(pIt);
                        container.Insert(++pIt, temp);

                        feedback.isChanged = true;
                        SR_IMMEDIATE_GUI_NS::EndPopup();
                        SR_IMMEDIATE_GUI_NS::PopID();
                        break;
                    }

                    if (index > 0 && SR_IMMEDIATE_GUI_NS::MenuItem("Move to start")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = (*pIt).Copy();
                        container.Erase(pIt);
                        container.PushFront(temp);
                        pIt = container.Begin();

                        feedback.isChanged = true;
                    }

                    if (index + 1 < container.Size() && SR_IMMEDIATE_GUI_NS::MenuItem("Move to end")) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }

                        SR_UTILS_NS::Reflection::Value temp = (*pIt).Copy();
                        container.Erase(pIt);
                        container.PushBack(temp);
                        pIt = --container.End();

                        feedback.isChanged = true;
                    }


                    SR_IMMEDIATE_GUI_NS::EndPopup();
                    if (removed) {
                        SR_IMMEDIATE_GUI_NS::PopID();
                        continue;
                    }
                }

                SR_IMMEDIATE_GUI_NS::SameLine();

                if (index >= m_drawers.size()) {
                    m_drawers.emplace_back();

                    SR_UTILS_NS::StringAtom inspector = SR_CORE_GUI_NS::GetValueInspector(element);
                    if (!inspector.Empty()) {
                        auto&& pDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
                        m_drawers.back() = pDrawer;
                    }
                }

                if (!m_drawers[index]) {
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Missing inspector for element!");
                    SR_IMMEDIATE_GUI_NS::PopID();
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

                SR_IMMEDIATE_GUI_NS::BeginGroup();
                PropertyDrawerFeedback elementFeedback = m_drawers[index]->Draw(elementContext);
                SR_IMMEDIATE_GUI_NS::EndGroup();

                if (elementFeedback.isChanged) {
                    feedback.isChanged = true;
                }

                SR_IMMEDIATE_GUI_NS::PopID();

                ++pIt;
            }
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }
}
