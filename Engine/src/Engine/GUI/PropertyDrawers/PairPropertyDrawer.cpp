//
// Created by Monika on 13.02.2025.
//

#include <Engine/GUI/PropertyDrawers/PairPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PropertyDrawerUtils.h>

#include <ImmediateGUI/GUI/ImmediateGUI.h>

#include <Codegen/PairPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback PairPropertyDrawer::Draw(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        if (!m_firstValue) {
            m_firstValue = new SR_UTILS_NS::Reflection::Value();
        }
        if (!m_secondValue) {
            m_secondValue = new SR_UTILS_NS::Reflection::Value();
        }

        SR_UTILS_NS::Reflection::Value value = context.GetValue();

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pUID);
        SR_GRAPH_GUI_NS::Immediate::PushID(context.GetProperty().GetName().c_str());

        SR_GRAPH_GUI_NS::Immediate::PushStyleVar(SR_GRAPH_GUI_NS::Immediate::StyleVar::ItemSpacing, SR_MATH_NS::FVector2());

        if (!context.pValue) {
            const SR_MATH_NS::FVector2 buttonSize = { context.fieldTitleWidth, context.fieldHeight };

            if (SR_GRAPH_GUI_NS::Immediate::Button(context.GetProperty().GetDisplayName().c_str(), buttonSize)) {
                value = context.GetProperty().GetResetValue() ? context.GetProperty().GetResetValue() : context.GetProperty().GetDefaultValue();
                value = value.Copy();
                SetReflectedValue(context, feedback, value);
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
        }

        SR_GRAPH_GUI_NS::Immediate::PushItemWidth(context.fieldWidth);

        if (!m_firstDrawer) {
            *m_firstValue = SR_UTILS_NS::Reflection::Value::CreateDefault(value.GetTypeInfo().pNext[0]);
            SR_UTILS_NS::StringAtom inspectorName = GetValueInspector(*m_firstValue);
            m_firstDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspectorName);
        }

        if (!m_secondDrawer) {
            *m_secondValue = SR_UTILS_NS::Reflection::Value::CreateDefault(value.GetTypeInfo().pNext[1]);
            SR_UTILS_NS::StringAtom inspectorName = GetValueInspector(*m_secondValue);
            m_secondDrawer = SR_UTILS_NS::Factory::Instance().Create<PropertyDrawerBase>(inspectorName);
        }

        SR_GRAPH_GUI_NS::Immediate::PopItemWidth();

        SR_GRAPH_GUI_NS::Immediate::PopStyleVar();

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }
}
