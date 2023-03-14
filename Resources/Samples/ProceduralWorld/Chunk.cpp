//
// Created by Monika on 26.02.2023.
//

#include <Libraries/Utils/Allocator.h>
#include <Libraries/Types/Behaviour.h>
#include <Libraries/Math/Quaternion.h>

#include <Libraries/Debug.h>
#include <Libraries/Input.h>
#include <Libraries/Casts.h>
#include <Libraries/ProceduralMesh.h>
#include <Libraries/Observer.h>
#include <Libraries/Scene.h>
#include <Libraries/Mesh.h>
#include <Libraries/Mathf.h>
#include <Libraries/Math/Vertices.h>

constexpr StaticMeshVertex CUBE_TOP_VERTICES[] = {
        {{-1.000000, 1.000000,  -1.000000}, {0.875000, 0.500000}, {0.000000,  1.000000,  0.000000}},
        {{1.000000,  1.000000,  1.000000},  {0.625000, 0.250000}, {0.000000,  1.000000,  0.000000}},
        {{1.000000,  1.000000,  -1.000000}, {0.625000, 0.500000}, {0.000000,  1.000000,  0.000000}},
        {{-1.000000, 1.000000,  -1.000000}, {0.875000, 0.500000}, {0.000000,  1.000000,  0.000000}},
        {{-1.000000, 1.000000,  1.000000},  {0.875000, 0.250000}, {0.000000,  1.000000,  0.000000}},
        {{1.000000,  1.000000,  1.000000},  {0.625000, 0.250000}, {0.000000,  1.000000,  0.000000}},
};

constexpr StaticMeshVertex CUBE_FRONT_VERTICES[] = {
        {{1.000000,  1.000000,  1.000000},  {0.625000, 0.250000}, {0.000000,  0.000000,  1.000000}},
        {{-1.000000, 1.000000,  1.000000},  {0.625000, 0.000000}, {0.000000,  0.000000,  1.000000}},
        {{-1.000000, -1.000000, 1.000000},  {0.375000, 0.000000}, {0.000000,  0.000000,  1.000000}},
        {{1.000000,  1.000000,  1.000000},  {0.625000, 0.250000}, {0.000000,  0.000000,  1.000000}},
        {{-1.000000, -1.000000, 1.000000},  {0.375000, 0.000000}, {0.000000,  0.000000,  1.000000}},
        {{1.000000,  -1.000000, 1.000000},  {0.375000, 0.250000}, {0.000000,  0.000000,  1.000000}},
};

constexpr StaticMeshVertex CUBE_BOTTOM_VERTICES[] = {
        {{1.000000,  -1.000000, -1.000000}, {0.375000, 0.500000}, {0.000000,  -1.000000, 0.000000}},
        {{-1.000000, -1.000000, 1.000000},  {0.125000, 0.250000}, {0.000000,  -1.000000, 0.000000}},
        {{-1.000000, -1.000000, -1.000000}, {0.125000, 0.500000}, {0.000000,  -1.000000, 0.000000}},
        {{1.000000,  -1.000000, -1.000000}, {0.375000, 0.500000}, {0.000000,  -1.000000, 0.000000}},
        {{1.000000,  -1.000000, 1.000000},  {0.375000, 0.250000}, {0.000000,  -1.000000, 0.000000}},
        {{-1.000000, -1.000000, 1.000000},  {0.125000, 0.250000}, {0.000000,  -1.000000, 0.000000}},
};

constexpr StaticMeshVertex CUBE_LEFT_VERTICES[] = {
        {{1.000000, 1.000000,  -1.000000}, {0.625000, 0.500000}, {1.000000, 0.000000, 0.000000}},
        {{1.000000, -1.000000, 1.000000},  {0.375000, 0.250000}, {1.000000, 0.000000, 0.000000}},
        {{1.000000, -1.000000, -1.000000}, {0.375000, 0.500000}, {1.000000, 0.000000, 0.000000}},
        {{1.000000, 1.000000,  -1.000000}, {0.625000, 0.500000}, {1.000000, 0.000000, 0.000000}},
        {{1.000000, 1.000000,  1.000000},  {0.625000, 0.250000}, {1.000000, 0.000000, 0.000000}},
        {{1.000000, -1.000000, 1.000000},  {0.375000, 0.250000}, {1.000000, 0.000000, 0.000000}},
};

