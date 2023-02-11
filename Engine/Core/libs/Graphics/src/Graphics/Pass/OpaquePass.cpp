//
// Created by Monika on 24.07.2022.
//

#include <Graphics/Pass/OpaquePass.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(OpaquePass)

    OpaquePass::OpaquePass(RenderTechnique *pTechnique, BasePass* pParent)
        : BasePass(pTechnique, pParent)
    { }

    bool OpaquePass::PreRender() {
        return false;
    }

    bool OpaquePass::Render() {
        auto&& opaque = GetRenderScene()->GetOpaque();

        if (opaque.Empty()) {
            return false;
        }

        for (auto&& [shader, subCluster] : opaque) {
            if (!shader || (shader && !shader->Use())) {
                continue;
            }

            for (auto&& [key, meshGroup] : subCluster) {
                (*meshGroup.begin())->BindMesh();

                for (auto&& pMesh : meshGroup) {
                    pMesh->Draw();
                }
            }

            shader->UnUse();
        }

        return true;
    }

    void OpaquePass::Update() {
        if (!m_camera) {
            return;
        }

        auto&& opaque = GetRenderScene()->GetOpaque();
        auto&& time = SR_HTYPES_NS::Time::Instance().FClock();

        for (auto const& [pShader, subCluster] : opaque) {
            if (!pShader || !pShader->Ready()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            pShader->SetFloat(SHADER_TIME, time);

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto& pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    pMesh->UseMaterial();

                    pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());
                    pShader->SetVec3(SHADER_VIEW_POSITION, m_camera->GetPositionRef());

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("OpaquePass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        BasePass::Update();
    }
}