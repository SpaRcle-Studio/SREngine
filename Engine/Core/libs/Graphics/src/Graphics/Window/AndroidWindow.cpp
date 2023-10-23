//
// Created by Monika on 08.12.2022.
//

#include <Graphics/Window/AndroidWindow.h>

#include <Utils/Platform/Platform.h>

namespace SR_GRAPH_NS {
    bool AndroidWindow::Initialize(const std::string& name,
        const SR_MATH_NS::IVector2& position,
        const SR_MATH_NS::UVector2& size,
        bool fullScreen, bool resizable
    ) {
        auto&& pAndroidApp = (android_app*)SR_PLATFORM_NS::GetInstance();

        pAndroidApp->userData = (void*)this;
        pAndroidApp->onAppCmd = HandleCmd;
        pAndroidApp->onInputEvent = HandleInput;

        return true;
    }

    int32_t AndroidWindow::HandleInput(android_app* app, AInputEvent* event) {
        return 0;
    }

    ANativeWindow* AndroidWindow::GetNativeWindow() const {
        auto&& pAndroidApp = (android_app*)SR_PLATFORM_NS::GetInstance();
        return pAndroidApp->window;
    }

    void AndroidWindow::HandleCmd(android_app* pAndroidApp, int32_t cmd) {
        switch (cmd) {
        case APP_CMD_SAVE_STATE:
            break;
        case APP_CMD_INIT_WINDOW:
            break;
        case APP_CMD_TERM_WINDOW:
            break;
        case APP_CMD_GAINED_FOCUS:
            break;
        case APP_CMD_LOST_FOCUS:
            break;
        default:
            break;
        }
    }

    void SR_GRAPH_NS::AndroidWindow::PollEvents() const {
        auto&& pAndroidApp = (android_app*)SR_PLATFORM_NS::GetInstance();

        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident = ALooper_pollAll(0, nullptr, &events, (void**)&source)) >= 0) {
            // Process this event.
            if (source != nullptr) {
                source->process(pAndroidApp, source);
            }

            // If a sensor has data, process it now.
            /*if (ident == LOOPER_ID_USER) {

            }*/

            // Check if we are exiting.
            if (pAndroidApp->destroyRequested != 0) {
                return;
            }
        }
    }
}
