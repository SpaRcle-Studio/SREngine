

# File ColorBufferPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**ColorBufferPass.h**](ColorBufferPass_8h.md)

[Go to the documentation of this file](ColorBufferPass_8h.md)


```C++
//
// Created by Monika on 10.10.2022.
//

#ifndef SR_ENGINE_COLOR_BUFFER_PASS_H
#define SR_ENGINE_COLOR_BUFFER_PASS_H

#include <Graphics/Pass/OffScreenMeshDrawerPass.h>
#include <Graphics/Pass/IColorBufferPass.h>

namespace SR_GRAPH_NS {
    class ColorBufferRenderQueue : public RenderQueue {
        using Super = RenderQueue;
    public:
        ColorBufferRenderQueue(RenderStrategy* pStrategy, MeshDrawerPass* pDrawer);

        void CustomDrawMesh(const MeshInfo& info) override;

    };

    class ColorBufferPass : public OffScreenMeshDrawerPass, public IColorBufferPass {
        SR_REGISTER_LOGICAL_NODE(ColorBufferPass, Color Buffer Pass, { "Passes" })
        using ShaderPtr = SR_GTYPES_NS::Shader*;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
        using MeshPtr = SR_GTYPES_NS::Mesh*;
        using Super = OffScreenMeshDrawerPass;
        friend class ColorBufferRenderQueue;
    public:
        bool Render() override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        SR_NODISCARD SR_GTYPES_NS::Framebuffer* GetColorFrameBuffer() const noexcept override;
        SR_NODISCARD bool IsNeedUseMaterials() const noexcept override { return false; }

        void UseConstants(ShaderUseInfo info) override;

    protected:
        void UseUniforms(ShaderUseInfo info, MeshPtr pMesh) override;

        SR_NODISCARD RenderQueuePtr AllocateRenderQueue() override;

    };
}

#endif //SR_ENGINE_COLORBUFFERPASS_H
```


