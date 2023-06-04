//
// Created by Monika on 04.06.2023.
//

#include <Graphics/Pass/IMeshClusterPass.h>

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
            /// TODO
        }
    }

    MeshClusterTypeFlag IMeshClusterPass::GetClusterType() const noexcept {
        return m_meshClusters;
    }

    bool IMeshClusterPass::Load(const SR_XML_NS::Node& passNode) {
        for (auto&& meshClusterNode : passNode.TryGetNode("MeshClusters").TryGetNodes()) {
            auto&& clusterType = SR_UTILS_NS::EnumReflector::FromString<MeshClusterType>(meshClusterNode.Name());
            m_meshClusters |= static_cast<MeshClusterTypeFlag>(clusterType);
        }

        return Super::Load(passNode);
    }

    void IMeshClusterPass::Prepare() {
        Super::Prepare();
    }

    void IMeshClusterPass::UseSharedUniforms(IMeshClusterPass::ShaderPtr pShader) {
        /// определяется классом-наследником 
    }
}