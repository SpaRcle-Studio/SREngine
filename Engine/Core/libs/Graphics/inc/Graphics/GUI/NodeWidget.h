//
// Created by Monika on 14.01.2023.
//

#ifndef SRENGINE_NODEWIDGET_H
#define SRENGINE_NODEWIDGET_H

#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/Widget.h>
#include <Graphics/GUI/PopupMenu.h>

namespace SR_GRAPH_GUI_NS {
    class NodeWidget : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        explicit NodeWidget(std::string name, SR_MATH_NS::IVector2 size = SR_MATH_NS::IVector2MAX);
        ~NodeWidget() override;

    public:
        Node& AddNode(Node* pNode);
        Link& AddLink(Link* pLink);

        void RemoveNode(Node* pNode);
        void RemoveLink(Link* pLink);

    protected:
        virtual bool CanAddNode(Node* pNode) { return true; }

        virtual void UpdateTouch();
        virtual void DrawPopupMenu();
        virtual void DrawTopPanel();

        virtual void TopPanelSaveAt();
        virtual void TopPanelOpen();
        virtual void TopPanelSave();
        virtual void TopPanelClose();

        virtual void InitCreationPopup();

        void Clear();

        void Init() override;

        void Draw() override;
        void OnClose() override;

    protected:
        PopupItemSubWidget::Ptr m_creationPopup;

        NodesTouchTimes m_nodeTouchTime;
        ax::NodeEditor::EditorContext* m_editor = nullptr;

        SR_GRAPH_GUI_NS::NodeBuilder* m_nodeBuilder = nullptr;

        std::map<uintptr_t, Node*> m_nodes;
        std::map<uintptr_t, Link*> m_links;

    };
}

#endif //SRENGINE_NODEWIDGET_H
