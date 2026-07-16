//
// Created by Monika on 07.07.2026.
//

#include <ImmediateGUI/Backend/PlatformBackend.h>
#include <ImmediateGUI/Impl/ImGUI.h>

#include <Utils/Input/InputSystem.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Platform/Platform.h>

#ifdef SR_ANDROID
    #include <imgui/backends/imgui_impl_android.h>
#endif

#ifdef SR_EMSCRIPTEN
    #include <emscripten/html5.h>
    #if defined(__EMSCRIPTEN_PTHREADS__)
        #include <pthread.h>
    #endif
#endif

#ifdef SR_USE_IMGUI
namespace SR_GRAPH_GUI_NS::Immediate {
    const char* EMSCRIPTEN_CANVAS_ID = "#srengine-canvas";
    namespace {
        SR_UTILS_NS::Subscription g_inputTextSubscription;
        std::vector<SR_UTILS_NS::InputTextEvent> g_inputTextEvents;

        bool g_waylandInputInitialized = false;
        SR_PLATFORM_NS::KeyboardState g_prevKeyboardState;
        SR_PLATFORM_NS::MouseState g_prevMouseState;

        ImGuiKey KeyCodeToImGuiKey(SR_UTILS_NS::KeyCode keyCode) {
            switch (keyCode) {
                case SR_UTILS_NS::KeyCode::BackSpace:   return ImGuiKey_Backspace;
                case SR_UTILS_NS::KeyCode::Tab:         return ImGuiKey_Tab;
                case SR_UTILS_NS::KeyCode::Enter:       return ImGuiKey_Enter;
                case SR_UTILS_NS::KeyCode::LShift:      return ImGuiKey_LeftShift;
                case SR_UTILS_NS::KeyCode::LCtrl:       return ImGuiKey_LeftCtrl;
                case SR_UTILS_NS::KeyCode::LAlt:        return ImGuiKey_LeftAlt;
                case SR_UTILS_NS::KeyCode::Escape:      return ImGuiKey_Escape;
                case SR_UTILS_NS::KeyCode::Space:       return ImGuiKey_Space;

                case SR_UTILS_NS::KeyCode::LeftArrow:   return ImGuiKey_LeftArrow;
                case SR_UTILS_NS::KeyCode::UpArrow:     return ImGuiKey_UpArrow;
                case SR_UTILS_NS::KeyCode::RightArrow:  return ImGuiKey_RightArrow;
                case SR_UTILS_NS::KeyCode::DownArrow:   return ImGuiKey_DownArrow;

                case SR_UTILS_NS::KeyCode::Delete:      return ImGuiKey_Delete;
                case SR_UTILS_NS::KeyCode::Insert:      return ImGuiKey_Insert;
                case SR_UTILS_NS::KeyCode::Home:        return ImGuiKey_Home;
                case SR_UTILS_NS::KeyCode::End:         return ImGuiKey_End;
                case SR_UTILS_NS::KeyCode::PageUp:      return ImGuiKey_PageUp;
                case SR_UTILS_NS::KeyCode::PageDown:    return ImGuiKey_PageDown;

                case SR_UTILS_NS::KeyCode::_0: return ImGuiKey_0;
                case SR_UTILS_NS::KeyCode::_1: return ImGuiKey_1;
                case SR_UTILS_NS::KeyCode::_2: return ImGuiKey_2;
                case SR_UTILS_NS::KeyCode::_3: return ImGuiKey_3;
                case SR_UTILS_NS::KeyCode::_4: return ImGuiKey_4;
                case SR_UTILS_NS::KeyCode::_5: return ImGuiKey_5;
                case SR_UTILS_NS::KeyCode::_6: return ImGuiKey_6;
                case SR_UTILS_NS::KeyCode::_7: return ImGuiKey_7;
                case SR_UTILS_NS::KeyCode::_8: return ImGuiKey_8;
                case SR_UTILS_NS::KeyCode::_9: return ImGuiKey_9;

                case SR_UTILS_NS::KeyCode::A: return ImGuiKey_A;
                case SR_UTILS_NS::KeyCode::B: return ImGuiKey_B;
                case SR_UTILS_NS::KeyCode::C: return ImGuiKey_C;
                case SR_UTILS_NS::KeyCode::D: return ImGuiKey_D;
                case SR_UTILS_NS::KeyCode::E: return ImGuiKey_E;
                case SR_UTILS_NS::KeyCode::F: return ImGuiKey_F;
                case SR_UTILS_NS::KeyCode::G: return ImGuiKey_G;
                case SR_UTILS_NS::KeyCode::H: return ImGuiKey_H;
                case SR_UTILS_NS::KeyCode::I: return ImGuiKey_I;
                case SR_UTILS_NS::KeyCode::J: return ImGuiKey_J;
                case SR_UTILS_NS::KeyCode::K: return ImGuiKey_K;
                case SR_UTILS_NS::KeyCode::L: return ImGuiKey_L;
                case SR_UTILS_NS::KeyCode::M: return ImGuiKey_M;
                case SR_UTILS_NS::KeyCode::N: return ImGuiKey_N;
                case SR_UTILS_NS::KeyCode::O: return ImGuiKey_O;
                case SR_UTILS_NS::KeyCode::P: return ImGuiKey_P;
                case SR_UTILS_NS::KeyCode::Q: return ImGuiKey_Q;
                case SR_UTILS_NS::KeyCode::R: return ImGuiKey_R;
                case SR_UTILS_NS::KeyCode::S: return ImGuiKey_S;
                case SR_UTILS_NS::KeyCode::T: return ImGuiKey_T;
                case SR_UTILS_NS::KeyCode::U: return ImGuiKey_U;
                case SR_UTILS_NS::KeyCode::V: return ImGuiKey_V;
                case SR_UTILS_NS::KeyCode::W: return ImGuiKey_W;
                case SR_UTILS_NS::KeyCode::X: return ImGuiKey_X;
                case SR_UTILS_NS::KeyCode::Y: return ImGuiKey_Y;
                case SR_UTILS_NS::KeyCode::Z: return ImGuiKey_Z;

                case SR_UTILS_NS::KeyCode::Super: return ImGuiKey_LeftSuper;

                case SR_UTILS_NS::KeyCode::F1:  return ImGuiKey_F1;
                case SR_UTILS_NS::KeyCode::F2:  return ImGuiKey_F2;
                case SR_UTILS_NS::KeyCode::F3:  return ImGuiKey_F3;
                case SR_UTILS_NS::KeyCode::F4:  return ImGuiKey_F4;
                case SR_UTILS_NS::KeyCode::F5:  return ImGuiKey_F5;
                case SR_UTILS_NS::KeyCode::F6:  return ImGuiKey_F6;
                case SR_UTILS_NS::KeyCode::F7:  return ImGuiKey_F7;
                case SR_UTILS_NS::KeyCode::F8:  return ImGuiKey_F8;
                case SR_UTILS_NS::KeyCode::F9:  return ImGuiKey_F9;
                case SR_UTILS_NS::KeyCode::F10: return ImGuiKey_F10;
                case SR_UTILS_NS::KeyCode::F11: return ImGuiKey_F11;
                case SR_UTILS_NS::KeyCode::F12: return ImGuiKey_F12;

                case SR_UTILS_NS::KeyCode::Plus:       return ImGuiKey_Equal;
                case SR_UTILS_NS::KeyCode::Minus:      return ImGuiKey_Minus;
                case SR_UTILS_NS::KeyCode::Dot:        return ImGuiKey_Period;
                case SR_UTILS_NS::KeyCode::Slash:      return ImGuiKey_Slash;
                case SR_UTILS_NS::KeyCode::BackSlash:  return ImGuiKey_Backslash;
                case SR_UTILS_NS::KeyCode::Tilde:      return ImGuiKey_GraveAccent;
                case SR_UTILS_NS::KeyCode::CapsLock:   return ImGuiKey_CapsLock;
                default: break;
            }
            return ImGuiKey_None;
        }

