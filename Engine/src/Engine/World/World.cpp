//
// Created by Monika on 06.04.2022.
//

#include <Engine/Common/Importers.h>
#include <Engine/World/World.h>
#include <Engine/Engine.h>

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

#ifdef SR_UTILS_ASSIMP
    #include <Utils/Resources/AssimpTools.h>
#endif

namespace SR_CORE_NS {
    SR_UTILS_NS::SceneObject::Ptr World::Instance(SR_HTYPES_NS::RawMesh* pRawMesh) {
        static constexpr auto processMaterial = [](const SR_HTYPES_NS::RawMesh* pRawMesh, uint32_t meshId, SR_GTYPES_NS::Mesh* pMesh) {
        #ifdef SR_UTILS_ASSIMP
            const auto texturePath = SR_UTILS_NS::AssimpTools::GetDiffuseTexturePath(pRawMesh->GetAssimpScene(), meshId);
            if (texturePath.empty()) {
                return;
            }

            if (SR_UTILS_NS::Path(texturePath).IsFile()) {
                if (auto&& pTexture = CoreResLoader::Load<SR_GTYPES_NS::Texture>(SR_UTILS_NS::Path(texturePath))) {
                    pMesh->GetMaterial()->SetTexture("diffuse", pTexture);
                    pTexture->CheckResourceUsage();
                }
            }
            else {
                SR_LOG("World::Instance() : diffuse texture path is not a file: {}", texturePath);
            }
        #endif
        };

        SR_UTILS_NS::Vector<SR_GTYPES_NS::SkinnedMesh::Ptr> skinnedMeshes;

        pRawMesh->ForceLoad();

        SR_UTILS_NS::Vector<SR_UTILS_NS::GameObject::Ptr> nodesPool;
        nodesPool.resize(pRawMesh->GetSceneStructure().GetNodesCount());
        pRawMesh->GetSceneStructure().ForEachNode(true, [&](const SR_HTYPES_NS::MeshSceneStructure::SceneNode& node) {
            auto&& pGameObject = nodesPool.emplace_back(SRNew<SR_UTILS_NS::GameObject>(node.name));
            pGameObject->GetTransform()->SetMatrix(node.localTransform.translation, node.localTransform.rotation, node.localTransform.scale);

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

        const SR_UTILS_NS::StringView resourceId = pRawMesh->GetResourceId();
        auto first = resourceId.find('/');
        if (first == SR_UTILS_NS::StringView::npos) {
            first = 0;
        }

        auto last = resourceId.find('.');
        if (last == SR_UTILS_NS::StringView::npos) {
            last = resourceId.size() - 1;
        }

        nodesPool.front()->SetName(resourceId.substr(first + 1, last - first - 1));

        RegisterSceneObject(nodesPool.front().StaticCast<SR_UTILS_NS::SceneObject>());

        if (!skinnedMeshes.empty()) {
            if (auto&& pSkeleton = SR_ANIMATIONS_NS::Skeleton::ImportSkeletonFromRawMesh(*pRawMesh)) {
                nodesPool.front()->AddComponent(pSkeleton.StaticCast<SR_UTILS_NS::Component>());
                for (auto &&pSkinnedMesh: skinnedMeshes) {
                    pSkinnedMesh->GetSkeletonRef().SetEntityId(pSkeleton->GetEntityId());
                }
            }
        }

        return nodesPool.front().StaticCast<SR_UTILS_NS::SceneObject>();
    }

    World::RenderScenePtr World::GetRenderScene() const {
        return dynamic_cast<SR_GRAPH_NS::RenderScene*>(GetModule("Render"));
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
