//
// Created by Monika on 24.07.2022.
//

#include <Pass/OpaquePass.h>
#include <Types/Material.h>
#include <Types/Shader.h>
#include <Types/Geometry/IndexedMesh.h>
#include <Render/MeshCluster.h>
#include <Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(OpaquePass)

    OpaquePass::OpaquePass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    void OpaquePass::PreRender() {
        GetRenderScene()->GetOpaque().Update();
        BasePass::PreRender();
    }

    void OpaquePass::Render() {
        auto&& pipeline = GetPipeline();
        auto&& opaque = GetRenderScene()->GetOpaque();

        for (auto&& [shader, subCluster] : opaque) {
            if (!shader || shader && !shader->Use()) {
                continue;
            }

            for (auto&& [key, meshGroup] : subCluster) {
                pipeline->BindVBO((*meshGroup.begin())->GetVBO<true>());
                pipeline->BindIBO((*meshGroup.begin())->GetIBO<true>());

                for (auto&& pMesh : meshGroup)
                    pMesh->DrawVulkan();
            }

            shader->UnUse();
        }

        BasePass::Render();
    }

    void OpaquePass::Update() {
        if (!m_camera) {
            return;
        }

        auto&& pipeline = GetPipeline();
        auto&& opaque = GetRenderScene()->GetOpaque();
        auto&& time = clock();

        for (auto const& [shader, subCluster] : opaque) {
            if (!shader || !shader->Ready()) {
                continue;
            }

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            shader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            shader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            shader->SetFloat(SHADER_TIME, time);

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto &mesh : meshGroup) {
                    if (!mesh->IsActive()) {
                        continue;
                    }

                    auto&& virtualUbo = mesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    mesh->GetMaterial()->Use();

                    shader->SetMat4(SHADER_MODEL_MATRIX, mesh->GetModelMatrixRef());

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("VulkanRender::UpdateUBOs() : memory has been duplicated!");
                    }

                    shader->Flush();
                }
            }
        }

        BasePass::Update();
    }
}