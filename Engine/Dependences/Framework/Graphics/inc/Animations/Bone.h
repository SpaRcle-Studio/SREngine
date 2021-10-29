//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <EntityComponentSystem/Component.h>
#include <Debug.h>
#include <Types/Mesh.h>
#include <Render/Render.h>

namespace Framework::Graphics::Animations {
    class Bone : public Helper::Component {
    public:
        Bone();
    private:
        ~Bone() = default;
    private:
        Types::Mesh* m_mesh = nullptr;
    public:
        void SetRender(Render* render) {
            if (m_mesh) {
                Helper::Debug::Error("Bone::SetRender() : render is already set!");
            } else if (auto meshes = Types::Mesh::Load("Engine/Bone.obj"); !meshes.empty()) {
                m_mesh = meshes[0];
                render->RegisterMesh(m_mesh);
            } else {
                Helper::Debug::Error("Bone::SetRender() : failed to load mesh!");
            }
        }
        void OnMove(Math::Vector3 value) noexcept override {
            if (m_mesh)
                m_mesh->OnMove(value);
        }
        void OnRotate(Math::Vector3 value) noexcept override {
            if (m_mesh)
                m_mesh->OnRotate(value);
        }
        void OnScaled(Math::Vector3 value) noexcept override {
            if (m_mesh)
                m_mesh->OnScaled(value);
        }
        void OnDestroyGameObject() noexcept override {
            delete this;
        }
        void OnRemoveComponent() noexcept override {
            if (m_mesh)
                m_mesh->OnRemoveComponent();

            OnDestroyGameObject();
        }
        void OnAttachComponent() override {
            Component::OnAttachComponent();
        }
    };
}

#endif //GAMEENGINE_BONE_H
