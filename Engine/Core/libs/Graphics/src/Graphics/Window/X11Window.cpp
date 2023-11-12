//
// Created by innerviewer on 06/11/23.
//

#include <Graphics/Window/X11Window.h>

//#include <X11/Xlib.h>
#include <X11/Xutil.h>
//#include <X11/Xlib-xcb.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb.h>

namespace SR_GRAPH_NS {
    bool X11Window::Initialize(const std::string &name,
           const Utils::Math::IVector2 &position,
           const Utils::Math::UVector2 &size,
           bool fullScreen, bool resizable
   ) {
        SR_LOG("X11Window::Initialize() : creating X11 window...");

        Display* pDisplay = XOpenDisplay(nullptr);
        if (!pDisplay)
        {
            SR_ERROR("X11Window::Initialize() : failed to create X11 display!");
            return false;
        }

        xcb_connection_t* pConnection = XGetXCBConnection(pDisplay);
        if (!pConnection) {
            SR_ERROR("X11Window::Initialize() : failed to create X11 connection!");
            return false;
        }

        const xcb_setup_t* pSetup = xcb_get_setup(pConnection);
        xcb_screen_t* pScreen = (xcb_setup_roots_iterator(pSetup)).data;
        xcb_window_t window = xcb_generate_id (pConnection);

        uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        uint32_t values[2] = {pScreen->white_pixel,
                                  XCB_EVENT_MASK_NO_EVENT |
                                  XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                                  XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                  XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                                  XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE |
                                  XCB_EVENT_MASK_PROPERTY_CHANGE | XCB_EVENT_MASK_VISIBILITY_CHANGE |
                                  XCB_EVENT_MASK_RESIZE_REDIRECT | XCB_EVENT_MASK_FOCUS_CHANGE
       };

        xcb_create_window(pConnection, 0, window, pScreen->root, position.x, position.y, size.x, size.y,
                           0, InputOutput, pScreen->root_visual, mask, values);

        m_connection = pConnection;
        m_display = pDisplay;
        m_window = window;

        SetResizable(resizable);
        SetFullscreen(fullScreen);

        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);

        /*xcb_ewmh_connection_t* ewmhConnection;
        ewmhConnection->connection = m_connection;
        ewmhConnection->nb_screens = 1;
        ewmhConnection->screens = &pScreen;

        auto&& frameExtentsCookie = xcb_ewmh_get_frame_extents(ewmhConnection, window);
        xcb_ewmh_get_extents_reply_t extentsReply;
        xcb_ewmh_get_frame_extents_reply(ewmhConnection, frameExtentsCookie, &extentsReply, nullptr);*/

        //xcb_get_geometry_cookie_t geometryCookie = xcb_get_geometry_unchecked(m_connection, m_window);
        //auto&& geometryReply =  xcb_get_geometry_reply(m_connection, geometryCookie, nullptr);

        //m_surfaceSize = {size.x, size.y - extentsReply.bottom - extentsReply.top};
        m_surfaceSize = size;
        m_size = size;

        //m_surfaceSize.y += 1;

        //free(geometryReply);
        m_isValid = true;
        return true;
    }

    void* X11Window::GetHandle() const {
        return nullptr;
    }

    xcb_connection_t* X11Window::GetConnection() const {
        return m_connection;
    }

    uint32_t X11Window::GetWindow() const {
        return m_window;
    }

    void X11Window::SetResizable(bool resizable) const {
        XSizeHints* pSizeHints = XAllocSizeHints();
        pSizeHints->flags = resizable ? 0L : PMinSize | PMaxSize;
        if(!resizable) {
            XWindowAttributes windowAttributes;
            XGetWindowAttributes((Display*)GetDisplay(), GetWindow(), &windowAttributes);
            pSizeHints->min_width = windowAttributes.width;
            pSizeHints->max_width = windowAttributes.width;
            pSizeHints->min_height = windowAttributes.height;
            pSizeHints->max_height = windowAttributes.height;
        }

        XSetWMNormalHints((Display*)GetDisplay(), GetWindow(), pSizeHints);
        XFree(pSizeHints);
    }

    void X11Window::SetFullscreen(bool fullscreen) const {
        //TODO: (Linux) Finish implementing SetFullscreen() for X11.
    }

    void* X11Window::GetDisplay() const {
        return m_display;
    }

    SR_MATH_NS::IVector2 X11Window::GetScreenResolution() const {
        //TODO: (Linux) Finish implementing GetScreenResolution() for X11.

        return BasicWindowImpl::GetScreenResolution();
        //return SR_MATH_NS::IVector2(width, height);
    }

    void X11Window::PollEvents() {
        auto&& event = xcb_wait_for_event(m_connection);
        if (!event) {
            return;
        }

        switch (event->response_type & ~0x80) {
            case XCB_EXPOSE: {
                //xcb_expose_event_t *expose = (xcb_expose_event_t *)event;

                break;
            }
            case XCB_BUTTON_PRESS: {
                //xcb_button_press_event_t *bp = (xcb_button_press_event_t *)event;
                //print_modifiers (bp->state);

                break;
            }
            case XCB_BUTTON_RELEASE: {
                //xcb_button_release_event_t *br = (xcb_button_release_event_t *)event;
                //print_modifiers(br->state);

                break;
            }
            case XCB_MOTION_NOTIFY: {
                //xcb_motion_notify_event_t *motion = (xcb_motion_notify_event_t *)event;

                break;
            }
            case XCB_ENTER_NOTIFY: {
                //xcb_enter_notify_event_t *enter = (xcb_enter_notify_event_t *)event;

                break;
            }
            case XCB_LEAVE_NOTIFY: {
                //xcb_leave_notify_event_t *leave = (xcb_leave_notify_event_t *)event;

                break;
            }
            case XCB_KEY_PRESS: {
                //xcb_key_press_event_t *kp = (xcb_key_press_event_t *)event;
                //print_modifiers(kp->state);

                break;
            }
            case XCB_KEY_RELEASE: {
                //xcb_key_release_event_t *kr = (xcb_key_release_event_t *)event;
                //print_modifiers(kr->state);

                break;
            }
            case XCB_RESIZE_REQUEST: {
                //auto&& resizeEvent = (xcb_resize_request_event_t *) event;
                //m_surfaceSize = { resizeEvent->width, resizeEvent->height };
                break;
            }
            case XCB_CONFIGURE_NOTIFY: {
                auto&& configureEvent = (xcb_configure_notify_event_t*)event;
                if (configureEvent->width != m_surfaceSize.x || configureEvent->height != m_surfaceSize.y)
                {
                    if (configureEvent->width > 0 && configureEvent->height > 0) {
                        m_surfaceSize.x = configureEvent->width;
                        m_surfaceSize.y = configureEvent->height;

                        if (m_resizeCallback) {
                            m_resizeCallback(this, GetSurfaceWidth(), GetSurfaceHeight());
                        }
                    }
                }
            }
            default:
                break;
        }

        free (event);
    }

    void X11Window::Close() {

        BasicWindowImpl::Close();
    }
}