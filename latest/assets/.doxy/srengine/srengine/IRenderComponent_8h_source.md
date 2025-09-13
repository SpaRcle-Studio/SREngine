

# File IRenderComponent.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**IRenderComponent.h**](IRenderComponent_8h.md)

[Go to the documentation of this file](IRenderComponent_8h.md)


```C++
//
// Created by Monika on 22.05.2023.
//

#ifndef SR_ENGINE_I_RENDER_COMPONENT_H
#define SR_ENGINE_I_RENDER_COMPONENT_H

#include <Graphics/macros.h>

#include <Utils/ECS/Component.h>

namespace SR_GRAPH_NS {
    class RenderScene;
}

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