        void EnsureWaylandInputSubscribed() {
            if (g_inputTextSubscription.IsValid()) {
                return;
            }

            g_inputTextSubscription = SR_UTILS_NS::Input::Instance().Subscribe(SR_UTILS_NS::INPUT_TEXT_EVENT_ID, [](const SR_UTILS_NS::SubscriptionMessage& msg) {
                if (g_inputTextEvents.size() > 64) {
                    g_inputTextEvents.erase(g_inputTextEvents.begin());
                }
                g_inputTextEvents.push_back(std::any_cast<SR_UTILS_NS::InputTextEvent>(msg.GetAny(SR_UTILS_NS::INPUT_TEXT_EVENT_DATA_ID)));
            });
        }

        void WaylandProcessInput() {
            auto&& io = ImGui::GetIO();

            const auto& mouseState = SR_PLATFORM_NS::GetMouseState();
            if (!g_waylandInputInitialized || g_prevMouseState.position.x != mouseState.position.x || g_prevMouseState.position.y != mouseState.position.y) {
                io.AddMousePosEvent(mouseState.position.x, mouseState.position.y);
            }

            for (size_t i = 0; i < mouseState.COUNT; i++) {
                if (!g_waylandInputInitialized || g_prevMouseState.GetButton(i) != mouseState.GetButton(i)) {
                    io.AddMouseButtonEvent(static_cast<int>(i), mouseState.buttonStates[i]);
                }
            }

            const auto& keyboardState = SR_PLATFORM_NS::GetSystemKeyboardState();
            for (const SR_UTILS_NS::KeyCode keyCode : SR_UTILS_NS::KeyCodes) {
                if (!g_waylandInputInitialized || g_prevKeyboardState.Get(keyCode) != keyboardState.Get(keyCode)) {
                    if (const ImGuiKey imguiKey = KeyCodeToImGuiKey(keyCode); imguiKey != ImGuiKey_None) {
                        io.AddKeyEvent(imguiKey, keyboardState.Get(keyCode));
                    }
                }
            }

            const auto& mouseScroll = SR_UTILS_NS::Input::Instance().GetMouseScroll();
            if (mouseScroll.IsNotEmpty()) {
                io.AddMouseWheelEvent(mouseScroll.x, mouseScroll.y);
            }

            for (auto& event : g_inputTextEvents) {
                io.AddInputCharactersUTF8(event.GetText().data());
            }
            g_inputTextEvents.clear();

            g_prevKeyboardState = keyboardState;
            g_prevMouseState = mouseState;
            g_waylandInputInitialized = true;
        }

