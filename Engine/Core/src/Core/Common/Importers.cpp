//
// Created by Monika on 11.01.2023.
//

#include <Core/Common/Importers.h>

#include <Utils/Debug.h>
#include <Utils/Types/RawMesh.h>

#include <Graphics/Animations/Skeleton.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace SR_CORE_NS {
    bool Importers::ImportSkeletonFromRawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, SR_ANIMATIONS_NS::Skeleton* pSkeleton) {
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

        return pSkeleton->ReCalculateSkeleton();
    }
}