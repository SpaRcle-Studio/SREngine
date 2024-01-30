//
// Created by Monika on 18.10.2023.
//

#include <Graphics/Pass/FlatClusterPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(FlatClusterPass)

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

        if (!m_hasRendered) {
            return;
        }

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
            if (!pShader || !pShader->Ready() || !pShader->IsAvailable()) {
                continue;
            }

            GetContext()->SetCurrentShader(pShader);

            if (pCurrentShader != pShader) {
                pCurrentShader = pShader;
                UseSharedUniforms(pShader);
            }

            UseUniforms(pShader, pMesh);

            if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                SR_ERROR("FlatClusterPass::UpdateCluster() : memory has been duplicated!");
            }

            pShader->Flush();
        }

        GetContext()->SetCurrentShader(nullptr);

        Super::Update();
    }

    bool FlatClusterPass::Render() {
        SR_TRACY_ZONE;

        m_hasRendered = false;

        if (!Super::Render()) {
            return false;
        }

        GetRenderScene()->GetFlatCluster().Sort();

        ShaderPtr pCurrentShader = nullptr;

        for (auto&& pMesh : GetRenderScene()->GetFlatCluster()) {
            if (!pMesh || !pMesh->IsMeshActive()) {
                continue;
            }

            auto&& pShader = pMesh->GetShader();
            if (!pShader) {
                continue;
            }

            if (pCurrentShader != pShader) {
                if (pCurrentShader) {
                    pCurrentShader->UnUse();
                    pCurrentShader = nullptr;
                }

                if (pShader->Use() == ShaderBindResult::Failed) {
                    continue;
                }

                pCurrentShader = pShader;

                UseSamplers(pShader);
                UseConstants(pShader);
            }

            pMesh->BindMesh();
            pMesh->Draw();

            m_hasRendered |= true;
        }

        if (pCurrentShader) {
            pCurrentShader->UnUse();
        }

        return m_hasRendered;
    }

    void FlatClusterPass::UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslate());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjection());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonal());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPosition());
        }

        Super::UseSharedUniforms(pShader);
    }
}
