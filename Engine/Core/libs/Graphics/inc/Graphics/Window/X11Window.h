//
// Created by innerviewer on 06/11/23.
//

#ifndef SRENGINE_X11WINDOW_H
#define SRENGINE_X11WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>

namespace SR_GRAPH_NS {
    class X11Window : public BasicWindowImpl {
        using Super = BasicWindowImpl;
    public:
        explicit X11Window()
                : Super()
        { }

    public:
        bool Initialize(const std::string& name,
                        const SR_MATH_NS::IVector2& position,
                        const SR_MATH_NS::UVector2& size,
                        bool fullScreen, bool resizable) override;

        SR_NODISCARD WindowType GetType() const override { return BasicWindowImpl::WindowType::X11; }

        /*void PollEvents() const override;

        SR_NODISCARD ANativeWindow* GetNativeWindow() const;

    private:
        static int32_t HandleInput(struct android_app* app, AInputEvent* event);
        static void HandleCmd(struct android_app* app, int32_t cmd);*/

    };
}

#endif //SRENGINE_X11WINDOW_H
