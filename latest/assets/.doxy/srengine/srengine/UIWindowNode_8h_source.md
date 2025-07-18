

# File UIWindowNode.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**UIWindowNode.h**](UIWindowNode_8h.md)

[Go to the documentation of this file](UIWindowNode_8h.md)


```C++
//
// Created by Monika on 02.08.2024.
//

#ifndef SR_ENGINE_GRAPHICS_UI_WINDOW_NODE_H
#define SR_ENGINE_GRAPHICS_UI_WINDOW_NODE_H

#include <Graphics/UI/UIContainerNode.h>

#include <Utils/ECS/EntityRef.h>

namespace SR_GTYPES_NS {
    class Sprite;
}

namespace SR_GRAPH_UI_NS {
    SR_ENUM_NS_STRUCT_T(UIWindowAttributes, uint32_t,
        None = 0,
        Dockable = 1 << 0,
        Resizable = 1 << 1,
        Movable = 1 << 2,
        Closable = 1 << 3,
        Minimizable = 1 << 4,
        Maximizable = 1 << 5
    );

    class UIWindowNode : public UIContainerNode {
        SR_CLASS()
        using Super = UIContainerNode;
    public:
        void Layout(const SR_MATH_NS::FRect& available) override;

    private:
        SR_UTILS_NS::EntityRef<SR_GTYPES_NS::Sprite> m_border;

    };
}

#endif //SR_ENGINE_GRAPHICS_UI_WINDOW_NODE_H
```


