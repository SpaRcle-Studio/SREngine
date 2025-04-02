

# File DragNDropHelper.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**DragNDropHelper.h**](DragNDropHelper_8h.md)

[Go to the documentation of this file](DragNDropHelper_8h.md)


```C++
//
// Created by Monika on 15.04.2023.
//

#ifndef SR_ENGINE_DRAGNDROPHELPER_H
#define SR_ENGINE_DRAGNDROPHELPER_H

#include <Utils/ECS/EntityRef.h>

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    SR_MAYBE_UNUSED bool DragDropTargetEntityRef(EditorGUI* pContext, SR_UTILS_NS::EntityRef& entityRef, const char* id, float_t width = 300.f);
}

#endif //SR_ENGINE_DRAGNDROPHELPER_H
```


