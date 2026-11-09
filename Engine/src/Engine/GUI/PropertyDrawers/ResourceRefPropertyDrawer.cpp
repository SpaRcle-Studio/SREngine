//
// Created by Monika on 19.02.2026.
//

#include <Engine/GUI/PropertyDrawers/ResourceRefPropertyDrawer.h>
#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Utils/Resources/ResourceRef.h>
#include <Utils/FileSystem/FileDialog.h>

#include <Codegen/ResourceRefPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback ResourceRefPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_IMMEDIATE_GUI_NS::PushID(context.pUID);
        SR_IMMEDIATE_GUI_NS::PushID(context.GetPropertyName().c_str());

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_IMMEDIATE_GUI_NS::GetCurrentWindow();
        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_IMMEDIATE_GUI_NS::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_IMMEDIATE_GUI_NS::Direction::Down : SR_IMMEDIATE_GUI_NS::Direction::Right;
        const float arrowWidth = context.GetArrowWidth() * 1.15f;
        const SR_MATH_NS::FVector2 arrowButtonSize = { arrowWidth, context.fieldHeight };

        {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_IMMEDIATE_GUI_NS::RenderArrow(pDrawList, arrowPos, SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text), dir, 1.f);

            auto&& stackSize = SR_IMMEDIATE_GUI_NS::BeginForceEnabled();
            if (SR_IMMEDIATE_GUI_NS::Button("", arrowButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_IMMEDIATE_GUI_NS::EndForceEnabled(stackSize);
            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const SR_MATH_NS::FVector2 buttonSize = SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.75f - arrowButtonSize.x, context.fieldHeight);

            if (SR_IMMEDIATE_GUI_NS::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.pProperty) {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    feedback.isChanged = true;
                    value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                    value = value.Copy();
                }
            }
            DrawTitleContextMenu(context, feedback);

            SR_IMMEDIATE_GUI_NS::SameLine();
        }

        /// picking
        {
            if (SR_IMMEDIATE_GUI_NS::Button("...", SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.25f, context.fieldHeight))) {
                auto&& filterName = context.GetEditorParams().GetCustomArg("filter name");
                auto&& filterValue = context.GetEditorParams().GetCustomArg("filter value");

                // const bool relativeRes = context.GetEditorParams().GetCustomArg("relative") != "resources" || (filterName.empty() && filterValue.empty());
                // something strange...
                // looks for https://github.com/SpaRcle-Studio/SREngine/commit/d127c0513013765b890941ea68511c547134cbeb if new change will break skeleton retargeting

                const bool relativeRes = context.GetEditorParams().GetCustomArg("relative") == "resources";

                if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
                    if (filterName.empty()) {
                        filterName = SR_UTILS_NS::Reflection::MakeDisplayName(pRef->GetResourceType());
                    }

                    if (!filterName.empty() && filterValue.empty()) {
                        filterValue = SR_UTILS_NS::Factory::Instance().GetType(pRef->GetResourceType())->GetExtension();
                    }

                    if (!filterName.empty() && !filterValue.empty()) {
                        auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath, { { filterName, filterValue } });

                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;

                        if (relativeRes) {
                            path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPathRef());
                        }

                        if (!path.empty()) {
                            pRef->SetResource(SR_UTILS_NS::StringAtom(path.View()));
                        }
                    }
                }
            }
        }

        SR_IMMEDIATE_GUI_NS::SameLine();

        SR_IMMEDIATE_GUI_NS::PushItemWidth(context.fieldWidth);

        if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
            SR_UTILS_NS::StringAtom type = pRef->GetResourceType();

            static SR_UTILS_NS::String formatted;
            formatted.clear();

            if (pRef->GetId().empty()) {
                SR_UTILS_NS::FormatTo(formatted, " Is not set ({})", type);
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
                SR_IMMEDIATE_GUI_NS::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }
            else if (!pRef->GetResourceBase()) {
                SR_UTILS_NS::FormatTo(formatted, " {} ({} is missing)", pRef->GetId(), type);
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
                SR_IMMEDIATE_GUI_NS::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }
            else {
                SR_UTILS_NS::FormatTo(formatted, " {} ({})", pRef->GetId(), type);
                SR_IMMEDIATE_GUI_NS::BeginDisabled();
                SR_IMMEDIATE_GUI_NS::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }

            if (auto&& pResource = pRef->GetResourceBase(); pResource && m_isOpened) {
                const SR_UTILS_NS::StringAtom factoryName = pResource->GetMeta()->GetFactoryName();
                if (m_lastTypeName != factoryName) {
                    m_lastTypeName = factoryName;

                    if (auto&& inspectorName = pResource->GetMeta()->GetInspectorName(); !inspectorName.empty()) {
                        m_objectDrawer = SR_UTILS_NS::Factory::Instance().Create<ObjectPropertyDrawer>(inspectorName);
                    }
                    if (!m_objectDrawer) {
                        m_objectDrawer = SRNew<ObjectPropertyDrawer>();
                    }
                }

                if (!context.pValue && !context.noHeader) {
                    SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(arrowWidth, 5.0f));
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }

                SR_UTILS_NS::SRClass* pClassValue = pResource->GetSRClass();
                PropertyDrawerContext propertyContext = context;
                auto&& valueRef = SR_UTILS_NS::Reflection::Value::CreateRef(*pClassValue);
                propertyContext.pValue = &valueRef;
                float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
                totalWidth -= ((!context.pValue && !context.noHeader) ? arrowWidth : 0.f);
                propertyContext.fieldWidth = totalWidth * 0.7f;
                propertyContext.fieldTitleWidth = totalWidth * 0.3f;
                propertyContext.pProperty = nullptr;
                propertyContext.pOwner = pClassValue;
                propertyContext.noHeader = true;

                SR_IMMEDIATE_GUI_NS::BeginGroup();
                PropertyDrawerFeedback propertyFeedback = m_objectDrawer->Draw(propertyContext);
                SR_IMMEDIATE_GUI_NS::EndGroup();

                if (propertyFeedback.isChanged) {
                    feedback.isChanged = true;
                }
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map resource ref value!");
        }

        SR_IMMEDIATE_GUI_NS::PopItemWidth();

        SetValue(context, feedback, value);

        SR_IMMEDIATE_GUI_NS::PopStyleVar();

        SR_IMMEDIATE_GUI_NS::PopID();
        SR_IMMEDIATE_GUI_NS::PopID();

        return feedback;
    }
}
