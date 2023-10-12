//
// Created by Monika on 27.07.2022.
//

#include <Graphics/Pass/TransparentPass.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(TransparentPass)

    MeshClusterTypeFlag TransparentPass::GetClusterType() const noexcept {
        return static_cast<MeshClusterTypeFlag>(MeshClusterType::Transparent);
    }

    void TransparentPass::UseSharedUniforms(SR_GTYPES_NS::Shader *pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());
        }
        IMeshClusterPass::UseSharedUniforms(pShader);
    }
}