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
        };

        std::list<SR_GTYPES_NS::SkinnedMesh::Ptr> skinnedMeshes;

        static const auto isAssimpFbxHelperSuffix = [](std::string_view suffix) -> bool {
            return
                    suffix == "Translation" ||
                    suffix == "PreRotation" ||
                    suffix == "Rotation" ||
                    suffix == "PostRotation" ||
                    suffix == "Scaling" ||
                    suffix == "RotationPivot" ||
                    suffix == "RotationOffset" ||
                    suffix == "ScalingPivot" ||
                    suffix == "ScalingOffset" ||
                    suffix == "GeometricTranslation" ||
                    suffix == "GeometricRotation" ||
                    suffix == "GeometricScaling";
        };

        static const auto isAssimpFbxHelperNode = [](std::string_view name) -> bool {
            constexpr std::string_view tag = "_$AssimpFbx$_";
            const auto pos = name.find(tag);
            if (pos == std::string_view::npos)
                return false;

            const auto suffix = name.substr(pos + tag.size());
            std::string_view baseOut = name.substr(0, pos);

            if (!isAssimpFbxHelperSuffix(suffix))
                return false;

            // ограничиваем только Mixamo (осторожный scope)
            return baseOut.find("mixamorig") != std::string_view::npos ||
                   baseOut.find("Mixamo") != std::string_view::npos;
        };

        static  const std::function<void(aiNode*&, aiMatrix4x4&)> extractPreTransforms = [](aiNode*& node, aiMatrix4x4& parent) {
            aiMatrix4x4 local = node->mTransformation;
            parent = parent * local;

            if (isAssimpFbxHelperNode(node->mName.C_Str())) {
                if (node->mNumChildren > 0) {
                    node = node->mChildren[0];
                    extractPreTransforms(node, parent);
                }
                else {
                    node = nullptr;
                }
            }
        };

        const std::function<SR_UTILS_NS::GameObject::Ptr(aiNode*)> processNode = [&](aiNode* node) -> SR_UTILS_NS::GameObject::Ptr {
            aiMatrix4x4 global;
            extractPreTransforms(node, global);
            if (!node) {
                return {};
            }

            const std::string_view nodeName = node->mName.C_Str();

            // создаём объект (но НЕ применяем transform пока)
            auto obj = Scene::InstanceGameObject(nodeName);

            // =========================
            // CHILDREN FIRST (важно для корректного bake)
            // =========================
            for (uint32_t i = 0; i < node->mNumChildren; ++i) {
                auto child = processNode(node->mChildren[i]);

                obj->AddChild(
                    child.StaticCast<SR_UTILS_NS::SceneObject>()
                );
            }

            // =========================
            // MESHES
            // =========================
            const aiScene* scene =
                static_cast<const aiScene*>(pRawMesh->GetAssimpScene());

            for (uint32_t i = 0; i < node->mNumMeshes; ++i) {

                const uint64_t meshId = node->mMeshes[i];
                const aiMesh* mesh = scene->mMeshes[meshId];

                if (auto pMesh = SR_GTYPES_NS::Mesh::Load(pRawMesh->GetResourcePath(), meshId)) {

                    pMesh->SetMaterial(
                        SR_GRAPH_NS::FileMaterial::LoadAsUnique(
                            GetRenderScene()->GetContext()->GetSettings().defaultMaterial
                        )
                    );

                    if (mesh->mNumBones > 0) {
                        if (auto mat = pMesh->GetMaterial()) {
                            if (auto data = mat->GetMaterialData()) {
                                data->AddShaderDefine("HAS_SKELETON");
                            }
                        }
                    }

                    processMaterial(pRawMesh, meshId, pMesh.Get(), mesh->mMaterialIndex);

                    obj->AddComponent(pMesh.StaticCast<SR_UTILS_NS::Component>());

                    if (auto skinned = pMesh.DynamicCast<SR_GTYPES_NS::SkinnedMesh>()) {
                        skinnedMeshes.emplace_back(skinned);
                    }
                }
                else {
                    SRHalt("failed to load mesh!");
                }
            }

            // =========================
            // APPLY TRANSFORM (НО ТОЛЬКО ЕСЛИ НЕ FBX HELPER)
            // =========================
            aiVector3D scale, rot, trans;
            global.Decompose(scale, rot, trans);

            rot = {
                SR_DEG(rot.x),
                SR_DEG(rot.y),
                SR_DEG(rot.z)
            };

            obj->GetTransform()->Translate(trans.x, trans.y, trans.z);
            obj->GetTransform()->Rotate(rot.x, rot.y, rot.z);
            obj->GetTransform()->Scale(scale.x, scale.y, scale.z);

            return { obj };
        };

        SR_ANIMATIONS_NS::Skeleton::Ptr pSkeleton = nullptr;

        pRawMesh->Execute([&]() -> bool {
            auto&& result = processNode(static_cast<const aiScene*>(pRawMesh->GetAssimpScene())->mRootNode);
            if (SRVerifyFalse(!result)) {
                root = result;
            }

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