    #if defined(SR_EMSCRIPTEN)
        bool g_emscriptenInputInitialized = false;
        double g_emscriptenPrevTime = 0.0;

        ImGuiKey DomKeyCodeToImGuiKey(int keyCode) {
            // DOM keyCode values (deprecated but stable enough in Emscripten HTML5 events).
            // We map the most common keys needed by the editor.
            switch (keyCode) {
                case 8:   return ImGuiKey_Backspace;
                case 9:   return ImGuiKey_Tab;
                case 13:  return ImGuiKey_Enter;
                case 16:  return ImGuiKey_LeftShift;
                case 17:  return ImGuiKey_LeftCtrl;
                case 18:  return ImGuiKey_LeftAlt;
                case 27:  return ImGuiKey_Escape;
                case 32:  return ImGuiKey_Space;

                case 37:  return ImGuiKey_LeftArrow;
                case 38:  return ImGuiKey_UpArrow;
                case 39:  return ImGuiKey_RightArrow;
                case 40:  return ImGuiKey_DownArrow;

                case 46:  return ImGuiKey_Delete;
                case 45:  return ImGuiKey_Insert;
                case 36:  return ImGuiKey_Home;
                case 35:  return ImGuiKey_End;
                case 33:  return ImGuiKey_PageUp;
                case 34:  return ImGuiKey_PageDown;

                // Digits
                case 48: return ImGuiKey_0;
                case 49: return ImGuiKey_1;
                case 50: return ImGuiKey_2;
                case 51: return ImGuiKey_3;
                case 52: return ImGuiKey_4;
                case 53: return ImGuiKey_5;
                case 54: return ImGuiKey_6;
                case 55: return ImGuiKey_7;
                case 56: return ImGuiKey_8;
                case 57: return ImGuiKey_9;

                // Letters
                case 65: return ImGuiKey_A;
                case 66: return ImGuiKey_B;
                case 67: return ImGuiKey_C;
                case 68: return ImGuiKey_D;
                case 69: return ImGuiKey_E;
                case 70: return ImGuiKey_F;
                case 71: return ImGuiKey_G;
                case 72: return ImGuiKey_H;
                case 73: return ImGuiKey_I;
                case 74: return ImGuiKey_J;
                case 75: return ImGuiKey_K;
                case 76: return ImGuiKey_L;
                case 77: return ImGuiKey_M;
                case 78: return ImGuiKey_N;
                case 79: return ImGuiKey_O;
                case 80: return ImGuiKey_P;
                case 81: return ImGuiKey_Q;
                case 82: return ImGuiKey_R;
                case 83: return ImGuiKey_S;
                case 84: return ImGuiKey_T;
                case 85: return ImGuiKey_U;
                case 86: return ImGuiKey_V;
                case 87: return ImGuiKey_W;
                case 88: return ImGuiKey_X;
                case 89: return ImGuiKey_Y;
                case 90: return ImGuiKey_Z;

                // Function keys
                case 112: return ImGuiKey_F1;
                case 113: return ImGuiKey_F2;
                case 114: return ImGuiKey_F3;
                case 115: return ImGuiKey_F4;
                case 116: return ImGuiKey_F5;
                case 117: return ImGuiKey_F6;
                case 118: return ImGuiKey_F7;
                case 119: return ImGuiKey_F8;
                case 120: return ImGuiKey_F9;
                case 121: return ImGuiKey_F10;
                case 122: return ImGuiKey_F11;
                case 123: return ImGuiKey_F12;

                // Punctuation (US keyboard common)
                case 187: return ImGuiKey_Equal;
                case 189: return ImGuiKey_Minus;
                case 190: return ImGuiKey_Period;
                case 191: return ImGuiKey_Slash;
                case 220: return ImGuiKey_Backslash;
                case 192: return ImGuiKey_GraveAccent;
                case 20:  return ImGuiKey_CapsLock;

                default: break;
            }
            return ImGuiKey_None;
        }

