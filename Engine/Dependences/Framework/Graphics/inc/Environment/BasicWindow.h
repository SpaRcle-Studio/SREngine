//
// Created by Monika on 20.03.2021.
//

#ifndef GAMEENGINE_BASICWINDOW_H
#define GAMEENGINE_BASICWINDOW_H

namespace Framework::Graphics {
    bool MakeFakeWindow(void *winInstance, void *ref_hDC, void *ref_HWND, void *ref_hrc);

    bool MakeRealWindow(void *winInstance, void *ref_hrc, void *ref_hDC, void *ref_HWND);

    void DestroyWindow(void *hDC, void *hwnd, void* hrc);

    void *GetCurrentInstance();
}

#ifdef _WIN32

#include <WinUser.h>
#include <wingdi.h>
#include <Windows.h>
#include <GL/GL.h>

namespace Framework::Graphics {
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    void *GetCurrentInstance() {
        return (void *) GetModuleHandle(NULL);
    }

    void ShowBasicWindow(void* window, bool show){
        ShowWindow((HWND)window, show);
    }
    void* GetDCFromBasicWindow(void* hwnd) {
        return (void*)GetDC((HWND)hwnd);
    }
    void* InitBasicWindow(void* hDC) {
        // Before we can load extensions, we need a dummy OpenGL context, created using a dummy window.
        // We use a dummy window because you can only set the pixel format for a window once. For the
        // real window, we want to use wglChoosePixelFormatARB (so we can potentially specify options
        // that aren't available in PIXELFORMATDESCRIPTOR), but we can't load and use that before we
        // have a context.
        WNDCLASSA window_class = {
                .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
                .lpfnWndProc = DefWindowProcA,
                .hInstance = GetModuleHandle(0),
                .lpszClassName = "Dummy_WGL_djuasiodwa",
        };

        if (!RegisterClassA(&window_class))
            return nullptr;

        HWND dummy_window = CreateWindowExA(
                0,
                window_class.lpszClassName,
                "Dummy OpenGL Window",
                0,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                window_class.hInstance,
                0);

        if (!dummy_window)
            return nullptr;

        HDC dummy_dc = GetDC(dummy_window);

        PIXELFORMATDESCRIPTOR pfd = {
                .nSize = sizeof(pfd),
                .nVersion = 1,
                .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
                .iPixelType = PFD_TYPE_RGBA,
                .cColorBits = 32,
                .cAlphaBits = 8,
                .cDepthBits = 24,
                .cStencilBits = 8,
                .iLayerType = PFD_MAIN_PLANE,
        };

        int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
        if (!pixel_format)
            return nullptr;
        if (!SetPixelFormat(dummy_dc, pixel_format, &pfd))
            return nullptr;

        HGLRC dummy_context = wglCreateContext(dummy_dc);
        if (!dummy_context)
            return nullptr;

        if (!wglMakeCurrent(dummy_dc, dummy_context))
            return nullptr;

        wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress(
                "wglCreateContextAttribsARB"));
        wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress(
                "wglChoosePixelFormatARB"));

        wglMakeCurrent(dummy_dc, 0);
        wglDeleteContext(dummy_context);
        ReleaseDC(dummy_window, dummy_dc);
        DestroyWindow(dummy_window);

        //==============================================================================================================

        int pixel_format_attribs[] = {
                WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
                WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
                WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB,         32,
                WGL_DEPTH_BITS_ARB,         24,
                WGL_STENCIL_BITS_ARB,       8,
                0
        };

        UINT num_formats;
        wglChoosePixelFormatARB((HDC)hDC, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
        if (!num_formats)
            return nullptr;

        DescribePixelFormat((HDC)hDC, pixel_format, sizeof(pfd), &pfd);
        if (!SetPixelFormat((HDC)hDC, pixel_format, &pfd))
            return nullptr;

        // Specify that we want to create an OpenGL 3.3 core profile context
        int gl33_attribs[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
                WGL_CONTEXT_MINOR_VERSION_ARB, 3,
                WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
        };

        HGLRC gl33_context = wglCreateContextAttribsARB((HDC)hDC, 0, gl33_attribs);
        if (!gl33_context)
            return nullptr;

        if (!wglMakeCurrent((HDC)hDC, gl33_context))
            return nullptr;

        return (void*)gl33_context;
    }
    void* CreateBasicWindow(void *winInstance) {
        WNDCLASSEX wndclass = {
                sizeof(WNDCLASSEX), CS_DBLCLKS, WndProc,
                0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
                LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
                0, "SpaRcleWindowClass", LoadIcon(0, IDI_APPLICATION)
        };

        if (!RegisterClassEx(&wndclass))
            return nullptr;

        HWND hwnd = CreateWindowExW(
                0,
                L"SpaRcleWindowClass",
                L"SpaRcle Engine",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                500, 500, 0, 0,
                GetModuleHandle(nullptr), 0);

        return (void*)hwnd;

        /*WNDCLASSA window_class = {
                .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
                .lpfnWndProc = (WNDPROC) WndProc,
                .hInstance = (HINSTANCE)winInstance,
                .hCursor = LoadCursor(nullptr, IDC_ARROW),
                .hbrBackground = nullptr,
                .lpszClassName = "WGL_fdjhsklf",
        };

        if (!RegisterClassA(&window_class))
            return nullptr;

        // Specify a desired width and height, then adjust the rect so the window's client area will be
        // that size.
        RECT rect = {
                .right = 1024,
                .bottom = 576,
        };
        DWORD window_style = WS_OVERLAPPEDWINDOW;
        AdjustWindowRect(&rect, window_style, false);

        HWND window = CreateWindowExA(
                0,
                window_class.lpszClassName,
                "SpaRcle Engine",
                window_style,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                rect.right - rect.left,
                rect.bottom - rect.top,
                nullptr,
                nullptr,
                (HINSTANCE)winInstance,
                nullptr);

        if (!window)
            return nullptr;

        return window;*/
    }

    void DestroyWindow(void *hDC, void *hwnd, void* hrc){
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext((HGLRC)hrc);
        ReleaseDC((HWND)hwnd, (HDC)hDC);
        DestroyWindow((HWND)hwnd);
    }

    bool MakeRealWindow(void *winInstance, void *ref_hrc, void *ref_hDC, void *ref_HWND) {
        ref_HWND = (void*)CreateWindow(
                "coco",
                "ddddd",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                500, 500,
                nullptr,
                nullptr,
                (HINSTANCE)winInstance,
                nullptr
        );

        ref_hDC = (void*)GetDC((HWND)ref_HWND);

        const int iPixelFormatAttribList[] = {
                WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
                WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
                WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
                WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
                WGL_COLOR_BITS_ARB, 32,
                WGL_DEPTH_BITS_ARB, 24,
                WGL_STENCIL_BITS_ARB, 8,
                0 // End of attributes list
        };
        int attributes[] = {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 3
                , WGL_CONTEXT_MINOR_VERSION_ARB, 2
                , WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
                , 0
        };

        int nPixelFormat = 0;
        UINT iNumFormats = 0;

        wglChoosePixelFormatARB((HDC)ref_hDC, iPixelFormatAttribList, NULL, 1, &nPixelFormat, (UINT*)&iNumFormats );

        PIXELFORMATDESCRIPTOR pfd;
        SetPixelFormat((HDC)ref_hDC, nPixelFormat, &pfd);

        ref_hrc = (void*)wglCreateContextAttribsARB((HDC)ref_hDC, nullptr, attributes);

        wglMakeCurrent(NULL, NULL);
        wglMakeCurrent((HDC)ref_hDC, (HGLRC)ref_hrc);

        return true;
    }
    bool MakeFakeWindow(void *winInstance, void *ref_hDC, void *ref_HWND, void *ref_HGLRC) {
        WNDCLASSEX wcex;
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wcex.lpfnWndProc = (WNDPROC) WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = (HINSTANCE) winInstance;
        wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wcex.lpszMenuName = nullptr;
        wcex.lpszClassName = "coco";
        wcex.hIconSm = nullptr;

        //-------------------------------

        if (!RegisterClassEx(&wcex))
            return false;

        PIXELFORMATDESCRIPTOR pfd;

        HWND hwnd = CreateWindow(
                "coco",
                "dddd",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                500, 500,
                nullptr,
                nullptr,
                (HINSTANCE) winInstance,
                nullptr
        );

        HDC hdc = GetDC(hwnd);

        memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 32;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int nPixelFormat = ChoosePixelFormat(hdc, &pfd);

        SetPixelFormat(hdc, nPixelFormat, &pfd);

        HGLRC hrc = wglCreateContext(hdc);

        wglMakeCurrent(hdc, hrc);

        ref_HWND = (void *) hwnd;
        ref_hDC = (void *) hdc;
        ref_HGLRC = (void *) hrc;

        return true;
    }
}

#endif

#endif //GAMEENGINE_BASICWINDOW_H
