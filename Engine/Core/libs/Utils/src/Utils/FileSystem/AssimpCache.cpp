//
// Created by Monika on 15.02.2023.
//

#include <Utils/FileSystem/AssimpCache.h>
#include <Utils/Types/Marshal.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/include/assimp/Exporter.hpp>
#include <assimp/include/assimp/cexport.h>

namespace SR_UTILS_NS {
    const uint8_t AssimpCache::SR_ASSIMP_MAX_NUMBER_OF_COLOR_SETS = AI_MAX_NUMBER_OF_COLOR_SETS;
    const uint8_t AssimpCache::SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS = AI_MAX_NUMBER_OF_TEXTURECOORDS;

    bool AssimpCache::Save(const SR_UTILS_NS::Path& path, const aiScene* pScene) const {
        SR_HTYPES_NS::Marshal marshal;

        marshal.Write<uint64_t>(VERSION);

        marshal.Write<std::string>(std::string(pScene->mName.C_Str()));
        marshal.Write<uint64_t>(pScene->mFlags);

        marshal.Write<bool>(pScene->mRootNode); /// has root node
        if (pScene->mRootNode) {
            SaveNode(&marshal, pScene->mRootNode);
        }

        SaveMeshes(&marshal, pScene);
        SaveSkeletons(&marshal, pScene);
        SaveAnimations(&marshal, pScene);

        return marshal.Save(path);
    }

    aiScene* AssimpCache::Load(const Path& path) const {
        auto&& marshal = SR_HTYPES_NS::Marshal::Load(path);
        if (!marshal.Valid()) {
            return nullptr;
        }

        /// version
        if (marshal.Read<uint64_t>() != VERSION) {
            return nullptr;
        }

        auto&& pScene = new aiScene();

        pScene->mName = marshal.Read<std::string>();
        pScene->mFlags = marshal.Read<uint64_t>();

        if (marshal.Read<bool>()) { /// has root node
            LoadNode(&marshal, pScene->mRootNode);
        }

        LoadMeshes(&marshal, pScene);
        LoadSkeletons(&marshal, pScene);
        LoadAnimations(&marshal, pScene);

        return pScene;
    }

