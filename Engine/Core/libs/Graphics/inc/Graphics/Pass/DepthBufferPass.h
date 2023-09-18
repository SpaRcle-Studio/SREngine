//
// Created by Monika on 21.01.2023.
//

#ifndef SRENGINE_DEPTHBUFFERPASS_H
#define SRENGINE_DEPTHBUFFERPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GRAPH_NS {
    class DepthBufferPass : public ShaderOverridePass {
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = ShaderOverridePass;
    public:
        explicit DepthBufferPass(RenderTechnique* pTechnique, BasePass* pParent);

    protected:
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SRENGINE_DEPTHBUFFERPASS_H
