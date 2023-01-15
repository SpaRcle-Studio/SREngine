//
// Created by Monika on 24.03.2022.
//

#include <Utils/Types/RawMesh.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

namespace SR_HTYPES_NS {
    RawMesh::RawMesh()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(RawMesh), true /** auto remove */)
    {
        m_importer = new Assimp::Importer();
    }

    RawMesh::~RawMesh() {
        delete m_importer;
    }

    RawMesh *RawMesh::Load(const SR_UTILS_NS::Path &rawPath) {
        SR_GLOBAL_LOCK

        RawMesh* pRawMesh = nullptr;

        ResourceManager::Instance().Execute([&]() {
            Path&& path = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetResPath());

            if (auto&& pResource = ResourceManager::Instance().Find<RawMesh>(path)) {
                pRawMesh = pResource;
                return;
            }

            pRawMesh = new RawMesh();
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

        return !hasErrors;
    }

    bool RawMesh::Load() {
        SR_SCOPED_LOCK

        bool hasErrors = !IResource::Load();

        Path&& path = Path(GetResourceId());
        if (!path.IsAbs()) {
            path = ResourceManager::Instance().GetResPath().Concat(path);
        }

        /// m_importer.SetPropertyBool(AI_CONFIG_FBX_CONVERT_TO_M, true);

        m_scene = m_importer->ReadFile(path.ToString(),
                aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_GenUVCoords | aiProcess_TransformUVCoords | aiProcess_SortByPType
                // | aiProcess_GlobalScale
        );

        if (!m_scene) {
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
            SR_UTILS_NS::Vertex vertex;
            vertex.weightsNum = 0;
            vertex.position = *reinterpret_cast<Vec3*>(&mesh->mVertices[i]);
            vertex.uv = hasUV ? (*reinterpret_cast<Vec2*>(&mesh->mTextureCoords[0][i])) : Vec2 { 0.f, 0.f };
            vertex.normal = hasNormals ? (*reinterpret_cast<Vec3*>(&mesh->mNormals[i])) : Vec3 { 0.f, 0.f, 0.f };
            vertex.tangent = hasTangents ? (*reinterpret_cast<Vec3*>(&mesh->mTangents[i])) : Vec3 { 0.f, 0.f, 0.f };
            vertex.bitangent = hasTangents ? (*reinterpret_cast<Vec3*>(&mesh->mBitangents[i])) : Vec3 { 0.f, 0.f, 0.f };
            vertices.emplace_back(vertex);
        }

        if (hasBones) {
            for (uint32_t i = 0; i < mesh->mNumBones; i++) {
                for (uint32_t j = 0; j < mesh->mBones[i]->mNumWeights; j++) {
                    auto&& vertex = vertices[mesh->mBones[i]->mWeights[j].mVertexId];
                    vertex.weightsNum++;
                    if (vertex.weightsNum > SR_MAX_BONES_ON_VERTEX)
                    {
                        SR_WARN(SR_FORMAT("RawMesh::GetVertices() : number of weights on vertex is already %i. Some weights will be omitted! VertexID = %i. weightsNum = %i",
                                          SR_MAX_BONES_ON_VERTEX, mesh->mBones[i]->mWeights[j].mVertexId, vertex.weightsNum));
                        continue;
                    }
                    vertex.weights[vertex.weightsNum-1].boneId = i;
                    vertex.weights[vertex.weightsNum-1].weight = mesh->mBones[i]->mWeights[j].mWeight;
                }
            }
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
}