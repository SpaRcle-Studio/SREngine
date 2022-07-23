//
// Created by Monika on 23.07.2022.
//

#include <Pass/WidgetPass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(WidgetPass)

    WidgetPass::WidgetPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    void WidgetPass::Overlay() {
        auto&& pipeline = GetContext()->GetPipeline();

        auto&& widgetManagers = GetRenderScene()->GetWidgetManagers();

        if (pipeline->BeginDrawGUI()) {
            for (auto&& pWidgetManager : widgetManagers)
                pWidgetManager->Draw();

            pipeline->EndDrawGUI();
        }

        BasePass::Overlay();
    }
}