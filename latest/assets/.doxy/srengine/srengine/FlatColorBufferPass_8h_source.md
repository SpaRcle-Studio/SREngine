

# File FlatColorBufferPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**FlatColorBufferPass.h**](FlatColorBufferPass_8h.md)

[Go to the documentation of this file](FlatColorBufferPass_8h.md)


```C++
//
// Created by Monika on 18.11.2023.
//

#ifndef SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H
#define SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H

#include <Graphics/Pass/IColorBufferPass.h>
#include <Graphics/Pass/FlatClusterPass.h>

namespace SR_GRAPH_NS {
    /*class FlatColorBufferPass : public FlatClusterPass, public IColorBufferPass, public IFramebufferPass {
        using Super = FlatClusterPass;
    public:
        void Update() override;
        bool Render() override;
        bool Init() override;
        bool Load(const SR_XML_NS::Node& passNode) override;
        void OnResize(const SR_MATH_NS::UVector2& size) override;

        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override { return GetTechnique(); }

    public:
        SR_NODISCARD SR_GTYPES_NS::Framebuffer* GetColorFrameBuffer() const noexcept override;
        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

        void UseConstants(SR_GTYPES_NS::Shader* pShader) override;
        void UseUniforms(SR_GTYPES_NS::Shader* pShader, MeshPtr pMesh) override;

    };*/
}

#endif //SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H
```


