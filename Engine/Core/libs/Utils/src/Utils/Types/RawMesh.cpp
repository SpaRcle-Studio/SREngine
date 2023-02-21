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
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(RawMesh), true /** auto remove */)
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

    RawMesh *RawMesh::Load(const SR_UTILS_NS::Path &rawPath) {
        return Load(rawPath, false);
    }

    RawMesh *RawMesh::Load(const SR_UTILS_NS::Path &rawPath, bool animation) {
        SR_GLOBAL_LOCK

        RawMesh* pRawMesh = nullptr;

        ResourceManager::Instance().Execute([&]() {
            Path&& path = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetResPath());

            if (auto&& pResource = ResourceManager::Instance().Find<RawMesh>(path)) {
                pRawMesh = pResource;
                SRAssert(pRawMesh->m_asAnimation == animation);
                return;
            }

            pRawMesh = new RawMesh();
            pRawMesh->m_asAnimation = animation;
            pRawMesh->SetId(path, false /** auto register */);

            if (!pRawMesh->Reload()) {
                SR_ERROR("RawMesh::Load() : failed to load raw mesh! \n\tPath: " + path.ToString());
                delete pRawMesh;
                pRawMesh = nullptr;
                return;
            }

            /// отложенная ручная регистрация
            ResourceManager::Instance().RegisterResource(pRawMesh);
        });

        return pRawMesh;
    }

    bool RawMesh::Unload() {
        SR_SCOPED_LOCK

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
        m_boneOffsets.clear();

        return !hasErrors;
    }

    bool RawMesh::Load() {
        SR_SCOPED_LOCK

        bool hasErrors = !IResource::Load();

        Path&& path = Path(GetResourceId());
        if (!path.IsAbs()) {
            path = ResourceManager::Instance().GetResPath().Concat(path);
        }

        Path&& cache = ResourceManager::Instance().GetCachePath().Concat("Models").Concat(GetResourceId());
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
            m_scene = m_importer->ReadFile(path.ToString(), m_asAnimation ? SR_RAW_MESH_ASSIMP_ANIMATION_FLAGS : SR_RAW_MESH_ASSIMP_FLAGS);

            if (needFastLoad) {
                SR_LOG("RawMesh::Load() : export model to cache... \n\tPath: " + binary.ToString());

                Assimp::Exporter exporter;
                const aiExportFormatDesc* format = exporter.GetExportFormatDescription(14);

                exporter.Export(m_scene, format->id, binary.ToString(), m_asAnimation ? SR_RAW_MESH_ASSIMP_ANIMATION_FLAGS : SR_RAW_MESH_ASSIMP_FLAGS);

                SR_UTILS_NS::FileSystem::WriteHashToFile(hashFile, resourceHash);
            }
        }

        if (m_scene && !m_fromCache && supportFastLoad) {
            SR_UTILS_NS::AssimpCache::Instance().Save(binary, m_scene);
        }

        if (m_scene) {
            CalculateBones();
        }
        else {
            SR_ERROR("RawMesh::Load() : failed to read file! \n\tPath: " + path.ToString() + "\n\tReason: " + m_importer->GetErrorString());
            hasErrors |= true;
        }

        return !hasErrors;
    }

    uint32_t RawMesh::GetMeshesCount() const {
        SR_LOCK_GUARD

        if (!m_scene) {
            SRHalt("RawMesh::GetMeshesCount() : assimp scene is invalid!");
            return 0;
        }

        return m_scene->mNumMeshes;
    }

    std::string RawMesh::GetGeometryName(uint32_t id) const {
        SR_LOCK_GUARD

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

                    vertex.weights[vertex.weightsNum - 1].boneId = bones.at(SR_HASH_STR(mesh->mBones[i]->mName.C_Str()));
                    vertex.weights[vertex.weightsNum - 1].weight = mesh->mBones[i]->mWeights[j].mWeight;
                }
            }

        #ifdef SR_DEBUG
            for (auto&& vertex : vertices) {
                float sum = 0.f;
                for (auto&& [boneId, weight] : vertex.weights) {
                    sum += weight;
                }
                SRAssertOnce(SR_EQUALS(sum, 1.f));
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

        auto&& pIt = m_boneOffsets.find(hashName);
        if (pIt == m_boneOffsets.end()) {
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

                if (m_boneOffsets.count(hashName) == 1) {
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

                m_boneOffsets.insert(std::make_pair(hashName, std::move(matrix4X4)));
            }
        }
    }
}