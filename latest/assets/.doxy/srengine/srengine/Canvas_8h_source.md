

# File Canvas.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**UI**](dir_0e9eeef58803927b1310c845186ea8b3.md) **>** [**Canvas.h**](Canvas_8h.md)

[Go to the documentation of this file](Canvas_8h.md)


```C++
//
// Created by Monika on 01.08.2022.
//

#ifndef SR_ENGINE_CANVAS_H
#define SR_ENGINE_CANVAS_H

#include <Utils/ECS/Component.h>
#include <Graphics/Render/RenderScene.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;
}

namespace SR_GRAPH_UI_NS {
    class Canvas : public SR_UTILS_NS::Component {
        SR_CLASS()
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using Super = SR_UTILS_NS::Component;
    public:
        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        void OnAttached() override;
        void OnDestroy() override;

    protected:
        void Update(float_t dt) override;

    private:
        SR_MATH_NS::UVector2 m_size;

        RenderContextPtr m_context;
        RenderScenePtr m_renderScene;

    };
}

#endif //SR_ENGINE_CANVAS_H
```


