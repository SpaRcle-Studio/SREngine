

# File World.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**World**](dir_748c98af40e9646c77253b96f05954cd.md) **>** [**World.h**](World_8h.md)

[Go to the documentation of this file](World_8h.md)


```C++
//
// Created by Monika on 05.01.2022.
//

#ifndef SR_ENGINE_WORLD_H
#define SR_ENGINE_WORLD_H

#include <Engine/Engine.h>

#include <Utils/World/Scene.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

#include <Graphics/Window/Window.h>

namespace SR_GRAPH_NS {
    class RenderScene;
}

namespace SR_CORE_NS {
    class SR_CORE_DLL_API World : public SR_WORLD_NS::Scene {
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
    public:
        World() = default;

    private:
        ~World() override = default;

    public:
        SR_UTILS_NS::SceneObject::Ptr Instance(const SR_HTYPES_NS::RawMesh* rawMesh) override;

    private:
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

    };
}

#endif //SR_ENGINE_WORLD_H
```


