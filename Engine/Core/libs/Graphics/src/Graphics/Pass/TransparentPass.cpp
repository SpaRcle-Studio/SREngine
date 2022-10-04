//
// Created by Monika on 27.07.2022.
//

#include <Graphics/Pass/TransparentPass.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>
#include <Graphics/Render/MeshCluster.h>
#include <Graphics/Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(TransparentPass)

    TransparentPass::TransparentPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    bool TransparentPass::PreRender() {
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
                (*meshGroup.begin())->BindMesh();

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
                    if (!mesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = mesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    mesh->UseMaterial();

                    shader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection(mesh->GetTranslation()));

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