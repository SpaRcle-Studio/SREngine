//
// Created by innerviewer on 06/11/23.
//

#include <Graphics/Window/X11Window.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

namespace SR_GRAPH_NS {
    bool X11Window::Initialize(const std::string &name,
           const Utils::Math::IVector2 &position,
           const Utils::Math::UVector2 &size,
           bool fullScreen, bool resizable
   ) {
        SR_LOG("X11Window::Initialize() : creating X11 window...");

        Display* pDisplay;
        pDisplay = XOpenDisplay(nullptr);
        if (!pDisplay) {
            SR_ERROR("X11Window::Initialize() : failed to create X11 display!");
        }

        XEvent event;
        int32_t screen = DefaultScreen(pDisplay);
        GC gc;
        auto&& window = XCreateSimpleWindow(pDisplay, RootWindow(pDisplay, screen), 10, 10, 100, 100, 1,
                                BlackPixel(pDisplay, screen), WhitePixel(pDisplay, screen));

        XSizeHints sizeHints;
        sizeHints.width = 1920;
        sizeHints.height = 1080;

        XSetStandardProperties(pDisplay, window, name.c_str(), name.c_str(), None, nullptr, 0, &sizeHints);
        XSelectInput(pDisplay, window, ExposureMask | ButtonPressMask | KeyPressMask);
        gc = XCreateGC(pDisplay, window, 0,0);
        XMapWindow(pDisplay, window);
        XClearWindow(pDisplay, window);

        /*KeySym key;
        char text[255];
        while (true)
        {
            XNextEvent(pDisplay, &event);
            if(event.type==Expose && event.xexpose.count==0) {
                XClearWindow(pDisplay, window);
            }
            if(event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, nullptr) == 1) {
                if(text[0]=='q') {
                    XDestroyWindow(pDisplay, window);
                    XCloseDisplay(pDisplay);
                }
            }
        }
        return false;*/
    }
}