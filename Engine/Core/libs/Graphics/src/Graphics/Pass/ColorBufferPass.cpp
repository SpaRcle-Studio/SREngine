//
// Created by Monika on 10.10.2022.
//

#include <Graphics/Pass/ColorBufferPass.h>
#include <Graphics/Pipeline/Pipeline.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ColorBufferPass)

    void ColorBufferPass::Update() {
        ResetColorIndex();
        Super::Update();
    }

    MeshClusterTypeFlag ColorBufferPass::GetClusterType() const noexcept {
        return static_cast<uint64_t>(MeshClusterType::Opaque) | static_cast<uint64_t>(MeshClusterType::Transparent);
    }

    void ColorBufferPass::UseUniforms(ColorBufferPass::ShaderPtr pShader, ColorBufferPass::MeshPtr pMesh) {
        pMesh->UseModelMatrix();

        IncrementColorIndex();
        SetMeshIndex(pMesh, GetColorIndex());

        static const uint64_t colorHashName = SR_UTILS_NS::StringAtom("color").GetHash();
        pShader->SetVec3(colorHashName, GetMeshColor());
    }

    void ColorBufferPass::UseSharedUniforms(ColorBufferPass::ShaderPtr pShader) {
        if (m_camera) {
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());
        }
        Super::UseSharedUniforms(pShader);
    }

    SR_GTYPES_NS::Framebuffer* ColorBufferPass::GetColorFrameBuffer() const noexcept {
        return GetFramebuffer();
    }
}
