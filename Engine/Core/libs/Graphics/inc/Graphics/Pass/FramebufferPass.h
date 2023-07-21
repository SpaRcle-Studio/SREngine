//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_FRAMEBUFFERPASS_H
#define SRENGINE_FRAMEBUFFERPASS_H

#include <Graphics/Pass/GroupPass.h>
#include <Graphics/Pass/IFramebufferPass.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FramebufferPass : public GroupPass, public IFramebufferPass {
    public:
        FramebufferPass(RenderTechnique* pTechnique, BasePass* pParent);

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;
        bool Init() override;

        bool PreRender() override;
        bool Render() override;
        bool PostRender() override;

        void Update() override;

        SR_NODISCARD std::vector<SR_GTYPES_NS::Framebuffer*> GetFrameBuffers() const override;

    private:
        bool m_isRendered = false;

    };
}

#endif //SRENGINE_FRAMEBUFFERPASS_H
