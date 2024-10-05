//
// Created by Monika on 06.04.2022.
//

#include <Core/World/World.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Material/FileMaterial.h>

#include <Physics/PhysicsLib.h>
#include <Physics/LibraryImpl.h>

#include <assimp/scene.h>

namespace SR_CORE_NS {
    SR_UTILS_NS::SceneObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh* pRawMesh) {
        GameObjectPtr root;

        std::list<SR_GTYPES_NS::SkinnedMesh*> skinnedMeshes;

        const std::function<GameObjectPtr(aiNode*)> processNode = [&processNode, &skinnedMeshes, this, pRawMesh](aiNode* node) -> GameObjectPtr {
            GameObjectPtr ptr = Scene::InstanceGameObject(node->mName.C_Str());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
                const uint64_t meshId = node->mMeshes[i];
                const int64_t countBones = pRawMesh->GetAssimpScene()->mMeshes[meshId]->mNumBones;
                const SR_GRAPH_NS::MeshType meshType = countBones > 0 ? SR_GRAPH_NS::MeshType::Skinned : SR_GRAPH_NS::MeshType::Static;

                if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load(pRawMesh->GetResourcePath(), meshType, node->mMeshes[i])) {
                    if (countBones > 256) {
                        pMesh->SetMaterial(SR_GRAPH_NS::FileMaterial::Load("Engine/Materials/skinned-384.mat"));
                    }
                    else if (countBones > 128) {
                        pMesh->SetMaterial(SR_GRAPH_NS::FileMaterial::Load("Engine/Materials/skinned-256.mat"));
                    }
                    else if (countBones > 0) {
                        pMesh->SetMaterial(SR_GRAPH_NS::FileMaterial::Load("Engine/Materials/skinned.mat"));
                    }

                    ptr->AddComponent(dynamic_cast<SR_UTILS_NS::Component*>(pMesh));

                    if (pMesh->GetMeshType() == SR_GRAPH_NS::MeshType::Skinned) {
                        skinnedMeshes.emplace_back(dynamic_cast<SR_GTYPES_NS::SkinnedMesh*>(pMesh));
                    }

                    continue;
                }

                SRHalt("failed to load mesh!");
            }

            for (uint32_t i = 0; i < node->mNumChildren; ++i) {
                ptr->AddChild(processNode(node->mChildren[i]).StaticCast<SR_UTILS_NS::SceneObject>());
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

        SR_ANIMATIONS_NS::Skeleton* pSkeleton = nullptr;

        pRawMesh->Execute([&]() -> bool {
            SRVerifyFalse(!(root = processNode(pRawMesh->GetAssimpScene()->mRootNode)).Valid());
            if (!skinnedMeshes.empty() && root) {
                pSkeleton = Importers::ImportSkeletonFromRawMesh(pRawMesh);
            }
            return true;
        });

        if (!root) {
            return SR_UTILS_NS::SceneObject::Ptr();
        }

        root->SetName(SR_UTILS_NS::StringUtils::GetBetween(std::string(pRawMesh->GetResourceId()), "/", "."));

        if (pSkeleton) {
            root->AddComponent(pSkeleton);
            for (auto&& pSkinnedMesh : skinnedMeshes) {
                pSkinnedMesh->GetSkeleton().SetPathTo(pSkeleton);
            }
        }

        return root.StaticCast<SR_UTILS_NS::SceneObject>();
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return GetDataStorage().GetValue<RenderScenePtr>();
    }
}