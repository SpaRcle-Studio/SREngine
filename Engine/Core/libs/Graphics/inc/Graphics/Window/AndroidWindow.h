//
// Created by Monika on 08.12.2022.
//

#ifndef SRENGINE_ANDROIDWINDOW_H
#define SRENGINE_ANDROIDWINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>

#include <Utils/Platform/AndroidNativeAppGlue.h>

#include <android/log.h>
#include <android/native_activity.h>
#include <android/configuration.h>

namespace SR_GRAPH_NS {
    class AndroidWindow : public BasicWindowImpl {
        using Super = BasicWindowImpl;
    public:
        explicit AndroidWindow()
            : Super()
        { }

    public:
        bool Initialize(const std::string& name,
                        const SR_MATH_NS::IVector2& position,
                        const SR_MATH_NS::UVector2& size,
                        bool fullScreen, bool resizable) override;

        SR_NODISCARD WindowType GetType() const override { return BasicWindowImpl::WindowType::Android; }

        void PollEvents() const override;

        SR_NODISCARD ANativeWindow* GetNativeWindow() const;

    private:
        static int32_t HandleInput(struct android_app* app, AInputEvent* event);
        static void HandleCmd(struct android_app* app, int32_t cmd);

    };
}

#endif //SRENGINE_ANDROIDWINDOW_H
