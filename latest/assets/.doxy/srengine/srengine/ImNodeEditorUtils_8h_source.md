

# File ImNodeEditorUtils.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**ImNodeEditorUtils.h**](ImNodeEditorUtils_8h.md)

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