        void EmscriptenUpdateModifiers(const EmscriptenKeyboardEvent* e) {
            ImGuiIO& io = ImGui::GetIO();
            io.AddKeyEvent(ImGuiMod_Ctrl, e->ctrlKey);
            io.AddKeyEvent(ImGuiMod_Shift, e->shiftKey);
            io.AddKeyEvent(ImGuiMod_Alt, e->altKey);
            io.AddKeyEvent(ImGuiMod_Super, e->metaKey);
        }

        EM_BOOL EmscriptenKeyCallback(int eventType, const EmscriptenKeyboardEvent* e, void* userData) {
            (void)userData;
            ImGuiIO& io = ImGui::GetIO();

            EmscriptenUpdateModifiers(e);

            const ImGuiKey key = DomKeyCodeToImGuiKey(e->keyCode);
            if (key != ImGuiKey_None) {
                const bool down = (eventType == EMSCRIPTEN_EVENT_KEYDOWN);
                io.AddKeyEvent(key, down);
            }

            // Keypress provides text input (UTF-8).
            if (eventType == EMSCRIPTEN_EVENT_KEYPRESS) {
                if (e->key[0] != '\0') {
                    io.AddInputCharactersUTF8(e->key);
                }
            }

            return EM_TRUE;
        }

        EM_BOOL EmscriptenMouseCallback(int eventType, const EmscriptenMouseEvent* e, void* userData) {
            (void)userData;
            ImGuiIO& io = ImGui::GetIO();

            if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE) {
                // canvasX/canvasY are deprecated and may not be reported reliably.
                // targetX/targetY are relative to the event target element (EMSCRIPTEN_CANVAS_ID).
                io.AddMousePosEvent(static_cast<float>(e->targetX), static_cast<float>(e->targetY));
            }
            else if (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN || eventType == EMSCRIPTEN_EVENT_MOUSEUP) {
                const bool down = (eventType == EMSCRIPTEN_EVENT_MOUSEDOWN);
                io.AddMousePosEvent(static_cast<float>(e->targetX), static_cast<float>(e->targetY));
                // Emscripten: 0 left, 1 middle, 2 right. ImGui: 0 left, 1 right, 2 middle.
                int button = e->button;
                if (button == 1) button = 2;
                else if (button == 2) button = 1;

                if (button >= 0 && button < 5) {
                    io.AddMouseButtonEvent(button, down);
                }
            }

