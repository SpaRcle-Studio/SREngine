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
    bool AssimpCache::Save(const SR_UTILS_NS::Path& path, const aiScene* pScene) const {
        SR_HTYPES_NS::Marshal marshal;

        marshal.Write<uint64_t>(VERSION);

        marshal.Write<std::string>(std::string(pScene->mName.C_Str()));

        marshal.Write<uint64_t>(pScene->mNumMeshes);

        for (uint64_t meshId = 0; meshId < pScene->mNumMeshes; ++meshId) {
            auto&& pMesh = pScene->mMeshes[meshId];

            marshal.Write<std::string>(std::string(pMesh->mName.C_Str()));

            marshal.Write<uint64_t>(pMesh->mPrimitiveTypes);
            marshal.Write<uint64_t>(pMesh->mMaterialIndex);
            marshal.Write<uint64_t>(pMesh->mMethod);

            marshal.WriteBlock(&pMesh->mAABB, 2 * 3 * sizeof(float_t));

            /// --------------------------------------------------------------------------------------------------------

            marshal.Write<uint64_t>(pMesh->mNumVertices);

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t colorId = 0; colorId < AI_MAX_NUMBER_OF_COLOR_SETS; ++colorId) {
                marshal.Write<bool>(pMesh->mColors[colorId]);
                if (auto&& pColors = pMesh->mColors[colorId]) {
                    marshal.WriteBlock(pMesh->mColors[colorId], pMesh->mNumVertices * 4 * sizeof(float_t));
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            marshal.Write<bool>(pMesh->mVertices); /// has vertices
            if (pMesh->mVertices) {
                marshal.WriteBlock(pMesh->mVertices, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            marshal.Write<bool>(pMesh->mNormals); /// has normals
            if (pMesh->mNormals) {
                marshal.WriteBlock(pMesh->mNormals, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            marshal.Write<bool>(pMesh->mTangents); /// has tangents
            if (pMesh->mTangents) {
                marshal.WriteBlock(pMesh->mTangents, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            marshal.Write<bool>(pMesh->mBitangents); /// has bitangents
            if (pMesh->mBitangents) {
                marshal.WriteBlock(pMesh->mBitangents, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                marshal.Write<uint64_t>(pMesh->mNumUVComponents[i]);
            }

            marshal.Write<bool>(pMesh->mTextureCoordsNames); /// has texture coords names

            for (uint8_t i = 0; pMesh->mTextureCoordsNames && i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                auto&& pTextureCoordName = pMesh->mTextureCoordsNames[i];
                marshal.Write<bool>(pTextureCoordName); /// has name
                if (pTextureCoordName) {
                    marshal.Write<std::string>(pTextureCoordName->C_Str());
                }
            }

            for (uint8_t numberTextureCoords = 0; numberTextureCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++numberTextureCoords) {
                marshal.Write<bool>(pMesh->mTextureCoords[numberTextureCoords]);
                if (auto&& textureCoords = pMesh->mTextureCoords[numberTextureCoords]) {
                    marshal.WriteBlock(textureCoords, pMesh->mNumVertices * sizeof(float_t) * 3);
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            marshal.Write<uint64_t>(pMesh->mNumFaces);

            for (uint64_t faceId = 0; faceId < pMesh->mNumFaces; ++faceId) {
                auto&& face = pMesh->mFaces[faceId];
                marshal.Write<uint64_t>(face.mNumIndices);
                if (face.mNumIndices > 0) {
                    marshal.WriteBlock(face.mIndices, face.mNumIndices * sizeof(unsigned int));
                }
            }
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

        pScene->mNumMeshes = marshal.Read<uint64_t>();
        pScene->mMeshes = new aiMesh*[pScene->mNumMeshes];

        for (uint64_t meshId = 0; meshId < pScene->mNumMeshes; ++meshId) {
            auto&& pMesh = pScene->mMeshes[meshId];
            pMesh = new aiMesh();

            pMesh->mName = marshal.Read<std::string>();

            pMesh->mPrimitiveTypes = marshal.Read<uint64_t>();
            pMesh->mMaterialIndex = marshal.Read<uint64_t>();
            pMesh->mMethod = marshal.Read<uint64_t>();

            marshal.ReadBlock(&pMesh->mAABB);

            /// --------------------------------------------------------------------------------------------------------

            pMesh->mNumVertices = marshal.Read<uint64_t>();

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t colorId = 0; colorId < AI_MAX_NUMBER_OF_COLOR_SETS; ++colorId) {
                if (marshal.Read<bool>()) {
                    auto&& pColors = pMesh->mColors[colorId];
                    pColors = new aiColor4D[pMesh->mNumVertices];
                    marshal.ReadBlock(pColors);
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            /// has vertices
            if (marshal.Read<bool>()) {
                pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];
                marshal.ReadBlock(pMesh->mVertices);
            }

            /// has normals
            if (marshal.Read<bool>()) {
                pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];
                marshal.ReadBlock(pMesh->mNormals);
            }

            /// has tangents
            if (marshal.Read<bool>()) {
                pMesh->mTangents = new aiVector3D[pMesh->mNumVertices];
                marshal.ReadBlock(pMesh->mTangents);
            }

            /// has bitangents
            if (marshal.Read<bool>()) {
                pMesh->mBitangents = new aiVector3D[pMesh->mNumVertices];
                marshal.ReadBlock(pMesh->mBitangents);
            }

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                pMesh->mNumUVComponents[i] = marshal.Read<uint64_t>();
            }

            /// has texture coords names
            if (marshal.Read<bool>()) {
                pMesh->mTextureCoordsNames = new aiString*[AI_MAX_NUMBER_OF_TEXTURECOORDS];
            }

            for (uint8_t i = 0; pMesh->mTextureCoordsNames && i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
                auto&& pTextureCoordName = pMesh->mTextureCoordsNames[i];

                /// has name
                if (marshal.Read<bool>()) {
                    pTextureCoordName = new aiString();
                    *pTextureCoordName = marshal.Read<std::string>();
                }
            }

            for (uint8_t numberTextureCoords = 0; numberTextureCoords < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++numberTextureCoords) {
                if (marshal.Read<bool>()) {
                    auto&& textureCoords = pMesh->mTextureCoords[numberTextureCoords];
                    textureCoords = new aiVector3D[pMesh->mNumVertices];

                    marshal.ReadBlock(textureCoords);
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMesh->mNumFaces = marshal.Read<uint64_t>();

            if (pMesh->mNumFaces > 0) {
                pMesh->mFaces = new aiFace[pMesh->mNumFaces];
            }

            for (uint64_t faceId = 0; faceId < pMesh->mNumFaces; ++faceId) {
                auto&& face = pMesh->mFaces[faceId];
                face.mNumIndices = marshal.Read<uint64_t>();
                if (face.mNumIndices > 0) {
                    face.mIndices = new unsigned int[face.mNumIndices];
                    marshal.ReadBlock(face.mIndices);
                }
            }
        }

        return pScene;
    }
}