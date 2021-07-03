//
// Created by Nikita on 16.03.2021.
//

#ifndef GAMEENGINE_EDITOR_H
#define GAMEENGINE_EDITOR_H

#include <Types/Mesh.h>
#include <Render/Camera.h>
#include <EntityComponentSystem/GameObject.h>
#include <EntityComponentSystem/Scene.h>
#include <EntityComponentSystem/Transform.h>

namespace Framework {
    class Editor {
    public:
        Editor() = delete;

        Editor(Editor &) = delete;

        Editor(const Editor &) = delete;

        ~Editor() = delete;

        // meshName is Resources/Models/Engine/
        inline static bool InstanceBaseGameObject(const std::string &meshName,
                                                  Framework::Helper::Scene *scene,
                                                  Framework::Graphics::Camera *camera) {
            if (!scene || !camera)
                return false;

            auto meshes = Graphics::Types::Mesh::Load(meshName);
            if (meshes.size() != 1) {
                Debug::Error("Editor::InstanceBaseGameObject() : failed load \""+meshName+"\" mesh!");

                for (auto a : meshes)
                    a->Destroy();

                return false;
            }

            auto mesh = meshes[0];

            mesh->GetMaterial()->SetColor(0.5, 0.5, 0.5);

            GameObject* gm = scene->Instance("New GameObject");
            gm->AddComponent(mesh);

            gm->GetTransform()->SetPosition(camera->GetGLPosition());
            gm->GetTransform()->SetRotation(camera->GetRotation());

            return true;
        }
    };
}

#endif //GAMEENGINE_EDITOR_H
