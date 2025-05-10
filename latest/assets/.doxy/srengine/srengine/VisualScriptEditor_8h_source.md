

# File VisualScriptEditor.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**VisualScriptEditor.h**](VisualScriptEditor_8h.md)

[Go to the documentation of this file](VisualScriptEditor_8h.md)


```C++
//
// Created by Monika on 11.01.2022.
//

#ifndef SR_ENGINE_VISUALSCRIPTEDITOR_H
#define SR_ENGINE_VISUALSCRIPTEDITOR_H

#include <Graphics/GUI/Widget.h>

namespace SR_GRAPH_NS::GUI {
    class Pin;
    class Node;
    class Link;
}

namespace SR_CORE_NS::GUI {
    class VisualScriptEditor : public SR_GRAPH_NS::GUI::Widget {
    public:
        VisualScriptEditor();
        ~VisualScriptEditor() override;

    public:
        void Draw() override;
        void AddNode(SR_GRAPH_NS::GUI::Node* node);
        void AddLink(SR_GRAPH_NS::GUI::Link* link);


    private:
        void LoadConfig();

    private:
        //ax::NodeEditor::EditorContext* m_editor = nullptr;
        std::unordered_map<uintptr_t, SR_GRAPH_NS::GUI::Node*> m_nodes;
        std::unordered_map<uintptr_t, SR_GRAPH_NS::GUI::Link*> m_links;
        std::unordered_map<std::string, SR_GRAPH_NS::GUI::Node*> m_blueprints;

    };
}

#endif //SR_ENGINE_VISUALSCRIPTEDITOR_H
```


