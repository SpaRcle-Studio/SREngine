//
// Created by Monika on 20.03.2021.
//

#ifndef SR_ENGINE_BASICWINDOW_IMPL_H
#define SR_ENGINE_BASICWINDOW_IMPL_H

#include <Utils/Math/Vector3.h>
#include <Graphics/Pipeline/PipelineType.h>

namespace SR_GRAPH_NS {
    enum class WindowState {
        Default, Collapsed, Maximized, FullScreen
    };

    class BasicWindowImpl : public SR_UTILS_NS::NonCopyable {
    public:
        SR_ENUM_CLASS_T(WindowType, uint8_t, Unknown, Auto, Android, Win32, X11, GLFW, SDL);
        using Super = SR_UTILS_NS::NonCopyable;
        using ResizeCallback = std::function<void(BasicWindowImpl*, int32_t, int32_t)>;
        using MoveCallback = std::function<void(BasicWindowImpl*, int32_t, int32_t)>;
        using ScrollCallback = std::function<void(BasicWindowImpl*, double_t, double_t)>;
        using FocusCallback = std::function<void(BasicWindowImpl*, bool)>;
        using CloseCallback = std::function<void(BasicWindowImpl*)>;
    public:
        explicit BasicWindowImpl(PipelineType pipelineType, WindowType type)
            : Super()
            , m_pipeline(pipelineType)
            , m_type(type)
        { }

        static BasicWindowImpl* CreatePlatformWindow(PipelineType pipelineType, WindowType type);

    public:
        void SetResizeCallback(const ResizeCallback& callback);
        void SetMoveCallback(const MoveCallback& callback);
        void SetScrollCallback(const ScrollCallback& callback);
        void SetFocusCallback(const FocusCallback& callback);
        void SetCloseCallback(const CloseCallback& callback);

        SR_NODISCARD WindowType GetType() const { return m_type; }
        SR_NODISCARD WindowState GetState() const { return m_state; }
        SR_NODISCARD virtual uint32_t GetSurfaceWidth()  const { return m_surfaceSize.x; }
        SR_NODISCARD virtual uint32_t GetSurfaceHeight() const { return m_surfaceSize.y; }
        SR_NODISCARD virtual uint32_t GetWidth()  const { return m_size.x; }
        SR_NODISCARD virtual uint32_t GetHeight() const { return m_size.y; }
        SR_NODISCARD virtual bool IsValid() const { return m_isValid; };
        SR_NODISCARD virtual bool IsCollapsed() const { return m_collapsed; };
        SR_NODISCARD virtual SR_MATH_NS::IVector2 GetPosition() const { return SR_MATH_NS::IVector2(); }
        SR_NODISCARD virtual SR_MATH_NS::IVector2 GetScreenResolution() const { return SR_MATH_NS::IVector2(); }

        virtual void Resize(uint32_t width, uint32_t height) { }
        virtual void Move(int32_t x, int32_t y) { }
        virtual void Centralize() { }
        virtual void Collapse() { }
        virtual void Expand() { }
        virtual void Maximize() { }
        virtual void Restore() { }
        virtual bool Destroy() { return false; }
        virtual bool Free() { return false; }
        virtual void PollEvents() const { };
        virtual void SwapBuffers() const { };
        virtual bool MakeContextCurrent() { return false; };
        virtual void SetIcon(const std::string& path) { }
        virtual void SetHeaderEnabled(bool enable) { }
        virtual void SetSwapInterval(int interval) { }
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual void NextFrameGUI() {  }
        virtual bool IsFullScreen() { return false; }

        SR_NODISCARD virtual void* GetHandle() const = 0;

        virtual bool Initialize(const std::string& name,
                const SR_MATH_NS::IVector2& position,
                const SR_MATH_NS::UVector2& size,
                bool fullScreen, bool resizable) = 0;

    protected:
        const PipelineType m_pipeline;
        const WindowType m_type;

        bool m_headerEnabled = true;
        bool m_collapsed = false;
        bool m_maximize = false;
        bool m_isValid = false;
        bool m_eventHandlerIsRun = false;

        ResizeCallback m_resizeCallback;
        MoveCallback m_moveCallback;
        ScrollCallback m_scrollCallback;
        FocusCallback m_focusCallback;
        CloseCallback m_closeCallback;

        WindowState m_state = WindowState::Default;

        SR_MATH_NS::IVector2 m_position;
        SR_MATH_NS::UVector2 m_size;
        SR_MATH_NS::UVector2 m_surfaceSize;

    };
}

#endif //SR_ENGINE_BASICWINDOW_IMPL_H