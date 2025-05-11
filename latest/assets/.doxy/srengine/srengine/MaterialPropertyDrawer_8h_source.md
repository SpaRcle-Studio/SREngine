

# File MaterialPropertyDrawer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**PropertyDrawers**](dir_30dc1e095f689d337a3714af764d731f.md) **>** [**MaterialPropertyDrawer.h**](MaterialPropertyDrawer_8h.md)

[Go to the documentation of this file](MaterialPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 17.02.2025.
//

#ifndef SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_MATERIAL_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

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


