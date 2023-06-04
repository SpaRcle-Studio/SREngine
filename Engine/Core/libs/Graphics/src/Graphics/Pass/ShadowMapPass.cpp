//
// Created by innerviewer on 5/21/2023.
//

#include <Graphics/Pass/ShadowMapPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ShadowMapPass);

    ShadowMapPass::ShadowMapPass(RenderTechnique *pTechnique, BasePass *pParent)
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

    void ShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader) {
        if (m_camera) {
            /// ортогональная матрица у glm не работает, тварь.
            SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4::Perspective(
                SR_RAD(45.f),
                m_camera->GetAspect(),
                m_camera->GetNear(),
                m_camera->GetFar()
            );

            SR_MATH_NS::Matrix4x4 lightView = SR_MATH_NS::Matrix4x4::LookAt(
                SR_MATH_NS::FVector3(-2.0f, 4.0f, -1.0f),
                SR_MATH_NS::FVector3(0.0f, 0.0f, 0.0f),
                SR_MATH_NS::FVector3(0.0f, 1.0f, 0.0f)
            );

            m_lightSpaceMatrix = lightProjection * lightView;

            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, m_lightSpaceMatrix);
        }
    }

    void ShadowMapPass::UseSamplers(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }

    MeshClusterTypeFlag ShadowMapPass::GetClusterType() const noexcept {
        return static_cast<uint64_t>(MeshClusterType::Opaque) | static_cast<uint64_t>(MeshClusterType::Transparent);
    }
}