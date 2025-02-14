//
// Created by Monika on 13.02.2025.
//

#include <Core/GUI/PropertyDrawers/MaterialDataPropertyDrawer.h>

#include <Codegen/MaterialDataPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    PropertyDrawerFeedback MaterialDataPropertyDrawer::DrawCustomProperties(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        ImGui::PushID(context.pOwner);

        m_stagesToRemove.clear();

        SR_GRAPH_NS::MaterialData& materialData = *static_cast<SR_GRAPH_NS::MaterialData*>(context.pOwner);

        feedback.isChanged |= DrawShaderData("Default", materialData.GetDefaultShaderData(), context);

        for (auto&& [stage, data] : materialData.GetShadersData()) {
            feedback.isChanged |= DrawShaderData(stage, data, context);
        }

        for (auto&& stage : m_stagesToRemove) {
            materialData.RemoveStage(stage);
        }

        ImGui::PopID();

        return feedback;
    }

    bool MaterialDataPropertyDrawer::DrawShaderData(SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context) {
        bool isChanged = false;

        ImGui::PushID(&shaderData);

        static const SR_UTILS_NS::StringAtom defaultName = "Default";

        if (m_shaderDataOpened.count(defaultName) == 0) {
            m_shaderDataOpened[name] = true;
        }

        bool& opened = m_shaderDataOpened[name];

        {
            auto&& pWindow = ImGui::GetCurrentWindow();

            const ImGuiDir_ dir = opened ? ImGuiDir_Down : ImGuiDir_Right;
            const ImVec2 arrowPos = pWindow->DC.CursorPos + ImVec2(0, 5);
            ImGui::RenderArrow(pWindow->DrawList, arrowPos, ImGui::GetColorU32(ImGuiCol_Text), dir, 1.f);

            ImGui::Dummy(ImVec2(context.GetArrowWidth(), 0));

            ImGui::SameLine();

            const float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth) - context.GetArrowWidth();
            const float_t removeWidth = SR_MAX(context.lineHeight * 2.5f, 0);

            const ImVec2 mainButtonSize = { SR_MAX(totalWidth - removeWidth, 0), context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::BeginForceEnabled();
            if (ImGui::Button(name.c_str(), mainButtonSize)) {
                opened = !opened;
            }
            SR_GRAPH_GUI_NS::EndForceEnabled(stackSize);

            ImGui::SameLine();

            const ImVec2 removeButtonSize = { SR_MAX(removeWidth, 0), context.fieldHeight };
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(name == defaultName);
            if (ImGui::Button("Delete", removeButtonSize)) {
                isChanged = true;
                m_stagesToRemove.insert(name);
            }
        }

        if (opened) {
            ImGui::Dummy(ImVec2(context.GetArrowWidth(), 0));
            ImGui::SameLine();
            ImGui::BeginGroup();

            uint32_t editorOrder = 0;

            for (uint32_t i = 0; i < shaderData.uniforms.size() + shaderData.samplers.size(); ++i) {
                SR_GRAPH_NS::MaterialShaderProperty* pProperty = nullptr;
                for (auto&& property : shaderData.uniforms) {
                    if (property.editorOrder == editorOrder) {
                        pProperty = &property;
                        break;
                    }
                }

                if (!pProperty) {
                    for (auto&& property : shaderData.samplers) {
                        if (property.editorOrder == editorOrder) {
                            pProperty = &property;
                            break;
                        }
                    }
                }

                ++editorOrder;

                if (!pProperty) {
                    SRHaltOnce("Invalid editor order!");
                    continue;
                }

                ImGui::PushID(i);
                isChanged |= DrawShaderProperty(shaderData, *pProperty, context);
                ImGui::PopID();
            }

            ImGui::EndGroup();
        }

        ImGui::PopID();

        return isChanged;
    }

    bool MaterialDataPropertyDrawer::DrawShaderProperty(SR_GRAPH_NS::MaterialShaderData& shaderData, SR_GRAPH_NS::MaterialShaderProperty& property, const PropertyDrawerContext& context) {
        if (!m_vectorDrawer) {
            m_vectorDrawer = SRNew<MathVectorPropertyDrawer>();
        }

        PropertyDrawerFeedback feedback;
        bool wasReset = false;
        SR_UTILS_NS::Reflection::Value value;

        PropertyDrawerContext propertyContext = context;
        propertyContext.pProperty = nullptr;
        propertyContext.pValue = &value;
        propertyContext.noHeader = false;
        propertyContext.maxPartsInLine = 4;
        propertyContext.fieldWidth += context.fieldTitleWidth;
        propertyContext.fieldWidth -= context.GetArrowWidth();
        propertyContext.fieldTitleWidth = 0.f;

        const ImVec2 propertyButtonSize = { SR_MAX(propertyContext.fieldWidth * 0.25f, 0), context.fieldHeight };

        propertyContext.fieldWidth -= propertyButtonSize.x;

        if (ImGui::Button(property.displayName.c_str(), propertyButtonSize)) {
            wasReset = true;
            shaderData.SetData(property.id, SR_GRAPH_NS::GetVariantFromShaderVarType(property.type), property.type);
        }

        switch (property.type) {
            case SR_GRAPH_NS::ShaderVarType::Vec4: {
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<SR_MATH_NS::FVector4>(property.data));
                feedback = m_vectorDrawer->Draw(propertyContext);
                break;
            }
            default:
                //SRHaltOnce("Invalid shader property type!");
                return false;
        }

        return feedback.isChanged || wasReset;
    }
}
