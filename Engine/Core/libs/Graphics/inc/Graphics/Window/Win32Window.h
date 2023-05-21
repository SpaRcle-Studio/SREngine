//
// Created by Nikita on 26.03.2021.
//

#ifndef GAMEENGINE_WIN32WINDOW_H
#define GAMEENGINE_WIN32WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>

/// TODO: move to platform class
#include <Windows.h>

namespace SR_GRAPH_NS::WinAPI {
    enum class StyleState {
        Wait, Changing, Changed
    };
}

namespace SR_GRAPH_NS {
    class Win32Window : public BasicWindowImpl {
        using Super = BasicWindowImpl;
    public:
        explicit Win32Window()
            : Super()
            , m_styleState(WinAPI::StyleState::Changed)
        { }

    public:
        bool Initialize(const std::string& name,
                        const SR_MATH_NS::IVector2& position,
                        const SR_MATH_NS::UVector2& size,
                        bool fullScreen, bool resizable) override;

        SR_NODISCARD SR_MATH_NS::IVector2 GetPosition() const override;
        SR_NODISCARD SR_FORCE_INLINE HINSTANCE GetHINSTANCE() const { return m_hInst; }
        SR_NODISCARD SR_FORCE_INLINE HWND GetHWND() const { return m_hWnd; }
        SR_NODISCARD SR_MATH_NS::IVector2 GetScreenResolution() const override;
        SR_NODISCARD void* GetHandle() const override;

        SR_NODISCARD SR_MATH_NS::IVector2 ClientToScreen(const SR_MATH_NS::IVector2& pos) const override;
        SR_NODISCARD SR_MATH_NS::IVector2 ScreenToClient(const SR_MATH_NS::IVector2& pos) const override;

        SR_NODISCARD WindowType GetType() const override { return BasicWindowImpl::WindowType::Win32; }
        SR_NODISCARD bool IsVisible() const override;

        void SwapBuffers() const override;
        void PollEvents() const override;

        bool InitGUI() override;
        bool StopGUI() override;
        void NextFrameGUI() override;

        void Close() override;
        void Maximize() override;
        void Restore() override;
        void Collapse() override;
        void Expand() override;
        void Centralize() override;

        void SetHeaderEnabled(bool enable) override;
        void SetIcon(const std::string& path) override;
        void Move(int32_t x, int32_t y) override;
        void Resize(uint32_t w, uint32_t h) override;

    private:
        LRESULT CALLBACK ReadWmdProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        static LRESULT CALLBACK WndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        std::atomic<WinAPI::StyleState> m_styleState;

        SR_MATH_NS::IVector2 m_position;

        HWND      m_hWnd       = nullptr;
        HDC       m_hDC        = nullptr;
        HGLRC     m_hRC        = nullptr;
        HINSTANCE m_hInst      = nullptr;
        DWORD     m_dwExStyle  = 0;
        DWORD     m_dwStyle    = 0;

    };
}

#endif //GAMEENGINE_WIN32WINDOW_H