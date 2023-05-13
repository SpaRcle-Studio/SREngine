//
// Created by Nikita on 18.11.2020.
//

#ifndef SRENGINE_WINDOW_H
#define SRENGINE_WINDOW_H

#include <Utils/Math/Vector3.h>
#include <Utils/Types/Thread.h>
#include <Utils/Types/Function.h>
#include <Utils/Math/Vector2.h>

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
    class Environment;

    class Window : public SR_HTYPES_NS::SafePtr<Window> {
    public:
        using Super = SR_HTYPES_NS::SafePtr<Window>;
        using Ptr = SR_HTYPES_NS::SafePtr<Window>;
        using WindowHandle = void*;
        using ScrollCallback = SR_HTYPES_NS::Function<void(double_t xOffset, double_t yOffset)>;
        using FocusCallback = SR_HTYPES_NS::Function<void(bool)>;
        using DrawCallback = SR_HTYPES_NS::Function<void(void)>;
        using CloseCallback = SR_HTYPES_NS::Function<void(void)>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using ResizeCallback = SR_HTYPES_NS::Function<void(const SR_MATH_NS::UVector2&)>;
    public:
        Window();
        ~Window();

    public:
        bool Initialize(const std::string& name, const SR_MATH_NS::UVector2& size);
        void Close();

        SR_NODISCARD SR_HTYPES_NS::Thread::Ptr GetThread() const;
        SR_NODISCARD SR_MATH_NS::UVector2 GetSize() const;
        SR_NODISCARD SR_MATH_NS::IVector2 GetPosition() const;
        SR_NODISCARD bool IsWindowFocus() const;
        SR_NODISCARD bool IsWindowCollapsed() const;
        SR_NODISCARD bool IsValid() const;
        SR_NODISCARD WindowHandle GetHandle() const;
        SR_NODISCARD bool IsFullScreen() const;
        SR_NODISCARD bool IsMaximized() const;

        SR_NODISCARD SR_MATH_NS::IVector2 ScreenToClient(const SR_MATH_NS::IVector2& pos) const;
        SR_NODISCARD SR_MATH_NS::IVector2 ClientToScreen(const SR_MATH_NS::IVector2& pos) const;

        void SetFocusCallback(const FocusCallback& callback);
        void SetDrawCallback(const DrawCallback& callback);
        void SetCloseCallback(const CloseCallback& callback);
        void SetResizeCallback(const ResizeCallback& callback);
        void SetScrollCallback(const ScrollCallback& callback);

        void SetFullScreen(bool value);

        template<typename T> SR_NODISCARD T* GetImplementation() const {
            return dynamic_cast<T*>(m_windowImpl);
        }

    private:
        void ThreadFunction();

    private:
        CloseCallback m_closeCallback;
        DrawCallback m_drawCallback;
        ScrollCallback m_scrollCallback;

        SR_HTYPES_NS::Thread::Ptr m_thread = nullptr;

        BasicWindowImpl* m_windowImpl = nullptr;

    };
}

#endif //SRENGINE_WINDOW_H
