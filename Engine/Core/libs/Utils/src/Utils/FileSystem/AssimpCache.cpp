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

        SaveMeshes(&marshal, pScene);

        marshal.Write<bool>(pScene->mRootNode); /// has root node
        if (pScene->mRootNode) {
            SaveNode(&marshal, pScene->mRootNode);
        }

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

        LoadMeshes(&marshal, pScene);

        if (marshal.Read<bool>()) { /// has root node
            LoadNode(&marshal, pScene->mRootNode);
        }

        return pScene;
    }

    void AssimpCache::LoadMeshes(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const {
        pScene->mNumMeshes = pMarshal->Read<uint64_t>();
        pScene->mMeshes = new aiMesh*[pScene->mNumMeshes];

        for (uint64_t meshId = 0; meshId < pScene->mNumMeshes; ++meshId) {
            auto&& pMesh = pScene->mMeshes[meshId];
            pMesh = new aiMesh();

            pMesh->mPrimitiveTypes = pMarshal->Read<uint64_t>();
            pMesh->mMaterialIndex = pMarshal->Read<uint64_t>();
            pMesh->mMethod = pMarshal->Read<uint64_t>();

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
        pMarshal->WriteBlock((void*)&pNode->mMeshes, pNode->mNumMeshes * sizeof(uint32_t));

        pMarshal->Write<uint64_t>(pNode->mNumChildren);

        for (uint64_t childId = 0; childId < pNode->mNumChildren; ++childId) {
            SaveNode(pMarshal, pNode->mChildren[childId]);
        }
    }
}