constexpr StaticMeshVertex CUBE_BACK_VERTICES[] = {
        {{-1.000000, 1.000000,  -1.000000}, {0.625000, 0.750000}, {0.000000,  0.000000,  -1.000000}},
        {{1.000000,  -1.000000, -1.000000}, {0.375000, 0.500000}, {0.000000,  0.000000,  -1.000000}},
        {{-1.000000, -1.000000, -1.000000}, {0.375000, 0.750000}, {0.000000,  0.000000,  -1.000000}},
        {{-1.000000, 1.000000,  -1.000000}, {0.625000, 0.750000}, {0.000000,  0.000000,  -1.000000}},
        {{1.000000,  1.000000,  -1.000000}, {0.625000, 0.500000}, {0.000000,  0.000000,  -1.000000}},
        {{1.000000,  -1.000000, -1.000000}, {0.375000, 0.500000}, {0.000000,  0.000000,  -1.000000}}
};

constexpr StaticMeshVertex CUBE_RIGHT_VERTICES[] = {
        {{-1.000000, 1.000000,  1.000000},  {0.625000, 1.000000}, {-1.000000, 0.000000,  0.000000}},
        {{-1.000000, 1.000000,  -1.000000}, {0.625000, 0.750000}, {-1.000000, 0.000000,  0.000000}},
        {{-1.000000, -1.000000, -1.000000}, {0.375000, 0.750000}, {-1.000000, 0.000000,  0.000000}},
        {{-1.000000, 1.000000,  1.000000},  {0.625000, 1.000000}, {-1.000000, 0.000000,  0.000000}},
        {{-1.000000, -1.000000, -1.000000}, {0.375000, 0.750000}, {-1.000000, 0.000000,  0.000000}},
        {{-1.000000, -1.000000, 1.000000},  {0.375000, 1.000000}, {-1.000000, 0.000000,  0.000000}},
};

#define SR_ABS_CHUNK_POSITION_AXIS(regionAxis, ChunkAxis, regionSize) ((regionAxis > 0 ? regionAxis - 1 : regionAxis) * regionSize) + (ChunkAxis > 0 ? (ChunkAxis - 1) : (ChunkAxis + regionSize))

#define SR_ABS_CHUNK_POSITION(region, chunk, regionSize) IVector3 { \
        SR_ABS_CHUNK_POSITION_AXIS(region.x, chunk.x, regionSize),  \
        SR_ABS_CHUNK_POSITION_AXIS(region.y, chunk.y, regionSize),  \
        SR_ABS_CHUNK_POSITION_AXIS(region.z, chunk.z, regionSize) } \

#define SR_OFFSET_CUBE_VERTEX(vertex, x, y, z) \
    vertex.pos[0] += float(-(x + 1) * 2 + 1);  \
    vertex.pos[1] += float(+(y + 1) * 2 - 1);  \
    vertex.pos[2] += float(+(z + 1) * 2 - 1);  \

#define SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, vertex) \
    {                                                                 \
        auto copyVertex = vertex;                                     \
        SR_OFFSET_CUBE_VERTEX(copyVertex, x, y, z);                   \
        if (uniqueVertices.count(copyVertex) == 0) {                  \
            auto&& vSize = static_cast<uint32_t>(vertices.size());    \
            uniqueVertices[copyVertex] = vSize;                       \
            indices.emplace_back(vSize);                              \
            vertices.emplace_back(copyVertex);                        \
        }                                                             \
        else {                                                        \
            indices.emplace_back(uniqueVertices[copyVertex]);         \
        }                                                             \
    }                                                                 \

#define SR_ADD_CUBE_FACE(face)                                        \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[0])    \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[1])    \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[2])    \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[3])    \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[4])    \
    SR_ADD_CUBE_VERTEX(uniqueVertices, vertices, indices, face[5])    \