            return EM_TRUE;
        }

        EM_BOOL EmscriptenMouseEnterLeaveCallback(int eventType, const EmscriptenMouseEvent* e, void* userData) {
            (void)userData;
            ImGuiIO& io = ImGui::GetIO();
            if (eventType == EMSCRIPTEN_EVENT_MOUSEENTER) {
                io.AddMousePosEvent(static_cast<float>(e->targetX), static_cast<float>(e->targetY));
            }
            else if (eventType == EMSCRIPTEN_EVENT_MOUSELEAVE) {
                io.AddMousePosEvent(-FLT_MAX, -FLT_MAX);
            }
            return EM_TRUE;
        }

        EM_BOOL EmscriptenContextMenuCallback(int eventType, const EmscriptenMouseEvent* e, void* userData) {
            (void)eventType;
            (void)e;
            (void)userData;
            // Prevent browser context menu so RMB works in ImGui.
            return EM_TRUE;
        }

        EM_BOOL EmscriptenWheelCallback(int eventType, const EmscriptenWheelEvent* e, void* userData) {
            (void)eventType;
            (void)userData;
            ImGuiIO& io = ImGui::GetIO();

            // Emscripten wheel delta is in pixels (depending on browser), scale to ImGui "lines".
            const float wheelX = static_cast<float>(-e->deltaX) * 0.01f;
            const float wheelY = static_cast<float>(-e->deltaY) * 0.01f;
            io.AddMouseWheelEvent(wheelX, wheelY);
            return EM_TRUE;
        }

