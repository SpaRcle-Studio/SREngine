//
// Created by Monika on 05.01.2022.
//

#ifndef SRENGINE_WORLD_H
#define SRENGINE_WORLD_H

#include <Core/Engine.h>
#include <Window/Window.h>

#include <Utils/World/Scene.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/Transform3D.h>
#include <Utils/ECS/GameObject.h>

namespace SR_CORE_NS::World {
    class World : public SR_WORLD_NS::Scene {
        using GameObjectPtr = SR_UTILS_NS::GameObject::Ptr;
    public:
        explicit World(const std::string& name)
            : Scene(name)
        { }

    private:
        ~World() override = default;

    public:
        SR_UTILS_NS::GameObject::Ptr Instance(SR_HTYPES_NS::Marshal& marshal) override;
        SR_UTILS_NS::GameObject::Ptr Instance(const SR_HTYPES_NS::RawMesh* rawMesh) override;
        void FindObserver() override;

    };
}

#endif //SRENGINE_WORLD_H
