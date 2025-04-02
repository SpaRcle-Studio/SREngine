

# File Canvas.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**UI**](dir_4db2cc8eada578aa57e9f12bf4119b9f.md) **>** [**Canvas.h**](Canvas_8h.md)

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


