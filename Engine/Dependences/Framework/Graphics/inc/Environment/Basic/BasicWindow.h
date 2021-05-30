//
// Created by Monika on 20.03.2021.
//

#ifndef GAMEENGINE_BASICWINDOW_H
#define GAMEENGINE_BASICWINDOW_H

#include <macros.h>
#include <functional>
#include <utility>
#include <string>
#include <Math/Vector3.h>

#include <Environment/PipeLine.h>

namespace Framework::Graphics {
    class BasicWindow {
    public:
        enum class Type { Unknown, Win32, X11, GLFW, SDL };
    protected:
        BasicWindow(PipeLine pipeLine, Type type) : m_pipeLine(pipeLine), m_type(type) {

        }
        ~BasicWindow() = default;
        BasicWindow(BasicWindow&) = default;
        //BasicWindow(const BasicWindow&) = default;
    protected:
        const PipeLine m_pipeLine = PipeLine::Unknown;
        const Type     m_type     = Type::Unknown;

        std::thread m_eventHandler = std::thread();

        std::function<void(BasicWindow*, int, int)> m_callback_resize;
        std::function<void(BasicWindow*, int, int)> m_callback_move;
        std::function<void(BasicWindow*, double, double)> m_callback_scroll;
        std::function<void(BasicWindow*, int)> m_callback_focus;
        std::function<void(BasicWindow*)> m_callback_close;

        unsigned int m_width  = 0;
        unsigned int m_height = 0;

        unsigned int m_realWidth  = 0;
        unsigned int m_realHeight = 0;

        unsigned int m_posX   = 0;
        unsigned int m_posY   = 0;

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
        SR_FORCE_INLINE void SetCallbackFocus(std::function<void(BasicWindow*, int)> fun) {
            this->m_callback_focus = std::move(fun);
        }
        SR_FORCE_INLINE void SetCallbackClose(std::function<void(BasicWindow*)> fun) {
            this->m_callback_close = std::move(fun);
        }

        virtual bool RunEventHandler() { return false; }
        virtual bool Create(
                const char* name,
                int posX, int posY,
                unsigned int sizeX, unsigned int sizeY,
                bool fullscreen, bool resizable) { return false; }
    public:
        [[nodiscard]] SR_FORCE_INLINE Type GetType() const noexcept { return m_type; }

        [[nodiscard]] virtual SR_FORCE_INLINE unsigned int GetRealWidth()  const noexcept { return 0; }
        [[nodiscard]] virtual SR_FORCE_INLINE unsigned int GetRealHeight() const noexcept { return 0; }

        [[nodiscard]] virtual SR_FORCE_INLINE unsigned int GetWidth()  const noexcept { return 0; }
        [[nodiscard]] virtual SR_FORCE_INLINE unsigned int GetHeight() const noexcept { return 0; }
    public:
        virtual Helper::Math::Vector2 GetScreenResolution(unsigned int monitorID) const noexcept { return {0,0}; }
        virtual void Resize(unsigned int w, unsigned int h) { }
        virtual void Move(int x, int y) { }
        virtual bool Destroy() { return false; }
        virtual bool Free() { return false; }
        virtual SR_FORCE_INLINE void PollEvents() const noexcept { };
        virtual SR_FORCE_INLINE void SwapBuffers() const noexcept { };
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsWindowOpen() const noexcept { return m_windowOpen; };
        virtual SR_FORCE_INLINE bool MakeContextCurrent() { return false; };
        virtual void SetIcon(const char* path) { }
        virtual SR_FORCE_INLINE void SetSwapInterval(int interval) noexcept {}
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual void NextFrameGUI() {  }
        virtual bool IsFullScreen() {
            return false;
        }
    };
}

#endif //GAMEENGINE_BASICWINDOW_H