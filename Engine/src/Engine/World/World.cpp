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
#include <Graphics/Types/Camera.h>

#include <Physics/LibraryImpl.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#ifdef SR_UTILS_ASSIMP
    #include <assimp/scene.h>
#endif

namespace SR_CORE_NS {
    SR_UTILS_NS::SceneObject::Ptr World::Instance(const SR_HTYPES_NS::RawMesh* pRawMesh) {
        static std::function processMaterial = [](const SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t meshId, SR_GTYPES_NS::Mesh* pMesh) {
        #ifdef SR_UTILS_ASSIMP
            const aiScene* pScene = static_cast<const aiScene*>(pRawMesh->GetAssimpScene());

            if (pScene->mMeshes[meshId]->mMaterialIndex >= pScene->mNumMaterials) {
                return;
            }

            aiMaterial* pMaterial = pScene->mMaterials[pScene->mMeshes[meshId]->mMaterialIndex];

            aiString diffuseTexturePath;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &diffuseTexturePath) == aiReturn_SUCCESS) {
                if (SR_UTILS_NS::Path(diffuseTexturePath.C_Str()).IsFile()) {
                    if (auto&& pTexture = CoreResLoader::Load<SR_GTYPES_NS::Texture>(std::string_view(diffuseTexturePath.C_Str()))) {
                        pMesh->GetMaterial()->SetTexture("diffuse", pTexture);
                        pTexture->CheckResourceUsage();
                    }
                }
                else {
                    SR_LOG("World::Instance() : diffuse texture path is not a file: {}", diffuseTexturePath.C_Str());
                }
            }
        #endif
        };

        std::list<SR_GTYPES_NS::SkinnedMesh::Ptr> skinnedMeshes;

        SR_UTILS_NS::Vector<SR_UTILS_NS::GameObject::Ptr> nodesPool;
        nodesPool.resize(pRawMesh->GetSceneStructure().GetNodesCount());
        pRawMesh->GetSceneStructure().ForEachNode(true, [&](const SR_HTYPES_NS::MeshSceneStructure::SceneNode& node) {
            auto&& pGameObject = nodesPool.emplace_back(SRNew<SR_UTILS_NS::GameObject>(node.name));
            SR_MATH_NS::FVector3 translation, scale;
            SR_MATH_NS::Quaternion rotation;
            node.transform.Decompose(translation, rotation, scale);
            pGameObject->GetTransform()->SetMatrix(translation, rotation, scale);

            nodesPool[node.index] = pGameObject;

            if (node.parent) {
                nodesPool[node.parent.value()]->AddChild(pGameObject.StaticCast<SR_UTILS_NS::SceneObject>());
            }

            pRawMesh->GetSceneStructure().ForEachMeshOnNode(node.index, [&](auto&& mesh) {
                if (SR_GTYPES_NS::Mesh::Ptr pMesh = SR_GTYPES_NS::Mesh::Load(pRawMesh->GetResourcePath(), mesh.meshId)) {
                    auto&& pMaterial = SR_GRAPH_NS::FileMaterial::LoadAsUnique(GetRenderScene()->GetContext()->GetSettings().defaultMaterial);
                    pMesh->SetMaterial(pMaterial);

                    processMaterial(pRawMesh, mesh.meshId, pMesh.Get());
                    pGameObject->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());
                    if (auto skinned = pMesh.DynamicCast<SR_GTYPES_NS::SkinnedMesh>()) {
                        pMaterial->GetMaterialData()->AddShaderDefine("HAS_SKELETON");
                        skinnedMeshes.emplace_back(skinned);
                    }
                }
            });
        });

        if (nodesPool.empty() || !nodesPool.front()) {
            SR_ERROR("World::Instance() : failed to create game object for root node!");
            return SR_UTILS_NS::SceneObject::Ptr();
        }

        nodesPool.front()->SetName(SR_UTILS_NS::StringUtils::GetBetween(std::string(pRawMesh->GetResourceId()), "/", "."));

        RegisterSceneObject(nodesPool.front().StaticCast<SR_UTILS_NS::SceneObject>());

        if (!skinnedMeshes.empty()) {
            if (auto&& pSkeleton = Importers::ImportSkeletonFromRawMesh(pRawMesh)) {
                nodesPool.front()->AddComponent(pSkeleton.StaticCast<SR_UTILS_NS::Component>());
                for (auto &&pSkinnedMesh: skinnedMeshes) {
                    pSkinnedMesh->GetSkeletonRef().SetEntityId(pSkeleton->GetEntityId());
                }
            }
        }

        return nodesPool.front().StaticCast<SR_UTILS_NS::SceneObject>();
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return GetDataStorage().GetValue<RenderScenePtr>();
    }

    World::GameObjectPtr World::GetMainCamera() const {
        SR_TRACY_ZONE;
        if (auto&& pRenderScene = GetRenderScene()) {
            if (auto&& pCamera = pRenderScene->GetMainCamera()) {
                return pCamera->GetGameObject();
            }
        }
        return nullptr;
    }
}
