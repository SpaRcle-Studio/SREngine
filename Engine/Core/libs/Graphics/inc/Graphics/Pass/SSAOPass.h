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

        bool Load(const SR_XML_NS::Node &passNode) override;

        void UseTextures() override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

    protected:
        SR_NODISCARD SSAOKernel CreateKernel() const;
        SR_NODISCARD SR_GTYPES_NS::Texture* CreateNoise() const;

    private:
        SSAOKernel m_kernel;
        SR_GTYPES_NS::Texture* m_noise = nullptr;

    };
}


#endif //SR_ENGINE_SSAOPASS_H
