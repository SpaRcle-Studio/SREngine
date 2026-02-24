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

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetPropertyName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
        auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
        const auto cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

        const auto dir = m_isOpened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;
        const float arrowWidth = context.GetArrowWidth() * 1.15f;
        const SR_MATH_NS::FVector2 arrowButtonSize = { arrowWidth, context.fieldHeight };

        {
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(5, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button("", arrowButtonSize)) {
                m_isOpened = !m_isOpened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);
            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        if (!context.pValue || !context.GetPropertyDisplayName().empty()) {
            const SR_MATH_NS::FVector2 buttonSize = SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.75f - arrowButtonSize.x, context.fieldHeight);

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetPropertyDisplayName().c_str(), buttonSize)) {
                if (context.pProperty) {
                    if (context.onBeforeChangeCallback) {
                        context.onBeforeChangeCallback(false);
                    }
                    feedback.isChanged = true;
                    value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                    value = value.DetachIfConst();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        /// picking
        {
            if (SR_GRAPH_GUI_NS::Immediate::Button("...", SR_MATH_NS::FVector2(context.fieldTitleWidth * 0.25f, context.fieldHeight))) {
                auto&& filterName = context.GetEditorParams().GetCustomArg("filter name");
                auto&& filterValue = context.GetEditorParams().GetCustomArg("filter value");

                const bool relativeRes = context.GetEditorParams().GetCustomArg("relative") == "resources";

                if (!filterName.empty() && !filterValue.empty()) {
                    auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesPath, { { filterName, filterValue } });

                    if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
                        if (context.onBeforeChangeCallback) {
                            context.onBeforeChangeCallback(false);
                        }
                        feedback.isChanged = true;

                        if (relativeRes) {
                            path = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
                        }

                        pRef->SetResource(path.ToStringRef());
                    }
                }
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        if (auto&& pRef = dynamic_cast<SR_UTILS_NS::ResourceRefBase*>(value.GetSRClass())) {
            SR_UTILS_NS::StringAtom type = pRef->GetResourceType();

            if (pRef->GetId().empty()) {
                std::string formatted = " Is not set ({})"_format(type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                SR_GRAPH_GUI_NS::Immediate::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 1.f, 0.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }
            else if (!pRef->GetResourceBase()) {
                std::string formatted = " {} ({} is missing)"_format(pRef->GetId().ToCStr(), type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                SR_GRAPH_GUI_NS::Immediate::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
            }
            else {
                std::string formatted = " {} ({})"_format(pRef->GetId().ToCStr(), type.ToCStr());
                SR_GRAPH_GUI_NS::Immediate::BeginDisabled();
                SR_GRAPH_GUI_NS::Immediate::ButtonColoredText(formatted.c_str(), SR_MATH_NS::FColor(1.f, 1.f, 1.f, 1.f), SR_MATH_NS::FVector2(context.fieldWidth, 0));
                SR_GRAPH_GUI_NS::Immediate::EndDisabled();
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
                    SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(arrowWidth, 5.0f));
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
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

                SR_GRAPH_GUI_NS::Immediate::BeginGroup();
                PropertyDrawerFeedback propertyFeedback = m_objectDrawer->Draw(propertyContext);
                SR_GRAPH_GUI_NS::Immediate::EndGroup();

                if (propertyFeedback.isChanged) {
                    feedback.isChanged = true;
                }
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to map resource ref value!");
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SetValue(context, feedback, value);

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
