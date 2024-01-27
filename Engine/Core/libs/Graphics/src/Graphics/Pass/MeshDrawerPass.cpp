//
// Created by Monika on 18.01.2024.
//

#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Pass/CascadedShadowMapPass.h>
#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Render/RenderStrategy.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Mesh.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(MeshDrawerPass)

    bool MeshDrawerPass::Load(const SR_XML_NS::Node& passNode) {
        m_samplers.clear();
        m_allowedLayers.clear();
        m_disallowedLayers.clear();

        ClearOverrideShaders();

        if (auto&& shaderOverrideNode = passNode.TryGetNode("Shaders")) {
            for (auto&& overrideNode : shaderOverrideNode.TryGetNodes("Override")) {
                auto&& shaderPath = overrideNode.TryGetAttribute("Shader").ToString(std::string());
                if (shaderPath.empty()) {
                    SR_ERROR("MeshDrawerPass::Load() : override shader is not set!");
                    continue;
                }

                if (auto&& shaderTypeAttribute = overrideNode.TryGetAttribute("Type")) {
                    auto&& shaderType = SR_UTILS_NS::EnumReflector::FromString<SR_SRSL_NS::ShaderType>(shaderTypeAttribute.ToString());
                    if (m_shaderTypeReplacements[shaderType]) {
                        SRHalt("Shader is already set!");
                        continue;
                    }

                    if (auto&& pShader = SR_GTYPES_NS::Shader::Load(shaderPath)) {
                        pShader->AddUsePoint();
                        m_shaderTypeReplacements[shaderType] = pShader;
                    }
                }
                else if (auto&& shaderPathAttribute = overrideNode.TryGetAttribute("Path")) {
                    bool found = false;
                    for (auto&& [pShaderKey, pShader] : m_shaderReplacements) {
                        if (shaderPathAttribute.ToString() == pShaderKey->GetResourcePath()) {
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        SRHalt("Shader is already set!");
                        continue;
                    }

                    auto&& pShader = SR_GTYPES_NS::Shader::Load(shaderPath);
                    if (pShader) {
                        pShader->AddUsePoint();
                    }

                    auto&& pKeyShader = SR_GTYPES_NS::Shader::Load(shaderPathAttribute.ToString());
                    if (pKeyShader) {
                        pKeyShader->AddUsePoint();
                    }
                    else {
                        pShader->RemoveUsePoint();
                        continue;
                    }

                    m_shaderReplacements[pKeyShader] = pShader;
                }
            }
        }

        if (auto&& allowedLayersNode = passNode.TryGetNode("AllowedLayers")) {
            for (auto&& layerNode : allowedLayersNode.TryGetNodes()) {
                m_allowedLayers.insert(SR_UTILS_NS::StringAtom(layerNode.NameView()));
            }
        }

        if (auto&& allowedLayersNode = passNode.TryGetNode("DisallowedLayers")) {
            for (auto&& layerNode : allowedLayersNode.TryGetNodes()) {
                m_disallowedLayers.insert(SR_UTILS_NS::StringAtom(layerNode.NameView()));
            }
        }

        m_useMaterials = passNode.TryGetAttribute("UseMaterials").ToBool(true);

        for (auto&& samplerNode : passNode.TryGetNodes("Sampler")) {
            Sampler sampler = Sampler();

            if (auto&& idNode = samplerNode.TryGetAttribute("Id")) {
                sampler.id = idNode.ToString();
            }
            else {
                continue;
            }

            if (auto&& fboNameNode = samplerNode.TryGetAttribute("FBO")) {
                sampler.fboName = fboNameNode.ToString();

                if (auto&& depthAttribute = samplerNode.TryGetAttribute("Depth")) {
                    sampler.depth = depthAttribute.ToBool();
                }

                if (!sampler.depth) {
                    sampler.index = samplerNode.TryGetAttribute("Index").ToUInt64(-1);
                }
            }

            m_samplers.emplace_back(sampler);
        }

        return Super::Load(passNode);
    }

    bool MeshDrawerPass::IsLayerAllowed(SR_UTILS_NS::StringAtom layer) const {
        if (m_allowedLayers.empty()) {
            if (m_disallowedLayers.empty()) {
                return true;
            }
            return m_disallowedLayers.count(layer) == 0;
        }
        else if (m_allowedLayers.count(layer) == 1) {
            return true;
        }

        if (m_disallowedLayers.empty()) {
            return m_allowedLayers.count(layer) == 1;
        }

        return m_disallowedLayers.count(layer) == 0;
    }

    bool MeshDrawerPass::Render() {
        return (m_passWasRendered = GetRenderStrategy()->Render());
    }

    void MeshDrawerPass::Prepare() {
        PrepareSamplers();
        Super::Prepare();
    }

    void MeshDrawerPass::Update() {
        if (m_passWasRendered) {
            GetRenderStrategy()->Update();
        }
    }

    void MeshDrawerPass::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {
        if (IsNeedUseMaterials()) {
            pMesh->UseMaterial();
        }
    }

    void MeshDrawerPass::UseSharedUniforms(ShaderPtr pShader) {
        SR_TRACY_ZONE;

        pShader->SetFloat(SHADER_TIME, SR_HTYPES_NS::Time::Instance().Clock());

        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());
        }

        const SR_MATH_NS::FVector3 lightPos = GetRenderScene()->GetLightSystem()->GetDirectionalLightPosition();
        pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);

        if (m_shadowMapPass) {
            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, m_shadowMapPass->GetLightSpaceMatrix());
        }
        else if (m_cascadedShadowMapPass) {
            pShader->SetValue<false>(SHADER_CASCADE_LIGHT_SPACE_MATRICES, m_cascadedShadowMapPass->GetCascadeMatrices().data());
            pShader->SetValue<false>(SHADER_CASCADE_SPLITS, m_cascadedShadowMapPass->GetSplitDepths().data());
        }
    }

    void MeshDrawerPass::UseConstants(ShaderPtr pShader) {
        pShader->SetConstInt(SHADER_COLOR_BUFFER_MODE, 0);
    }

    void MeshDrawerPass::UseSamplers(ShaderPtr pShader) {
        for (auto&& sampler : m_samplers) {
            if (sampler.textureId == SR_ID_INVALID) {
                continue;
            }

            pShader->SetSampler2D(sampler.id, sampler.textureId);
        }
    }

    void MeshDrawerPass::Bind() {
        SR_TRACY_ZONE;

        auto&& pStrategy = GetRenderStrategy();

        pStrategy->BindFilterCallback([this](auto&& layer) { return IsLayerAllowed(layer); });
        pStrategy->BindShaderReplaceCallback([this](auto&& pShader) { return ReplaceShader(pShader); });
        pStrategy->BindSharedUniformsCallback([this](auto&& pShader) { UseSharedUniforms(pShader); });
        pStrategy->BindUniformsCallback([this](auto&& pShader, auto&& pMesh) { UseUniforms(pShader, pMesh); });
        pStrategy->BindConstantsCallback([this](auto&& pShader) { UseConstants(pShader); });
        pStrategy->BindSamplersCallback([this](auto&& pShader) { UseSamplers(pShader); });

        Super::Bind();
    }

    RenderStrategy* MeshDrawerPass::GetRenderStrategy() const {
        return GetRenderScene()->GetRenderStrategy();
    }

    BasePass::ShaderPtr MeshDrawerPass::ReplaceShader(ShaderPtr pShader) const {
        SR_TRACY_ZONE;

        if (!pShader) {
            return nullptr;
        }

        if (m_shaderReplacements.empty() && m_shaderTypeReplacements.empty()) {
            return pShader;
        }

        if (auto&& pIt = m_shaderReplacements.find(pShader); pIt != m_shaderReplacements.end()) {
            return pIt->second;
        }

        if (auto&& pIt = m_shaderTypeReplacements.find(pShader->GetType()); pIt != m_shaderTypeReplacements.end()) {
            return pIt->second;
        }

        return pShader;
    }

    void MeshDrawerPass::OnResize(const SR_MATH_NS::UVector2& size) {
        m_dirtySamplers = true;
        m_needUpdateMeshes = true;
        Super::OnResize(size);
    }

    void MeshDrawerPass::OnSamplesChanged() {
        m_dirtySamplers = true;
        m_needUpdateMeshes = true;
        Super::OnSamplesChanged();
    }

    void MeshDrawerPass::PrepareSamplers() {
        if (!m_dirtySamplers) {
            return;
        }

        SR_TRACY_ZONE;

        for (auto&& sampler : m_samplers) {
            int32_t textureId = SR_ID_INVALID;

            sampler.fboId = SR_ID_INVALID;

            if (!sampler.fboName.Empty()) {
                auto&& pFBOPass = dynamic_cast<IFramebufferPass*>(GetTechnique()->FindPass(sampler.fboName));
                if (pFBOPass && pFBOPass->GetFramebuffer()) {
                    auto&& pFBO = pFBOPass->GetFramebuffer();

                    sampler.fboId = pFBO->GetId();

                    if (sampler.depth) {
                        textureId = pFBO->GetDepthTexture();
                    }
                    else {
                        textureId = pFBO->GetColorTexture(sampler.index);
                    }
                }
            }

            if (textureId == SR_ID_INVALID && !sampler.depth) {
                textureId = GetContext()->GetDefaultTexture()->GetId();
            }

            if (textureId != sampler.textureId) {
                m_needUpdateMeshes = true;
                sampler.textureId = textureId;
            }
        }

        if (m_needUpdateMeshes && !m_samplers.empty()) {
            GetRenderStrategy()->ForEachMesh([](auto&& pMesh) {
               pMesh->MarkMaterialDirty();
            });
            m_needUpdateMeshes = false;
        }

        m_dirtySamplers = false;
    }

    void MeshDrawerPass::ClearOverrideShaders() {
        for (auto&& [type, pShader] : m_shaderTypeReplacements) {
            pShader->RemoveUsePoint();
        }
        m_shaderTypeReplacements.clear();

        for (auto&& [pShaderKey, pShader] : m_shaderReplacements) {
            pShaderKey->RemoveUsePoint();
            pShader->RemoveUsePoint();
        }
        m_shaderReplacements.clear();
    }

    void MeshDrawerPass::DeInit() {
        ClearOverrideShaders();
        Super::DeInit();
    }

    bool MeshDrawerPass::Init() {
        m_shadowMapPass = GetTechnique()->FindPass<ShadowMapPass>();
        m_cascadedShadowMapPass = GetTechnique()->FindPass<CascadedShadowMapPass>();
        return Super::Init();
    }
}