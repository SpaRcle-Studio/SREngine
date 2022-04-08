//
// Created by Monika on 05.01.2022.
//

#ifndef SRENGINE_WORLD_H
#define SRENGINE_WORLD_H

#include <World/Scene.h>
#include <Engine.h>
#include <Window/Window.h>
#include <EntityComponentSystem/Component.h>
#include <EntityComponentSystem/Transform3D.h>
#include <EntityComponentSystem/GameObject.h>

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

    };
}

#endif //SRENGINE_WORLD_H
