//
// Created by Monika on 24.03.2022.
//

#include <Utils/Types/RawMesh.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/include/assimp/Exporter.hpp>
#include <assimp/include/assimp/cexport.h>

namespace SR_HTYPES_NS {
    SR_INLINE_STATIC int SR_RAW_MESH_ASSIMP_FLAGS = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder | aiProcess_JoinIdenticalVertices | aiProcess_GenUVCoords | aiProcess_TransformUVCoords | aiProcess_SortByPType | aiProcess_GlobalScale;
    SR_INLINE_STATIC int SR_RAW_MESH_ASSIMP_CACHED_FLAGS = aiProcess_FlipUVs;
    SR_INLINE_STATIC int SR_RAW_MESH_ASSIMP_ANIMATION_FLAGS = aiProcess_MakeLeftHanded | aiProcess_FlipWindingOrder;

    RawMesh::RawMesh()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(RawMesh))
    {
        m_importer = new Assimp::Importer();
    }

    RawMesh::~RawMesh() {
        delete m_importer;

        if (m_fromCache) {
            delete m_scene;
            m_scene = nullptr;
        }
    }

    SR_UTILS_NS::Path RawMesh::InitializeResourcePath() const {
        return SR_UTILS_NS::Path(
                std::move(SR_UTILS_NS::StringUtils::SubstringView(GetResourceId(), '|', 1)),
                true /** fast */
        );
    }

    RawMesh::Ptr RawMesh::Load(const SR_UTILS_NS::Path &rawPath) {
        return Load(rawPath, RawMeshParams());
    }

    RawMesh::Ptr RawMesh::Load(const SR_UTILS_NS::Path &rawPath, RawMeshParams params) {
        RawMesh::Ptr pRawMesh = nullptr;

        ResourceManager::Instance().Execute([&]() {
            Path&& id = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetResPath());

            if (params.animation) {
                id = id.EmplaceFront("Animation|");
            }

            if (auto&& pResource = ResourceManager::Instance().Find<RawMesh>(id)) {
                pRawMesh = pResource;
                SRAssert(pRawMesh->m_params.animation == params.animation);
                return;
            }

            pRawMesh = new RawMesh();
            pRawMesh->m_params.animation = params.animation;
            pRawMesh->SetId(id, false /** auto register */);

            if (!pRawMesh->Reload()) {
                SR_ERROR("RawMesh::Load() : failed to load raw mesh! \n\tPath: " + rawPath.ToString());
                pRawMesh->DeleteResource();
                pRawMesh = nullptr;
                return;
            }

            /// отложенная ручная регистрация
            ResourceManager::Instance().RegisterResource(pRawMesh);
        });

        return pRawMesh;
    }

    bool RawMesh::Unload() {
        bool hasErrors = !IResource::Unload();

        if (m_importer) {
            m_importer->FreeScene();
        }

        if (m_fromCache) {
            delete m_scene;
            m_scene = nullptr;
        }

        m_fromCache = false;

        m_bones.clear();
        m_optimizedBones.clear();

        m_boneOffsetsMap.clear();
        m_boneOffsets.clear();

        m_animations.clear();

        return !hasErrors;
    }

    bool RawMesh::Load() {
        bool hasErrors = !IResource::Load();

        auto&& resPath = GetResourcePath();

        Path&& path = ResourceManager::Instance().GetResPath().Concat(resPath);
        Path&& cache = ResourceManager::Instance().GetCachePath().Concat("Models").Concat(resPath);

        if (m_params.animation) {
            cache = cache.ConcatExt("animation");
        }

        Path&& binary = cache.ConcatExt("cache");
        Path&& hashFile = cache.ConcatExt("hash");

        const uint64_t resourceHash = path.GetFileHash();

        const bool supportFastLoad = SR_UTILS_NS::Features::Instance().Enabled("FastModelsLoad", false);
        bool needFastLoad = supportFastLoad;

    retry:
        if (needFastLoad && resourceHash == SR_UTILS_NS::FileSystem::ReadHashFromFile(hashFile)) {
            if ((m_scene = SR_UTILS_NS::AssimpCache::Instance().Load(binary))) {
                m_fromCache = true;
            }
            else {
                needFastLoad = false;
                goto retry;
            }
        }
        else {
            m_scene = m_importer->ReadFile(path.ToStringRef(), m_params.animation ? SR_RAW_MESH_ASSIMP_ANIMATION_FLAGS : SR_RAW_MESH_ASSIMP_FLAGS);

            if (!m_scene) {
                SR_ERROR("RawMesh::Load() : failed to load file!\n\tPath: " + path.ToStringRef() + "\n\tReason: " + std::string(m_importer->GetErrorString()));
                return false;
            }

            NormalizeWeights();

            if (needFastLoad) {
                SR_LOG("RawMesh::Load() : export model to cache... \n\tPath: " + binary.ToString());

                Assimp::Exporter exporter;
                const aiExportFormatDesc* format = exporter.GetExportFormatDescription(14);

                exporter.Export(m_scene, format->id, binary.ToString(), m_params.animation ? SR_RAW_MESH_ASSIMP_ANIMATION_FLAGS : SR_RAW_MESH_ASSIMP_FLAGS);

                SR_UTILS_NS::FileSystem::WriteHashToFile(hashFile, resourceHash);
            }
        }

        if (m_scene && !m_fromCache && supportFastLoad) {
            SR_UTILS_NS::AssimpCache::Instance().Save(binary, m_scene);
        }

        if (m_scene) {
            CalculateBones();
            OptimizeSkeleton();
            CalculateOffsets();
            CalculateAnimations();
        }
        else {
            SR_ERROR("RawMesh::Load() : failed to read file! \n\tPath: " + path.ToString() + "\n\tReason: " + m_importer->GetErrorString());
            hasErrors |= true;
        }

        return !hasErrors;
    }

    uint32_t RawMesh::GetMeshesCount() const {
        if (!m_scene) {
            SRHalt("RawMesh::GetMeshesCount() : assimp scene is invalid!");
            return 0;
        }

        return m_scene->mNumMeshes;
    }

    std::string RawMesh::GetGeometryName(uint32_t id) const {
        if (!m_scene || id >= m_scene->mNumMeshes) {
            SRAssert2(false, "Out of range or invalid scene!");
            return {};
        }

        return m_scene->mMeshes[id]->mName.C_Str();
    }

    std::vector<SR_UTILS_NS::Vertex> RawMesh::GetVertices(uint32_t id) const {
        if (!m_scene || id >= m_scene->mNumMeshes) {
            SRAssert2(false, "Out of range or invalid scene!");
            return {};
        }

        auto&& mesh = m_scene->mMeshes[id];

        std::vector<SR_UTILS_NS::Vertex> vertices;
        vertices.reserve(mesh->mNumVertices);

        const bool hasUV = mesh->mTextureCoords[0];
        const bool hasNormals = mesh->mNormals;
        const bool hasTangents = mesh->mTangents;
        const bool hasBones = mesh->mBones;

        for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
            SR_UTILS_NS::Vertex vertex = SR_UTILS_NS::Vertex();
            vertex.position = *reinterpret_cast<Vec3*>(&mesh->mVertices[i]);
            vertex.uv = hasUV ? (*reinterpret_cast<Vec2*>(&mesh->mTextureCoords[0][i])) : Vec2 { 0.f, 0.f };
            //vertex.uv.x = -vertex.uv.x;
            vertex.normal = hasNormals ? (*reinterpret_cast<Vec3*>(&mesh->mNormals[i])) : Vec3 { 0.f, 0.f, 0.f };
            vertex.tangent = hasTangents ? (*reinterpret_cast<Vec3*>(&mesh->mTangents[i])) : Vec3 { 0.f, 0.f, 0.f };
            vertex.bitangent = hasTangents ? (*reinterpret_cast<Vec3*>(&mesh->mBitangents[i])) : Vec3 { 0.f, 0.f, 0.f };

            /*vertex.position.x = -vertex.position.x;
            vertex.normal.x = -vertex.normal.x;
            vertex.tangent.x = -vertex.tangent.x;
            vertex.bitangent.x = -vertex.bitangent.x;*/

            vertices.emplace_back(vertex);
        }

        //std::reverse(vertices.begin(), vertices.end());

        //for (uint32_t i = 0; i < vertices.size() / 3; i += 3) {
        //    std::swap(vertices[i + 1], vertices[i + 2]);
        //}

        if (hasBones) {
            auto&& bones = GetBones(id);

            bool hasWarn = false;

            for (uint32_t i = 0; i < mesh->mNumBones; i++) {
                for (uint32_t j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
                    auto&& vertex = vertices[mesh->mBones[i]->mWeights[j].mVertexId];

                    vertex.weightsNum++;

                    if (vertex.weightsNum > SR_MAX_BONES_ON_VERTEX) {
                        if (!hasWarn) {
                            SR_WARN(SR_FORMAT("RawMesh::GetVertices() : number of weights on vertex is already %i. Some weights will be omitted! VertexID = %i. weightsNum = %i",
                                SR_MAX_BONES_ON_VERTEX, mesh->mBones[i]->mWeights[j].mVertexId, vertex.weightsNum));
                            hasWarn = true;
                        }
                        continue;
                    }

                    auto&& boneIndex = bones.at(SR_HASH_STR(mesh->mBones[i]->mName.C_Str()));

                    vertex.weights[vertex.weightsNum - 1].boneId = boneIndex;
                    vertex.weights[vertex.weightsNum - 1].weight = mesh->mBones[i]->mWeights[j].mWeight;
                }
            }

        #ifdef SR_DEBUG
            static bool hasError = false;

            if (!hasError) {
                for (auto&& vertex : vertices) {
                    float_t sum = 0.f;

                    for (auto&&[boneId, weight] : vertex.weights) {
                        sum += weight;
                    }

                    if (!SR_EQUALS(sum, 1.f)) {
                        SR_WARN("RawMesh::GetVertices() : incorrect mesh weight!\n\tPath: " + GetResourcePath().ToStringRef() +
                            "\n\tIndex: " + std::to_string(id) + "\n\tSum: " + std::to_string(sum)
                        );
                        hasError = true;
                        break;
                    }
                }
            }
        #endif
        }

        return vertices;
    }

    std::vector<uint32_t> RawMesh::GetIndices(uint32_t id) const {
        if (!m_scene || id >= m_scene->mNumMeshes) {
            SRAssert2(false, "Out of range or invalid scene!");
            return {};
        }

        auto&& mesh = m_scene->mMeshes[id];

        std::vector<uint32_t> indices;

        indices.reserve(mesh->mNumFaces * 3);

        for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
            aiFace face = mesh->mFaces[i];

            SRAssert2(face.mNumIndices <= 3, "Mesh isn't triangulated!");

            if (face.mNumIndices == 1) {
                indices.emplace_back(face.mIndices[0]);
            }
            else if (face.mNumIndices == 2) {
                indices.emplace_back(face.mIndices[0]);
                indices.emplace_back(face.mIndices[1]);
            }
            else {
                indices.emplace_back(face.mIndices[0]);
                indices.emplace_back(face.mIndices[1]);
                indices.emplace_back(face.mIndices[2]);
            }
        }

        return indices;
    }

    uint32_t RawMesh::GetVerticesCount(uint32_t id) const {
        if (!m_scene || id >= m_scene->mNumMeshes) {
            SRAssert2(false, "Out of range or invalid scene!");
            return {};
        }

        return m_scene->mMeshes[id]->mNumVertices;
    }

    uint32_t RawMesh::GetIndicesCount(uint32_t id) const {
        if (!m_scene || id >= m_scene->mNumMeshes) {
            SRAssert2(false, "Out of range or invalid scene!");
            return {};
        }

        auto&& mesh = m_scene->mMeshes[id];

        uint32_t sum = 0;

        for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
            sum += mesh->mFaces[i].mNumIndices;
        }

        return sum;
    }

    float_t RawMesh::GetScaleFactor() const {
        float_t factor = 0.f;

        if (m_scene->mMetaData->Get("UnitScaleFactor", factor))
           return static_cast<double_t>(factor);

        SRAssert(false);

        return 1.f;
    }

    SR_UTILS_NS::Path RawMesh::GetAssociatedPath() const {
        return ResourceManager::Instance().GetResPath();
    }

    uint32_t RawMesh::GetAnimationsCount() const {
        if (!m_scene) {
            SRHalt("Invalid scene!");
            return 0;
        }

        return m_scene->mNumAnimations;
    }

    const ska::flat_hash_map<uint64_t, uint32_t>& RawMesh::GetBones(uint32_t id) const {
        static const auto&& def = ska::flat_hash_map<uint64_t, uint32_t>();

        if (id >= m_bones.size()) {
            return def;
        }

        return m_bones.at(id);
    }

    const SR_MATH_NS::Matrix4x4& RawMesh::GetBoneOffset(uint64_t hashName) const {
        static const auto&& def = SR_MATH_NS::Matrix4x4::Identity();

        auto&& pIt = m_boneOffsetsMap.find(hashName);
        if (pIt == m_boneOffsetsMap.end()) {
            return def;
        }

        return pIt->second;
    }

    void RawMesh::CalculateBones() {
        m_bones.resize(m_scene->mNumMeshes);

        for (uint32_t meshId = 0; meshId < m_scene->mNumMeshes; ++meshId) {
            auto&& pMesh = m_scene->mMeshes[meshId];

            for (uint32_t boneId = 0; boneId < pMesh->mNumBones; ++boneId) {
                auto&& hashName = SR_HASH_STR(pMesh->mBones[boneId]->mName.data);

                m_bones[meshId].insert(std::make_pair(hashName, static_cast<uint32_t>(m_bones[meshId].size())));
            }
        }
    }

    void RawMesh::CalculateAnimations() {
        if (!m_params.animation || !m_scene) {
            return;
        }

        for (uint32_t i = 0; i < m_scene->mNumAnimations; ++i) {
            auto&& pAnimation = m_scene->mAnimations[i];
            m_animations[SR_HASH_STR(pAnimation->mName.C_Str())] = pAnimation;
        }
    }

    void RawMesh::OptimizeSkeleton() {
        m_optimizedBones.clear();

        for (auto&& mesh : m_bones) {
            for (auto&& [hashName, index] : mesh) {
                m_optimizedBones[hashName] = index;
            }
        }
    }

    void RawMesh::CalculateOffsets() {
        for (uint32_t meshId = 0; meshId < m_scene->mNumMeshes; ++meshId) {
            auto&& pMesh = m_scene->mMeshes[meshId];

            for (uint32_t boneId = 0; boneId < pMesh->mNumBones; ++boneId) {
                auto&& hashName = SR_HASH_STR(pMesh->mBones[boneId]->mName.data);

                if (m_boneOffsetsMap.count(hashName) == 1) {
                    continue;
                }

                auto&& offsetMatrix = pMesh->mBones[boneId]->mOffsetMatrix;

                aiQuaternion rotation;
                aiVector3D scaling, translation;
                offsetMatrix.Decompose(scaling, rotation, translation);

                SR_MATH_NS::Matrix4x4 matrix4X4(
                        SR_MATH_NS::FVector3(translation.x, translation.y, translation.z),
                        SR_MATH_NS::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w),
                        SR_MATH_NS::FVector3(scaling.x, scaling.y, scaling.z)
                );

                m_boneOffsetsMap.insert(std::make_pair(hashName, std::move(matrix4X4)));
            }
        }

        m_boneOffsets.resize(m_boneOffsetsMap.size());

        for (auto&& [hashName, boneId] : m_optimizedBones) {
            if (boneId >= m_boneOffsets.size()) {
                m_boneOffsets.resize(boneId + 1);
            }
            m_boneOffsets[boneId] = GetBoneOffset(hashName);
        }
    }

    uint16_t RawMesh::GetBoneIndex(uint64_t hashName) const {
        auto&& pIt = m_optimizedBones.find(hashName);
        if (pIt == m_optimizedBones.end()) {
            return SR_UINT16_MAX;
        }

        return pIt->second;
    }

    void RawMesh::NormalizeWeights() {
        if (!m_scene) {
            SR_ERROR("RawMesh::NormalizeWeights() : scene is nullptr!");
            return;
        }

        for (uint32_t i = 0; i < m_scene->mNumMeshes; ++i) {
            NormalizeWeights(m_scene->mMeshes[i]);
        }
    }

    uint32_t RawMesh::NormalizeWeights(const aiMesh* pMesh) {
        if (pMesh->mNumBones == 0) {
            return 0;
        }

        struct BoneWeight {
            uint32_t mBoneIndex; /// index of a bone in current mesh
            aiVertexWeight* mVertexWeight; /// a pointer to mVertexWeight in meshs[x]->mBones[x]->mWeight for quick visit
        };

        struct VertexBoneWeights {
            float_t mTotalWeight = 0.f;
            std::vector<BoneWeight> mBoneWeights;
        };

        std::map<uint32_t, VertexBoneWeights> map;

        for (uint32_t b = 0; b < pMesh->mNumBones; b++)
        {
            auto bone = pMesh->mBones[b];

            for (unsigned int w = 0; w < bone->mNumWeights; w++)
            {
                auto vertexWeight = &bone->mWeights[w];
                auto key = vertexWeight->mVertexId;

                if (map.find(key) == map.end()) {
                    map.insert(std::map<uint32_t, VertexBoneWeights>::value_type(key, VertexBoneWeights()));
                }

                auto& vertex_BoneWeights = map[key];

                BoneWeight boneWeights = {};
                boneWeights.mBoneIndex = b;
                boneWeights.mVertexWeight = vertexWeight;

                vertex_BoneWeights.mTotalWeight += vertexWeight->mWeight;
                vertex_BoneWeights.mBoneWeights.push_back(boneWeights);
            }
        }


        uint32_t count = 0;
        /// normalize all weights:
        /// every weight for a same vertex divided by totalWeight of this vertex
        for (auto& item : map)
        {
            auto& vertex_BoneWeights = item.second;
            auto f = 1.f / vertex_BoneWeights.mTotalWeight;
            for (auto&& mBoneWeight : vertex_BoneWeights.mBoneWeights)
            {
                mBoneWeight.mVertexWeight->mWeight *= f;
                count++;
            }
        }

        return count;
    }
}