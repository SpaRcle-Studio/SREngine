//
// Created by Monika on 11.01.2023.
//

#include <Core/Common/Importers.h>

#include <Utils/Debug.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/Animations/Skeleton.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace SR_CORE_NS {
    bool Importers::ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh, SR_ANIMATIONS_NS::Skeleton* pSkeleton) {
        const aiScene* pScene = pRawMesh->GetAssimpScene();

        if (!pScene->mRootNode) {
            return false;
        }

        const SR_HTYPES_NS::Function<void(aiNode*, SR_ANIMATIONS_NS::Bone*)> processNode = [&](aiNode* node, SR_ANIMATIONS_NS::Bone* pBone) {
            pBone = pSkeleton->AddBone(pBone, node->mName.C_Str(), false);

            for (uint32_t i = 0; i < node->mNumChildren; ++i) {
                processNode(node->mChildren[i], pBone);
            }
        };

        processNode(pScene->mRootNode, pSkeleton->GetRootBone());

        /// если нет сцены, значит загружаем сырой компонент
        if (!pSkeleton->HasScene()) {
            return true;
        }

        return pSkeleton->ReCalculateSkeleton();
    }

    SR_ANIMATIONS_NS::Skeleton* Importers::ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh *pRawMesh) {
        auto&& pSkeleton = SR_UTILS_NS::ComponentManager::Instance().CreateComponent<SR_ANIMATIONS_NS::Skeleton>();
        if (!pSkeleton) {
            SRHalt0();
            return nullptr;
        }

        if (!ImportSkeletonFromRawMesh(pRawMesh, pSkeleton)) {
            SRHalt("Importers::ImportSkeletonFromRawMesh() : failed to import skeleton!");
            pSkeleton->OnDestroy();
            return nullptr;
        }

        return pSkeleton;
    }
}