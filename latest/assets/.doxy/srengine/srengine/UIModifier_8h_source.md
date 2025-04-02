

# File UIModifier.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**UI**](dir_ccab98ed2f4ae92257108f1b96ae4039.md) **>** [**UIModifier.h**](UIModifier_8h.md)

[Go to the documentation of this file](UIModifier_8h.md)


```C++
//
// Created by Monika on 19.01.2025.
//

#ifndef SR_UTILS_UI_MODIFIER_H
#define SR_UTILS_UI_MODIFIER_H

#include <Utils/ECS/Component.h>
#include <Utils/Math/Rect.h>
#include <Utils/Math/Size.h>

namespace SR_UTILS_NS::UI {
    SR_ENUM_NS_CLASS_T(Stretch, uint8_t,
        ShowAll,
        NoBorder,
        ChangeAspect,
        WidthControlsHeight,
        HeightControlsWidth,
        SavePosition 
    );

    SR_ENUM_NS_CLASS_T(PositionMode, uint8_t,
        None,
        ProportionalX,
        ProportionalY,
        ProportionalXY
    )

    SR_ENUM_NS_CLASS_T(FixedSize, uint8_t,
        None,
        FixedWidth,
        FixedHeight,
        All
    );

    SR_ENUM_NS_CLASS_T(Anchor, uint8_t,
        None,
        TopLeft, TopCenter, TopRight,
        MiddleLeft, MiddleCenter, MiddleRight,
        BottomLeft, BottomCenter, BottomRight
    );

    struct UIModifierContext {
        bool xSizeChangable = true;
        bool ySizeChangable = true;
        float_t zOrder = 0.f;
        SR_MATH_NS::FPoint position;
        SR_MATH_NS::FSize2 contentSize;
        SR_MATH_NS::FSize2 ocuppiedSize;

        SR_MATH_NS::FVector3 childTranslation;
        SR_MATH_NS::FVector2 childSize;
    };

    class UIModifierComponent : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:
        ~UIModifierComponent() override;

    public:
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        void OnAttached() override;
        void OnDetached() override;
        void OnDestroy() override;

        void OnTransformSet() override;

        virtual void Prepare(UIModifierContext& context) const { }
        virtual void PostProcess(UIModifierContext& context) const { }
        virtual void ApplyChild(UIModifierContext& context) const { }

    protected:
        void SetUITreeDirty();

    private:
        void ConnectModifier();

    private:
        bool m_connected = false;

    };
}

#endif //SR_UTILS_UI_MODIFIER_H
```


