//
// Created by Monika on 13.02.2025.
//

#include <Core/GUI/PropertyDrawers/MaterialDataPropertyDrawer.h>

#include <Enum/ImageAspect.hpp>
#include <Enum/ImageFormat.hpp>
#include <Enum/TextureFilter.hpp>
#include <Enum/TextureCompression.hpp>
#include <Enum/BoolExt.hpp>
#include <Enum/ShaderVarType.hpp>

#include <Codegen/MaterialDataPropertyDrawer.generated.hpp>

namespace SR_CORE_GUI_NS {
    MaterialDataPropertyDrawer::MaterialDataPropertyDrawer()
        : Super()
    {
        m_vectorDrawer = SRNew<MathVectorPropertyDrawer>();
        m_numericDrawer = SRNew<NumericPropertyDrawer>();
        m_boolDrawer = SRNew<BoolPropertyDrawer>();
        m_pathDrawer = SRNew<PathPropertyDrawer>();
        m_shaderDataOpened["Default"] = true;
    }

    PropertyDrawerFeedback MaterialDataPropertyDrawer::DrawCustomProperties(const PropertyDrawerContext& context) {
        PropertyDrawerFeedback feedback;

        ImGui::PushID(context.pOwner);

        m_stagesToRemove.clear();

        SR_GRAPH_NS::MaterialData& materialData = *static_cast<SR_GRAPH_NS::MaterialData*>(context.pOwner);

        feedback.isChanged |= DrawShaderData(true, "Default", materialData.GetDefaultShaderData(), context);

        for (auto&& [stage, data] : materialData.GetShadersData()) {
            feedback.isChanged |= DrawShaderData(false, stage, data, context);
        }

        for (auto&& stage : m_stagesToRemove) {
            materialData.RemoveStage(stage);
        }

        ImGui::PopID();

        return feedback;
    }

