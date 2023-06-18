//
// Created by Monika on 24.07.2022.
//

#include <Graphics/Pass/OpaquePass.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Lighting/LightSystem.h>
#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(OpaquePass)

    OpaquePass::OpaquePass(RenderTechnique *pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    void OpaquePass::UseSharedUniforms(SR_GTYPES_NS::Shader *pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
            pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());
        }

        SR_MATH_NS::FVector3 lightPos = GetRenderScene()->GetLightSystem()->m_position;
        pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);

        if (m_shadowMapPass) {
            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, m_shadowMapPass->GetLightSpaceMatrix());
        }

        Super::UseSharedUniforms(pShader);
    }

    MeshClusterTypeFlag OpaquePass::GetClusterType() const noexcept {
        return static_cast<MeshClusterTypeFlag>(MeshClusterType::Opaque);
    }
}