

# File DragNDropHelper.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**DragNDropHelper.h**](DragNDropHelper_8h.md)

[Go to the documentation of this file](DragNDropHelper_8h.md)


```C++
//
// Created by Monika on 15.04.2023.
//

#ifndef SR_ENGINE_DRAGNDROPHELPER_H
#define SR_ENGINE_DRAGNDROPHELPER_H

#include <Utils/ECS/EntityRefOld.h>

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    SR_MAYBE_UNUSED bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRefOld& entityRef, const char* id, float_t width = 300.f);
}

#endif //SR_ENGINE_DRAGNDROPHELPER_H
```


