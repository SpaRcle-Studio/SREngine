//
// Created by Monika on 11.01.2023.
//

#include <Engine/Common/Importers.h>

#include <Utils/Debug.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/ECS/ComponentManager.h>

#include <Graphics/Animations/Skeleton.h>

#ifdef SR_UTILS_ASSIMP
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
    #include <assimp/Importer.hpp>
#endif

namespace SR_CORE_NS {
    bool Importers::ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh* pRawMesh, SR_ANIMATIONS_NS::Skeleton::Ptr pSkeleton) {
    #ifdef SR_UTILS_ASSIMP
        const aiScene* pScene = static_cast<const aiScene*>(pRawMesh->GetAssimpScene());

        if (!pScene->mRootNode) {
            return false;
        }


        pSkeleton->SetRawMesh(pRawMesh);

        const SR_HTYPES_NS::Function<void(aiNode*, SR_ANIMATIONS_NS::Bone*)> processNode = [&](aiNode* node, SR_ANIMATIONS_NS::Bone* pBone) {
            pBone = pSkeleton->AddBone(pBone, node->mName.C_Str(), false);

            for (uint32_t i = 0; i < node->mNumChildren; ++i) {
                processNode(node->mChildren[i], pBone);
            }
        };

        processNode(pScene->mRootNode, pSkeleton->GetRootBone());
    #endif

        /// если нет сцены, значит загружаем сырой компонент
        if (!pSkeleton->HasScene()) {
            return true;
        }

        return pSkeleton->ReCalculateSkeleton();
    }

    SR_ANIMATIONS_NS::Skeleton::Ptr Importers::ImportSkeletonFromRawMesh(const SR_HTYPES_NS::RawMesh *pRawMesh) {
        auto&& pSkeleton = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::Skeleton>();
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