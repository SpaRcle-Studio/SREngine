

# File SSAOPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**SSAOPass.h**](SSAOPass_8h.md)

[Go to the documentation of this file](SSAOPass_8h.md)


```C++
//
// Created by Monika on 09.02.2023.
//

#ifndef SR_ENGINE_SSAOPASS_H
#define SR_ENGINE_SSAOPASS_H

#include <Graphics/Pass/PostProcessPass.h>
#include <Graphics/Pass/IFramebufferPass.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class SSAOPass : public PostProcessPass, public IFramebufferPass {
        SR_REGISTER_LOGICAL_NODE(SSAOPass, SSAO Pass, { "Passes" })
        using SSAOKernel = std::vector<SR_MATH_NS::FVector4>;
    public:
        bool Init() override;
        void DeInit() override;

        bool Render() override;
        void Update() override;

        void OnResize(const SR_MATH_NS::UVector2& size) override;

        bool Load(const SR_XML_NS::Node& passNode) override;

        void UseSamplers(ShaderUseInfo info) override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

    protected:
        SR_NODISCARD SSAOKernel CreateKernel() const;
        SR_NODISCARD SR_GTYPES_NS::Texture* CreateNoise() const;
        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override;

    private:
        SSAOKernel m_kernel;
        SR_GTYPES_NS::Texture* m_noise = nullptr;

    };
}


#endif //SR_ENGINE_SSAOPASS_H
```


