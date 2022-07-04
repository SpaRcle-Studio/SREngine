//
// Created by Monika on 06.04.2022.
//

#include <Core/World/World.h>

#include <Utils/Types/RawMesh.h>
#include <assimp/scene.h>
#include <Render/CameraManager.h>

namespace Framework::Core::World {
    SR_UTILS_NS::GameObject::Ptr World::Instance(Framework::Helper::Types::Marshal &marshal)  {
        SR_UTILS_NS::GameObject::Ptr gameObject;

        auto&& entityId = marshal.Read<uint64_t>();

        auto&& version = marshal.Read<uint16_t>();
        if (version != SR_UTILS_NS::GameObject::VERSION) {
            SRAssert2Once(false, "Version is different! Version: " + Helper::ToString(version));
            return gameObject;
        }

        auto&& enabled = marshal.Read<bool>();
        auto&& name = marshal.Read<std::string>();
        auto&& hasTag = marshal.Read<bool>();
        std::string tag;

        if (hasTag) {
            tag = marshal.Read<std::string>();
        }

        if (entityId == UINT64_MAX) {
            gameObject = Scene::Instance(name);
        }
        else {
            SR_UTILS_NS::EntityManager::Instance().GetReserved(entityId, [&gameObject, name, this]() -> SR_UTILS_NS::Entity * {
                return (gameObject = Scene::Instance(name)).DynamicCast<SR_UTILS_NS::Entity *>();
            });
        }

        if (!gameObject.Valid())
            return gameObject;

        /// ----------------------

        gameObject->SetTransform(SR_UTILS_NS::Transform3D::Load(marshal));

        if (hasTag) {
            gameObject->SetTag(tag);
        }

        /// ----------------------

        auto&& componentManager = Helper::ComponentManager::Instance();
        componentManager.LoadComponents([&](SR_HTYPES_NS::DataStorage& context) -> bool {
            context.SetPointer<Render>(Engine::Instance().GetRender());
            context.SetPointer<Window>(Engine::Instance().GetWindow());

            auto&& componentCount = marshal.Read<uint32_t>();

            for (uint32_t i = 0; i < componentCount; ++i) {
                auto&& bytesCount = marshal.Read<uint64_t>();
                auto&& position = marshal.GetPosition();
                /// TODO: use entity id
                auto&& compEntityId = marshal.Read<uint64_t>();

                if (auto&& component = componentManager.Load(marshal)) {
                    gameObject->AddComponent(component);
                }
                else {
                    SR_WARN("World::Instance() : failed to load \"" + SR_UTILS_NS::ComponentManager::Instance().GetLastComponentName() + "\" component!");
                }

                const uint64_t readBytes = marshal.GetPosition() - position;
                const uint64_t lostBytes = bytesCount - readBytes;

                if (lostBytes > 0) {
                    SR_WARN("World::Instance() : bytes were lost when loading the component!\n\tBytes count: " + std::to_string(lostBytes));
                    marshal.SkipBytes(lostBytes);
                }
            }

            return true;
        });

        /// ----------------------

        auto&& childrenCount = marshal.Read<uint32_t>();
        for (uint32_t i = 0; i < childrenCount; ++i) {
            if (auto&& child = Instance(marshal))
                gameObject->AddChild(child);
        }

        return gameObject;
    }

    SR_UTILS_NS::GameObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh *rawMesh) {
        GameObjectPtr root;

        const std::function<GameObjectPtr(aiNode*)> processNode = [&processNode, this, rawMesh](aiNode* node) -> GameObjectPtr {
            GameObjectPtr ptr = Scene::Instance(node->mName.C_Str());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
                if (auto&& mesh = Mesh::Load(rawMesh->GetResourceId(), MeshType::Static, node->mMeshes[i])) {
                    auto&& render = Engine::Instance().GetRender();

                    mesh->SetMaterial(Material::GetDefault());

                    render->RegisterMesh(mesh);

                    ptr->AddComponent(mesh);
                }
                else {
                    SRAssert2(false, "failed to load mesh!");
                }
            }

            for (uint32_t i = 0; i < node->mNumChildren; ++i) {
                ptr->AddChild(processNode(node->mChildren[i]));
            }

            aiVector3D scaling, rotation, translation;
            node->mTransformation.Decompose(scaling, rotation, translation);

            rotation = {
                    (float_t)SR_DEG(rotation.x),
                    (float_t)SR_DEG(rotation.y),
                    (float_t)SR_DEG(rotation.z)
            };

            ptr->GetTransform()->Translate(translation.x, translation.y, translation.z);
            ptr->GetTransform()->Rotate(rotation.x, rotation.y, rotation.z);
            ptr->GetTransform()->Scale(scaling.x, scaling.y, scaling.z);

            return ptr;
        };

        rawMesh->Access([&root, processNode](const aiScene* scene) -> bool {
            SRVerifyFalse(!(root = processNode(scene->mRootNode)).Valid());
            return true;
        });

        root->SetName(SR_UTILS_NS::StringUtils::GetBetween(rawMesh->GetResourceId(), "/", "."));

        return root;
    }

    void World::FindObserver() {
        auto&& cameraManager = SR_GRAPH_NS::CameraManager::Instance();

        SR_GRAPH_NS::CameraManager::LockSingleton();

        if (auto&& pCamera = cameraManager.GetFirstCamera()) {
            if (auto &&gameObject = pCamera->GetParent()) {
                if (gameObject->TryLockIfValid()) {
                    auto&& target = gameObject->GetThis();
                    if (target != m_observer->m_target) {
                        m_observer->SetTarget(target);
                    }
                    gameObject->Unlock();
                }
            }
        }

        SR_GRAPH_NS::CameraManager::UnlockSingleton();
    }
}