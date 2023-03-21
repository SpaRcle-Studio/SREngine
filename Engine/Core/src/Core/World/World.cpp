//
// Created by Monika on 06.04.2022.
//

#include <Core/World/World.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Render/RenderScene.h>

#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>

#include <assimp/scene.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::GameObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh* pRawMesh) {
        GameObjectPtr root;

        const std::function<GameObjectPtr(aiNode*)> processNode = [&processNode, this, pRawMesh](aiNode* node) -> GameObjectPtr {
            GameObjectPtr ptr = Scene::Instance(node->mName.C_Str());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
                const uint64_t meshId = node->mMeshes[i];
                const bool hasBones = pRawMesh->GetAssimpScene()->mMeshes[meshId]->HasBones();
                const SR_GRAPH_NS::MeshType meshType = hasBones ? SR_GRAPH_NS::MeshType::Skinned : SR_GRAPH_NS::MeshType::Static;

                if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load(pRawMesh->GetResourceId(), meshType, node->mMeshes[i])) {
                    if (hasBones) {
                        pMesh->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/skinned.mat"));
                    }

                    ptr->AddComponent(dynamic_cast<SR_UTILS_NS::Component *>(pMesh));
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

        pRawMesh->Execute([&]() -> bool {
            SRVerifyFalse(!(root = processNode(pRawMesh->GetAssimpScene()->mRootNode)).Valid());
            return true;
        });

        root->SetName(SR_UTILS_NS::StringUtils::GetBetween(std::string(pRawMesh->GetResourceId()), "/", "."));

        return root;
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return GetDataStorage().GetValue<RenderScenePtr>();
    }
}