    bool MaterialDataPropertyDrawer::DrawShaderData(bool isDefault, SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context) {
        bool isChanged = false;

        ImGui::PushID(&shaderData);
        ImGui::PushID(name.c_str());

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
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(isDefault);
            if (ImGui::Button("Delete", removeButtonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                isChanged = true;
                m_stagesToRemove.insert(name);
            }
        }

        if (opened) {
            ImGui::Dummy(ImVec2(context.GetArrowWidth(), 0));
            ImGui::SameLine();
            ImGui::BeginGroup();

            isChanged |= DrawShaderPath(name, shaderData, context);

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
        ImGui::PopID();

        return isChanged;
    }

    bool MaterialDataPropertyDrawer::DrawShaderProperty(SR_GRAPH_NS::MaterialShaderData& shaderData, SR_GRAPH_NS::MaterialShaderProperty& property, const PropertyDrawerContext& context) {
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
            if (context.onBeforeChangeCallback) {
                context.onBeforeChangeCallback(false);
            }
            wasReset = true;
            shaderData.SetData(property.id, SR_GRAPH_NS::GetVariantFromShaderVarType(property.type), property.type);
        }

        switch (property.type) {
            case SR_GRAPH_NS::ShaderVarType::Vec2:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<SR_MATH_NS::FVector2>(property.data));
                feedback = m_vectorDrawer->Draw(propertyContext);
                break;
            case SR_GRAPH_NS::ShaderVarType::Vec3:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<SR_MATH_NS::FVector3>(property.data));
                feedback = m_vectorDrawer->Draw(propertyContext);
                break;
            case SR_GRAPH_NS::ShaderVarType::Vec4:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<SR_MATH_NS::FVector4>(property.data));
                feedback = m_vectorDrawer->Draw(propertyContext);
                break;
            case SR_GRAPH_NS::ShaderVarType::Int:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<int32_t>(property.data));
                feedback = m_numericDrawer->Draw(propertyContext);
                break;
            case SR_GRAPH_NS::ShaderVarType::Float:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<float_t>(property.data));
                feedback = m_numericDrawer->Draw(propertyContext);
                break;
            case SR_GRAPH_NS::ShaderVarType::Bool: {
                ImGui::SameLine();
                bool boolean = std::get<int32_t>(property.data) != 0;
                value = SR_UTILS_NS::Reflection::Value::CreateRef(boolean);
                feedback = m_boolDrawer->Draw(propertyContext);
                std::get<int32_t>(property.data) = boolean ? 1 : 0;
                break;
            }
            case SR_GRAPH_NS::ShaderVarType::Sampler2D: {
                ImGui::SameLine();
                SR_UTILS_NS::Path path;
                if (auto&& pTexture = std::get<SR_GTYPES_NS::Texture*>(property.data)) {
                    path = pTexture->GetResourcePath();
                }
                value = SR_UTILS_NS::Reflection::Value::CreateRef(path);
                feedback = m_pathDrawer->Draw(propertyContext);
                if (feedback.isChanged) {
                    auto&& pTexture = SR_GTYPES_NS::Texture::Load(path);
                    shaderData.SetData(property.id, pTexture, SR_GRAPH_NS::ShaderVarType::Sampler2D);
                }

                auto&& pTexture = std::get<SR_GTYPES_NS::Texture*>(property.data);
                if (void* pDescriptor = pTexture ? pTexture->GetDescriptor() : nullptr) {
                    const float_t imageSize = context.lineHeight * 2.5f;

                    SR_GRAPH_GUI_NS::ImageButton((void*)pDescriptor, SR_MATH_NS::FVector2(imageSize), 0.25f * context.lineHeight));

                    ImGui::SameLine();

                    const SR_GRAPH_NS::Memory::TextureConfig& config = pTexture->GetTextureConfig();

                    ImGui::BeginGroup();

                    ImGui::Text("%s", "Size: {}x{}\nChannels: {}\nFormat: {}\nFilter: {}"_format(
                        pTexture->GetWidth(),
                        pTexture->GetHeight(),
                        pTexture->GetChannels(),
                        config.GetFormat(),
                        config.GetFilter()).c_str()
                    );

                    ImGui::EndGroup();

                    ImGui::SameLine();
                    ImGui::Dummy(ImVec2(context.lineHeight, 0));
                    ImGui::SameLine();

                    ImGui::BeginGroup();

                    ImGui::Text("%s", "Compression: {}\nMipLevels: {}\nCpuUsage: {}\nAlpha: {}"_format(
                        config.GetCompression(),
                        config.GetMipLevels(),
                        config.GetCpuUsage(),
                        config.GetAlpha()).c_str()
                    );

                    ImGui::EndGroup();
                }

                break;
            }
            default:
                ImGui::SameLine();
                SR_GRAPH_GUI_NS::ColoredText("Unsupported type! Type: {}"_format(property.type), ImColor(255, 0, 0));
                return false;
        }

        if (feedback.isChanged || wasReset) {
            const bool onlyUniforms = !SR_GRAPH_NS::IsSamplerType(property.type);
            shaderData.pOwnedMaterialData->OnPropertyChanged(onlyUniforms);
            return true;
        }

        return false;
    }

    bool MaterialDataPropertyDrawer::DrawShaderPath(SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context) {
        SR_UTILS_NS::Path shaderPath = shaderData.pShader ? shaderData.pShader->GetResourcePath() : SR_UTILS_NS::Path();

        SR_UTILS_NS::Reflection::Value value = SR_UTILS_NS::Reflection::Value::CreateRef(shaderPath);

        PropertyDrawerContext propertyContext = context;
        propertyContext.pProperty = nullptr;
        propertyContext.pValue = &value;
        float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth) - context.GetArrowWidth();
        propertyContext.fieldWidth = totalWidth * 0.75f;
        propertyContext.fieldTitleWidth = totalWidth * 0.25f;
        propertyContext.customDisplayName = "Shader";

        const PropertyDrawerFeedback feedback = m_pathDrawer->Draw(propertyContext);

        if (feedback.isChanged) {
            SR_GRAPH_NS::MaterialData& materialData = *static_cast<SR_GRAPH_NS::MaterialData*>(context.pOwner);
            materialData.SetShader(shaderPath, name);
            return true;
        }

        return false;
    }
}
