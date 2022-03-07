//
// Created by Monika on 20.03.2021.
//

#ifndef GAMEENGINE_BASICWINDOW_H
#define GAMEENGINE_BASICWINDOW_H

#include <macros.h>
#include <functional>
#include <utility>
#include <string>
#include <thread>
#include <atomic>
#include <Math/Vector3.h>

#include <Environment/PipeLine.h>

namespace Framework::Graphics {
    enum class ResizeReason {
        Unknown, None, WndCreate, UserResize, AppResize
    };

    enum class WindowState {
        Default, Collapsed, Maximized, FullScreen
    };

    class BasicWindow {
    public:
        enum class Type { Unknown, Win32, X11, GLFW, SDL };
    protected:
        BasicWindow(PipeLine pipeLine, Type type)
            : m_pipeLine(pipeLine)
            , m_type(type)
            , m_headerEnabled(true) { }
        ~BasicWindow() = default;
        BasicWindow(BasicWindow&) = default;
    protected:
        /// TO_REFACTORING

        const PipeLine m_pipeLine = PipeLine::Unknown;
        const Type     m_type     = Type::Unknown;

        std::thread m_eventHandler = std::thread();

        std::atomic<ResizeReason> m_resizeReason = ResizeReason::None;

        std::function<void(BasicWindow*, int, int)> m_callback_resize;
        std::function<void(BasicWindow*, int, int)> m_callback_move;
        std::function<void(BasicWindow*, double, double)> m_callback_scroll;
        std::function<void(BasicWindow*, bool)> m_callback_focus;
        std::function<void(BasicWindow*)> m_callback_close;

        WindowState m_state = WindowState::Default;

        uint32_t m_absWidth  = 0;
        uint32_t m_absHeight = 0;

        uint32_t m_surfaceWidth  = 0;
        uint32_t m_surfaceHeight = 0;

        int32_t m_posX   = 0;
        int32_t m_posY   = 0;

        bool m_collapsed = false;
        bool m_headerEnabled = true;
        bool m_maximize = false;
        bool m_windowOpen = false;
        bool m_eventHandlerIsRun = false;
    public:
        SR_FORCE_INLINE void SetCallbackResize(std::function<void(BasicWindow*, int, int)> fun) {
            this->m_callback_resize = std::move(fun);
        }
        SR_FORCE_INLINE void SetCallbackMove(std::function<void(BasicWindow*, int, int)> fun) {
            this->m_callback_move = std::move(fun);
        }
        SR_FORCE_INLINE void SetCallbackScroll(std::function<void(BasicWindow*, double, double)> fun) {
            this->m_callback_scroll = std::move(fun);
        }
        SR_FORCE_INLINE void SetCallbackFocus(std::function<void(BasicWindow*, bool)> fun) {
            this->m_callback_focus = std::move(fun);
        }
        SR_FORCE_INLINE void SetCallbackClose(std::function<void(BasicWindow*)> fun) {
            this->m_callback_close = std::move(fun);
        }

        virtual bool RunEventHandler() { return false; }
        virtual bool Create(
                const char* name,
                int32_t posX, int32_t posY,
                uint32_t sizeX, uint32_t sizeY,
                bool fullscreen, bool resizable) { return false; }
    public:
        [[nodiscard]] SR_FORCE_INLINE Type GetType() const { return m_type; }
        [[nodiscard]] SR_FORCE_INLINE WindowState GetState() const { return m_state; }

        [[nodiscard]] virtual uint32_t GetSurfaceWidth()  const { return 0; }
        [[nodiscard]] virtual uint32_t GetSurfaceHeight() const { return 0; }

        [[nodiscard]] virtual uint32_t GetWidth()  const { return 0; }
        [[nodiscard]] virtual uint32_t GetHeight() const { return 0; }

        [[nodiscard]] virtual Helper::Math::IVector2 GetPosition() const { return Helper::Math::IVector2(); }
        [[nodiscard]] virtual Helper::Math::IVector2 GetSize() const { return Helper::Math::IVector2(); }
    public:
        [[nodiscard]] virtual Helper::Math::IVector2 GetScreenResolution() const { return {0,0}; }
        virtual void Resize(unsigned int w, unsigned int h) { }
        virtual void Move(int x, int y) { }
        virtual void Centralize() { }
        virtual void Collapse() { }
        virtual void Expand() { }
        virtual void Maximize() { }
        virtual void Restore() { }
        virtual bool Destroy() { return false; }
        virtual bool Free() { return false; }
        virtual SR_FORCE_INLINE void PollEvents() const { };
        virtual SR_FORCE_INLINE void SwapBuffers() const { };
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsWindowOpen() const { return m_windowOpen; };
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsCollapsed() const { return m_collapsed; };
        virtual SR_FORCE_INLINE bool MakeContextCurrent() { return false; };
        virtual void SetIcon(const char* path) { }
        virtual void SetHeaderEnabled(bool enable) { }
        virtual SR_FORCE_INLINE void SetSwapInterval(int interval) {}
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual void NextFrameGUI() {  }
        virtual bool IsFullScreen() { return false; }
        virtual void* GetHandle() const = 0;
    };
}

#endif //GAMEENGINE_BASICWINDOW_H