//
// Created by Monika on 03.02.2025.
//

#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

#include <Graphics/GUI/Utils.h>
#include <Graphics/GUI/ImmediateGUI.h>

#include <Codegen/ObjectPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ObjectPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        SR_TRACY_ZONE;

        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().ToCStr());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);

        if (!m_openedByDefault) {
            m_isOpened |= context.openedByDefault;
            m_openedByDefault = true;
        }

        m_isOpened |= context.noHeader;
        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;

        SR_UTILS_NS::SRClass* pClassValue = value.GetSRClass();

        SR_MATH_NS::FVector2 buttonSize;

        if (context.pValue && !context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow) + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            const SR_MATH_NS::FVector2 mainButtonSize = { 30, context.fieldHeight };
            buttonSize = { context.fieldWidth - mainButtonSize.x, context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button("", mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }
        else if (!context.noHeader) {
            const SR_MATH_NS::FVector2 arrowPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow) + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            //SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 0));
            //SR_GRAPH_GUI_NS::Immediate::SameLine();

            //const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth - context.GetArrowWidth(), 0), context.fieldHeight };
            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(context.fieldTitleWidth, 0), context.fieldHeight };
            const float_t titleTotalWidth = context.fieldTitleWidth;
            buttonSize = { (context.fieldWidth + context.fieldTitleWidth) - titleTotalWidth, context.fieldHeight };

            SR_UTILS_NS::StringAtom displayName = context.GetEditorParams().GetDisplayName();
            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button(displayName.c_str(), mainButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
        }

        if (!context.noHeader) {
            SR_GRAPH_GUI_NS::Immediate::SameLine();

            SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
            SR_GRAPH_GUI_NS::Immediate::Button("{}"_format(pClassValue->GetMeta()->GetFactoryName()).c_str(), buttonSize);
            SR_GRAPH_GUI_NS::Immediate::EndDisabled();
        }

        m_groups.clear();

        if (m_isOpened) {
            if (const SR_UTILS_NS::SRClassMeta* pMeta = pClassValue->GetMeta()) {
                const float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
                float_t widthNoArrow = totalWidth - ((!context.pValue && !context.noHeader) ? context.GetArrowWidth() : 0.f);

                PropertyDrawerContext propertyContext = context;
                propertyContext.pValue = nullptr;
                propertyContext.fieldWidth = widthNoArrow * 0.7f;
                propertyContext.fieldTitleWidth = widthNoArrow * 0.3f;
                propertyContext.pOwner = pClassValue;
                //propertyContext.pUID = value.IsRef() ? pClassValue : (static_cast<void*>(static_cast<uint64_t*>(propertyContext.pUID) + 1));
                propertyContext.noHeader = false;

                pMeta->ForEachProperty([&](auto&& property, uint64_t index) {
                    SR_GRAPH_GUI_NS::Immediate::PushID(index);
                    DrawPropertyGroup(SR_UTILS_NS::StringAtom(), pClassValue, index, property, context, propertyContext, feedback);
                    SR_GRAPH_GUI_NS::Immediate::PopID();
                });

                widthNoArrow = widthNoArrow - context.GetArrowWidth();
                propertyContext.fieldWidth = widthNoArrow * 0.7f;
                propertyContext.fieldTitleWidth = widthNoArrow * 0.3f;

                for (const auto& group : m_groups) {
                    SR_GRAPH_GUI_NS::Immediate::PushID(group.c_str());

                    bool isGroupOpened = m_openedGroups.count(group) > 0;
                    const auto groupDir = isGroupOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;
                    const SR_MATH_NS::FVector2 arrowPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow) + SR_MATH_NS::FVector2(1, 5);
                    SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), groupDir, 1.f);

                    auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
                    if (SR_GRAPH_GUI_NS::Immediate::Button(group.c_str(), { context.fieldTitleWidth + context.fieldWidth, context.fieldHeight })) {
                        if (isGroupOpened) {
                            m_openedGroups.erase(group);
                        }
                        else {
                            m_openedGroups.insert(group);
                        }
                        isGroupOpened = !isGroupOpened;
                    }
                    SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);

                    if (isGroupOpened) {
                        SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 5.0f));
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                        pMeta->ForEachProperty([&](auto&& property, uint64_t index) {
                            SR_GRAPH_GUI_NS::Immediate::PushID(index);
                            DrawPropertyGroup(group, pClassValue, index, property, context, propertyContext, feedback);
                            SR_GRAPH_GUI_NS::Immediate::PopID();
                        });
                        SR_GRAPH_GUI_NS::Immediate::EndGroup();
                    }

                    SR_GRAPH_GUI_NS::Immediate::PopID();
                }

                propertyContext.noHeader = false;

                PropertyDrawerFeedback customFeedback = DrawCustomProperties(context);
                if (customFeedback.isChanged) {
                    feedback.isChanged = true;
                }
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Failed to get meta for object!");
            }
        }

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        SetValue(context, feedback, value);

        return feedback;
    }

    void ObjectPropertyDrawer::DrawPropertyGroup(
        SR_UTILS_NS::StringAtom group,
        SR_UTILS_NS::SRClass* pClassValue,
        uint64_t index,
        const SR_UTILS_NS::Reflection::Property& property,
        const PropertyDrawerContext& context,
        PropertyDrawerContext& propertyContext,
        PropertyDrawerFeedback& feedback
    ) {
        SR_TRACY_ZONE;

        if (property.IsHidden(pClassValue)) {
            return;
        }

        if (property.GetEditorParams().IsDebugOnly() && !context.isDebugMode) {
            return;
        }

        const SR_UTILS_NS::StringAtom propertyGroup = property.GetEditorParams().GetGroup();
        if (group != propertyGroup) {
            if (!propertyGroup.empty() && group.empty() && std::ranges::find(m_groups, propertyGroup) == m_groups.end()) {
                m_groups.emplace_back(propertyGroup);
            }
            return;
        }

        SR_UTILS_NS::StringAtom inspector = property.GetEditorParams().GetInspector();
        if (inspector.Empty()) {
            inspector = GetValueInspector(property.Get(pClassValue));
        }

        if (inspector == ObjectPropertyDrawer::GetClassStaticName()) {
            /// возможно, это не безопасно, и может привести к UB
            if (SR_UTILS_NS::SRClass* pValueClass = property.Get(pClassValue).GetSRClass()) {
                inspector = pValueClass->GetMeta()->GetInspectorName();
            }
        }

        if (inspector.Empty()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Missing inspector for element!");
            return;
        }

        if (m_drawers.size() <= index) {
            m_drawers.resize(index + 1);
        }

        if (!m_drawers[index] || m_drawers[index]->GetMeta()->GetFactoryName() != inspector) {
            m_drawers[index] = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspector);
        }

        if (!m_drawers[index]) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), "Missing inspector for element!");
            return;
        }

        if (!context.pValue && !context.noHeader) {
            SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 5.0f));
            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        propertyContext.noHeader = property.GetEditorParams().IsNoHeader();
        propertyContext.pProperty = &property;

        SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(property.IsReadOnly());

        SR_GRAPH_GUI_NS::Immediate::BeginGroup();
        PropertyDrawerFeedback propertyFeedback = m_drawers[index]->Draw(propertyContext);
        SR_GRAPH_GUI_NS::Immediate::EndGroup();

        if (propertyFeedback.isChanged) {
            property.OnChanged(propertyContext.pOwner);
            feedback.isChanged = true;
        }
    }
}
