//
// Created by Monika on 18.10.2023.
//

#include <Graphics/Pass/FlatClusterPass.h>

namespace SR_GRAPH_NS {
    MeshClusterTypeFlag FlatClusterPass::GetClusterType() const noexcept {
        return MeshClusterType::Flat;
    }

    void FlatClusterPass::OnClusterDirty() {
        for (auto&& pMesh : GetRenderScene()->GetFlatCluster()) {
            if (!pMesh) {
                continue;
            }
            pMesh->MarkMaterialDirty();
        }

        Super::OnClusterDirty();
    }

    void FlatClusterPass::Update() {
        SR_TRACY_ZONE;

        GetRenderScene()->GetFlatCluster().Sort();

        ShaderPtr pCurrentShader = nullptr;

        for (auto&& pMesh : GetRenderScene()->GetFlatCluster()) {
            if (!pMesh || !pMesh->IsMeshActive()) {
                continue;
            }

            auto&& virtualUbo = pMesh->GetVirtualUBO();
            if (virtualUbo == SR_ID_INVALID) {
                continue;
            }

            auto&& pShader = pMesh->GetShader();
            if (!pShader) {
                continue;
            }

            if (pCurrentShader != pShader) {
                m_context->SetCurrentShader(pCurrentShader);
                pCurrentShader = pShader;
                UseSharedUniforms(pShader);
            }

            if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                SR_ERROR("FlatClusterPass::UpdateCluster() : memory has been duplicated!");
            }

            pShader->Flush();
        }

        m_context->SetCurrentShader(nullptr);

        Super::Update();
    }

    bool FlatClusterPass::Render() {
        SR_TRACY_ZONE;

        GetRenderScene()->GetFlatCluster().Sort();

        ShaderPtr pCurrentShader = nullptr;

        for (auto&& pMesh : GetRenderScene()->GetFlatCluster()) {
            if (!pMesh || !pMesh->IsMeshActive()) {
                continue;
            }

            auto&& virtualUbo = pMesh->GetVirtualUBO();
            if (virtualUbo == SR_ID_INVALID) {
                continue;
            }

            auto&& pShader = pMesh->GetShader();
            if (!pShader) {
                continue;
            }

            if (pCurrentShader != pShader) {
                if (pCurrentShader) {
                    pCurrentShader->UnUse();
                }

                m_context->SetCurrentShader(pShader);

                if (pShader->Use() == ShaderBindResult::Failed) {
                    continue;
                }

                pCurrentShader = pShader;

                UseSamplers(pShader);
                UseConstants(pShader);
            }

            pMesh->BindMesh();
            pMesh->Draw();
        }

        if (pCurrentShader) {
            pCurrentShader->UnUse();
        }

        return Super::Render();
    }
}
