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

    void ShadowMapPass::UpdateCluster(MeshCluster *pCluster) {
        if (!m_camera) {
            return;
        }

        SR_MATH_NS::Matrix4x4 lightProjection = SR_MATH_NS::Matrix4x4::Perspective( /// ортогональная матрица у glm не работает, тварь.
            SR_RAD(45.f),
            m_camera->GetAspect(),
            m_camera->GetNear(),
            m_camera->GetFar()
        );

        SR_MATH_NS::Matrix4x4 lightView = SR_MATH_NS::Matrix4x4::LookAt(
            SR_MATH_NS::FVector3(-2.0f, 4.0f, -1.0f),
            SR_MATH_NS::FVector3( 0.0f, 0.0f,  0.0f),
            SR_MATH_NS::FVector3( 0.0f, 1.0f,  0.0f)
        );

        m_lightSpaceMatrix = lightProjection * lightView;

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
            pShader->SetMat4(SHADER_LIGHT_SPACE_MATRIX, m_lightSpaceMatrix);

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
                        SR_ERROR("ShaderMapPass::UpdateCluster() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }

}