//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_EDITOR_H
#define GAMEENGINE_EDITOR_H

#include <Types/Mesh.h>
#include <Render/Camera.h>
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Scene.h>

namespace Framework {
    class Editor {
    public:
        Editor() = delete;
        Editor(Editor&) = delete;
        Editor(const Editor&) = delete;
        ~Editor() = delete;

        // meshName is Resources/Models/Engine/
        inline static bool InstanceBaseGameObject(const std::string &meshName,
                                                  Framework::Helper::Scene *scene,
                                                  Framework::Graphics::Camera *camera) {
            return false;
        }
    };
}

#endif //GAMEENGINE_EDITOR_H
