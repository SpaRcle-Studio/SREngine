//
// Created by Monika on 06.04.2022.
//

#include <Engine/Common/Importers.h>
#include <Engine/World/World.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Material/FileMaterial.h>
#include <Graphics/Types/Texture.h>

#include <Physics/LibraryImpl.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#ifdef SR_UTILS_ASSIMP
    #include <assimp/scene.h>
#endif

namespace SR_CORE_NS {
    SR_UTILS_NS::SceneObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh* pRawMesh) {
        SR_UTILS_NS::GameObject::Ptr root;
    #ifdef SR_UTILS_ASSIMP
        static std::function processMaterial = [](const SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t meshId, SR_GTYPES_NS::Mesh* pMesh, uint64_t materialIndex) {
            const aiScene* pScene = static_cast<const aiScene*>(pRawMesh->GetAssimpScene());

            if (pScene->mMeshes[meshId]->mMaterialIndex >= pScene->mNumMaterials) {
                return;
            }

            aiMaterial* pMaterial = pScene->mMaterials[pScene->mMeshes[meshId]->mMaterialIndex];

            aiString diffuseTexturePath;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexturePath) == aiReturn_SUCCESS) {
                if (auto&& pTexture = SR_GTYPES_NS::Texture::Load(diffuseTexturePath.C_Str())) {
                    pMesh->GetMaterial()->SetTexture("diffuse", pTexture);
                    pTexture->CheckResourceUsage();
                }
            }
        };

        std::list<SR_GTYPES_NS::SkinnedMesh::Ptr> skinnedMeshes;

        const std::function<SR_UTILS_NS::GameObject::Ptr(aiNode*)> processNode = [&processNode, &skinnedMeshes, this, pRawMesh](aiNode* node) -> SR_UTILS_NS::GameObject::Ptr {
            SR_UTILS_NS::GameObject::Ptr ptr = Scene::InstanceGameObject(node->mName.C_Str());

            const aiScene* pScene = static_cast<const aiScene*>(pRawMesh->GetAssimpScene());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
                const uint64_t meshId = node->mMeshes[i];
                const int64_t countBones = pScene->mMeshes[meshId]->mNumBones;
                const SR_GRAPH_NS::MeshType meshType = countBones > 0 ? SR_GRAPH_NS::MeshType::Skinned : SR_GRAPH_NS::MeshType::Static;

                if (auto&& pMesh = SR_GTYPES_NS::Mesh::Load(pRawMesh->GetResourcePath(), meshType, node->mMeshes[i])) {
                    pMesh->SetMaterial(SR_GRAPH_NS::FileMaterial::LoadAsUnique(GetRenderScene()->GetContext()->GetSettings().defaultMaterial));

                    if (countBones > 0) {
                        if (auto&& pMaterial = pMesh->GetMaterial()) {
                            if (auto&& pData = pMaterial->GetMaterialData()) {
                                pData->AddShaderDefine("HAS_SKELETON");
                            }
                        }
                    }

                    processMaterial(pRawMesh, meshId, pMesh.Get(), pScene->mMeshes[meshId]->mMaterialIndex);

                    ptr->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());

                    if (pMesh->GetMeshType() == SR_GRAPH_NS::MeshType::Skinned) {
                        skinnedMeshes.emplace_back(pMesh.StaticCast<SR_GTYPES_NS::SkinnedMesh>());
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

        SR_ANIMATIONS_NS::Skeleton::Ptr pSkeleton = nullptr;

        pRawMesh->Execute([&]() -> bool {
            SRVerifyFalse(!(root = processNode(static_cast<const aiScene*>(pRawMesh->GetAssimpScene())->mRootNode)).Valid());
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
            root->AddComponent(pSkeleton.StaticCast<SR_UTILS_NS::Component>());
            for (auto&& pSkinnedMesh : skinnedMeshes) {
                pSkinnedMesh->GetSkeletonRef().SetEntityId(pSkeleton->GetEntityId());
            }
        }
    #endif

        return root.StaticCast<SR_UTILS_NS::SceneObject>();
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return GetDataStorage().GetValue<RenderScenePtr>();
    }
}
