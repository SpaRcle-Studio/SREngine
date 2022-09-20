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

    bool OpaquePass::PreRender() {
        return false;
    }

    bool OpaquePass::Render() {
        auto&& pipeline = GetPipeline();
        auto&& opaque = GetRenderScene()->GetOpaque();

        if (opaque.Empty()) {
            return false;
        }

        for (auto&& [shader, subCluster] : opaque) {
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
                        SR_ERROR("OpaquePass::Update() : memory has been duplicated!");
                    }

                    shader->Flush();
                }
            }
        }

        BasePass::Update();
    }
}