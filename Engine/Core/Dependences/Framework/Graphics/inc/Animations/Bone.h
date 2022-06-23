//
// Created by Monika on 19.08.2021.
//

#ifndef GAMEENGINE_BONE_H
#define GAMEENGINE_BONE_H

#include <Utils/ECS/Component.h>

#include <Types/Mesh.h>
#include <Render/Render.h>

namespace SR_GRAPH_NS::Animations {
    class Bone : public SR_UTILS_NS::Component {
        SR_ENTITY_SET_VERSION(1000);
    public:
        Bone();
    private:
        ~Bone() override = default;
    private:
        Types::Mesh* m_mesh = nullptr;
    public:
        static Component* LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage* dataStorage) {
            return nullptr;
        }

        void SetRender(Render* render) {
            if (m_mesh) {
                SR_ERROR("Bone::SetRender() : render is already set!");
            }
            else if (auto meshes = Types::Mesh::Load("Engine/Bone.obj", Types::MeshType::Static); !meshes.empty()) {
                m_mesh = meshes[0];
                render->RegisterMesh(m_mesh);
            }
            else {
                SR_ERROR("Bone::SetRender() : failed to load mesh!");
            }
        }
        void OnMove(const Helper::Math::FVector3& value) override {
            if (m_mesh)
                m_mesh->OnMove(value);
        }
        void OnRotate(const Helper::Math::FVector3& value) override {
            if (m_mesh)
                m_mesh->OnRotate(value);
        }
        void OnScaled(const Helper::Math::FVector3& value) override {
            if (m_mesh)
                m_mesh->OnScaled(value);
        }
        void OnDestroy() override {
            if (m_mesh) {
                m_mesh->OnDestroy();
                m_mesh = nullptr;
            }

            delete this;
        }
    };
}

#endif //GAMEENGINE_BONE_H
