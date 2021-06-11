//
// Created by Nikita on 26.03.2021.
//

#ifndef GAMEENGINE_WIN32WINDOW_H
#define GAMEENGINE_WIN32WINDOW_H

#include <Environment/Basic/BasicWindow.h>

#include <iostream>
#include <Windows.h>
#include <Utils/StringUtils.h>

#include <imgui.h>
#include <imgui_impl_win32.h>

#include <Events/EventManager.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Framework::Graphics {
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
        Win32Window(PipeLine pipeLine) : BasicWindow(pipeLine, Type::Win32) {

        }
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
                case WM_SIZE: {
                    if ((wParam != SIZE_MINIMIZED)) {
                        if (((wParam == SIZE_MAXIMIZED) || (wParam == SIZE_RESTORED))) {
                            //Helper::Debug::Log("Win32Window::CallBack() : resize...");

                            m_realWidth = LOWORD(lParam);
                            m_realHeight = HIWORD(lParam);
                            this->m_callback_resize(this, GetRealWidth(), GetRealHeight());
                        }
                    } else {
                        m_realWidth = 0;
                        m_realHeight = 0;
                        this->m_callback_resize(this, GetRealWidth(), GetRealHeight());
                    }
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }

                case WM_MOUSEWHEEL: {
                    auto wheel = GET_WHEEL_DELTA_WPARAM(wParam);

                    this->m_callback_scroll(this, 0.0, (double)wheel / 10.0);

                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }

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

                case(WM_DESTROY):
                    PostQuitMessage(NULL);
                    this->m_windowOpen = false;
                    return 0;
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }
    private:
        void Move(int x, int y) override {
            if (m_maximize)
                return;

            RECT rect;
            GetWindowRect(m_hWnd, &rect);

            //! Я ненавижу ебаный WinAPI!!!!!!!!!!!!!!
            //MoveWindow(m_hWnd, x - 16 / 2, y - (31 - 12),
            MoveWindow(m_hWnd, x - (16 / 2) - 1, y - (39 - 4),
                       (rect.right  - rect.left),
                       (rect.bottom - rect.top), FALSE);
        }
        /*void OnResize(unsigned __int16 width, unsigned __int16 height) {
            this->m_width = width;
            this->m_height = height;

            RECT rect;
            GetClientRect(m_hWnd, &rect);

            DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX | WS_MAXIMIZEBOX;
            DWORD exStyle = WS_EX_APPWINDOW;

            AdjustWindowRectEx(&rect, style, FALSE, exStyle);

            SetWindowLong(m_hWnd, GWL_STYLE, style);
            SetWindowLong(m_hWnd, GWL_EXSTYLE, exStyle);

            SetWindowPos(m_hWnd, HWND_TOP, rect.left, rect.top,
                         rect.right - rect.left, rect.bottom - rect.top,
                         SWP_FRAMECHANGED);

            ShowWindow(m_hWnd, SW_SHOW);
            SetForegroundWindow(m_hWnd);
            SetFocus(m_hWnd);
            UpdateWindow(m_hWnd);
        }*/

        void Resize(unsigned int w, unsigned int h) override {
            /*auto scr = GetScreenResolution(0);

            w += 16;
            h += 7;

            int x = scr.x / 2 - w / 2;
            int y = scr.y / 2 - h / 2;

            SetWindowPos(m_hWnd, nullptr, x, y + 4, (int)w, (int)h, 0);*/

            //Helper::Debug::Error("Win32Window::Resize() : todo!");

            RECT rec;
            rec.left = 0L;
            rec.top = 0L;
            rec.right = w + 8;
            rec.bottom = h;

            AdjustWindowRectEx(&rec, m_dwStyle, FALSE, m_dwExStyle);

            this->m_width  = rec.right  - rec.left;
            this->m_height = rec.bottom - rec.top;

            SetWindowPos(m_hWnd, NULL, rec.left, rec.top, rec.right, rec.bottom, SWP_NOMOVE);
        }

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
            if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
                return true;

            auto* me = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            if (me)
                return me->realWndProc(hWnd, message, wParam, lParam);
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    private:
        HWND m_hWnd = nullptr;
        HDC m_hDC  = nullptr;
        HGLRC m_hRC = nullptr;
        HINSTANCE m_hInst = nullptr;
        DWORD     m_dwExStyle = NULL;
        DWORD     m_dwStyle   = NULL;
    public:
        [[nodiscard]] SR_FORCE_INLINE HINSTANCE GetHINSTANCE() const noexcept { return m_hInst; }
        [[nodiscard]] SR_FORCE_INLINE HWND GetHWND() const noexcept { return m_hWnd; }
    public:
        SR_FORCE_INLINE void SetSwapInterval(int interval) const noexcept {

        }

        [[nodiscard]] SR_FORCE_INLINE unsigned int GetRealWidth()  const noexcept override { return m_realWidth;  }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetRealHeight() const noexcept override { return m_realHeight; }

        [[nodiscard]] SR_FORCE_INLINE unsigned int GetWidth()  const noexcept override { return m_width;  }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetHeight() const noexcept override { return m_height; }

        Helper::Math::Vector2 GetScreenResolution(unsigned int monitorID) const noexcept override {
            RECT size;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &size, 0);
            //GetDeviceCaps(m_hDC, 0);

            return { (double)size.right, (double) size.bottom };
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

        bool Create(const char* name, int posX, int posY, unsigned int sizeX, unsigned int sizeY, bool fullscreen, bool resizable) override {
            this->m_realWidth  = sizeX;
            this->m_realHeight = sizeY;

            this->m_hInst = GetModuleHandleA(nullptr);

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
                windowRect.left = 0L;
                windowRect.top = 0L;
                windowRect.right = sizeX;
                windowRect.bottom = sizeY;

                AdjustWindowRectEx(&windowRect, m_dwStyle, FALSE, m_dwExStyle);

                this->m_width  = windowRect.right - windowRect.left;
                this->m_height = windowRect.bottom - windowRect.top;
            }

            m_hWnd = CreateWindowEx(0,
                                    "SREngineWinClass",
                                    name,
                                    m_dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                    0,
                                    0,
                                    m_width,
                                    m_height,
                                    NULL,
                                    NULL,
                                    m_hInst,
                                    NULL);

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
        SR_FORCE_INLINE void SwapBuffers() const noexcept override {
            ::SwapBuffers(m_hDC);
        }
        SR_FORCE_INLINE void PollEvents() const noexcept override {
            MSG msg = {};
            while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE)) {
                if (!::GetMessage(&msg, NULL, NULL, NULL))
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
        SR_FORCE_INLINE void SetSwapInterval(int interval) noexcept  override {
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
    };
}

#endif //GAMEENGINE_WIN32WINDOW_H
