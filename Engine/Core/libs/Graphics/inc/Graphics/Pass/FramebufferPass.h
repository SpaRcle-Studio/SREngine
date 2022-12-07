//
// Created by Monika on 22.07.2022.
//

#ifndef SRENGINE_FRAMEBUFFERPASS_H
#define SRENGINE_FRAMEBUFFERPASS_H

#include <Graphics/Pass/GroupPass.h>

namespace SR_GTYPES_NS {
    class Framebuffer;
}

namespace SR_GRAPH_NS {
    class FramebufferPass : public GroupPass {
        using ColorFormats = std::list<ColorFormat>;
        using ClearColors = std::vector<SR_MATH_NS::FColor>;
        using FramebufferPtr = SR_GTYPES_NS::Framebuffer*;
    public:
        explicit FramebufferPass(RenderTechnique* pTechnique, BasePass* pParent);
        ~FramebufferPass() override;

    public:
        bool Load(const SR_XML_NS::Node& passNode) override;
        void OnResize(const SR_MATH_NS::UVector2 &size) override;
        bool Init() override;

        bool PreRender() override;
        bool Render() override;
        bool PostRender() override;

        void Update() override;

        SR_NODISCARD FramebufferPtr GetFramebuffer() const;

    private:
        void LoadSettings(const SR_XML_NS::Node& settingsNode);

    private:
        bool m_dynamicResizing = false;
        bool m_depthEnabled = true;

        SR_MATH_NS::FVector2 m_preScale;
        SR_MATH_NS::IVector2 m_size;

        ColorFormats m_colorFormats;
        ClearColors m_clearColors;

        FramebufferPtr m_framebuffer = nullptr;

        float_t m_depth = 1.f;
        uint8_t m_samples = 0;
        DepthFormat m_depthFormat = DepthFormat::Unknown;


    };
}

#endif //SRENGINE_FRAMEBUFFERPASS_H
