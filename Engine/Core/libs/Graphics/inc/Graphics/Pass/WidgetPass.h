//
// Created by Monika on 14.07.2022.
//

#ifndef SR_ENGINE_WIDGETPASS_H
#define SR_ENGINE_WIDGETPASS_H

#include <Graphics/Pass/BasePass.h>

namespace SR_GRAPH_NS {
    class WidgetPass : public BasePass {
        SR_REGISTER_LOGICAL_NODE(WidgetPass, Widget Pass, { "Passes" })
    public:
        bool Overlay() override;

    };
}


#endif //SR_ENGINE_WIDGETPASS_H
