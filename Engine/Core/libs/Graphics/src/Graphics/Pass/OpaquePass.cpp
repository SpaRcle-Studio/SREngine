//
// Created by Monika on 24.07.2022.
//

#include <Graphics/Pass/OpaquePass.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Pipeline/IShaderProgram.h>

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

            ///// ортогональная матрица у glm не работает, тварь.
            //SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4::Perspective(
            //        SR_RAD(45.f),
            //        m_camera->GetAspect(),
            //        m_camera->GetNear(),
            //        m_camera->GetFar()
            //);

            SR_MATH_NS::FVector3 lightPos = SR_MATH_NS::FVector3(40, 20, 5);

            float zNear = 1.0f;
            float zFar = 96.0f;
            SR_MATH_NS::Matrix4x4 depthProjectionMatrix = SR_MATH_NS::Matrix4x4(glm::perspective(glm::radians(45.f), 1.0f, zNear, zFar));
            SR_MATH_NS::Matrix4x4 depthViewMatrix = SR_MATH_NS::Matrix4x4(glm::lookAt(lightPos.ToGLM(), glm::vec3(0.0f), glm::vec3(0, 1, 0)));

            //SR_MATH_NS::Matrix4x4 lightView = q.Inverse().ToMat4x4();
            //lightView = lightView.Translate(m_camera->GetPosition().Inverse());

            //SR_MATH_NS::Matrix4x4 lightView = SR_MATH_NS::Matrix4x4::LookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
            //                                  glm::vec3( 0.0f, 0.0f,  0.0f),
            //                                  glm::vec3( 0.0f, 1.0f,  0.0f));

            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, depthProjectionMatrix * depthViewMatrix);
            pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);
        }
        Super::UseSharedUniforms(pShader);
    }

    MeshClusterTypeFlag OpaquePass::GetClusterType() const noexcept {
        return static_cast<MeshClusterTypeFlag>(MeshClusterType::Opaque);
    }
}