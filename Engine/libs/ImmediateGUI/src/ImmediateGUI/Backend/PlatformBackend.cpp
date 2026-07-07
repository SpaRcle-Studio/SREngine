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

#ifdef SR_USE_IMGUI
namespace SR_GRAPH_GUI_NS::Immediate {
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