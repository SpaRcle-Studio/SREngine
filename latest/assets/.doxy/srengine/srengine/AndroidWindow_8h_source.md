

# File AndroidWindow.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Window**](dir_eceba3be4a9ee281baac1dc94ed42c6c.md) **>** [**AndroidWindow.h**](AndroidWindow_8h.md)

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

    private:
        static int32_t HandleInput(struct android_app* app, AInputEvent* event);
        static void HandleCmd(struct android_app* app, int32_t cmd);

    };
}

#endif //SR_ENGINE_ANDROIDWINDOW_H
```


