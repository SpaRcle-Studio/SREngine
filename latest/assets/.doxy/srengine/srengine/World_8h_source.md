

# File World.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**World**](dir_61ddcda44ab5988dd2bd052e2f237885.md) **>** [**World.h**](World_8h.md)

[Go to the documentation of this file](World_8h.md)


```C++
//
// Created by Monika on 05.01.2022.
//

#ifndef SR_ENGINE_WORLD_H
#define SR_ENGINE_WORLD_H

#include <Core/Engine.h>

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


