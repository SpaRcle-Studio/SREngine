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
    protected:
        const PipeLine m_pipeLine = PipeLine::Unknown;
        const Type     m_type     = Type::Unknown;

        std::thread m_eventHandler = std::thread();

        std::function<void(BasicWindow*, int, int)> m_callback_resize;
        std::function<void(BasicWindow*, int, int)> m_callback_move;
        std::function<void(BasicWindow*, double, double)> m_callback_scroll;
        std::function<void(BasicWindow*, int)> m_callback_focus;
        std::function<void(BasicWindow*)> m_callback_close;

        uint32_t m_width  = 0;
        uint32_t m_height = 0;

        uint32_t m_realWidth  = 0;
        uint32_t m_realHeight = 0;

        unsigned int m_posX   = 0; // TODO: unsigned?
        unsigned int m_posY   = 0; // TODO: unsigned?

        bool m_collapsed = false;
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
                int32_t posX, int32_t posY,
                uint32_t sizeX, uint32_t sizeY,
                bool fullscreen, bool resizable) { return false; }
    public:
        [[nodiscard]] SR_FORCE_INLINE Type GetType() const { return m_type; }

        [[nodiscard]] virtual SR_FORCE_INLINE uint32_t GetRealWidth()  const { return 0; }
        [[nodiscard]] virtual SR_FORCE_INLINE uint32_t GetRealHeight() const { return 0; }

        [[nodiscard]] virtual SR_FORCE_INLINE uint32_t GetWidth()  const { return 0; }
        [[nodiscard]] virtual SR_FORCE_INLINE uint32_t GetHeight() const { return 0; }
    public:
        [[nodiscard]] virtual Helper::Math::IVector2 GetScreenResolution(uint32_t monitorID) const { return {0,0}; }
        virtual void Resize(unsigned int w, unsigned int h) { }
        virtual void Move(int x, int y) { }
        virtual bool Destroy() { return false; }
        virtual bool Free() { return false; }
        virtual SR_FORCE_INLINE void PollEvents() const { };
        virtual SR_FORCE_INLINE void SwapBuffers() const { };
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsWindowOpen() const { return m_windowOpen; };
        [[nodiscard]] virtual SR_FORCE_INLINE bool IsCollapsed() const { return m_collapsed; };
        virtual SR_FORCE_INLINE bool MakeContextCurrent() { return false; };
        virtual void SetIcon(const char* path) { }
        virtual SR_FORCE_INLINE void SetSwapInterval(int interval) {}
        virtual bool InitGUI() { return false; }
        virtual bool StopGUI() { return false; }
        virtual void NextFrameGUI() {  }
        virtual bool IsFullScreen() { return false; }
    };
}

#endif //GAMEENGINE_BASICWINDOW_H