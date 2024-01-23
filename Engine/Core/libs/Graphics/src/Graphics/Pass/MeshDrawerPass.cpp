//
// Created by Monika on 18.01.2024.
//

#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Render/RenderStrategy.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Pass/IFramebufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(MeshDrawerPass)

    bool MeshDrawerPass::Load(const SR_XML_NS::Node& passNode) {
        m_samplers.clear();
        m_allowedLayers.clear();
        m_disallowedLayers.clear();

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
        if (m_useMaterials) {
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

        if (m_shaderReplacements.empty()) {
            return pShader;
        }

        if (auto&& pIt = m_shaderReplacements.find(pShader); pIt != m_shaderReplacements.end()) {
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

            if (textureId == SR_ID_INVALID) {
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
}