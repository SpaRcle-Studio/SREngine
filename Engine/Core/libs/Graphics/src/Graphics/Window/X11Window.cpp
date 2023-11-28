//
// Created by innerviewer on 06/11/23.
//

#include <Graphics/Window/X11Window.h>

#include <X11/Xutil.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb.h>
#include <xcb/xcb_util.h>

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
                                  //XCB_EVENT_MASK_NO_EVENT |
                                  XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
                                  XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
                                  XCB_EVENT_MASK_BUTTON_MOTION |
                                  XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
                                  XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE |
                                  XCB_EVENT_MASK_PROPERTY_CHANGE | XCB_EVENT_MASK_VISIBILITY_CHANGE |
                                  //XCB_EVENT_MASK_RESIZE_REDIRECT | //XCB_EVENT_MASK_FOCUS_CHANGE |
                                  XCB_EVENT_MASK_FOCUS_CHANGE | XCB_EVENT_MASK_STRUCTURE_NOTIFY
       };

        xcb_create_window(pConnection, 0, window, pScreen->root, position.x, position.y, size.x, size.y,
                           0, InputOutput, pScreen->root_visual, mask, values);

        m_connection = pConnection;
        m_display = pDisplay;
        m_window = window;
        m_surfaceSize = size;
        m_size = size;

        SetResizable(resizable);
        SetFullscreen(fullScreen);

        m_deleteWindowReply = ChangeWMProtocol("WM_DELETE_WINDOW");

        //ChangeWMAllowedActions({"_NET_WM_ACTION_MOVE", "_NET_WM_ACTION_RESIZE"});

        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);

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
        PollEventsHandler();
    }

    void X11Window::Close() {
        if (m_connection) {
            xcb_destroy_window(m_connection, m_window);
            xcb_disconnect(m_connection);

            m_connection = nullptr;
        }

        BasicWindowImpl::Close();
    }

    void X11Window::PollEventsHandler() {
        auto&& event = xcb_poll_for_event(m_connection);
        if (!event) {
            return;
        }

        uint8_t responseType = XCB_EVENT_RESPONSE_TYPE(event);
        if (responseType == 0) {
            SR_ERROR("X11Window::PollEvents() : response type is 0!")
            return;
        }

        if (ImGui::GetCurrentContext()) {
            ImGui_ImplX11_ProcessEvent(event);
        }

        switch (responseType) {
            case XCB_CLIENT_MESSAGE: {
                if ((*(xcb_client_message_event_t*)event).data.data32[0] == (*m_deleteWindowReply).atom) {
                    Close();
                }

                break;
            }
            case XCB_EXPOSE: {
                //xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
                xcb_flush(m_connection);
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
                SR_FALLTHROUGH;
            }
            case XCB_CONFIGURE_NOTIFY: {
                auto&& configureEvent = (xcb_configure_notify_event_t*)event;
                if (configureEvent->width != m_surfaceSize.x || configureEvent->height != m_surfaceSize.y) {
                    if (configureEvent->width > 0 && configureEvent->height > 0) {
                        m_surfaceSize = {configureEvent->width, configureEvent->height};
                        m_size = m_surfaceSize;

                        if (m_resizeCallback) {
                            m_resizeCallback(this, GetSurfaceWidth(), GetSurfaceHeight());
                        }
                    }
                }

                if (ImGui::GetCurrentContext()) {
                    ImGui::GetIO().DisplaySize = ImVec2(configureEvent->width, configureEvent->height);
                }

                break;
            }
            default:
                break;
        }

        free(event);
    }

    std::vector<xcb_intern_atom_reply_t*> X11Window::ChangeWMProtocols(const std::vector<std::string>& protocolNames) {
        std::vector<xcb_intern_atom_reply_t*> replies;
        if (!m_wmProtocols) {
            xcb_intern_atom_cookie_t protocolsAtom = xcb_intern_atom(m_connection, false, 12, "WM_PROTOCOLS");
            m_wmProtocols = xcb_intern_atom_reply(m_connection, protocolsAtom, nullptr);
        }

        for (auto&& protocolName : protocolNames) {
            xcb_intern_atom_cookie_t cookie = xcb_intern_atom(m_connection, false, protocolName.size(), protocolName.c_str());
            xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(m_connection, cookie, nullptr);

            replies.emplace_back(reply);

            xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, m_wmProtocols->atom, XCB_ATOM_ATOM, 32, 1, &(*reply).atom);
        }

        return replies;
    }

    xcb_intern_atom_reply_t* X11Window::ChangeWMProtocol(const std::string &protocolName) {
        if (!m_wmProtocols) {
            xcb_intern_atom_cookie_t protocolsAtom = xcb_intern_atom(m_connection, false, 12, "WM_PROTOCOLS");
            m_wmProtocols = xcb_intern_atom_reply(m_connection, protocolsAtom, nullptr);
        }

        xcb_intern_atom_cookie_t cookie = xcb_intern_atom(m_connection, false, protocolName.size(), protocolName.c_str());
        xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(m_connection, cookie, nullptr);

        xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, m_wmProtocols->atom, XCB_ATOM_ATOM, 32, 1, &(*reply).atom);

        return reply;
    }

    std::vector<xcb_intern_atom_reply_t *> X11Window::ChangeWMAllowedActions(const std::vector<std::string>& actionNames) {
        std::vector<xcb_intern_atom_reply_t*> replies;
        if (!m_wmProtocols) {
            xcb_intern_atom_cookie_t protocolsAtom = xcb_intern_atom(m_connection, false, 12, "_NET_WM_ALLOWED_ACTIONS");
            m_wmProtocols = xcb_intern_atom_reply(m_connection, protocolsAtom, nullptr);
        }

        for (auto&& actionName : actionNames) {
            xcb_intern_atom_cookie_t cookie = xcb_intern_atom(m_connection, false, actionName.size(), actionName.c_str());
            xcb_intern_atom_reply_t* reply = xcb_intern_atom_reply(m_connection, cookie, nullptr);

            replies.emplace_back(reply);

            xcb_change_property(m_connection, XCB_PROP_MODE_REPLACE, m_window, m_wmProtocols->atom, XCB_ATOM_ATOM, 32, 1, &(*reply).atom);
        }

        return replies;
    }
}