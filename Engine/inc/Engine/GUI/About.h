//
// Created by Igor on 12/03/2023.
//

#ifndef SR_ENGINE_ABOUT_H
#define SR_ENGINE_ABOUT_H

#include <Engine/stdInclude.h>

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class About : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        About();

    protected:
        void Draw() override;

    };
}

#endif //SR_ENGINE_ABOUT_H
