//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/DepthBufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(DepthBufferPass)

    void DepthBufferPass::UseUniforms(DepthBufferPass::ShaderPtr pShader, DepthBufferPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }

    void DepthBufferPass::UseSharedUniforms(DepthBufferPass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
        }
        Super::UseSharedUniforms(pShader);
    }
}