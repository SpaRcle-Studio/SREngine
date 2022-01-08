//
// Created by Monika on 05.01.2022.
//

#ifndef SRENGINE_WORLD_H
#define SRENGINE_WORLD_H

#include <World/Scene.h>
#include <Engine.h>
#include <Window/Window.h>

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

    };
}

#endif //SRENGINE_WORLD_H
