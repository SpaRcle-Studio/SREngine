//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_ANIMATOREDITOR_H
#define SR_ENGINE_ANIMATOREDITOR_H

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/Animations/AnimationGraph.h>

namespace SR_CORE_NS::GUI {
    class AnimatorNode : public SR_GRAPH_NS::GUI::Node {
    private:
        SR_UTILS_NS::Path m_animationPath;
        std::string m_clipName;

    };

    class AnimatorEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        using Super = SR_GRAPH_NS::GUI::NodeWidget;
        static constexpr uint16_t VERSION = 1000;
    public:
        AnimatorEditor();
        ~AnimatorEditor() override = default;

    protected:
        void OnOpen() override;
        void DrawPopupMenu() override;

    };
}

#endif //SR_ENGINE_ANIMATOREDITOR_H
