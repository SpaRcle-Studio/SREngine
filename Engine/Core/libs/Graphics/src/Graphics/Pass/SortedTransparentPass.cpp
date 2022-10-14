//
// Created by Monika on 01.08.2022.
//

#include <Graphics/Pass/SortedTransparentPass.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/IndexedMesh.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(SortedTransparentPass)

    SortedTransparentPass::SortedTransparentPass(RenderTechnique *pTechnique, BasePass* pParent)
        : BasePass(pTechnique, pParent)
    { }

    void SortedTransparentPass::Prepare() {
        if (!m_camera) {
            return;
        }

        auto&& transparent = GetRenderScene()->GetTransparent();

        m_sorted.Clear();

        for (auto const& [shader, subCluster] : transparent) {
            for (auto const&[key, meshGroup] : subCluster) {
                for (auto&& pMesh : meshGroup) {
                    m_sorted.Add(pMesh);
                }
            }
        }

        m_sorted.SetTarget(m_camera->GetPosition());

        if (m_sorted.Sort()) {
            GetTechnique()->GetRenderScene()->SetDirty();
        }

        BasePass::Prepare();
    }

    bool SortedTransparentPass::Render() {
        if (!m_camera || m_sorted.empty()) {
            return false;
        }

        auto&& pipeline = GetPipeline();

        ShaderPtr pShader = nullptr;

        int32_t currentVBO = SR_ID_INVALID;
        int32_t currentIBO = SR_ID_INVALID;

        for (auto pIt = std::prev(std::end(m_sorted)); ; ) {
            auto&& pMesh = *pIt;

            auto&& pIndexed = dynamic_cast<SR_GTYPES_NS::IndexedMesh*>(pMesh);

            if (!pIndexed) {
                SRHalt("Failed to cast!");
                continue;
            }

            if (auto&& shader = pMesh->GetShader(); shader != pShader) {
                pShader = shader;
                if (!pShader || pShader && !pShader->Use()) {
                    continue;
                }
            }

            if (auto&& VBO = pIndexed->GetVBO(); VBO != currentVBO) {
                pipeline->BindVBO((currentVBO = VBO));
            }

            if (auto&& IBO = pIndexed->GetIBO(); IBO != currentIBO) {
                pipeline->BindIBO((currentIBO = IBO));
            }

            pMesh->Draw();

            if (std::begin(m_sorted) == pIt) {
                break;
            }

            --pIt;
        }

        return true;
    }

    void SortedTransparentPass::Update() {
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

                    mesh->GetMaterial()->Use();

                    shader->SetMat4(SHADER_MODEL_MATRIX, mesh->GetModelMatrix());

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
