//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/DepthBufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(DepthBufferPass)

    DepthBufferPass::DepthBufferPass(RenderTechnique *pTechnique, BasePass *pParent)
        : Super(pTechnique, pParent)
    { }

    void DepthBufferPass::UpdateCluster(MeshCluster *pCluster) {
        for (auto const& [_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader || !pShader->Ready()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto& pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    pMesh->UseModelMatrix();

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("ColorBufferPass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }
}