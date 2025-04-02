

# File MaterialPropertyDrawer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**PropertyDrawers**](dir_4cfb8686e051f64f158d683134748f22.md) **>** [**MaterialPropertyDrawer.h**](MaterialPropertyDrawer_8h.md)

[Go to the documentation of this file](MaterialPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 17.02.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H

#include <Core/GUI/PropertyDrawers/PointerPropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class MaterialPropertyDrawer final : public PointerPropertyDrawer {
        using Super = PointerPropertyDrawer;
        SR_CLASS()
    public:
        void OnObjectReplaced(SRClass* pOld, SRClass* pNew) override;

    };
}


#endif //SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H
```


