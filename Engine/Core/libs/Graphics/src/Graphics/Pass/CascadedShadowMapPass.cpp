//
// Created by Monika on 06.06.2023.
//

#include <Graphics/Pass/CascadedShadowMapPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(CascadedShadowMapPass);

    CascadedShadowMapPass::CascadedShadowMapPass(RenderTechnique* pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    bool CascadedShadowMapPass::Init() {
        return Super::Init();
    }

    void CascadedShadowMapPass::DeInit() {
        Super::DeInit();
    }

    bool CascadedShadowMapPass::Load(const SR_XML_NS::Node& passNode) {
        return Super::Load(passNode);
    }

    MeshClusterTypeFlag CascadedShadowMapPass::GetClusterType() const noexcept {
        return static_cast<uint64_t>(MeshClusterType::Opaque) | static_cast<uint64_t>(MeshClusterType::Transparent);
    }

    void CascadedShadowMapPass::UseSharedUniforms(IMeshClusterPass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
        }
    }

    void CascadedShadowMapPass::UseUniforms(IMeshClusterPass::ShaderPtr pShader, IMeshClusterPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();
    }
}