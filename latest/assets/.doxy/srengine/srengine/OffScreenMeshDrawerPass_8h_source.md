

# File OffScreenMeshDrawerPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**OffScreenMeshDrawerPass.h**](OffScreenMeshDrawerPass_8h.md)

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


