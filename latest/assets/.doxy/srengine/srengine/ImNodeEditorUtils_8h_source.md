

# File ImNodeEditorUtils.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**ImNodeEditorUtils.h**](ImNodeEditorUtils_8h.md)

[Go to the documentation of this file](ImNodeEditorUtils_8h.md)


```C++
//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_IMNODEEDITORUTILS_H
#define SR_ENGINE_IMNODEEDITORUTILS_H

#include <Graphics/macros.h>

#ifdef SR_USE_IMGUI_NODE_EDITOR
    #include <imgui-node-editor/imgui_node_editor.h>
#endif

namespace SR_SRLM_NS {
    enum class DataTypeClass : uint8_t;
}

namespace SR_GRAPH_GUI_NS {
    class Pin;

    bool IsPinsCompatible(SR_SRLM_NS::DataTypeClass first, SR_SRLM_NS::DataTypeClass second);

    bool CanCreateLink(Pin* a, Pin* b);

#ifdef SR_USE_IMGUI_NODE_EDITOR
    struct ImNodeIdLess {
        bool operator()(const ax::NodeEditor::NodeId& lhs, const ax::NodeEditor::NodeId& rhs) const {
            return lhs.AsPointer() < rhs.AsPointer();
        }
    };

    typedef std::map<ax::NodeEditor::NodeId, float, ImNodeIdLess> NodesTouchTimes;
#endif
}

#endif //SR_ENGINE_IMNODEEDITORUTILS_H
```


