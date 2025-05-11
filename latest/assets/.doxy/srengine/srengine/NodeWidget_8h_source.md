

# File NodeWidget.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**NodeWidget.h**](NodeWidget_8h.md)

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


