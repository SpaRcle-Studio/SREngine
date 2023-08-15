//
// Created by Monika on 14.01.2023.
//

#ifndef SRENGINE_IMNODEEDITORUTILS_H
#define SRENGINE_IMNODEEDITORUTILS_H

#include <imgui-node-editor/imgui_node_editor.h>

namespace SR_GRAPH_GUI_NS {
    class Pin;

    enum class PinType : int32_t;

    bool IsPinsCompatible(PinType first, PinType second);

    bool CanCreateLink(Pin* a, Pin* b);

    struct ImNodeIdLess {
        bool operator()(const ax::NodeEditor::NodeId& lhs, const ax::NodeEditor::NodeId& rhs) const {
            return lhs.AsPointer() < rhs.AsPointer();
        }
    };

    typedef std::map<ax::NodeEditor::NodeId, float, ImNodeIdLess> NodesTouchTimes;
}

#endif //SRENGINE_IMNODEEDITORUTILS_H
