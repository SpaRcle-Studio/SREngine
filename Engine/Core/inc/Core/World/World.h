//
// Created by Monika on 05.01.2022.
//

#ifndef SRENGINE_WORLD_H
#define SRENGINE_WORLD_H

#include <Core/Engine.h>

#include <World/Scene.h>
#include <Window/Window.h>
#include <ECS/Component.h>
#include <ECS/Transform3D.h>
#include <ECS/GameObject.h>

namespace SR_CORE_NS::World {
    class World : public Helper::World::Scene {
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
