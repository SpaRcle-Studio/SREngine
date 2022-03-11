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

namespace Framework::Core::World {
    class World : public Helper::World::Scene {
    public:
        explicit World(const std::string& name)
            : Scene(name)
        { }

    private:
        ~World() override = default;

    public:
        void BeginSync() override { Framework::Engine::Instance().GetWindow()->BeginSync(); }
        void EndSync() override { Framework::Engine::Instance().GetWindow()->EndSync(); }
        bool TrySync() override { return Framework::Engine::Instance().GetWindow()->TrySync(); }

        GameObject::Ptr Instance(const Xml::Node& gameObjectXml) override {
            const auto&& tag = gameObjectXml.TryGetAttribute("Tag").ToString("Untagged");
            const auto&& enabled = gameObjectXml.TryGetAttribute("Enabled").ToBool(true);
            const auto&& name = gameObjectXml.GetAttribute("Name").ToString();
            const auto&& id = gameObjectXml.TryGetAttribute("EntityId").ToUInt64(UINT64_MAX);

            GameObject::Ptr gameObject;

            if (id == UINT64_MAX) {
                gameObject = Scene::Instance(name);
            }
            else {
                EntityManager::Instance().GetReserved(id, [&gameObject, name, this]() -> Entity * {
                    return (gameObject = Scene::Instance(name)).DynamicCast<Entity *>();
                });
            }

            if (!gameObject.Valid())
                return gameObject;

            gameObject->SetTransform(Transform3D::Load(gameObjectXml.TryGetNode("Transform3D")));

            auto&& componentManager = Helper::ComponentManager::Instance();

            componentManager.LoadComponents([&](Types::DataStorage& context) -> bool {
                context.SetPointer("Render", Engine::Instance().GetRender());
                context.SetPointer("Window", Engine::Instance().GetWindow());

                for (const auto& componentXml : gameObjectXml.TryGetNode("Components").TryGetNodes()) {
                    if (auto&& component = componentManager.Load(componentXml))
                        gameObject->AddComponent(component);
                    else {
                        SR_WARN("World::Instance() : failed to load \"" + componentXml.Name() + "\" component!")
                    }
                }

                return true;
            });

            for (const auto& childXml : gameObjectXml.TryGetNode("Children").TryGetNodes()) {
                if (auto&& child = Instance(childXml)) {
                    gameObject->AddChild(child);
                }
            }

            return gameObject;
        }
    };
}

#endif //SRENGINE_WORLD_H
