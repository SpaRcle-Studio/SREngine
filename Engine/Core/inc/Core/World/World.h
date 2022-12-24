//
// Created by Monika on 05.01.2022.
//

#ifndef SRENGINE_WORLD_H
#define SRENGINE_WORLD_H

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
    class SR_DLL_EXPORT World : public SR_WORLD_NS::Scene {
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
        using CameraPtr = SR_GTYPES_NS::Camera*;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
    public:
        World()
            : Scene("Unnamed")
        { }

        explicit World(const std::string& name)
            : Scene(name)
        { }

    private:
        ~World() override = default;

    public:
        SR_UTILS_NS::GameObject::Ptr Instance(const SR_HTYPES_NS::RawMesh* rawMesh) override;

    private:
        SR_NODISCARD RenderScenePtr GetRenderScene() const;

    };
}

#endif //SRENGINE_WORLD_H
