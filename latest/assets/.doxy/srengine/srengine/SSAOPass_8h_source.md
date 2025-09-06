

# File SSAOPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**SSAOPass.h**](SSAOPass_8h.md)

[Go to the documentation of this file](SSAOPass_8h.md)


```C++
//
// Created by Monika on 09.02.2023.
//

#ifndef SR_ENGINE_SSAOPASS_H
#define SR_ENGINE_SSAOPASS_H

#include <Graphics/Pass/PostProcessPass.h>
#include <Graphics/Types/Texture.h>

namespace SR_GRAPH_NS {
    class SSAOPass : public PostProcessPass {
        using Super = PostProcessPass;
        using SSAOKernel = std::vector<SR_MATH_NS::FVector4>;
    public:
        bool Init() override;
        void DeInit() override;

        bool Render() override;
        void Update() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        void UseSamplers(const ShaderUseInfo& info) override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

    protected:
        SR_NODISCARD SSAOKernel CreateKernel() const;
        SR_NODISCARD SR_GTYPES_NS::Texture::Ptr CreateNoise() const;
        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override;

    private:
        SSAOKernel m_kernel;
        SR_GTYPES_NS::Texture::Ptr m_noise;

    };
}


#endif //SR_ENGINE_SSAOPASS_H
```


