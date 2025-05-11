

# File VisualScriptEditor.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**VisualScriptEditor.h**](VisualScriptEditor_8h.md)

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


