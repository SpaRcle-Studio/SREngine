//
// Created by innerviewer on 5/21/2023.
//

#include <Graphics/Pass/ShadowMapPass.h>
#include <Graphics/Lighting/LightSystem.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ShadowMapPass);

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
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslate());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjection());

            SR_MATH_NS::FVector3 lightPos = GetRenderScene()->GetLightSystem()->m_position;

            float zNear = 1.0f;
            float zFar = 96.0f;
            SR_MATH_NS::Matrix4x4 depthProjectionMatrix = SR_MATH_NS::Matrix4x4(glm::perspective(glm::radians(45.f), 1.0f, zNear, zFar));
            SR_MATH_NS::Matrix4x4 depthViewMatrix = SR_MATH_NS::Matrix4x4::LookAt(lightPos, glm::vec3(0.0f), glm::vec3(0, 1, 0));

            m_lightSpaceMatrix = depthProjectionMatrix * depthViewMatrix;

            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, m_lightSpaceMatrix);
            pShader->SetVec3(SHADER_DIRECTIONAL_LIGHT_POSITION, lightPos);
        }
        Super::UseSharedUniforms(pShader);
    }

    void ShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }

    bool ShadowMapPass::Render() {
        return Super::Render();
    }
}