//
// Created by innerviewer on 5/21/2023.
//

#include <Graphics/Pass/ShadowMapPass.h>

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

    bool ShadowMapPass::Load(const SR_XML_NS::Node &passNode) {
        return Super::Load(passNode);
    }

    MeshClusterTypeFlag ShadowMapPass::GetClusterType() const noexcept {
        return static_cast<uint64_t>(MeshClusterType::Opaque) | static_cast<uint64_t>(MeshClusterType::Transparent);
    }

    void ShadowMapPass::UseSharedUniforms(IMeshClusterPass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());

            SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4::Ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.f, 7.5f);

            SR_MATH_NS::FVector3 lightPos = SR_MATH_NS::FVector3(-2.0f, 6.0f, -1.0f);
            SR_MATH_NS::Quaternion q = SR_MATH_NS::Quaternion::FromEuler(SR_MATH_NS::FVector3(45.f, 45.f, 0));

            SR_MATH_NS::Matrix4x4 lightView = q.RotateX(SR_DEG(SR_PI)).Inverse().ToMat4x4();
            lightView = lightView.Translate(lightPos.Inverse());

            //SR_MATH_NS::Matrix4x4 lightView = SR_MATH_NS::Matrix4x4::LookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
            //                                  glm::vec3( 0.0f, 0.0f,  0.0f),
            //                                  glm::vec3( 0.0f, 1.0f,  0.0f));

            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, lightProjection * m_camera->GetViewTranslateRef());
            pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, m_camera->GetPosition());
        }
    }

    void ShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }
}