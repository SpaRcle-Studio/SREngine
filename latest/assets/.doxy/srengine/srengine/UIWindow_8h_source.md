

# File UIWindow.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**UI**](dir_4db2cc8eada578aa57e9f12bf4119b9f.md) **>** [**UIWindow.h**](UIWindow_8h.md)

[Go to the documentation of this file](UIWindow_8h.md)


```C++
//
// Created by Monika on 02.08.2024.
//

#ifndef SR_ENGINE_GRAPHICS_UI_WINDOW_H
#define SR_ENGINE_GRAPHICS_UI_WINDOW_H

#include <Utils/ECS/Component.h>

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

    class UIWindow : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
    public:
        bool InitializeEntity() noexcept override;

        SR_NODISCARD bool IsResizable() const noexcept { return m_flags & UIWindowAttributes::Resizable; }
        SR_NODISCARD bool IsMovable() const noexcept { return m_flags & UIWindowAttributes::Movable; }
        SR_NODISCARD bool IsClosable() const noexcept { return m_flags & UIWindowAttributes::Closable; }
        SR_NODISCARD bool IsMinimizable() const noexcept { return m_flags & UIWindowAttributes::Minimizable; }
        SR_NODISCARD bool IsMaximizable() const noexcept { return m_flags & UIWindowAttributes::Maximizable; }
        SR_NODISCARD bool IsDockable() const noexcept { return m_flags & UIWindowAttributes::Dockable; }

        void SetResizable(bool value) noexcept;
        void SetMovable(bool value) noexcept;
        void SetClosable(bool value) noexcept;
        void SetMinimizable(bool value) noexcept;
        void SetMaximizable(bool value) noexcept;
        void SetDockable(bool value) noexcept;
        void SetWindowSize(const SR_MATH_NS::UVector2& size) noexcept;

    private:
        UIWindowAttributes m_flags = UIWindowAttributes::None;
        SR_MATH_NS::UVector2 m_windowSize;
        SR_UTILS_NS::GameObject::Ptr m_content;
        SR_UTILS_NS::GameObject::Ptr m_titleBar;

    };
}

#endif //SR_ENGINE_GRAPHICS_UI_WINDOW_H
```


