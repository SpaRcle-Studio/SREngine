

# File IRenderComponent.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**IRenderComponent.h**](IRenderComponent_8h.md)

[Go to the documentation of this file](IRenderComponent_8h.md)


```C++
//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_I_RENDER_COMPONENT_H
#define SR_ENGINE_I_RENDER_COMPONENT_H

#include <Graphics/macros.h>

#include <Utils/ECS/Component.h>

namespace SR_GTYPES_NS {
    class Camera;

    class IRenderComponent : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        using RenderScenePtr = RenderScene*;
        using CameraPtr = SR_HTYPES_NS::SharedPtr<Camera>;

    public:
        void OnEnable() override;
        void OnDisable() override;

        SR_NODISCARD CameraPtr GetCamera() const;
        SR_NODISCARD RenderScenePtr TryGetRenderScene() const;
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

    protected:
        mutable RenderScenePtr m_renderScene = nullptr;

    };
}

#endif //SR_ENGINE_I_RENDER_COMPONENT_H
```


