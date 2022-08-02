//
// Created by Monika on 22.07.2022.
//

#include <Pass/SwapchainPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(SwapchainPass)

    SwapchainPass::SwapchainPass(RenderTechnique *pTechnique)
        : GroupPass(pTechnique)
    { }

    bool SwapchainPass::Load(const SR_XML_NS::Node &passNode) {
        return GroupPass::Load(passNode);
    }

    bool SwapchainPass::Render() {
        auto&& pipeline = GetContext()->GetPipeline();

        pipeline->ClearBuffers(0.5f, 0.5f, 0.5f, 1.f, 1.f, 1);

        for (uint8_t i = 0; i < pipeline->GetCountBuildIter(); ++i) {
            pipeline->SetBuildIteration(i);

            pipeline->BindFrameBuffer(0);

            pipeline->BeginRender();
            {
                pipeline->SetViewport();
                pipeline->SetScissor();

                GroupPass::Render();
            }
            pipeline->EndRender();
        }

        return true;
    }

    void SwapchainPass::Update() {
        GroupPass::Update();
    }
}
