

# File Win32Window.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Window**](dir_eceba3be4a9ee281baac1dc94ed42c6c.md) **>** [**Win32Window.h**](Win32Window_8h.md)

[Go to the documentation of this file](Win32Window_8h.md)


```C++
//
// Created by Nikita on 26.03.2021.
//

#ifndef SR_ENGINE_WIN32WINDOW_H
#define SR_ENGINE_WIN32WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>

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
        void PollEvents() override;

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

#endif //SR_ENGINE_WIN32WINDOW_H
```


