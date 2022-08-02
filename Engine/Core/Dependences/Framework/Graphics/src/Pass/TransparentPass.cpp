//
// Created by Monika on 27.07.2022.
//

#include <Pass/TransparentPass.h>
#include <Types/Material.h>
#include <Types/Shader.h>
#include <Types/Geometry/IndexedMesh.h>
#include <Render/MeshCluster.h>
#include <Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(TransparentPass)

    TransparentPass::TransparentPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    bool TransparentPass::PreRender() {
        GetRenderScene()->GetTransparent().Update();
        return false;
    }

    bool TransparentPass::Render() {
        auto&& pipeline = GetPipeline();
        auto&& transparent = GetRenderScene()->GetTransparent();

        if (transparent.Empty()) {
            return false;
        }

        for (auto&& [shader, subCluster] : transparent) {
            if (!shader || shader && !shader->Use()) {
                continue;
            }

            for (auto&& [key, meshGroup] : subCluster) {
                pipeline->BindVBO((*meshGroup.begin())->GetVBO<true>());
                pipeline->BindIBO((*meshGroup.begin())->GetIBO<true>());

                for (auto&& pMesh : meshGroup) {
                    pMesh->Draw();
                }
            }

            shader->UnUse();
        }

        return true;
    }

    void TransparentPass::Update() {
        if (!m_camera) {
            return;
        }

        auto&& pipeline = GetPipeline();
        auto&& transparent = GetRenderScene()->GetTransparent();
        auto&& time = clock();

        for (auto const& [shader, subCluster] : transparent) {
            if (!shader || !shader->Ready()) {
                continue;
            }

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            shader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            shader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            shader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
            shader->SetFloat(SHADER_TIME, time);

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto &mesh : meshGroup) {
                    /// TODO: проверка очень тяжелая из-за мьютексов, нужно оптимизировать
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
                        SR_ERROR("TransparentPass::Update() : memory has been duplicated!");
                    }

                    shader->Flush();
                }
            }
        }

        BasePass::Update();
    }
}