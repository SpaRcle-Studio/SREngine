//
// Created by Monika on 22.07.2022.
//

#include <Graphics/Pass/SwapchainPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(SwapchainPass)

    SwapchainPass::SwapchainPass(RenderTechnique *pTechnique, BasePass* pParent)
        : GroupPass(pTechnique, pParent)
    { }

    bool SwapchainPass::Load(const SR_XML_NS::Node &passNode) {
        m_depth = passNode.TryGetAttribute("Depth").ToFloat(1.f);

        m_color.r = passNode.TryGetAttribute("R").ToFloat(0.f);
        m_color.g = passNode.TryGetAttribute("G").ToFloat(0.f);
        m_color.b = passNode.TryGetAttribute("B").ToFloat(0.f);
        m_color.a = passNode.TryGetAttribute("A").ToFloat(0.f);

        return GroupPass::Load(passNode);
    }

    bool SwapchainPass::Render() {
        SR_TRACY_ZONE_N("Swapchain pass");

        auto&& pipeline = GetContext()->GetPipeline();

        pipeline->SetCurrentFramebuffer(nullptr);

        for (uint8_t i = 0; i < pipeline->GetCountBuildIter(); ++i) {
            pipeline->SetBuildIteration(i);

            pipeline->BindFrameBuffer(nullptr);
            pipeline->ClearBuffers(m_color.r, m_color.g, m_color.b, m_color.a, m_depth, 1);

            pipeline->BeginCmdBuffer();
            {
                pipeline->BeginRender();

                pipeline->SetViewport();
                pipeline->SetScissor();

                GroupPass::Render();

                pipeline->EndRender();
            }
            pipeline->EndCmdBuffer();
        }

        return true;
    }

    void SwapchainPass::Update() {
        GroupPass::Update();
    }
}
