

# File DepthBufferPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**DepthBufferPass.h**](DepthBufferPass_8h.md)

[Go to the documentation of this file](DepthBufferPass_8h.md)


```C++
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
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = ShaderOverridePass;
    protected:
        void UseUniforms(ShaderPtr pShader, MeshPtr pMesh) override;
        void UseSharedUniforms(ShaderPtr pShader) override;

    };
}

#endif //SR_ENGINE_DEPTHBUFFERPASS_H
```


