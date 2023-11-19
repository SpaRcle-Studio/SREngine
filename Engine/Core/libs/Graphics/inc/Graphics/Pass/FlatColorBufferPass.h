//
// Created by Monika on 18.11.2023.
//

#include <Graphics/Pass/IColorBufferPass.h>
#include <Graphics/Pass/IFramebufferPass.h>
#include <Graphics/Pass/FlatClusterPass.h>

#ifndef SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H
#define SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H

namespace SR_GRAPH_NS {
    class FlatColorBufferPass : public FlatClusterPass, public IColorBufferPass, public IFramebufferPass {
        SR_REGISTER_LOGICAL_NODE(FlatColorBufferPass, Flat Color Buffer Pass, { "Passes" })
        using Super = FlatClusterPass;
    public:
        void Update() override;
        bool Render() override;
        bool Init() override;
        bool Load(const SR_XML_NS::Node& passNode) override;

    public:
        SR_NODISCARD SR_GTYPES_NS::Framebuffer* GetColorFrameBuffer() const noexcept override;

        void UseConstants(SR_GTYPES_NS::Shader* pShader) override;

    };
}

#endif //SR_ENGINE_GRAPHICS_FLAT_COLOR_BUFFER_PASS_H
