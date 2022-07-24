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
            /// Во время отрисовки виджета он может быть удален
            for (uint16_t i = 0; ; ++i) {
                if (i >= widgetManagers.size()) {
                    break;
                }

                widgetManagers[i]->Draw();
            }

            pipeline->EndDrawGUI();
        }

        BasePass::Overlay();
    }
}