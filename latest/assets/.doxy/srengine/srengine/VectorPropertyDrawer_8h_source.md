

# File VectorPropertyDrawer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**PropertyDrawers**](dir_30dc1e095f689d337a3714af764d731f.md) **>** [**VectorPropertyDrawer.h**](VectorPropertyDrawer_8h.md)

[Go to the documentation of this file](VectorPropertyDrawer_8h.md)


```C++
//
// Created by Monika on 30.01.2025.
//

#ifndef SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H
#define SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H

#include <Engine/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    class VectorPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        bool m_isOpened = false;
        std::vector<PropertyDrawerBase::Ptr> m_drawers;

    };
}

#endif //SR_ENGINE_GUI_VECTOR_PROPERTY_DRAWER_H
```