    void AssimpCache::SaveAnimations(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const {
        pMarshal->Write<uint64_t>(pScene->mNumAnimations);

        for (uint64_t animationId = 0; animationId < pScene->mNumAnimations; ++animationId) {
            auto&& pAnimation = pScene->mAnimations[animationId];

            pMarshal->Write<std::string>(std::string(pAnimation->mName.C_Str()));
            pMarshal->Write<double_t>(pAnimation->mDuration);
            pMarshal->Write<double_t>(pAnimation->mTicksPerSecond);

            pMarshal->Write<uint64_t>(pAnimation->mNumChannels);

            for (uint64_t channelId = 0; channelId < pAnimation->mNumChannels; ++channelId) {
                auto&& pChannel = pAnimation->mChannels[channelId];

                pMarshal->Write<std::string>(std::string(pChannel->mNodeName.C_Str()));
                pMarshal->Write<uint64_t>(pChannel->mPreState);
                pMarshal->Write<uint64_t>(pChannel->mPostState);

                pMarshal->Write<bool>(pChannel->mPositionKeys);
                if (pChannel->mPositionKeys) {
                    pMarshal->Write<uint64_t>(pChannel->mNumPositionKeys);
                    pMarshal->WriteBlock((void*)pChannel->mPositionKeys, pChannel->mNumPositionKeys * sizeof(aiVectorKey));
                }

                pMarshal->Write<bool>(pChannel->mRotationKeys);
                if (pChannel->mRotationKeys) {
                    pMarshal->Write<uint64_t>(pChannel->mNumRotationKeys);
                    pMarshal->WriteBlock((void*)pChannel->mRotationKeys, pChannel->mNumRotationKeys * sizeof(aiQuatKey));
                }

                pMarshal->Write<bool>(pChannel->mScalingKeys);
                if (pChannel->mScalingKeys) {
                    pMarshal->Write<uint64_t>(pChannel->mNumScalingKeys);
                    pMarshal->WriteBlock((void*)pChannel->mScalingKeys, pChannel->mNumScalingKeys * sizeof(aiVectorKey));
                }
            }

            pMarshal->Write<uint64_t>(pAnimation->mNumMeshChannels);

            for (uint64_t meshChannelId = 0; meshChannelId < pAnimation->mNumMeshChannels; ++meshChannelId) {
                auto&& pMeshChannel = pAnimation->mMeshChannels[meshChannelId];

                pMarshal->Write<std::string>(std::string(pMeshChannel->mName.C_Str()));

                pMarshal->Write<bool>(pMeshChannel->mKeys);
                if (pMeshChannel->mKeys) {
                    pMarshal->Write<uint64_t>(pMeshChannel->mNumKeys);
                    pMarshal->WriteBlock((void*)pMeshChannel->mKeys, pMeshChannel->mNumKeys * sizeof(aiMeshKey));
                }
            }

            pMarshal->Write<uint64_t>(pAnimation->mNumMorphMeshChannels);

            for (uint64_t morphMeshChannelId = 0; morphMeshChannelId < pAnimation->mNumMorphMeshChannels; ++morphMeshChannelId) {
                auto&& pMorphMeshChannel = pAnimation->mMorphMeshChannels[morphMeshChannelId];

                pMarshal->Write<std::string>(std::string(pMorphMeshChannel->mName.C_Str()));

                pMarshal->Write<uint64_t>(pMorphMeshChannel->mNumKeys);

                for (uint64_t keyId = 0; keyId < pMorphMeshChannel->mNumKeys; ++keyId) {
                    auto&& key = pMorphMeshChannel->mKeys[keyId];

                    pMarshal->Write<double_t>(key.mTime);
                    pMarshal->Write<uint64_t>(key.mNumValuesAndWeights);

                    if (key.mNumValuesAndWeights > 0) {
                        pMarshal->WriteBlock((void *) key.mValues, key.mNumValuesAndWeights * sizeof(uint32_t));
                        pMarshal->WriteBlock((void *) key.mWeights, key.mNumValuesAndWeights * sizeof(double_t));
                    }
                }
            }
        }
    }

    void AssimpCache::LoadAnimations(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const {
        pScene->mNumAnimations = pMarshal->Read<uint64_t>();
        if (pScene->mNumAnimations > 0) {
            pScene->mAnimations = new aiAnimation*[pScene->mNumAnimations];
        }
        else {
            pScene->mAnimations = nullptr;
        }

        for (uint64_t animationId = 0; animationId < pScene->mNumAnimations; ++animationId) {
            auto&& pAnimation = pScene->mAnimations[animationId];
            pAnimation = new aiAnimation();

            pAnimation->mName = pMarshal->Read<std::string>();
            pAnimation->mDuration = pMarshal->Read<double_t>();
            pAnimation->mTicksPerSecond = pMarshal->Read<double_t>();

            pAnimation->mNumChannels = pMarshal->Read<uint64_t>();
            if (pAnimation->mNumChannels > 0) {
                pAnimation->mChannels = new aiNodeAnim*[pAnimation->mNumChannels];
            }
            else {
                pAnimation->mChannels = nullptr;
            }

            for (uint64_t channelId = 0; channelId < pAnimation->mNumChannels; ++channelId) {
                auto&& pChannel = pAnimation->mChannels[channelId];
                pChannel = new aiNodeAnim();

                pChannel->mNodeName = pMarshal->Read<std::string>();
                pChannel->mPreState = static_cast<aiAnimBehaviour>(pMarshal->Read<uint64_t>());
                pChannel->mPostState = static_cast<aiAnimBehaviour>(pMarshal->Read<uint64_t>());

                if (pMarshal->Read<bool>()) {
                    pChannel->mNumPositionKeys = pMarshal->Read<uint64_t>();
                    pChannel->mPositionKeys = new aiVectorKey[pChannel->mNumPositionKeys];
                    pMarshal->ReadBlock((void*)pChannel->mPositionKeys);
                }
                else {
                    pChannel->mPositionKeys = nullptr;
                }

                if (pMarshal->Read<bool>()) {
                    pChannel->mNumRotationKeys = pMarshal->Read<uint64_t>();
                    pChannel->mRotationKeys = new aiQuatKey[pChannel->mNumRotationKeys];
                    pMarshal->ReadBlock((void*)pChannel->mRotationKeys);
                }
                else {
                    pChannel->mRotationKeys = nullptr;
                }

                if (pMarshal->Read<bool>()) {
                    pChannel->mNumScalingKeys = pMarshal->Read<uint64_t>();
                    pChannel->mScalingKeys = new aiVectorKey[pChannel->mNumScalingKeys];
                    pMarshal->ReadBlock((void*)pChannel->mScalingKeys);
                }
                else {
                    pChannel->mScalingKeys = nullptr;
                }
            }

            pAnimation->mNumMeshChannels = pMarshal->Read<uint64_t>();
            if (pAnimation->mNumMeshChannels > 0) {
                pAnimation->mMeshChannels = new aiMeshAnim*[pAnimation->mNumMeshChannels];
            }
            else {
                pAnimation->mMeshChannels = nullptr;
            }

            for (uint64_t meshChannelId = 0; meshChannelId < pAnimation->mNumMeshChannels; ++meshChannelId) {
                auto&& pMeshChannel = pAnimation->mMeshChannels[meshChannelId];
                pMeshChannel = new aiMeshAnim();

                pMeshChannel->mName = pMarshal->Read<std::string>();

                if (pMarshal->Read<bool>()) {
                    pMeshChannel->mNumKeys = pMarshal->Read<uint64_t>();
                    pMeshChannel->mKeys = new aiMeshKey[pMeshChannel->mNumKeys];
                    pMarshal->ReadBlock((void*)pMeshChannel->mKeys);
                }
                else {
                    pMeshChannel->mKeys = nullptr;
                }
            }

            pAnimation->mNumMorphMeshChannels = pMarshal->Read<uint64_t>();
            if (pAnimation->mNumMorphMeshChannels > 0) {
                pAnimation->mMorphMeshChannels = new aiMeshMorphAnim*[pAnimation->mNumMorphMeshChannels];
            }
            else {
                pAnimation->mMorphMeshChannels = nullptr;
            }

            for (uint64_t morphMeshChannelId = 0; morphMeshChannelId < pAnimation->mNumMorphMeshChannels; ++morphMeshChannelId) {
                auto&& pMorphMeshChannel = pAnimation->mMorphMeshChannels[morphMeshChannelId];
                pMorphMeshChannel = new aiMeshMorphAnim();

                pMorphMeshChannel->mName = pMarshal->Read<std::string>();

                pMorphMeshChannel->mNumKeys = pMarshal->Read<uint64_t>();
                if (pMorphMeshChannel->mNumKeys > 0) {
                    pMorphMeshChannel->mKeys = new aiMeshMorphKey[pMorphMeshChannel->mNumKeys];
                }
                else {
                    pMorphMeshChannel->mKeys = nullptr;
                }

                for (uint64_t keyId = 0; keyId < pMorphMeshChannel->mNumKeys; ++keyId) {
                    auto&& key = pMorphMeshChannel->mKeys[keyId];

                    key.mTime = pMarshal->Read<double_t>();
                    key.mNumValuesAndWeights = pMarshal->Read<uint64_t>();

                    if (key.mNumValuesAndWeights > 0) {
                        pMarshal->ReadBlock((void*)key.mValues);
                        pMarshal->ReadBlock((void*)key.mWeights);
                    }
                }
            }
        }
    }

    void AssimpCache::SaveSkeletons(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const {
        auto&& nodeMap = BuildNodeMap(pScene);
        auto&& meshMap = BuildMeshMap(pScene);

        pMarshal->Write<uint64_t>(pScene->mNumSkeletons);

        if (pScene->mNumSkeletons == 0) {
            return;
        }

        for (uint64_t skeletonId = 0; skeletonId < pScene->mNumSkeletons; ++skeletonId) {
            auto&& pSkeleton = pScene->mSkeletons[skeletonId];

            pMarshal->Write<std::string>(std::string(pSkeleton->mName.C_Str()));
            pMarshal->Write<uint64_t>(pSkeleton->mNumBones);

            for (uint64_t boneId = 0; boneId < pSkeleton->mNumBones; ++boneId) {
                auto&& pBone = pSkeleton->mBones[boneId];

                pMarshal->Write<bool>(pBone->mMeshId);
                if (pBone->mMeshId) {
                    pMarshal->Write<uint64_t>(meshMap.second.at(pBone->mMeshId));
                }

                pMarshal->Write<bool>(pBone->mArmature);
                if (pBone->mArmature) {
                    pMarshal->Write<uint64_t>(nodeMap.second.at(pBone->mArmature));
                }

                pMarshal->Write<bool>(pBone->mNode);
                if (pBone->mNode) {
                    pMarshal->Write<uint64_t>(nodeMap.second.at(pBone->mNode));
                }

                pMarshal->Write<uint64_t>(pBone->mParent);

                pMarshal->Write<uint64_t>(pBone->mNumnWeights);
                if (pBone->mNumnWeights > 0) {
                    pMarshal->WriteBlock((void *) pBone->mWeights, pBone->mNumnWeights * sizeof(aiVertexWeight));
                }

                pMarshal->WriteBlock((void*)&pBone->mLocalMatrix, sizeof(aiMatrix4x4));
                pMarshal->WriteBlock((void*)&pBone->mOffsetMatrix, sizeof(aiMatrix4x4));
            }
        }
    }

    void AssimpCache::LoadSkeletons(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const {
        auto&& nodeMap = BuildNodeMap(pScene);
        auto&& meshMap = BuildMeshMap(pScene);

        pScene->mNumSkeletons = pMarshal->Read<uint64_t>();
        if (pScene->mNumSkeletons > 0) {
            pScene->mSkeletons = new aiSkeleton*[pScene->mNumSkeletons];
        }

        for (uint64_t skeletonId = 0; skeletonId < pScene->mNumSkeletons; ++skeletonId) {
            auto&& pSkeleton = pScene->mSkeletons[skeletonId];
            pSkeleton = new aiSkeleton();

            pSkeleton->mName = pMarshal->Read<std::string>();

            pSkeleton->mNumBones = pMarshal->Read<uint64_t>();
            if (pSkeleton->mNumBones > 0) {
                pSkeleton->mBones = new aiSkeletonBone*[pSkeleton->mNumBones];
            }

            for (uint64_t boneId = 0; boneId < pSkeleton->mNumBones; ++boneId) {
                auto&& pBone = pSkeleton->mBones[boneId];
                pBone = new aiSkeletonBone();

                if (pMarshal->Read<bool>()) {
                    pBone->mMeshId = meshMap.first[pMarshal->Read<uint64_t>()];
                }
                else {
                    pBone->mMeshId = nullptr;
                }

                if (pMarshal->Read<bool>()) {
                    pBone->mArmature = nodeMap.first[pMarshal->Read<uint64_t>()];
                }
                else {
                    pBone->mArmature = nullptr;
                }

                if (pMarshal->Read<bool>()) {
                    pBone->mNode = nodeMap.first[pMarshal->Read<uint64_t>()];
                }
                else {
                    pBone->mNode = nullptr;
                }

                pBone->mParent = pMarshal->Read<uint64_t>();

                pBone->mNumnWeights = pMarshal->Read<uint64_t>();
                if (pBone->mNumnWeights > 0) {
                    pBone->mWeights = new aiVertexWeight[pBone->mNumnWeights];
                    pMarshal->ReadBlock((void *) pBone->mWeights);
                }
                else {
                    pBone->mWeights = nullptr;
                }

                pMarshal->ReadBlock((void*)&pBone->mLocalMatrix);
                pMarshal->ReadBlock((void*)&pBone->mOffsetMatrix);
            }
        }
    }

    void AssimpCache::LoadMeshes(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const {
        auto&& nodeMap = BuildNodeMap(pScene);

        pScene->mNumMeshes = pMarshal->Read<uint64_t>();
        pScene->mMeshes = new aiMesh*[pScene->mNumMeshes];

        for (uint64_t meshId = 0; meshId < pScene->mNumMeshes; ++meshId) {
            auto&& pMesh = pScene->mMeshes[meshId];
            pMesh = new aiMesh();

            pMesh->mPrimitiveTypes = pMarshal->Read<uint64_t>();
            pMesh->mMaterialIndex = pMarshal->Read<uint64_t>();
            pMesh->mMethod = static_cast<aiMorphingMethod>(pMarshal->Read<uint64_t>());

            pMarshal->ReadBlock(&pMesh->mAABB);

            /// --------------------------------------------------------------------------------------------------------

            LoadMesh(pMarshal, pMesh);

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t i = 0; i < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                pMesh->mNumUVComponents[i] = pMarshal->Read<uint64_t>();
            }

            /// has texture coords names
            if (pMarshal->Read<bool>()) {
                pMesh->mTextureCoordsNames = new aiString*[SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS];
            }

            for (uint8_t i = 0; pMesh->mTextureCoordsNames && i < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                auto&& pTextureCoordName = pMesh->mTextureCoordsNames[i];

                /// has name
                if (pMarshal->Read<bool>()) {
                    pTextureCoordName = new aiString();
                    *pTextureCoordName = pMarshal->Read<std::string>();
                }
                else {
                    pTextureCoordName = nullptr;
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMesh->mNumFaces = pMarshal->Read<uint64_t>();

            if (pMesh->mNumFaces > 0) {
                pMesh->mFaces = new aiFace[pMesh->mNumFaces];
            }

            for (uint64_t faceId = 0; faceId < pMesh->mNumFaces; ++faceId) {
                auto&& face = pMesh->mFaces[faceId];
                face.mNumIndices = pMarshal->Read<uint64_t>();
                if (face.mNumIndices > 0) {
                    face.mIndices = new unsigned int[face.mNumIndices];
                    pMarshal->ReadBlock(face.mIndices);
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMesh->mNumBones = pMarshal->Read<uint64_t>();
            if (pMesh->mNumBones > 0) {
                pMesh->mBones = new aiBone*[pMesh->mNumBones];
            }

            for (uint64_t boneId = 0; boneId < pMesh->mNumBones; ++boneId) {
                auto&& pBone = pMesh->mBones[boneId];
                pBone = new aiBone();

                pBone->mName = pMarshal->Read<std::string>();

                if (pMarshal->Read<bool>()) {
                    pBone->mArmature = nodeMap.first[pMarshal->Read<uint64_t>()];
                }
                else {
                    pBone->mArmature = nullptr;
                }

                if (pMarshal->Read<bool>()) {
                    pBone->mNode = nodeMap.first[pMarshal->Read<uint64_t>()];
                }
                else {
                    pBone->mNode = nullptr;
                }

                pBone->mNumWeights = pMarshal->Read<uint64_t>();
                if (pBone->mNumWeights > 0) {
                    pBone->mWeights = new aiVertexWeight[pBone->mNumWeights];
                    pMarshal->ReadBlock((void*)pBone->mWeights);
                }
                else {
                    pBone->mWeights = nullptr;
                }

                pMarshal->ReadBlock((void*)&pBone->mOffsetMatrix);
            }

            /// --------------------------------------------------------------------------------------------------------

            pMesh->mNumAnimMeshes = pMarshal->Read<uint64_t>();
            if (pMesh->mNumAnimMeshes > 0) {
                pMesh->mAnimMeshes = new aiAnimMesh*[pMesh->mNumAnimMeshes];
            }

            for (uint64_t animatedMeshId = 0; animatedMeshId < pMesh->mNumAnimMeshes; ++animatedMeshId) {
                auto&& pAnimatedMesh = pMesh->mAnimMeshes[animatedMeshId];
                pAnimatedMesh = new aiAnimMesh();

                pAnimatedMesh->mWeight = pMarshal->Read<float_t>();

                LoadMesh(pMarshal, pAnimatedMesh);
            }
        }
    }

    void AssimpCache::SaveMeshes(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const {
        auto&& nodeMap = BuildNodeMap(pScene);

        pMarshal->Write<uint64_t>(pScene->mNumMeshes);

        for (uint64_t meshId = 0; meshId < pScene->mNumMeshes; ++meshId) {
            auto&& pMesh = pScene->mMeshes[meshId];

            pMarshal->Write<uint64_t>(pMesh->mPrimitiveTypes);
            pMarshal->Write<uint64_t>(pMesh->mMaterialIndex);
            pMarshal->Write<uint64_t>(pMesh->mMethod);

            pMarshal->WriteBlock(&pMesh->mAABB, 2 * 3 * sizeof(float_t));

            /// --------------------------------------------------------------------------------------------------------

            SaveMesh(pMarshal, pMesh);

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t i = 0; i < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                pMarshal->Write<uint64_t>(pMesh->mNumUVComponents[i]);
            }

            pMarshal->Write<bool>(pMesh->mTextureCoordsNames); /// has texture coords names

            for (uint8_t i = 0; pMesh->mTextureCoordsNames && i < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                auto&& pTextureCoordName = pMesh->mTextureCoordsNames[i];
                pMarshal->Write<bool>(pTextureCoordName); /// has name
                if (pTextureCoordName) {
                    pMarshal->Write<std::string>(pTextureCoordName->C_Str());
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMarshal->Write<uint64_t>(pMesh->mNumFaces);

            for (uint64_t faceId = 0; faceId < pMesh->mNumFaces; ++faceId) {
                auto&& face = pMesh->mFaces[faceId];
                pMarshal->Write<uint64_t>(face.mNumIndices);
                if (face.mNumIndices > 0) {
                    pMarshal->WriteBlock(face.mIndices, face.mNumIndices * sizeof(unsigned int));
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMarshal->Write<uint64_t>(pMesh->mNumBones);

            for (uint64_t boneId = 0; boneId < pMesh->mNumBones; ++boneId) {
                auto&& pBone = pMesh->mBones[boneId];

                pMarshal->Write<std::string>(std::string(pBone->mName.C_Str()));

                pMarshal->Write<bool>(pBone->mArmature);
                if (pBone->mArmature) {
                    pMarshal->Write<uint64_t>(nodeMap.second.at(pBone->mArmature));
                }

                pMarshal->Write<bool>(pBone->mNode);
                if (pBone->mNode) {
                    pMarshal->Write<uint64_t>(nodeMap.second.at(pBone->mNode));
                }

                pMarshal->Write<uint64_t>(pBone->mNumWeights);
                SRAssertOnce(pBone->mNumWeights <= AI_MAX_BONE_WEIGHTS);
                if (pBone->mNumWeights > 0) {
                    pMarshal->WriteBlock((void *) pBone->mWeights, pBone->mNumWeights * sizeof(aiVertexWeight));
                }

                pMarshal->WriteBlock((void*)&pBone->mOffsetMatrix, sizeof(aiMatrix4x4));
            }

            /// --------------------------------------------------------------------------------------------------------

            pMarshal->Write<uint64_t>(pMesh->mNumAnimMeshes);

            for (uint64_t animatedMeshId = 0; animatedMeshId < pMesh->mNumAnimMeshes; ++animatedMeshId) {
                auto&& pAnimatedMesh = pMesh->mAnimMeshes[animatedMeshId];

                pMarshal->Write<float_t>(pAnimatedMesh->mWeight);

                SaveMesh(pMarshal, pAnimatedMesh);
            }
        }
    }

    void AssimpCache::LoadNode(SR_HTYPES_NS::Marshal* pMarshal, aiNode*& pNode) const {
        pNode = new aiNode();

        pNode->mName = pMarshal->Read<std::string>();

        pMarshal->ReadBlock((void*)&pNode->mTransformation);

        pNode->mNumMeshes = pMarshal->Read<uint64_t>();
        pNode->mMeshes = new uint32_t[pNode->mNumMeshes];
        pMarshal->ReadBlock((void*)pNode->mMeshes);

        pNode->mNumChildren = pMarshal->Read<uint64_t>();

        if (pNode->mNumChildren > 0) {
            pNode->mChildren = new aiNode*[pNode->mNumChildren];
        }

        for (uint64_t childId = 0; childId < pNode->mNumChildren; ++childId) {
            LoadNode(pMarshal, pNode->mChildren[childId]);
            pNode->mChildren[childId]->mParent = pNode;
        }
    }

    void AssimpCache::SaveNode(SR_HTYPES_NS::Marshal* pMarshal, const aiNode* pNode) const {
        pMarshal->Write<std::string>(std::string(pNode->mName.C_Str()));

        pMarshal->WriteBlock((void*)&pNode->mTransformation, sizeof(aiMatrix4x4));

        pMarshal->Write<uint64_t>(pNode->mNumMeshes);
        pMarshal->WriteBlock((void*)pNode->mMeshes, pNode->mNumMeshes * sizeof(uint32_t));

        pMarshal->Write<uint64_t>(pNode->mNumChildren);

        for (uint64_t childId = 0; childId < pNode->mNumChildren; ++childId) {
            SaveNode(pMarshal, pNode->mChildren[childId]);
        }
    }

    AssimpCache::NodeMap AssimpCache::BuildNodeMap(const aiScene* pScene) const {
        AssimpCache::NodeMap nodeMap;

        if (!pScene->mRootNode) {
            return std::move(nodeMap);
        }

        std::stack<uint64_t> stack;
        aiNode* pCurrentNode = pScene->mRootNode;

        uint64_t index = 0;
        uint64_t childId = 0;

        nodeMap.second[pCurrentNode] = index;
        nodeMap.first.emplace_back(pCurrentNode);

    retry:
        if (pCurrentNode && childId < pCurrentNode->mNumChildren) {
            pCurrentNode = pCurrentNode->mChildren[childId];
            nodeMap.second[pCurrentNode] = ++index;
            nodeMap.first.emplace_back(pCurrentNode);
            stack.push(childId);
            goto retry;
        }

        if (!stack.empty()) {
            pCurrentNode = pCurrentNode->mParent;
            childId = stack.top() + 1;
            stack.pop();
            goto retry;
        }

        return std::move(nodeMap);
    }

    AssimpCache::MeshMap AssimpCache::BuildMeshMap(const aiScene* pScene) const {
        AssimpCache::MeshMap meshMap;

        for (uint64_t i = 0; i < pScene->mNumMeshes; ++i) {
            meshMap.second[pScene->mMeshes[i]] = i;
            meshMap.first.emplace_back(pScene->mMeshes[i]);
        }

        return std::move(meshMap);
    }

    void AssimpCache::AllocateAiColor4t(void** pData, uint32_t count) {
        *pData = (void*)(new aiColor4t<float>[count]);
    }

    void AssimpCache::AllocateAiVector3t(void** pData, uint32_t count) {
        *pData = (void*)(new aiVector3t<float>[count]);
    }
}