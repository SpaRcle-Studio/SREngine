

# File UIControlNode.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**UIControlNode.h**](UIControlNode_8h.md)

[Go to the documentation of this file](UIControlNode_8h.md)


```C++
//
// Created by Monika on 17.05.2025.
//

#ifndef SR_GRAPHICS_UI_UI_CONTROL_NODE_H
#define SR_GRAPHICS_UI_UI_CONTROL_NODE_H

#include <Graphics/UI/UINode.h>

namespace SR_GRAPH_UI_NS {
    SR_ENUM_NS_CLASS_T(UIPositionType, uint8_t,
        Relative, 
        Absolute  
    )

    SR_ENUM_NS_CLASS_T(UISizePolicy, uint8_t,
        Fixed,   
        Percent, 
        Content, 
        Fill     
    )

    SR_ENUM_NS_CLASS_T(UIAlign, uint8_t,
        Start,
        Center,
        End,
        Stretch
    )

    struct UILayout : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        

        
        UISizePolicy widthPolicy = UISizePolicy::Fixed;
        UISizePolicy heightPolicy = UISizePolicy::Fixed;
        float_t width = 0.0f; 
        float_t height = 0.0f;


        UIPositionType positionType = UIPositionType::Relative;
        SR_MATH_NS::FVector2 absolutePosition = { 0.f, 0.f }; 
        SR_MATH_NS::FVector2 offset = { 0.f, 0.f }; 


        SR_MATH_NS::FRect margin;
        SR_MATH_NS::FRect padding;


        UIAlign horizontalAlign = UIAlign::Start;
        UIAlign verticalAlign = UIAlign::Start;
    };

    class UIControlNode : public UINode {
        SR_CLASS()
        using Super = UINode;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<UIControlNode>;

    public:
        void Layout(const SR_MATH_NS::FRect& available) override;

        SR_NODISCARD SR_MATH_NS::FVector2 CalculateContentSize() const override;
        SR_NODISCARD const UILayout& GetLayout() const noexcept;
        SR_NODISCARD SR_UTILS_NS::ECSNodeType GetNodeType() const noexcept override;

    private:
        UILayout m_layout;

    };
}

#endif //SR_GRAPHICS_UI_UI_CONTROL_NODE_H
```


