//
// Created by Monika on 13.02.2025.
//

#include <Engine/GUI/PropertyDrawers/MaterialDataPropertyDrawer.h>

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

        SR_GRAPH_GUI_NS::Immediate::PushID(context.pOwner);

        m_stagesToRemove.clear();

        SR_GRAPH_NS::MaterialData& materialData = *static_cast<SR_GRAPH_NS::MaterialData*>(context.pOwner);

        if ((!context.pProperty || !context.pProperty->IsReadOnly()) && !SR_GRAPH_GUI_NS::Immediate::IsCurrentlyDisabled()) {
            const float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
            const float_t addStageWidth = totalWidth / 4.f;

            if (SR_GRAPH_GUI_NS::Immediate::Button("Add Stage", {SR_MAX(addStageWidth, 0), context.fieldHeight})) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                feedback.isChanged = true;
                if (!m_newStageName.empty() && !materialData.HasStage(m_newStageName)) {
                    materialData.AddStage(m_newStageName);
                }
            }

            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::PushItemWidth(totalWidth - addStageWidth);
            SR_GRAPH_GUI_NS::Immediate::InputText("#Stage Name", &m_newStageName);
            SR_GRAPH_GUI_NS::Immediate::PopItemWidth();
        }

        feedback.isChanged |= DrawShaderData(true, "Default", materialData.GetDefaultShaderData(), context);

        for (auto&& [stage, data] : materialData.GetShadersData()) {
            feedback.isChanged |= DrawShaderData(false, stage, data, context);
        }

        for (auto&& stage : m_stagesToRemove) {
            materialData.RemoveStage(stage);
        }

        SR_GRAPH_GUI_NS::Immediate::PopID();

        return feedback;
    }

    bool MaterialDataPropertyDrawer::DrawShaderData(bool isDefault, SR_UTILS_NS::StringAtom name, SR_GRAPH_NS::MaterialShaderData& shaderData, const PropertyDrawerContext& context) {
        bool isChanged = false;

        SR_GRAPH_GUI_NS::Immediate::PushID(&shaderData);
        SR_GRAPH_GUI_NS::Immediate::PushID(name.c_str());

        bool& opened = m_shaderDataOpened[name];

        {
            auto&& pWindow = SR_GRAPH_GUI_NS::Immediate::GetCurrentWindow();
            auto&& pDrawList = SR_GRAPH_GUI_NS::Immediate::GetWindowDrawList(pWindow);
            auto&& cursorPos = SR_GRAPH_GUI_NS::Immediate::GetWindowCursorPos(pWindow);

            const auto dir = opened ? SR_GRAPH_GUI_NS::Immediate::Direction::Down : SR_GRAPH_GUI_NS::Immediate::Direction::Right;
            const SR_MATH_NS::FVector2 arrowPos = cursorPos + SR_MATH_NS::FVector2(1, 5);
            SR_GRAPH_GUI_NS::Immediate::RenderArrow(pDrawList, arrowPos, SR_GRAPH_GUI_NS::Immediate::GetColorU32(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text), dir, 1.f);

            //SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 0));
            //SR_GRAPH_GUI_NS::Immediate::SameLine();

            //const float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth) - context.GetArrowWidth();
            const float_t totalWidth = (context.fieldWidth + context.fieldTitleWidth);
            const float_t removeWidth = SR_MAX(context.lineHeight * 2.5f, 0);

            const SR_MATH_NS::FVector2 mainButtonSize = { SR_MAX(totalWidth - removeWidth, 0), context.fieldHeight };

            auto&& stackSize = SR_GRAPH_GUI_NS::Immediate::BeginForceEnabled();
            if (SR_GRAPH_GUI_NS::Immediate::Button(name.c_str(), mainButtonSize)) {
                opened = !opened;
            }
            SR_GRAPH_GUI_NS::Immediate::EndForceEnabled(stackSize);

            SR_GRAPH_GUI_NS::Immediate::SameLine();

            const SR_MATH_NS::FVector2 removeButtonSize = { SR_MAX(removeWidth, 0), context.fieldHeight };
            SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(isDefault);
            if (SR_GRAPH_GUI_NS::Immediate::Button("Delete", removeButtonSize)) {
                if (context.onBeforeChangeCallback) {
                    context.onBeforeChangeCallback(false);
                }
                isChanged = true;
                m_stagesToRemove.insert(name);
            }
        }

        if (opened) {
            SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.GetArrowWidth(), 0));
            SR_GRAPH_GUI_NS::Immediate::SameLine();
            SR_GRAPH_GUI_NS::Immediate::BeginGroup();

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

                SR_GRAPH_GUI_NS::Immediate::PushID(i);
                isChanged |= DrawShaderProperty(shaderData, *pProperty, context);
                SR_GRAPH_GUI_NS::Immediate::PopID();
            }

            SR_GRAPH_GUI_NS::Immediate::EndGroup();
        }

        SR_GRAPH_GUI_NS::Immediate::PopID();
        SR_GRAPH_GUI_NS::Immediate::PopID();

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

        const SR_MATH_NS::FVector2 propertyButtonSize = { SR_MAX(propertyContext.fieldWidth * 0.25f, 0), context.fieldHeight };

        propertyContext.fieldWidth -= propertyButtonSize.x;

        if (SR_GRAPH_GUI_NS::Immediate::Button(property.displayName.c_str(), propertyButtonSize)) {
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
            case SR_GRAPH_NS::ShaderVarType::IVec3:
                value = SR_UTILS_NS::Reflection::Value::CreateRef(std::get<SR_MATH_NS::IVector3>(property.data));
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
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                bool boolean = std::get<int32_t>(property.data) != 0;
                value = SR_UTILS_NS::Reflection::Value::CreateRef(boolean);
                feedback = m_boolDrawer->Draw(propertyContext);
                std::get<int32_t>(property.data) = boolean ? 1 : 0;
                break;
            }
            case SR_GRAPH_NS::ShaderVarType::Sampler2D: {
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_UTILS_NS::Path path;
                if (auto&& pTexture = std::get<SR_GTYPES_NS::Texture::Ptr>(property.data)) {
                    path = pTexture->GetResourcePath();
                }
                value = SR_UTILS_NS::Reflection::Value::CreateRef(path);
                feedback = m_pathDrawer->Draw(propertyContext);
                if (feedback.isChanged) {
                    auto&& pTexture = SR_GTYPES_NS::Texture::Load(path);
                    shaderData.SetData(property.id, pTexture, SR_GRAPH_NS::ShaderVarType::Sampler2D);
                }

                auto&& pTexture = std::get<SR_GTYPES_NS::Texture::Ptr>(property.data);
                if (void* pDescriptor = pTexture ? pTexture->GetDescriptor() : nullptr) {
                    const float_t imageSize = context.lineHeight * 2.5f;

                    SR_GRAPH_GUI_NS::Immediate::ImageButton((void*)pDescriptor, SR_MATH_NS::FVector2(imageSize), 0.25f * context.lineHeight);

                    SR_GRAPH_GUI_NS::Immediate::SameLine();

                    const SR_GRAPH_NS::Memory::TextureConfig& config = pTexture->GetTextureConfig();

                    SR_GRAPH_GUI_NS::Immediate::BeginGroup();

                    SR_GRAPH_GUI_NS::Immediate::Text("%s", "Size: {}x{}\nChannels: {}\nFormat: {}\nFilter: {}"_format(
                        pTexture->GetWidth(),
                        pTexture->GetHeight(),
                        pTexture->GetChannels(),
                        config.GetFormat(),
                        config.GetFilter()).c_str()
                    );

                    SR_GRAPH_GUI_NS::Immediate::EndGroup();

                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                    SR_GRAPH_GUI_NS::Immediate::Dummy(SR_MATH_NS::FVector2(context.lineHeight, 0));
                    SR_GRAPH_GUI_NS::Immediate::SameLine();

                    SR_GRAPH_GUI_NS::Immediate::BeginGroup();

                    SR_GRAPH_GUI_NS::Immediate::Text("%s", "Compression: {}\nMipLevels: {}\nCpuUsage: {}\nAlpha: {}"_format(
                        config.GetCompression(),
                        config.GetMipLevels(),
                        config.GetCpuUsage(),
                        config.GetAlpha()).c_str()
                    );

                    SR_GRAPH_GUI_NS::Immediate::EndGroup();
                }

                break;
            }
            default: {
                SR_GRAPH_GUI_NS::Immediate::SameLine();
                auto&& msg = "Unsupported type! Type: {}"_format(property.type);
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f), msg.c_str());
                return false;
            }
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
