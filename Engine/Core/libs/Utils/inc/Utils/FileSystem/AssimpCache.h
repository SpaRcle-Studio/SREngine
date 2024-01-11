//
// Created by Monika on 15.02.2023.
//

#ifndef SR_ENGINE_ASSIMPCACHE_H
#define SR_ENGINE_ASSIMPCACHE_H

#include <Utils/Debug.h>
#include <Utils/Types/Marshal.h>

namespace Assimp {
    class Importer;
}

class aiScene;
class aiNode;
class aiMesh;

namespace SR_HTYPES_NS {
    class Marshal;
}

namespace SR_UTILS_NS {
    class AssimpCache final : public Singleton<AssimpCache> {
        SR_REGISTER_SINGLETON(AssimpCache);
        SR_MAYBE_UNUSED SR_INLINE_STATIC const uint64_t VERSION = 1010;
        static const uint8_t SR_ASSIMP_MAX_NUMBER_OF_COLOR_SETS;
        static const uint8_t SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS;
        using NodeIndex = uint64_t;
        using MeshIndex = uint64_t;
        using NodeMap = std::pair<std::vector<aiNode*>, std::unordered_map<aiNode*, NodeIndex>>;
        using MeshMap = std::pair<std::vector<aiMesh*>, std::unordered_map<aiMesh*, MeshIndex>>;
    public:
        bool Save(const SR_UTILS_NS::Path& path, const aiScene* pScene) const;
        aiScene* Load(const SR_UTILS_NS::Path& path) const;

    private:
        static void AllocateAiColor4t(void** pData, uint32_t count);
        static void AllocateAiVector3t(void** pData, uint32_t count);

        SR_NODISCARD NodeMap BuildNodeMap(const aiScene* pScene) const;
        SR_NODISCARD MeshMap BuildMeshMap(const aiScene* pScene) const;

        void SaveSkeletons(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const;
        void LoadSkeletons(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const;

        void SaveAnimations(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const;
        void LoadAnimations(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const;

        void SaveNode(SR_HTYPES_NS::Marshal* pMarshal, const aiNode* pNode) const;
        void LoadNode(SR_HTYPES_NS::Marshal* pMarshal, aiNode*& pNode) const;

        void SaveMeshes(SR_HTYPES_NS::Marshal* pMarshal, const aiScene* pScene) const;
        void LoadMeshes(SR_HTYPES_NS::Marshal* pMarshal, aiScene* pScene) const;

        template<typename T> void SaveMesh(SR_HTYPES_NS::Marshal* pMarshal, const T* pMesh) const {
            pMarshal->Write<std::string>(std::string(pMesh->mName.C_Str()));

            pMarshal->Write<uint64_t>(pMesh->mNumVertices);

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t colorId = 0; colorId < SR_ASSIMP_MAX_NUMBER_OF_COLOR_SETS; ++colorId) {
                pMarshal->Write<bool>(pMesh->mColors[colorId]);
                if (auto&& pColors = pMesh->mColors[colorId]) {
                    pMarshal->WriteBlock(pMesh->mColors[colorId], pMesh->mNumVertices * 4 * sizeof(float_t));
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            pMarshal->Write<bool>(pMesh->mVertices); /// has vertices
            if (pMesh->mVertices) {
                pMarshal->WriteBlock(pMesh->mVertices, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            pMarshal->Write<bool>(pMesh->mNormals); /// has normals
            if (pMesh->mNormals) {
                pMarshal->WriteBlock(pMesh->mNormals, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            pMarshal->Write<bool>(pMesh->mTangents); /// has tangents
            if (pMesh->mTangents) {
                pMarshal->WriteBlock(pMesh->mTangents, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            pMarshal->Write<bool>(pMesh->mBitangents); /// has bitangents
            if (pMesh->mBitangents) {
                pMarshal->WriteBlock(pMesh->mBitangents, pMesh->mNumVertices * sizeof(float_t) * 3);
            }

            for (uint8_t numberTextureCoords = 0; numberTextureCoords < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++numberTextureCoords) {
                pMarshal->Write<bool>(pMesh->mTextureCoords[numberTextureCoords]);
                if (auto&& textureCoords = pMesh->mTextureCoords[numberTextureCoords]) {
                    pMarshal->WriteBlock(textureCoords, pMesh->mNumVertices * sizeof(float_t) * 3);
                }
            }
        }

        template<typename T> void LoadMesh(SR_HTYPES_NS::Marshal* pMarshal, T* pMesh) const {
            pMesh->mName = pMarshal->Read<std::string>();

            pMesh->mNumVertices = pMarshal->Read<uint64_t>();

            /// --------------------------------------------------------------------------------------------------------

            for (uint8_t colorId = 0; colorId < SR_ASSIMP_MAX_NUMBER_OF_COLOR_SETS; ++colorId) {
                auto&& pColors = pMesh->mColors[colorId];

                if (pMarshal->Read<bool>()) {
                    AllocateAiColor4t((void**)&pColors, pMesh->mNumVertices);
                    pMarshal->ReadBlock(pColors);
                }
                else {
                    pColors = nullptr;
                }
            }

            /// --------------------------------------------------------------------------------------------------------

            /// has vertices
            if (pMarshal->Read<bool>()) {
                AllocateAiVector3t((void**)&pMesh->mVertices, pMesh->mNumVertices);
                pMarshal->ReadBlock(pMesh->mVertices);
            }

            /// has normals
            if (pMarshal->Read<bool>()) {
                AllocateAiVector3t((void**)&pMesh->mNormals, pMesh->mNumVertices);
                pMarshal->ReadBlock(pMesh->mNormals);
            }

            /// has tangents
            if (pMarshal->Read<bool>()) {
                AllocateAiVector3t((void**)&pMesh->mTangents, pMesh->mNumVertices);
                pMarshal->ReadBlock(pMesh->mTangents);
            }

            /// has bitangents
            if (pMarshal->Read<bool>()) {
                AllocateAiVector3t((void**)&pMesh->mBitangents, pMesh->mNumVertices);
                pMarshal->ReadBlock(pMesh->mBitangents);
            }

            for (uint8_t numberTextureCoords = 0; numberTextureCoords < SR_ASSIMP_MAX_NUMBER_OF_TEXTURECOORDS; ++numberTextureCoords) {
                auto&& textureCoords = pMesh->mTextureCoords[numberTextureCoords];

                if (pMarshal->Read<bool>()) {
                    AllocateAiVector3t((void**)&textureCoords, pMesh->mNumVertices);
                    pMarshal->ReadBlock(textureCoords);
                }
                else {
                    textureCoords = nullptr;
                }
            }
        }

    };
}

#endif //SR_ENGINE_ASSIMPCACHE_H
