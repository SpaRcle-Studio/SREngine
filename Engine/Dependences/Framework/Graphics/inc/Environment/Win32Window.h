//
// Created by Nikita on 26.03.2021.
//

#ifndef GAMEENGINE_WIN32WINDOW_H
#define GAMEENGINE_WIN32WINDOW_H

#include <Environment/Basic/BasicWindow.h>

#include <Windows.h>
#include <Utils/StringUtils.h>

namespace Framework::Graphics {
    class Win32Window : public BasicWindow {
    private:
        ~Win32Window() = default;
    public:
        Win32Window() = default;
        Win32Window(Win32Window&) = delete;
        //Win32Window(const Win32Window&) = delete;
    public:
        LRESULT CALLBACK realWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            switch (msg) {
                case (WM_SIZING): {
                    //RECT rect;
                    //GetClientRect(m_hWnd, &rect);
                    //unsigned __int16 x = rect.right - rect.left;
                    //unsigned __int16 y = rect.bottom - rect.top;

                    //this->OnResize(m_width, m_height);

                    return 0;
                }
                case(WM_DESTROY):
                    PostQuitMessage(NULL);
                    this->m_windowOpen = false;
                    return 0;
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }
    private:
        void OnResize(unsigned __int16 width, unsigned __int16 height) {
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
        }

        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
            auto* me = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
            if (me)
                return me->realWndProc(hWnd, message, wParam, lParam);
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    private:
        HWND m_hWnd = nullptr;
        HDC m_hDC = nullptr;
        HINSTANCE m_hInst = nullptr;
    public:
        [[nodiscard]] SR_FORCE_INLINE HINSTANCE GetHINSTANCE() const noexcept { return m_hInst; }
        [[nodiscard]] SR_FORCE_INLINE HWND GetHWND() const noexcept { return m_hWnd; }
    public:
        bool Create(const char* name, int posX, int posY, unsigned int sizeX, unsigned int sizeY, bool fullscreen, bool resizable) override {
            this->m_width  = sizeX;
            this->m_height = sizeY;

            this->m_hInst = GetModuleHandleA(nullptr);

            WNDCLASSEX wcex     = {};
            wcex.cbSize         = sizeof(WNDCLASSEX);
            wcex.style          = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc    = WndProc;
            wcex.hInstance      = m_hInst;
            wcex.hIcon          = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_APPLICATION));
            wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
            wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
            wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszClassName  = TEXT("MyWndClass");

            if (!RegisterClassEx(&wcex))
                return false;

            this->m_hWnd = CreateWindowA(
                    TEXT("MyWndClass"),
                    name,
                    resizable ? WS_OVERLAPPEDWINDOW : WS_OVERLAPPEDWINDOW  ^ WS_THICKFRAME,
                    CW_USEDEFAULT,
                    CW_USEDEFAULT,
                    m_width,
                    m_height,
                    nullptr,
                    nullptr,
                    m_hInst,
                    nullptr);

            if (!this->m_hWnd)
                return false;

            SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

            if (fullscreen)
            {
                // Set new window style and size.
                SetWindowLong(m_hWnd, GWL_STYLE,
                              GetWindowLong(m_hWnd, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME));
                SetWindowLong(m_hWnd, GWL_EXSTYLE,
                              GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~(WS_EX_DLGMODALFRAME |
                                                              WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

                MONITORINFO monitor_info;
                monitor_info.cbSize = sizeof(monitor_info);
                GetMonitorInfo(MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST),
                               &monitor_info);
                RECT rect(monitor_info.rcMonitor);

                LONG width = rect.right - rect.left;
                LONG height = rect.bottom - rect.top;

                SetWindowPos(m_hWnd, NULL, 0, 0,
                             width, height,
                             SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }

            ShowWindow(m_hWnd, SW_SHOWNORMAL);
            //ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
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
        SR_FORCE_INLINE bool MakeContextCurrent(const std::string& pipelineName) override {
            if (pipelineName == "OpenGL") {
                PIXELFORMATDESCRIPTOR pfd =
                        {
                                sizeof(PIXELFORMATDESCRIPTOR),
                                1,
                                PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
                                PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
                                32,                   // Colordepth of the framebuffer.
                                0, 0, 0, 0, 0, 0,
                                0,
                                0,
                                0,
                                0, 0, 0, 0,
                                24,                   // Number of bits for the depthbuffer
                                8,                    // Number of bits for the stencilbuffer
                                0,                    // Number of Aux buffers in the framebuffer.
                                PFD_MAIN_PLANE,
                                0,
                                0, 0, 0
                        };

                HDC ourWindowHandleToDeviceContext = GetDC(m_hWnd);

                int  letWindowsChooseThisPixelFormat;
                letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
                SetPixelFormat(ourWindowHandleToDeviceContext,letWindowsChooseThisPixelFormat, &pfd);

                HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
                wglMakeCurrent (ourWindowHandleToDeviceContext, ourOpenGLRenderingContext);

                //Helper::Debug::Info("Win32Window::MakeContextCurrent() : OpenGL version: " + std::string((char*)glGetString(GL_VERSION)));

                return true;
            } else
                return false;
        }
    };
}

#endif //GAMEENGINE_WIN32WINDOW_H