        bool EnsureEmscriptenCallbacksInstalled() {
            if (g_emscriptenInputInitialized) {
                return true;
            }

            // With pthreads enabled (-sUSE_PTHREADS=1) we must proxy DOM events to the main runtime thread.
            // Emscripten default emscripten_set_*_callback uses EM_CALLBACK_THREAD_CONTEXT_CALLING_THREAD, which is unreliable.
        #if defined(__EMSCRIPTEN_PTHREADS__)
            constexpr pthread_t targetThread = EM_CALLBACK_THREAD_CONTEXT_MAIN_RUNTIME_THREAD;

            // Keyboard
            emscripten_set_keydown_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback, targetThread);
            emscripten_set_keyup_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback, targetThread);
            emscripten_set_keypress_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback, targetThread);

            // Mouse (canvas)
            emscripten_set_mousedown_callback_on_thread(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseCallback, targetThread);
            emscripten_set_mouseup_callback_on_thread(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenMouseCallback, targetThread);
            emscripten_set_mousemove_callback_on_thread(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseCallback, targetThread);
            emscripten_set_mouseenter_callback_on_thread(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseEnterLeaveCallback, targetThread);
            emscripten_set_mouseleave_callback_on_thread(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseEnterLeaveCallback, targetThread);

            // Wheel
            emscripten_set_wheel_callback_on_thread(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenWheelCallback, targetThread);
        #else
            // Single-threaded builds.
            emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback);
            emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback);
            emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenKeyCallback);

            emscripten_set_mousedown_callback(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseCallback);
            emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, EmscriptenMouseCallback);
            emscripten_set_mousemove_callback(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseCallback);
            emscripten_set_mouseenter_callback(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseEnterLeaveCallback);
            emscripten_set_mouseleave_callback(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenMouseEnterLeaveCallback);

            emscripten_set_wheel_callback(EMSCRIPTEN_CANVAS_ID, nullptr, EM_FALSE, EmscriptenWheelCallback);
        #endif

            g_emscriptenPrevTime = emscripten_get_now();
            g_emscriptenInputInitialized = true;
            return true;
        }
    #endif
    }

    bool PlatformInit(const PlatformInitInfo& info) {
        switch (info.backend) {
        #if defined(SR_WIN32)
            case PlatformBackend::Win32:
                return ImGui_ImplWin32_Init((HWND)info.window);
        #elif defined(SR_LINUX) && defined(SR_RENDER_GLFW)
            case PlatformBackend::GLFW:
                return ImGui_ImplGlfw_InitForVulkan((GLFWwindow*)info.window, true);
        #elif defined(SR_ANDROID)
            case PlatformBackend::Android:
                return ImGui_ImplAndroid_Init((ANativeWindow*)info.window);
        #elif defined(SR_LINUX) && defined(SR_RENDER_USE_NATIVE_WAYLAND)
            case PlatformBackend::WaylandCustom: {
                EnsureWaylandInputSubscribed();
                ImGuiIO& io = ImGui::GetIO();
                io.BackendPlatformName = "imgui_impl_wayland_custom";
                return true;
            }
        #elif defined(SR_EMSCRIPTEN)
            case PlatformBackend::Emscripten: {
                EnsureEmscriptenCallbacksInstalled();
                ImGuiIO& io = ImGui::GetIO();
                io.BackendPlatformName = "sr_imgui_impl_emscripten_custom";
                return true;
            }
        #endif
            default:
                break;
        }

        return false;
    }

    void PlatformShutdown(PlatformBackend backend) {
        switch (backend) {
        #if defined(SR_WIN32)
            case PlatformBackend::Win32:
                ImGui_ImplWin32_Shutdown();
                break;
        #elif defined(SR_LINUX) && defined(SR_RENDER_GLFW)
            case PlatformBackend::GLFW:
                ImGui_ImplGlfw_Shutdown();
                break;
        #elif defined(SR_ANDROID)
            case PlatformBackend::Android:
                ImGui_ImplAndroid_Shutdown();
                break;
        #elif defined(SR_LINUX) && defined(SR_RENDER_USE_NATIVE_WAYLAND)
            case PlatformBackend::WaylandCustom:
                g_inputTextSubscription = SR_UTILS_NS::Subscription();
                g_inputTextEvents.clear();
                g_waylandInputInitialized = false;
                break;
        #elif defined(SR_EMSCRIPTEN)
            case PlatformBackend::Emscripten:
                g_emscriptenInputInitialized = false;
                break;
        #endif
            default:
                break;
        }
    }

    void PlatformNewFrame(PlatformBackend backend, const PlatformNewFrameInfo& info) {
        switch (backend) {
        #if defined(SR_WIN32)
            case PlatformBackend::Win32:
                ImGui_ImplWin32_NewFrame();
                break;
        #elif defined(SR_LINUX) && defined(SR_RENDER_GLFW)
            case PlatformBackend::GLFW:
                ImGui_ImplGlfw_NewFrame();
                break;
        #elif defined(SR_ANDROID)
            case PlatformBackend::Android:
                ImGui_ImplAndroid_NewFrame();
                break;
        #elif defined(SR_LINUX) && defined(SR_RENDER_USE_NATIVE_WAYLAND)
            case PlatformBackend::WaylandCustom: {
                ImGuiIO& io = ImGui::GetIO();
                io.DisplayFramebufferScale = ImVec2(info.framebufferScale.x, info.framebufferScale.y);
                io.DisplaySize = ImVec2(info.displaySize.x, info.displaySize.y);
                io.DeltaTime = info.deltaTime == 0.0f ? (1.0f / 60.0f) : info.deltaTime;

                EnsureWaylandInputSubscribed();
                WaylandProcessInput();
                break;
            }
        #elif defined(SR_EMSCRIPTEN)
            case PlatformBackend::Emscripten: {
                EnsureEmscriptenCallbacksInstalled();
                double cssW = 0.0, cssH = 0.0;
                if (emscripten_get_element_css_size(EMSCRIPTEN_CANVAS_ID, &cssW, &cssH) == EMSCRIPTEN_RESULT_SUCCESS) {
                    ImGuiIO& io = ImGui::GetIO();
                    io.DisplaySize = ImVec2(static_cast<float>(cssW), static_cast<float>(cssH));
                    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

                    const double now = emscripten_get_now();
                    const double dt = (now - g_emscriptenPrevTime) / 1000.0;
                    g_emscriptenPrevTime = now;
                    io.DeltaTime = static_cast<float>(std::max(0.0, dt));
                }
                break;
            }
        #endif
            default:
                break;
        }
    }
}
#else
namespace SR_GRAPH_GUI_NS::Immediate {
    bool PlatformInit(const PlatformInitInfo& info) { return false; }
    void PlatformShutdown(PlatformBackend backend) { }
    void PlatformNewFrame(PlatformBackend backend, const PlatformNewFrameInfo& info) { }
}
#endif // SR_USE_IMGUI