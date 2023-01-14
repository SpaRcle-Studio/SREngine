//
// Created by Monika on 14.01.2023.
//

#ifndef SRENGINE_ANIMATOREDITOR_H
#define SRENGINE_ANIMATOREDITOR_H

#include <Graphics/GUI/NodeWidget.h>

namespace SR_CORE_NS::GUI {
    class AnimatorEditor : public SR_GRAPH_NS::GUI::NodeWidget {
        using Super = SR_GRAPH_NS::GUI::NodeWidget;
    public:
        AnimatorEditor();
        ~AnimatorEditor() override = default;

    protected:
        void OnOpen() override;
        void OnClose() override;

        void Draw() override;

    };
}

#endif //SRENGINE_ANIMATOREDITOR_H
