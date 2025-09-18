

# File AndroidWindow.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Window**](dir_387552b0934ce9512c4f7c4e31a03e0f.md) **>** [**AndroidWindow.h**](AndroidWindow_8h.md)

[Go to the documentation of this file](AndroidWindow_8h.md)


```C++
//
// Created by Monika on 08.12.2022.
//

#ifndef SR_ENGINE_ANDROIDWINDOW_H
#define SR_ENGINE_ANDROIDWINDOW_H

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

        void PollEvents() override;

        SR_NODISCARD ANativeWindow* GetNativeWindow() const;

        void* GetHandle() const { return GetNativeWindow(); }

    private:
        static int32_t HandleInput(struct android_app* app, AInputEvent* event);
        static void HandleCmd(struct android_app* app, int32_t cmd);

    };
}

#endif //SR_ENGINE_ANDROIDWINDOW_H
```


