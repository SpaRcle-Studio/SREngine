//
// Created by Monika on 21.01.2023.
//

#ifndef SR_ENGINE_DEPTHBUFFERPASS_H
#define SR_ENGINE_DEPTHBUFFERPASS_H

#include <Graphics/Pass/ShaderOverridePass.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GRAPH_NS {
    class DepthBufferPass : public ShaderOverridePass {
        SR_REGISTER_LOGICAL_NODE(DepthBufferPass, Depth Buffer Pass, { "Passes" })
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = ShaderOverridePass;
    protected:
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SR_ENGINE_DEPTHBUFFERPASS_H