class Chunk : public Behaviour { 
public:
    void Awake() override {
        m_logic = DynamicCastSceneLogicToSceneCubeChunkLogic(scene->GetLogicBase().Get());
        m_observer = m_logic->GetObserver();
        auto&& [region, chunk] = m_logic->GetRegionAndChunk(transform->GetTranslation());

        auto&& pComponent = gameObject->GetOrCreateComponent("ProceduralMesh");
        m_proceduralMesh = DynamicCastComponentToProceduralMesh(pComponent);
    }

    bool HasNeighbour(int32_t x, int32_t y, int32_t z, int32_t offsetX, int32_t offsetY, int32_t offsetZ) {
        x += offsetX;
        y += offsetY;
        z += offsetZ;

        const bool outOfBounds = (x < 0 || x >= sizeX) ||  (y < 0 || y >= sizeY) ||  (z < 0 || z >= sizeZ);

        if (outOfBounds) {
            return false;
        }

        const uint64_t position = z * sizeX * sizeY + y * sizeX + x;
        return m_voxel[position];
    }

    void GenerateVoxel() {
        m_voxel.resize(sizeX * sizeY * sizeZ);

        for (int32_t x = 0; x < sizeX; ++x) {
            for (int32_t y = 0; y < sizeY; ++y) {
                for (int32_t z = 0; z < sizeZ; ++z) {
                    const uint64_t position = z * sizeX * sizeY + y * sizeX + x;

                    float noise = Mathf::SNoise3D(
                        (static_cast<double>(m_chunk.x * sizeX + x) / 10.0 + seed),
                        (static_cast<double>(m_chunk.y * sizeY + y) / 10.0 + seed),
                        (static_cast<double>(m_chunk.z * sizeZ + z) / 10.0 + seed)
                    );

                    m_voxel[position] = noise > 0;
                }
            }
        }
    }

    void GenerateMesh() {
        std::vector<StaticMeshVertex> vertices;
        std::vector<uint32_t> indices;
        std::unordered_map<StaticMeshVertex, uint32_t> uniqueVertices;

        vertices.reserve(sizeX * sizeY * sizeZ);

        for (int32_t x = 0; x < sizeX; ++x)
        {
            for (int32_t y = 0; y < sizeY; ++y)
            {
                for (int32_t z = 0; z < sizeZ; ++z)
                {
                    const uint64_t position = z * sizeX * sizeY + y * sizeX + x;
                    if (!m_voxel[position]) {
                        continue;
                    }

                    /// top
                    if (!HasNeighbour(x, y, z, 0, 1, 0)) {
                        SR_ADD_CUBE_FACE(CUBE_TOP_VERTICES);
                    }

                    /// bottom
                    if (!HasNeighbour(x, y, z, 0, -1, 0)) {
                        SR_ADD_CUBE_FACE(CUBE_BOTTOM_VERTICES);
                    }

                    /// right
                    if (!HasNeighbour(x, y, z, 1, 0, 0)) {
                        SR_ADD_CUBE_FACE(CUBE_RIGHT_VERTICES);
                    }

                    /// left
                    if (!HasNeighbour(x, y, z, -1, 0, 0)) {
                        SR_ADD_CUBE_FACE(CUBE_LEFT_VERTICES);
                    }

                    /// front
                    if (!HasNeighbour(x, y, z, 0, 0, 1)) {
                        SR_ADD_CUBE_FACE(CUBE_FRONT_VERTICES);
                    }

                    /// back
                    if (!HasNeighbour(x, y, z, 0, 0, -1)) {
                        SR_ADD_CUBE_FACE(CUBE_BACK_VERTICES);
                    }
                }
            }
        }

        m_proceduralMesh->SetIndexedVertices(vertices.data(), vertices.size());
        m_proceduralMesh->SetIndices(indices.data(), indices.size());
    }

    void Start() {
        GenerateVoxel();
        GenerateMesh();
    }

    void Update(float_t dt) override {

    }

private:
    std::vector<bool> m_voxel;

    int32_t sizeX = 16;
    int32_t sizeY = 16;
    int32_t sizeZ = 16;

    int32_t seed = 65567756;

    ProceduralMesh* m_proceduralMesh = nullptr;

    Observer* m_observer = nullptr;
    SceneCubeChunkLogic* m_logic = nullptr;

    IVector3 m_region;
    IVector3 m_chunk;

};

REGISTER_BEHAVIOUR(Chunk)
