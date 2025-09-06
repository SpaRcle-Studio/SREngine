

# File ColorBufferPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**ColorBufferPass.h**](ColorBufferPass_8h.md)

[Go to the documentation of this file](ColorBufferPass_8h.md)


```C++
//
// Created by Monika on 10.10.2022.
//

#ifndef SR_ENGINE_COLOR_BUFFER_PASS_H
#define SR_ENGINE_COLOR_BUFFER_PASS_H

#include <Graphics/Pass/Data/FrameBufferPassData.h>
#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Pass/IColorBufferPass.h>

namespace SR_GRAPH_NS {
    class ColorBufferRenderQueue : public RenderQueue {
        using Super = RenderQueue;
    public:
        ColorBufferRenderQueue(RenderStrategy* pStrategy, MeshDrawerPass* pDrawer);

        void CustomDrawMesh(const MeshInfo& info) override;

    };

    class ColorBufferPass : public IColorBufferPass, public MeshDrawerPass {
        SR_CLASS()
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = MeshDrawerPass;
        friend class ColorBufferRenderQueue;
    public:
        bool Render() override;

        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer>& GetColorFrameBuffer() const noexcept override;

        void UseConstants(SR_GTYPES_NS::Shader* pShader) override;
        void UseSharedUniforms(SR_GTYPES_NS::Shader* pShader) override;

    protected:
        void UseUniforms(SR_GTYPES_NS::Shader* pShader, MeshPtr pMesh) override;

        SR_NODISCARD RenderQueuePtr AllocateRenderQueue() override;

        SR_VIRTUAL_PROPERTY

    };
}

#endif //SR_ENGINE_COLORBUFFERPASS_H
```


