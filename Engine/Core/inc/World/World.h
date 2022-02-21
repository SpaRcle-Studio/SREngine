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

            auto&& gameObject = Scene::Instance(gameObjectXml.GetAttribute("Name").ToString());
            gameObject->SetTransform(Transform3D::Load(gameObjectXml.TryGetNode("Transform3D")));

            Helper::ComponentManager::Instance().LockContext();

            if (auto&& context = Helper::ComponentManager::Instance().GetContext()) {
                context->SetPointer("Render", Engine::Instance().GetRender());
                context->SetPointer("Window", Engine::Instance().GetWindow());
            }

            for (const auto& childXml : gameObjectXml.TryGetNode("Components").TryGetNodes()) {

            }

            Helper::ComponentManager::Instance().UnlockContext();

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
