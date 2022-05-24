//
// Created by Nikita on 26.03.2021.
//

#ifndef GAMEENGINE_WIN32WINDOW_H
#define GAMEENGINE_WIN32WINDOW_H

#include <Environment/Basic/BasicWindow.h>

#include <Windows.h>
#include <Utils/StringUtils.h>

#include <Events/EventManager.h>
#include <Math/Mathematics.h>

#define BORDERWIDTH  5
#define BORDERSIZE BORDERWIDTH * 2
#define TITLEBARWIDTH  30

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Framework::Graphics {
    const int32_t g_hiddenHeaderHeight = 39;
    const int32_t g_headerHeight = TITLEBARWIDTH;// 31;

    enum class StyleState {
        Wait, Changing, Changed
    };

    static int32_t AbsHeightToWin32(int32_t value, bool headerEnabled) {
        //if (headerEnabled) {
            return value - TITLEBARWIDTH;
        //}

        //return value - 39;
    }

    //static int32_t Win32HeightToAbs(int32_t value) {
    //    return value + 31;
    //}

    static int GetBorderHeight(HWND hWnd) {
        RECT rcClient, rcWind;
        GetClientRect(hWnd, &rcClient);
        GetWindowRect(hWnd, &rcWind);
        return ((rcWind.right - rcWind.left) - rcClient.right) / 2;
        //return ((rcWind.bottom - rcWind.top) - (rcClient.bottom - rcClient.top);
    }

    // border is 39px, maximize 31

    class Win32Window : public BasicWindow {
    private:
        ~Win32Window() = default;
    public:
        Win32Window(PipeLine pipeLine)
            : BasicWindow(pipeLine, Type::Win32) { }
        Win32Window(Win32Window&) = delete;
        //Win32Window(const Win32Window&) = delete;
    public:
        LRESULT CALLBACK realWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            switch (msg) {
                /*case (WM_WINDOWPOSCHANGED): {
                    auto winPos = reinterpret_cast<PWINDOWPOS>(lParam);
                    //Helper::Debug::System(std::to_string(winPos->cx));
                    //Helper::Debug::System(std::to_string(winPos->cy));
                    this->m_width  = winPos->cx;
                    this->m_height = winPos->cy;

                    DWORD styles = GetWindowLongPtr(hwnd,GWL_STYLE);
                    this->m_maximize = styles & WS_MAXIMIZE;

                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }*/
                /*case (WM_SIZE):{
                    ImGui_ImplDX9_InvalidateDeviceObjects();
                    g_d3dpp.BackBufferWidth = LOWORD(lParam);
                    g_d3dpp.BackBufferHeight = HIWORD(lParam);
                    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
                    if (hr == D3DERR_INVALIDCALL)
                        IM_ASSERT(0);
                    ImGui_ImplDX9_CreateDeviceObjects();
                }*/
                /*case (WM_SIZING): {
                    OnResized();
                    return 0;
                }*/
                /*case WM_SIZE: {
                if ((wParam != SIZE_MINIMIZED)) {
                    if (((wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED))) {
                        this->m_realWidth = LOWORD(lParam);
                        this->m_realHeight = HIWORD(lParam);
                        //OnResized();
                    }
                }
                break;
            }*/
                case WM_NCHITTEST: {
                    auto point = POINT { LOWORD(lParam), HIWORD(lParam) };

                    // Convert screen coordinates into client
                    if (!ScreenToClient(m_hWnd, &point)) {
                        SRAssertOnce(false);
                        return 0;
                    }

                    RECT rect;
                    if(!GetClientRect(hwnd, &rect)) {
                        SRAssertOnce(false);
                        return 0;
                    }

                    rect.top -= 8; // делаем проверку выше на 8 пикселей для удобства

                    int width = rect.right - rect.left;
                    int height = rect.bottom - rect.top;

                    // Decide what result message should have
                    if ((std::abs(rect.left + width - point.x) < BORDERSIZE) && (std::abs(rect.top + height - point.y) < BORDERSIZE))
                        return HTBOTTOMRIGHT;
                    else if ((std::abs(rect.left - point.x) < BORDERSIZE) && (std::abs(rect.top + height - point.y) < BORDERSIZE))
                        return HTBOTTOMLEFT;
                    else if ((std::abs(rect.left + width - point.x) < BORDERSIZE) && (std::abs(rect.top - point.y) < BORDERSIZE))
                        return HTTOPRIGHT;
                    else if ((std::abs(rect.left - point.x) < BORDERSIZE) && (std::abs(rect.top - point.y) < BORDERSIZE))
                        return HTTOPLEFT;
                    else if (std::abs(rect.left - point.x) < BORDERSIZE)
                        return HTLEFT;
                    else if (std::abs(rect.top - point.y) < BORDERSIZE)
                        return HTTOP;
                    else if (std::abs(rect.left + width - point.x) < BORDERSIZE)
                        return HTRIGHT;
                    else if (std::abs(rect.top + height - point.y) < BORDERSIZE)
                        return HTBOTTOM;
                    else {
                        return DefWindowProc(hwnd, msg, wParam, lParam);
                    }
                }
                case WM_CLOSE: {
                    Helper::Debug::System("Win32Window::CallBack() : WM_CLOSE event has been received!");
                    Helper::EventManager::Push(Helper::EventManager::Event::Exit);
                    return 0;
                }
                case (WM_WINDOWPOSCHANGED): {
                    DWORD styles = GetWindowLongPtr(hwnd,GWL_STYLE);
                    this->m_maximize = styles & WS_MAXIMIZE;

                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_SETFOCUS: {
                    if (m_callback_focus)
                        m_callback_focus(this, true);
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_KILLFOCUS: {
                    if (m_callback_focus)
                        m_callback_focus(this, false);
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_SIZE: {
                    switch (wParam) {
                        case SIZE_MINIMIZED: m_state = WindowState::Collapsed; break;
                        case SIZE_MAXIMIZED: m_state = WindowState::Maximized; break;
                        case SIZE_RESTORED:  m_state = WindowState::Default;   break;
                        default:
                            break;
                    }

                    if (wParam != SIZE_MINIMIZED) {
                        if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED) {
                            m_surfaceWidth = LOWORD(lParam);
                            m_surfaceHeight = HIWORD(lParam);

                            if (m_surfaceWidth != 0 && m_styleState != StyleState::Changing) {
                                m_width = m_surfaceWidth;
                            }

                            if (m_surfaceHeight != 0 && m_styleState != StyleState::Changing) {
                                m_height = m_headerEnabled ? m_surfaceHeight + 30 : m_surfaceHeight;
                            }

                            m_resizeReason = ResizeReason::None;

                            m_callback_resize(this, GetSurfaceWidth(), GetSurfaceHeight());
                        }
                    }
                    else {
                        m_width = 0;
                        m_height = 0;

                        m_surfaceWidth = 0;
                        m_surfaceHeight = 0;

                        m_callback_resize(this, GetSurfaceWidth(), GetSurfaceHeight());
                    }

                    m_collapsed = m_surfaceWidth == 0 || m_surfaceHeight == 0;

                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_MOUSEWHEEL: {
                    auto wheel = GET_WHEEL_DELTA_WPARAM(wParam);

                    this->m_callback_scroll(this, 0.0, (double)wheel / 22.0 / 5.0);

                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                case WM_STYLECHANGING:
                case WM_STYLECHANGED:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                case WM_DESTROY:
                    PostQuitMessage(0);
                    this->m_windowOpen = false;
                    return 0;
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }
    private:
        [[nodiscard]] Helper::Math::IVector2 GetPosition() const override {
            HWND hWndParent = GetParent(m_hWnd);
            POINT p = {0};

            int32_t offsetY = m_headerEnabled ? (31) : 0;
            int32_t offsetX = m_headerEnabled ? ((16 / 2)) : 0;

            MapWindowPoints(m_hWnd, hWndParent, &p, 1);

            return Helper::Math::IVector2(p.x, p.y + offsetY);
        }

        void Move(int x, int y) override {
            if (m_maximize)
                return;

            RECT rect;
            GetWindowRect(m_hWnd, &rect);

            //! Я ненавижу ебаный WinAPI!!!!!!!!!!!!!!
            //MoveWindow(m_hWnd, x - 16 / 2, y - (31 - 12),
            //MoveWindow(m_hWnd, x - (16 / 2) - 1, y - (39 - 4),

            //int32_t offsetY = m_headerEnabled ? (39 - 4) : 0;
            //int32_t offsetX = m_headerEnabled ? ((16 / 2) - 1) : 0;

            int32_t offsetX = m_headerEnabled ? 8 : 0;
            //int32_t offsetY = m_headerEnabled ? 0 : 0;

            MoveWindow(m_hWnd, x - offsetX, y,
                       (rect.right  - rect.left),
                       (rect.bottom - rect.top), FALSE);
        }

        void Maximize() override {
            ShowWindow(m_hWnd, SW_MAXIMIZE);
        }

        void Restore() override {
            ShowWindow(m_hWnd, SW_RESTORE);
        }

        void Collapse() override {
            ShowWindow(m_hWnd, SW_MINIMIZE);
        }

        void Expand() override {
            ShowWindow(m_hWnd, SW_SHOW);
        }

        void SetHeaderEnabled(bool enable) override {
            if (m_headerEnabled == enable) {
                return;
            }

            m_styleState = StyleState::Changing;

            m_headerEnabled = enable;

            // костыль, чтобы окно всегда получало событие WM_SIZE, не зависимо от того,
            // изменился ли размер, иначе будет deadlock
            // SendMessage(m_hWnd, WM_SIZE, 0, 0);

            if (m_headerEnabled) {
                m_dwStyle |= WS_CAPTION;
                m_dwStyle |= WS_SIZEBOX;
                m_dwStyle |= WS_SYSMENU;
            } else {
                m_dwStyle &= ~WS_CAPTION;
                m_dwStyle &= ~WS_SIZEBOX;
                m_dwStyle &= ~WS_SYSMENU;
            }


            SetWindowLong(m_hWnd, GWL_STYLE, m_dwStyle);
            UpdateWindow(m_hWnd); 

            m_styleState = StyleState::Changed;

            Resize(m_width, m_height);
            Centralize();

            ShowWindow(m_hWnd, SW_SHOW);
        }

        void Centralize() override {
            auto screenSize = GetScreenResolution();

            uint32_t headerSize = m_headerEnabled ? 30 : 0;

            auto posX = (screenSize.x / 2 - m_width / 2);
            auto posY = (screenSize.y / 2 - m_height / 2);

            Move(posX, posY);
        }

        void Resize(uint32_t w, uint32_t h) override {
            Helper::Debug::Log(Helper::Format("Win32Window::Resize() : set new sizes %ux%u", w, h));

            RECT newRect = RECT {
                .left = 0L,
                .top = 0,
                .right = static_cast<LONG>(m_headerEnabled ? w + 8 : w /* + 7 */),
                .bottom = static_cast<LONG>(m_headerEnabled ? h + 1 : h)
            };

            AdjustWindowRectEx(&newRect, m_dwStyle, FALSE, m_dwExStyle);

            //this->m_width  = (rec.right - rec.left);
            //this->m_height = rec.bottom - rec.top;

            m_resizeReason = ResizeReason::AppResize;

            if (!SetWindowPos(m_hWnd, NULL, newRect.left, newRect.top, newRect.right, newRect.bottom, SWP_NOMOVE)) {
                SRAssert(false);
            }
            UpdateWindow(m_hWnd);
        }

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
            if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
                return true;

            if (auto* me = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
                return me->realWndProc(hWnd, message, wParam, lParam);

            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    private:
        HWND                    m_hWnd       = nullptr;
        HDC                     m_hDC        = nullptr;
        HGLRC                   m_hRC        = nullptr;
        HINSTANCE               m_hInst      = nullptr;
        DWORD                   m_dwExStyle  = 0;
        DWORD                   m_dwStyle    = 0;
        std::atomic<StyleState> m_styleState = StyleState::Changed;
    public:
        [[nodiscard]] SR_FORCE_INLINE HINSTANCE GetHINSTANCE() const { return m_hInst; }
        [[nodiscard]] SR_FORCE_INLINE HWND GetHWND() const { return m_hWnd; }
    public:
        SR_FORCE_INLINE void SetSwapInterval(int interval) const {

        }

        [[nodiscard]] uint32_t GetSurfaceWidth()  const override {
            return m_surfaceWidth;
        }
        [[nodiscard]] uint32_t GetSurfaceHeight() const override {
            return m_surfaceHeight;
        }

        [[nodiscard]] Helper::Math::IVector2 GetSize() const override {
            RECT rcClient, rcWind;
            POINT ptDiff;
            GetClientRect(m_hWnd, &rcClient);
            GetWindowRect(m_hWnd, &rcWind);
            ptDiff.x = (rcWind.right - rcWind.left) - rcClient.right;
            ptDiff.y = (rcWind.bottom - rcWind.top) - rcClient.bottom;

            //MoveWindow(hWnd,rcWind.left, rcWind.top, nWidth + ptDiff.x, nHeight + ptDiff.y, TRUE);

            return Helper::Math::IVector2(1600, 900);
        }

        [[nodiscard]] uint32_t GetWidth()  const override {
            return m_width;//GetSize().x;
        }
        [[nodiscard]] uint32_t GetHeight() const override {
            return m_height;//GetSize().y;
        }

        [[nodiscard]] Helper::Math::IVector2 GetScreenResolution() const override {
            //RECT size;
            //SystemParametersInfo(SPI_GETWORKAREA, 0, &size, 0);
            //return { static_cast<int32_t>(size.right), static_cast<int32_t>(size.bottom) };

            auto const hMonitor { ::MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONULL) };

            MONITORINFOEXW monInfo;
            monInfo.cbSize = sizeof(monInfo);
            if (!GetMonitorInfoW(hMonitor, &monInfo))
                return {}; // Error

            auto width = std::abs(monInfo.rcMonitor.left - monInfo.rcMonitor.right);
            auto height = std::abs(monInfo.rcMonitor.top  - monInfo.rcMonitor.bottom);

            return Helper::Math::IVector2(width, height);
        }

        void SetIcon(const char* path) override {
            Helper::Debug::Log("Win32Window::SetIcon() : set icon... \n\tPath: " + std::string(path));

            HICON hWindowIcon    = NULL;
            HICON hWindowIconBig = NULL;

            hWindowIcon    = (HICON)LoadImage(NULL, path, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            hWindowIconBig = (HICON)LoadImage(NULL, path, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
            SendMessage(m_hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon);
            SendMessage(m_hWnd, WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig);
        }

        bool Create(const char* name, int32_t posX, int32_t posY, uint32_t sizeX, uint32_t sizeY, bool fullscreen, bool resizable) override {
            this->m_hInst = GetModuleHandleA(nullptr);

            m_width = sizeX;
            m_height = sizeY;

            sizeY = AbsHeightToWin32(sizeY, m_headerEnabled);

            WNDCLASSEX wndClass;

            wndClass.cbSize = sizeof(WNDCLASSEX);
            wndClass.style = CS_HREDRAW | CS_VREDRAW;
            wndClass.lpfnWndProc = WndProc;
            wndClass.cbClsExtra = 0;
            wndClass.cbWndExtra = 0;
            wndClass.hInstance = m_hInst;
            wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
            wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            wndClass.lpszMenuName = NULL;
            wndClass.lpszClassName = "SREngineWinClass";
            wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

            if (!RegisterClassEx(&wndClass))
                return false;

            m_dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            m_dwStyle = WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            {
                RECT windowRect;
                windowRect.left = 0;
                windowRect.top = 0L;
                windowRect.right = sizeX;
                windowRect.bottom = sizeY;

                AdjustWindowRectEx(&windowRect, m_dwStyle, FALSE, m_dwExStyle);

                auto width = windowRect.right - windowRect.left;
                auto height = windowRect.bottom - windowRect.top;

                m_resizeReason = ResizeReason::WndCreate;

                m_hWnd = CreateWindowEx(
                        0, "SREngineWinClass",
                        name,
                        m_dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                        posX - 8, posY,
                        width,
                        height,
                        nullptr,
                        nullptr,
                        m_hInst,
                        nullptr
                );
            }

            if (!this->m_hWnd)
                return false;

            SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

            ShowWindow(m_hWnd, SW_SHOW);
            SetForegroundWindow(m_hWnd);
            SetFocus(m_hWnd);

            this->m_windowOpen = true;
            this->m_hDC = GetDC(m_hWnd);

            return true;
        }
        SR_FORCE_INLINE void SwapBuffers() const override {
            ::SwapBuffers(m_hDC);
        }
        SR_FORCE_INLINE void PollEvents() const override {
            MSG msg = {};
            while (::PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE)) {
                if (!::GetMessage(&msg, nullptr, 0, 0))
                    break;
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
            }
        }
        SR_FORCE_INLINE bool MakeContextCurrent() override {
            if (m_pipeLine == PipeLine::OpenGL) {
                static  PIXELFORMATDESCRIPTOR pfd=              // pfd Tells Windows How We Want Things To Be
                        {
                                sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
                                1,                                          // Version Number
                                PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
                                PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
                                PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
                                PFD_TYPE_RGBA,                              // Request An RGBA Format
                                24,                                         // Select Our Color Depth
                                0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
                                0,                                          // No Alpha Buffer
                                0,                                          // Shift Bit Ignored
                                0,                                          // No Accumulation Buffer
                                0, 0, 0, 0,                                 // Accumulation Bits Ignored
                                16,                                         // 16Bit Z-Buffer (Depth Buffer)
                                0,                                          // No Stencil Buffer
                                0,                                          // No Auxiliary Buffer
                                PFD_MAIN_PLANE,                             // Main Drawing Layer
                                0,                                          // Reserved
                                0, 0, 0                                     // Layer Masks Ignored
                        };

                auto pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
                SetPixelFormat(m_hDC, pixelFormat, &pfd);

                m_hRC = wglCreateContext(m_hDC);

                wglMakeCurrent(m_hDC, m_hRC);

                return true;
            } else
                return false;
        }
        SR_FORCE_INLINE void SetSwapInterval(int interval) override {
            if (m_pipeLine == PipeLine::OpenGL) {
                typedef BOOL (APIENTRY * wglSwapIntervalEXT_Func)(int);
                wglSwapIntervalEXT_Func wglSwapIntervalEXT =
                wglSwapIntervalEXT_Func(wglGetProcAddress("wglSwapIntervalEXT"));
                if(wglSwapIntervalEXT) wglSwapIntervalEXT(interval); // 1 - чтобы включить
            }
        }
        bool InitGUI() override {
            //Init Win32
            ImGui_ImplWin32_Init(m_hWnd);
            return true;
        }
        bool StopGUI() override {
            ImGui_ImplWin32_Shutdown();
            return true;
        }
        void NextFrameGUI() override {
            ImGui_ImplWin32_NewFrame();
        }
        void* GetHandle() const override {
            return reinterpret_cast<void*>(m_hWnd);
        }
    };
}

#endif //GAMEENGINE_WIN32WINDOW_H