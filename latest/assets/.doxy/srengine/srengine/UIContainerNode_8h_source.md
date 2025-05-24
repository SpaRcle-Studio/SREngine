

# File UIContainerNode.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**UIContainerNode.h**](UIContainerNode_8h.md)

[Go to the documentation of this file](UIContainerNode_8h.md)


```C++
//
// Created by Monika on 17.05.2025.
//

#ifndef SR_GRAPHICS_UI_UI_CONTAINER_NODE_H
#define SR_GRAPHICS_UI_UI_CONTAINER_NODE_H

#include <Graphics/UI/UIControlNode.h>

namespace SR_GRAPH_UI_NS {
    SR_ENUM_NS_CLASS_T(UIContainerDirection, uint8_t,
        Row, Column, RowReverse, ColumnReverse
    )

    class UIContainerNode : public UIControlNode {
        SR_CLASS()
        using Super = UIControlNode;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<UIContainerNode>;

    public:
        SR_NODISCARD SR_UTILS_NS::ECSNodeType GetNodeType() const noexcept override;

        void Prepare(uint64_t& priority) override;
        void Layout(const SR_MATH_NS::FRect& available) override;

    private:
        UIContainerDirection m_direction = UIContainerDirection::Row;
        UIAlign m_containerAlign = UIAlign::Auto;
        UIJustify m_justify = UIJustify::Auto;

    };
}

#endif //SR_GRAPHICS_UI_UI_CONTAINER_NODE_H
```


