

# File UIModifier.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**UI**](dir_6a9921db89a56a1548d450ac0e56d87b.md) **>** [**UIModifier.h**](UIModifier_8h.md)

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


