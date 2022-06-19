//
// Created by Monika on 11.01.2022.
//

#ifndef SRENGINE_VISUALSCRIPTEDITOR_H
#define SRENGINE_VISUALSCRIPTEDITOR_H

#include <GUI/Widget.h>

#include <imgui_node_editor.h>

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

        SR_NODISCARD SR_GRAPH_NS::GUI::Node* CreateBlueprint(const std::string& id) const;
        SR_NODISCARD bool ValidateLink(SR_GRAPH_NS::GUI::Pin* start, SR_GRAPH_NS::GUI::Pin* end) const;

    private:
        void LoadConfig();
        void RegisterBlueprint(SR_GRAPH_NS::GUI::Node* blueprint);

    private:
        ax::NodeEditor::EditorContext* m_editor = nullptr;
        std::unordered_map<uintptr_t, SR_GRAPH_NS::GUI::Node*> m_nodes;
        std::unordered_map<uintptr_t, SR_GRAPH_NS::GUI::Link*> m_links;
        std::unordered_map<std::string, SR_GRAPH_NS::GUI::Node*> m_blueprints;

    };
}

#endif //SRENGINE_VISUALSCRIPTEDITOR_H
