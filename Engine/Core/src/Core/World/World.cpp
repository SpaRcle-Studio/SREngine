//
// Created by Monika on 06.04.2022.
//

#include <Core/World/World.h>

#include <Utils/Types/RawMesh.h>

#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Render/RenderScene.h>

#include <assimp/scene.h>

namespace SR_CORE_NS {
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

        gameObject->SetEnabled(enabled);

        gameObject->SetTransform(SR_UTILS_NS::Transform::Load(
                marshal,
                gameObject.Get()
        ));

        if (hasTag) {
            gameObject->SetTag(tag);
        }

        /// ----------------------

        auto&& componentManager = Helper::ComponentManager::Instance();
        componentManager.LoadComponents([&](SR_HTYPES_NS::DataStorage& context) -> bool {
            context.SetPointer<SR_GRAPH_NS::Window>(Engine::Instance().GetWindow());

            auto&& componentCount = marshal.Read<uint32_t>();

            SRAssert2(componentCount <= 2048, "While loading the component errors occured!");

            for (uint32_t i = 0; i < componentCount; ++i) {
                auto&& bytesCount = marshal.Read<uint64_t>();
                auto&& position = marshal.GetPosition();
                /// TODO: use entity id
                auto&& compEntityId = marshal.Read<uint64_t>();

                if (auto&& component = componentManager.Load(marshal)) {
                    gameObject->LoadComponent(component);
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
                if (auto&& mesh = SR_GTYPES_NS::Mesh::Load(rawMesh->GetResourceId(), SR_GTYPES_NS::MeshType::Static, node->mMeshes[i])) {
                    ptr->LoadComponent(dynamic_cast<SR_UTILS_NS::Component *>(mesh));
                }
                else {
                    SRHalt("failed to load mesh!");
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

        root->SetName(SR_UTILS_NS::StringUtils::GetBetween(std::string(rawMesh->GetResourceId()), "/", "."));

        return root;
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return GetDataStorage().GetValue<RenderScenePtr>();
    }
}