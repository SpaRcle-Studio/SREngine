//
// Created by Monika on 22.07.2022.
//

#ifndef SR_ENGINE_FRAMEBUFFERPASS_H
#define SR_ENGINE_FRAMEBUFFERPASS_H

#include <Graphics/Pass/GroupPass.h>
#include <Graphics/Pass/IFramebufferPass.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FramebufferPass : public GroupPass, public IFramebufferPass {
        SR_REGISTER_LOGICAL_NODE(FramebufferPass, Framebuffer Pass, { "Passes" })
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;
        bool Init() override;

        bool PreRender() override;
        bool Render() override;
        bool PostRender() override;

        void Update() override;

    public:
        SR_NODISCARD IRenderTechnique* GetFrameBufferRenderTechnique() const override;
        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

    };

    class ClearBuffersPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(ClearBuffersPass, Clear Depth Pass, { "Passes" })
        using Super = BasePass;
    public:
        bool Load(const SR_XML_NS::Node& passNode) override;

        bool Render() override;

    private:
        bool m_clearDepth = true;
        bool m_clearColor = true;

    };
}

#endif //SR_ENGINE_FRAMEBUFFERPASS_H
