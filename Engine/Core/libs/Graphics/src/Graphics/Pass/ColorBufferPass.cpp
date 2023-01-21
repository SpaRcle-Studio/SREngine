//
// Created by Monika on 10.10.2022.
//

#include <Graphics/Pass/ColorBufferPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ColorBufferPass)

    ColorBufferPass::ColorBufferPass(RenderTechnique *pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    void ColorBufferPass::Update() {
        m_colorId = 0;
        Super::Update();
    }

    void ColorBufferPass::UpdateCluster(MeshCluster *pCluster) {
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
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto &pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    pMesh->UseModelMatrix();

                    ++m_colorId;
                    SetMeshIndex(pMesh, m_colorId);

                    auto&& color = SR_MATH_NS::HEXToBGR(m_colorId).Cast<SR_MATH_NS::Unit>();

                    pShader->SetVec3(SR_COMPILE_TIME_CRC32_STR("color"), color.ToGLM() / 255.f);

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("ColorBufferPass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }

    SR_MATH_NS::FColor ColorBufferPass::GetColor(float_t x, float_t y) const {
        if (x < 0 || x > 1 || y < 0 || y > 1) {
            return SR_MATH_NS::FColor(0.f);
        }

        if (!GetFramebuffer() || IsDirectional()) {
            return SR_MATH_NS::FColor(0.f);
        }

        auto&& textureId = GetFramebuffer()->GetColorTexture(0);

        const uint32_t xPos = GetFramebuffer()->GetWidth() * x;
        const uint32_t yPos = GetFramebuffer()->GetHeight() * y;

        return m_context->GetPipeline()->GetPixelColor(textureId, xPos, yPos);
    }

    SR_GTYPES_NS::Mesh *ColorBufferPass::GetMesh(float_t x, float_t y) const {
        auto&& color = GetColor(x, y);

        auto&& colorIndex = SR_MATH_NS::BGRToHEX(SR_MATH_NS::IVector3(
                static_cast<int32_t>(color.x),
                static_cast<int32_t>(color.y),
                static_cast<int32_t>(color.z)
        ));

        if (colorIndex > m_table.size() || colorIndex == 0) {
            return nullptr;
        }

        return m_table[colorIndex - 1];
    }

    void ColorBufferPass::SetMeshIndex(ColorBufferPass::MeshPtr pMesh, uint32_t colorId) {
        /// 0 - черный цвет, отсутствие мешей
        if (colorId == 0) {
            SRHalt("ColorBufferPass::SetMeshIndex() : invalid index!");
            return;
        }

        if (m_colorId - 1 >= m_table.size()) {
            if (m_table.empty()) {
                m_table.resize(32);
            }
            else {
                m_table.resize(m_table.size() * 2);
            }
        }

        m_table[m_colorId - 1] = pMesh;
    }

    uint32_t ColorBufferPass::GetIndex(float_t x, float_t y) const {
        auto&& color = GetColor(x, y);

        auto&& colorIndex = SR_MATH_NS::BGRToHEX(SR_MATH_NS::IVector3(
                static_cast<int32_t>(color.x),
                static_cast<int32_t>(color.y),
                static_cast<int32_t>(color.z)
        ));

        return colorIndex;
    }
}
