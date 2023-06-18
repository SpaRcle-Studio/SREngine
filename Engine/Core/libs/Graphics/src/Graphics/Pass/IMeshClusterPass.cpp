//
// Created by Monika on 04.06.2023.
//

#include <Graphics/Pass/IMeshClusterPass.h>

#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    IMeshClusterPass::IMeshClusterPass(RenderTechnique* pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    bool IMeshClusterPass::Render() {
        SR_TRACY_ZONE;

        bool rendered = false;

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Opaque)) {
            rendered |= RenderCluster(GetRenderScene()->GetOpaque());
        }

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Transparent)) {
            rendered |= RenderCluster(GetRenderScene()->GetTransparent());
        }

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Debug)) {
            rendered |= RenderCluster(GetRenderScene()->GetDebugCluster());
        }

        return rendered;
    }

    void IMeshClusterPass::Update() {
        SR_TRACY_ZONE;

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Opaque)) {
            UpdateCluster(GetRenderScene()->GetOpaque());
        }

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Transparent)) {
            UpdateCluster(GetRenderScene()->GetTransparent());
        }

        if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Debug)) {
            UpdateCluster(GetRenderScene()->GetDebugCluster());
        }

        BasePass::Update();
    }

    void IMeshClusterPass::UpdateCluster(MeshCluster& meshCluster) {
        SR_TRACY_ZONE;

        auto&& time = SR_HTYPES_NS::Time::Instance().Clock();

        for (auto const& [pClusterShader, subCluster] : meshCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader) {
                pShader = pClusterShader;
            }

            if (!pShader || !pShader->Ready()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

            pShader->SetFloat(SHADER_TIME, time);
            UseSharedUniforms(pShader);

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto& pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    UseUniforms(pShader, pMesh);

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("IMeshClusterPass::UpdateCluster() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }

            m_context->SetCurrentShader(nullptr);
        }
    }

    bool IMeshClusterPass::RenderCluster(MeshCluster& meshCluster) {
        SR_TRACY_ZONE;

        if (meshCluster.Empty()) {
            return false;
        }

        for (auto&& [pClusterShader, subCluster] : meshCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader) {
                pShader = pClusterShader;
            }

            if (!pShader) {
                continue;
            }

            if (pShader->Use() == ShaderBindResult::Failed) {
                continue;
            }

            UseSamplers(pShader);

            for (auto&& [key, meshGroup] : subCluster) {
                (*meshGroup.begin())->BindMesh();

                for (auto&& pMesh : meshGroup) {
                    pMesh->Draw();
                }
            }

            pShader->UnUse();
        }

        return true;
    }

    void IMeshClusterPass::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {
        pMesh->UseMaterial();
    }

    void IMeshClusterPass::UseSamplers(ShaderPtr pShader) {
        for (auto&& sampler : m_samplers) {
            if (sampler.textureId == SR_ID_INVALID) {
                continue;
            }

            pShader->SetSampler2D(sampler.hashId, sampler.textureId);
        }
    }

    MeshClusterTypeFlag IMeshClusterPass::GetClusterType() const noexcept {
        return m_meshClusters;
    }

    bool IMeshClusterPass::Load(const SR_XML_NS::Node& passNode) {
        m_meshClusters = static_cast<MeshClusterTypeFlag>(MeshClusterType::None);

        for (auto&& meshClusterNode : passNode.TryGetNode("MeshClusters").TryGetNodes()) {
            auto&& clusterType = SR_UTILS_NS::EnumReflector::FromString<MeshClusterType>(meshClusterNode.Name());
            m_meshClusters |= static_cast<MeshClusterTypeFlag>(clusterType);
        }

        m_samplers.clear();

        for (auto&& samplerNode : passNode.TryGetNodes("Sampler")) {
            Sampler sampler = Sampler();

            if (auto&& idNode = samplerNode.TryGetAttribute("Id")) {
                sampler.hashId = SR_RUNTIME_TIME_CRC32_STD_STR(idNode.ToString());
            }
            else {
                continue;
            }

            if (auto&& fboNameNode = samplerNode.TryGetAttribute("FBO")) {
                sampler.fboHashName = SR_HASH_STR(fboNameNode.ToString());

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

            if (sampler.fboHashName != 0) {
                auto&& pFBOPass = dynamic_cast<IFramebufferPass*>(GetTechnique()->FindPass(sampler.fboHashName));
                if (pFBOPass && pFBOPass->GetFramebuffer()) {
                    auto&& pFBO = pFBOPass->GetFramebuffer();

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
            if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Opaque)) {
                MarkDirtyCluster(GetRenderScene()->GetOpaque());
            }

            if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Transparent)) {
                MarkDirtyCluster(GetRenderScene()->GetTransparent());
            }

            if (GetClusterType() & static_cast<MeshClusterTypeFlag>(MeshClusterType::Debug)) {
                MarkDirtyCluster(GetRenderScene()->GetDebugCluster());
            }

            m_needUpdateMeshes = false;
        }

        m_dirtySamplers = false;
    }

    void IMeshClusterPass::MarkDirtyCluster(MeshCluster& meshCluster) {
        for (auto&& [pClusterShader, subCluster] : meshCluster) {
            for (auto&& [key, meshGroup] : subCluster) {
                for (auto&& pMesh : meshGroup) {
                    pMesh->MarkMaterialDirty();
                }
            }
        }
    }

    void IMeshClusterPass::OnResize(const SR_MATH_NS::UVector2 &size) {
        m_dirtySamplers = true;
        m_needUpdateMeshes = true;
        Super::OnResize(size);
    }

    bool IMeshClusterPass::Init() {
        m_shadowMapPass = GetTechnique()->FindPass<ShadowMapPass>();
        m_cascadedShadowMapPass = GetTechnique()->FindPass<CascadedShadowMapPass>();
        return Super::Init();
    }
}