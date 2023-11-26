//
// Created by Monika on 04.06.2023.
//

#include <Graphics/Pass/IMeshClusterPass.h>

#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    bool IMeshClusterPass::Render() {
        SR_TRACY_ZONE;

        PrepareFBODependencies();

        return true;
    }

    void IMeshClusterPass::Update() {
        SR_TRACY_ZONE;
        BasePass::Update();
    }

    void IMeshClusterPass::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {
        pMesh->UseMaterial();
    }

    void IMeshClusterPass::UseSamplers(ShaderPtr pShader) {
        for (auto&& sampler : m_samplers) {
            if (sampler.textureId == SR_ID_INVALID) {
                continue;
            }

            pShader->SetSampler2D(sampler.id, sampler.textureId);
        }
    }

    MeshClusterTypeFlag IMeshClusterPass::GetClusterType() const noexcept {
        return m_meshClusters;
    }

    bool IMeshClusterPass::Load(const SR_XML_NS::Node& passNode) {
        m_meshClusters = static_cast<MeshClusterTypeFlag>(MeshClusterType::None);

        for (auto&& meshClusterNode : passNode.TryGetNode("MeshClusters").TryGetNodes()) {
            auto&& clusterType = SR_UTILS_NS::EnumReflector::FromString<MeshClusterType::MeshClusterTypeT>(meshClusterNode.Name());
            m_meshClusters |= static_cast<MeshClusterTypeFlag>(clusterType);
        }

        m_samplers.clear();

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

    void IMeshClusterPass::Prepare() {
        PrepareSamplers();
        Super::Prepare();
    }

    void IMeshClusterPass::UseSharedUniforms(IMeshClusterPass::ShaderPtr pShader) {
        /// определяется классом-наследником
        auto&& time = SR_HTYPES_NS::Time::Instance().Clock();
        pShader->SetFloat(SHADER_TIME, time);
    }

    void IMeshClusterPass::OnSamplesChanged() {
        m_dirtySamplers = true;
        m_needUpdateMeshes = true;
        Super::OnSamplesChanged();
    }

    void IMeshClusterPass::PrepareSamplers() {
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
            OnClusterDirty();
            m_needUpdateMeshes = false;
        }

        m_dirtySamplers = false;
    }

    void IMeshClusterPass::OnResize(const SR_MATH_NS::UVector2 &size) {
        m_dirtySamplers = true;
        m_needUpdateMeshes = true;
        Super::OnResize(size);
    }

    bool IMeshClusterPass::Init() {
        return Super::Init();
    }

    void IMeshClusterPass::UseConstants(IMeshClusterPass::ShaderPtr pShader) {
        pShader->SetConstInt(SHADER_COLOR_BUFFER_MODE, 0);
    }

    void IMeshClusterPass::PrepareFBODependencies() {

    }
}