

# File Window.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Window**](dir_387552b0934ce9512c4f7c4e31a03e0f.md) **>** [**Window.h**](Window_8h.md)

[Go to the documentation of this file](Window_8h.md)


```C++
//
// Created by Nikita on 18.11.2020.
//

#ifndef SR_ENGINE_WINDOW_H
#define SR_ENGINE_WINDOW_H

#include <Utils/Math/Vector3.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Types/SharedPtr.h>

#include <Graphics/Window/BasicWindowImpl.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    namespace GUI {
        class WidgetManager;
    }

    class Render;
    class RenderContext;

    class Window : public SR_HTYPES_NS::SharedPtr<Window> {
    public:
        using Super = SR_HTYPES_NS::SharedPtr<Window>;
        using Ptr = SR_HTYPES_NS::SharedPtr<Window>;
        using WindowHandle = void*;
        using ScrollCallback = SR_HTYPES_NS::Function<void(double_t xOffset, double_t yOffset)>;
        using FocusCallback = SR_HTYPES_NS::Function<void(bool)>;
        using DrawCallback = SR_HTYPES_NS::Function<void(void)>;
        using CloseCallback = SR_HTYPES_NS::Function<void(void)>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using ResizeCallback = SR_HTYPES_NS::Function<void(const SR_MATH_NS::UVector2&)>;
    public:
        Window();
        ~Window() override;

    public:
        bool Initialize(const std::string& name, const SR_MATH_NS::UVector2& size);

        bool Open();
        void Close();

        void PollEvents();

        //void Update();

        SR_NODISCARD SR_MATH_NS::UVector2 GetSize() const;
        SR_NODISCARD SR_MATH_NS::IVector2 GetPosition() const;
        SR_NODISCARD bool IsWindowFocus() const;
        SR_NODISCARD bool IsWindowCollapsed() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD WindowHandle GetHandle() const;
        SR_NODISCARD bool IsFullScreen() const;
        SR_NODISCARD bool IsMaximized() const;
        SR_NODISCARD bool IsVisible() const;

        SR_NODISCARD SR_MATH_NS::IVector2 ScreenToClient(const SR_MATH_NS::IVector2& pos) const;
        SR_NODISCARD SR_MATH_NS::IVector2 ClientToScreen(const SR_MATH_NS::IVector2& pos) const;

        void SetFocusCallback(const FocusCallback& callback);
        void SetDrawCallback(const DrawCallback& callback);
        void SetCloseCallback(const CloseCallback& callback);
        void SetResizeCallback(const ResizeCallback& callback);
        void SetScrollCallback(const ScrollCallback& callback);

        void SetFullScreen(bool value);

        SR_NODISCARD BasicWindowImpl* GetBaseWindow() const noexcept { return m_windowImpl; }

        template<typename T> SR_NODISCARD T* GetImplementation() const {
            return dynamic_cast<T*>(m_windowImpl);
        }

    private:
        SR_MATH_NS::UVector2 m_initialSize;
        std::string m_name;

        CloseCallback m_closeCallback;
        DrawCallback m_drawCallback;
        ScrollCallback m_scrollCallback;

        BasicWindowImpl* m_windowImpl = nullptr;

    };
}

#endif //SR_ENGINE_WINDOW_H
```


