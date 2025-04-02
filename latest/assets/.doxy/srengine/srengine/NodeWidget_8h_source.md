

# File NodeWidget.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**NodeWidget.h**](NodeWidget_8h.md)

[Go to the documentation of this file](NodeWidget_8h.md)


```C++
//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_NODEWIDGET_H
#define SR_ENGINE_NODEWIDGET_H

#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/Widget.h>
#include <Graphics/GUI/PopupMenu.h>
#include <Utils/Resources/Xml.h>

namespace SR_SRLM_NS {
    class DataType;
}

namespace SR_GRAPH_GUI_NS {
    struct NodeWidgetProperty {
        std::string name;
        std::unique_ptr<SR_SRLM_NS::DataType> pData;
        bool expand = false;
    };

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
        virtual void DrawLeftPanel();
        virtual void DrawNodeEditor();

        virtual void TopPanelSaveAt();
        virtual void TopPanelOpen();
        virtual void TopPanelSave();
        virtual void TopPanelClose();

        virtual void Execute();

        virtual void InitCreationPopup();
        virtual void InitStructsCreationPopup();

        SR_NODISCARD NodeWidgetProperty* FindProperty(const std::string& name);

        void Clear();

        void Init() override;

        void Draw() override;
        void OnClose() override;

    protected:
        PopupItemSubWidget::Ptr m_creationPopup;

    #ifdef SR_USE_IMGUI_NODE_EDITOR
        NodesTouchTimes m_nodeTouchTime;
        ax::NodeEditor::EditorContext* m_editor = nullptr;
    #endif

        SR_GRAPH_GUI_NS::NodeBuilder* m_nodeBuilder = nullptr;

        std::map<uintptr_t, Node*> m_nodes;
        std::map<uintptr_t, Link*> m_links;

        std::vector<NodeWidgetProperty> m_properties;

        SR_UTILS_NS::Path m_currentFile;

        float_t m_leftPaneWidth = 400.0f;
        float_t m_rightPaneWidth = 800.0f;

    };
}

#endif //SR_ENGINE_NODEWIDGET_H
```


