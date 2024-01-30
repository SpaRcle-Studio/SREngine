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

    void ColorBufferPass::UseUniforms(ShaderPtr pShader, MeshPtr pMesh) {
        pMesh->UseModelMatrix();

        IncrementColorIndex();
        SetMeshIndex(pMesh, GetColorIndex());

        static const uint64_t colorHashName = SR_UTILS_NS::StringAtom("color").GetHash();
        pShader->SetVec3(colorHashName, GetMeshColor());
    }

    SR_GTYPES_NS::Framebuffer* ColorBufferPass::GetColorFrameBuffer() const noexcept {
        return GetFramebuffer();
    }
}
