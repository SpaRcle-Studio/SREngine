//
// Created by Monika on 14.01.2023.
//

#ifndef SRENGINE_NODEWIDGET_H
#define SRENGINE_NODEWIDGET_H

#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/Widget.h>

namespace SR_GRAPH_NS::GUI {
    class NodeWidget : public SR_GRAPH_NS::GUI::Widget {
        using Super = SR_GRAPH_NS::GUI::Widget;
    public:
        explicit NodeWidget(std::string name, SR_MATH_NS::IVector2 size = SR_MATH_NS::IVector2MAX);
        ~NodeWidget() override;

    protected:
        void UpdateTouch();

        void Clear();

        Node& AddNode(Node* pNode);
        Link& AddLink(Link* pLink);

    protected:
        NodesTouchTimes m_nodeTouchTime;
        ax::NodeEditor::EditorContext* m_editor = nullptr;

        SR_GRAPH_NS::GUI::NodeBuilder* m_nodeBuilder = nullptr;

        std::map<uintptr_t, Node*> m_nodes;
        std::map<uintptr_t, Link*> m_links;

    };
}

#endif //SRENGINE_NODEWIDGET_H
