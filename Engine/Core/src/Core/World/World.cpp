//
// Created by Monika on 06.04.2022.
//

#include <Core/World/World.h>

#include <Utils/Types/RawMesh.h>

#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Render/RenderScene.h>

#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>

#include <assimp/scene.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::GameObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh *rawMesh) {
        GameObjectPtr root;

        const std::function<GameObjectPtr(aiNode*)> processNode = [&processNode, this, rawMesh](aiNode* node) -> GameObjectPtr {
            GameObjectPtr ptr = Scene::Instance(node->mName.C_Str());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
                if (auto&& mesh = SR_GTYPES_NS::Mesh::Load(rawMesh->GetResourceId(), SR_GTYPES_NS::MeshType::Static, node->mMeshes[i])) {
                    ptr->LoadComponent(dynamic_cast<SR_UTILS_NS::Component *>(mesh));
                    continue;
                }

                SRHalt("failed to load mesh!");
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