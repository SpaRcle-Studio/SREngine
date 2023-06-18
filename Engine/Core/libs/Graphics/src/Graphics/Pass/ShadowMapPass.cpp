//
// Created by innerviewer on 5/21/2023.
//

#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Lighting/LightSystem.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ShadowMapPass);

    ShadowMapPass::ShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    bool ShadowMapPass::Init() {
        return Super::Init();
    }

    void ShadowMapPass::DeInit() {
        Super::DeInit();
    }

    bool ShadowMapPass::Load(const SR_XML_NS::Node& passNode) {
        return Super::Load(passNode);
    }

    MeshClusterTypeFlag ShadowMapPass::GetClusterType() const noexcept {
        return static_cast<uint64_t>(MeshClusterType::Opaque) | static_cast<uint64_t>(MeshClusterType::Transparent);
    }

    void ShadowMapPass::UseSharedUniforms(IMeshClusterPass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());

            //float_t AR = m_camera->GetSize().y / m_camera->GetSize().x;
            //SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4(glm::ortho(2.5f / AR, 0.0f, 0.0f, 2.5f, -1.0f, 1.0f));
            // SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4::Ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.f, 7.5f);
            //SR_MATH_NS::Quaternion q = m_camera->GetRotation(); //SR_MATH_NS::Quaternion::FromEuler(SR_MATH_NS::FVector3(45.f, 45.f, 0));

            SR_MATH_NS::FVector3 lightPos = GetRenderScene()->GetLightSystem()->m_position;

            float zNear = 1.0f;
            float zFar = 96.0f;
            SR_MATH_NS::Matrix4x4 depthProjectionMatrix = SR_MATH_NS::Matrix4x4(glm::perspective(glm::radians(45.f), 1.0f, zNear, zFar));
            SR_MATH_NS::Matrix4x4 depthViewMatrix = SR_MATH_NS::Matrix4x4::LookAt(lightPos, glm::vec3(0.0f), glm::vec3(0, 1, 0));

            //SR_MATH_NS::Matrix4x4 lightView = q.Inverse().ToMat4x4();
            //lightView = lightView.Translate(m_camera->GetPosition().Inverse());

            //SR_MATH_NS::Matrix4x4 lightView = SR_MATH_NS::Matrix4x4::LookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
            //                                  glm::vec3( 0.0f, 0.0f,  0.0f),
            //                                  glm::vec3( 0.0f, 1.0f,  0.0f));

            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, depthProjectionMatrix * depthViewMatrix);
            pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);
        }
    }

    void ShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }
}