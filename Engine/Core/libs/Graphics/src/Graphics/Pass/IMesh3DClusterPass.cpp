//
// Created by Monika on 18.10.2023.
//

#include <Graphics/Pass/IMesh3DClusterPass.h>

namespace SR_GRAPH_NS {
    bool IMesh3DClusterPass::Init() {
        SR_TRACY_ZONE;
        m_shadowMapPass = GetTechnique()->FindPass<ShadowMapPass>();
        m_cascadedShadowMapPass = GetTechnique()->FindPass<CascadedShadowMapPass>();
        return Super::Init();
    }

    void IMesh3DClusterPass::MarkDirtyCluster(MeshCluster& meshCluster) {
        SR_TRACY_ZONE;

        for (auto&& [pClusterShader, subCluster] : meshCluster) {
            for (auto&& [key, meshGroup] : subCluster) {
                for (auto&& pMesh : meshGroup) {
                    pMesh->MarkMaterialDirty();
                }
            }
        }
    }

    bool IMesh3DClusterPass::RenderCluster(MeshCluster& meshCluster) {
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

            /// Если нет ни одного активного меша, то нет смысла идти дальше
            for (auto&& [key, meshGroup] : subCluster) {
                for (auto&& pMesh : meshGroup) {
                    if (pMesh->IsMeshActive()) {
                        goto goDraw;
                    }
                }
            }

            continue;

        goDraw:
            if (pShader->Use() == ShaderBindResult::Failed) {
                continue;
            }

            UseSamplers(pShader);
            UseConstants(pShader);

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

    void IMesh3DClusterPass::UpdateCluster(MeshCluster& meshCluster) {
        SR_TRACY_ZONE;

        for (auto const& [pClusterShader, subCluster] : meshCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader) {
                pShader = pClusterShader;
            }

            if (!pShader || !pShader->Ready() || !pShader->IsAvailable()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

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

            GetRenderScene()->SetCurrentSkeleton(nullptr);
            m_context->SetCurrentShader(nullptr);
        }
    }

    bool IMesh3DClusterPass::Render() {
        SR_TRACY_ZONE;

        if (!Super::Render()) {
            return false;
        }

        bool rendered = false;

        if (GetClusterType() & MeshClusterType::Opaque) {
            rendered |= RenderCluster(GetRenderScene()->GetOpaque());
        }

        if (GetClusterType() & MeshClusterType::Transparent) {
            rendered |= RenderCluster(GetRenderScene()->GetTransparent());
        }

        if (GetClusterType() & MeshClusterType::Debug) {
            rendered |= RenderCluster(GetRenderScene()->GetDebugCluster());
        }

        return rendered;
    }

    void IMesh3DClusterPass::Update() {
        SR_TRACY_ZONE;

        if (GetClusterType() & MeshClusterType::Opaque) {
            UpdateCluster(GetRenderScene()->GetOpaque());
        }

        if (GetClusterType() & MeshClusterType::Transparent) {
            UpdateCluster(GetRenderScene()->GetTransparent());
        }

        if (GetClusterType() & MeshClusterType::Debug) {
            UpdateCluster(GetRenderScene()->GetDebugCluster());
        }

        Super::Update();
    }

    void IMesh3DClusterPass::OnClusterDirty() {
        if (GetClusterType() & MeshClusterType::Opaque) {
            MarkDirtyCluster(GetRenderScene()->GetOpaque());
        }

        if (GetClusterType() & MeshClusterType::Transparent) {
            MarkDirtyCluster(GetRenderScene()->GetTransparent());
        }

        if (GetClusterType() &MeshClusterType::Debug) {
            MarkDirtyCluster(GetRenderScene()->GetDebugCluster());
        }

        Super::OnClusterDirty();
    }
}
