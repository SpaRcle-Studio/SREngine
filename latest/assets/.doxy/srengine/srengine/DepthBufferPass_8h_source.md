

# File DepthBufferPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**DepthBufferPass.h**](DepthBufferPass_8h.md)

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
```


