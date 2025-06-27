//
// Created by Monika on 25.06.2025.
//

#include <Utils/Input/InputSystem.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    enum class BlockSide {
        Top,
        Bottom,
        Front,
        Back,
        Right,
        Left
    };

    struct BlockFaceDef {
        SR_MATH_NS::FVector3 originOffset;
        SR_MATH_NS::FVector3 normal;
        SR_MATH_NS::FVector3 offsetU;
        SR_MATH_NS::FVector3 offsetV;
        BlockSide side;
    };

    static const BlockFaceDef BLOCK_FACES[] = {
        { {0, 1, 0}, {0, 1, 0},  {1, 0, 0},  {0, 0, 1}, BlockSide::Top },
        { {0, 0, 1}, {0, -1, 0}, {1, 0, 0},  {0, 0, -1}, BlockSide::Bottom },
        { {0, 1, 1}, {0, 0, 1},  {1, 0, 0},  {0, -1, 0}, BlockSide::Front },
        { {0, 0, 0}, {0, 0, -1}, {1, 0, 0},  {0, 1, 0}, BlockSide::Back },
        { {1, 0, 0}, {1, 0, 0},  {0, 0, 1},  {0, 1, 0}, BlockSide::Right },
        { {0, 1, 0}, {-1, 0, 0}, {0, 0, 1},  {0, -1, 0}, BlockSide::Left }
    };

    static const SR_MATH_NS::IVector3 BLOCK_FACE_OFFSETS[] = {
        SR_MATH_NS::IVector3(0,  1,  0), // Top
        SR_MATH_NS::IVector3(0, -1,  0), // Bottom
        SR_MATH_NS::IVector3(0,  0,  1), // Front
        SR_MATH_NS::IVector3(0,  0, -1), // Back
        SR_MATH_NS::IVector3(1,  0,  0), // Right
        SR_MATH_NS::IVector3(-1, 0,  0)  // Left
    };

    struct BlockInfo {
        bool exists = false;
    };

    class ChunkRenderer : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        void Update(float_t dt) override {
            Regenerate();
        }

        void Regenerate() {
            if (!isDirty || !sceneObject) {
                return;
            }

            SR_TRACY_ZONE;

            isDirty = false;

            pMesh = sceneObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
            if (!pMesh) {
                SR_ERROR("ChunkRenderer::Start() : ProceduralMesh component not found!");
                return;
            }

            vertices.reserve(size.x * size.y * size.z * 6 * 4);
            indices.reserve(size.x * size.y * size.z * 6 * 6);

            RegenerateChunkData();
            RebuildVerticesAndIndices();

            /// some comment 2 3

            pMesh->SetIndexedVertices(vertices.data(), vertices.size());
            pMesh->SetIndices(indices.data(), indices.size());

            vertices.clear();
            indices.clear();
        }

        void MarkDirty() {
            isDirty = true;
        }

    private:
        void RebuildVerticesAndIndices() {
            SR_TRACY_ZONE;

            for (uint32_t x = 0; x < size.x; ++x) {
                for (uint32_t y = 0; y < size.y; ++y) {
                    for (uint32_t z = 0; z < size.z; ++z) {
                        if (!GetBlockUnsafe(x, y, z).exists) SR_UNLIKELY_ATTRIBUTE {
                            continue;
                        }
                        GenerateBlock(x, y, z);
                    }
                }
            }
        }

        void RegenerateChunkData() {
            SR_TRACY_ZONE;

            if (blocksCount != size.x * size.y * size.z) {
                delete[] pBlocks;
                blocksCount = size.x * size.y * size.z;
                pBlocks = new BlockInfo[blocksCount];
            }

            for (uint32_t x = 0; x < size.x; ++x) {
                for (uint32_t y = 0; y < size.y; ++y) {
                    for (uint32_t z = 0; z < size.z; ++z) {
                        const float_t noise = SR_MATH_NS::SNoise(
                            (static_cast<double>(x) / noiseScale + static_cast<double>(seed)),
                            (static_cast<double>(y) / noiseScale + static_cast<double>(seed)),
                            (static_cast<double>(z) / noiseScale + static_cast<double>(seed))
                        );

                        GetBlockUnsafe(x, y, z).exists = noise > 0.f;
                    }
                }
            }
        }

        void AddFace(
            uint32_t x, uint32_t y, uint32_t z,
            const SR_MATH_NS::FVector3& normal,
            const SR_MATH_NS::FVector3& offsetU,
            const SR_MATH_NS::FVector3& offsetV
        ) {
            SR_GRAPH_NS::Vertices::StaticMeshVertex vertex;
            const uint32_t count = vertices.size();

            vertex.norm = normal;

            vertex.pos = SR_MATH_NS::FVector3(x, y, z);
            vertex.uv = SR_MATH_NS::FVector2(0, 0);
            vertices.emplace_back(vertex);

            vertex.pos = SR_MATH_NS::FVector3(x, y, z) + offsetV;
            vertex.uv = SR_MATH_NS::FVector2(0, 1);
            vertices.emplace_back(vertex);

            vertex.pos = SR_MATH_NS::FVector3(x, y, z) + offsetU;
            vertex.uv = SR_MATH_NS::FVector2(1, 0);
            vertices.emplace_back(vertex);

            vertex.pos = SR_MATH_NS::FVector3(x, y, z) + offsetU + offsetV;
            vertex.uv = SR_MATH_NS::FVector2(1, 1);
            vertices.emplace_back(vertex);

            indices.emplace_back(count + 0);
            indices.emplace_back(count + 1);
            indices.emplace_back(count + 2);

            indices.emplace_back(count + 1);
            indices.emplace_back(count + 3);
            indices.emplace_back(count + 2);
        }

        void GenerateBlock(uint32_t x, uint32_t y, uint32_t z) {
            for (const auto& face : BLOCK_FACES) {
                if (GetBlockNeighbour(x, y, z, face.side).exists) {
                    continue;
                }

                AddFace(
                    x + face.originOffset.x,
                    y + face.originOffset.y,
                    z + face.originOffset.z,
                    face.normal,
                    face.offsetU,
                    face.offsetV
                );
            }
        }

        BlockInfo& GetBlock(uint32_t x, uint32_t y, uint32_t z) {
            if (x >= size.x || y >= size.y || z >= size.z) SR_UNLIKELY_ATTRIBUTE {
                static BlockInfo emptyBlock;
                return emptyBlock; // Return an empty block if out of bounds
            }
            return pBlocks[x + y * size.x + z * size.x * size.y];
        }

        BlockInfo& GetBlockUnsafe(uint32_t x, uint32_t y, uint32_t z) {
            return pBlocks[x + y * size.x + z * size.x * size.y];
        }

        BlockInfo& GetBlockNeighbour(uint32_t x, uint32_t y, uint32_t z, BlockSide side) {
            return GetBlock(
                static_cast<int32_t>(x) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].x,
                static_cast<int32_t>(y) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].y,
                static_cast<int32_t>(z) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].z
            );
        }

    private:
        std::vector<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;
        std::vector<uint32_t> indices;
        bool isDirty = true;

        BlockInfo* pBlocks = nullptr;
        uint32_t blocksCount = 0;

        SR_GTYPES_NS::ProceduralMesh::Ptr pMesh;

        /// @property @onChanged(MarkDirty)
        SR_MATH_NS::UVector3 size = SR_MATH_NS::UVector3(16, 64, 16);
        /// @property @onChanged(MarkDirty)
        float_t noiseScale = 10.0f;
        /// @property @onChanged(MarkDirty)
        int64_t seed = 1;

    };
}

#include <Codegen/ChunkRenderer.generated.hpp>