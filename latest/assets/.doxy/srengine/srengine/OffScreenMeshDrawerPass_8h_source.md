

# File OffScreenMeshDrawerPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**OffScreenMeshDrawerPass.h**](OffScreenMeshDrawerPass_8h.md)

[Go to the documentation of this file](OffScreenMeshDrawerPass_8h.md)


```C++
//
// Created by Monika on 25.01.2024.
//

#ifndef SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H
#define SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H

#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pass/MeshDrawerPass.h>

namespace SR_GRAPH_NS {
    class OffScreenMeshDrawerPass : public IFramebufferPass, public MeshDrawerPass {
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Init() override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;

        bool Render() override;
        void Update() override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;
        SR_NODISCARD uint8_t GetMeshDrawerFBOLayers() const noexcept override;

        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override { return GetTechnique(); }

    protected:
        void RenderFrameBufferInner() override;
        void UpdateFrameBufferInner() override;

    };
}

#endif //SR_ENGINE_OFF_SCREEN_MESH_DRAWER_PASS_H
```


