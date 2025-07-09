//
// Created by Monika on 25.06.2025.
//

#include <Utils/Input/InputSystem.h>
#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>
#include <Utils/Math/VectorRanges.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>

#include <Scripting/Cpp/CppBehaviour.h>

#include "ChunkRendererHelper.h"

namespace SpaRcle::Scripts::Samples {
    class ChunkRendererSSBO : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        SR_NODISCARD bool ExecuteInEditMode() const override {
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

            RegenerateChunkData();
            PreCalcBlockMeshes();

            vertices.resize(totalSides * 6);
            //indices.resize(totalSides * 4);

            RebuildVerticesAndIndices();

            pMesh->SwapIndexedVertices(vertices);
            //pMesh->SwapIndices(indices);
        }

        void MarkDirty() {
            isDirty = true;
        }

    private:
        void PreCalcBlockMeshes() {
            SR_TRACY_ZONE;

            SR_MATH_NS::UVector3Range chunkRange(size.x, size.y, size.z);

            std::atomic<uint32_t> blockIndex = 0;

            std::for_each(std::execution::par_unseq, chunkRange.begin(), chunkRange.end(), [&](const auto& pos) {
                BlockInfo& block = GetBlockUnsafe(pos.x, pos.y, pos.z);
                block.sides = 0;
                if (block.exists) {
                    for (const auto& face : BLOCK_FACES) {
                        if (!GetBlockNeighbour(pos.x, pos.y, pos.z, face.side).exists) {
                            block.sides += 1;
                        }
                    }
                    if (block.sides > 0) {
                        block.offset = blockIndex.fetch_add(block.sides, std::memory_order_relaxed);
                    }
                }
            });

            totalSides = std::transform_reduce(std::execution::par_unseq, chunkRange.begin(), chunkRange.end(), 0u, std::plus<>(), [&](const SR_MATH_NS::UVector3& pos) {
                return static_cast<uint32_t>(GetBlockUnsafe(pos.x, pos.y, pos.z).sides);
            });
        }

        void RebuildVerticesAndIndices() {
            SR_TRACY_ZONE;

            SR_MATH_NS::UVector3Range chunkRange(size.x, size.y, size.z);

            std::for_each(std::execution::par_unseq, chunkRange.begin(), chunkRange.end(), [&](const auto& pos) {
                const BlockInfo& blockInfo = GetBlockUnsafe(pos.x, pos.y, pos.z);

                if (blockInfo.sides == 0) {
                    return;
                }

                uint32_t baseIndex = blockInfo.offset * 6;

                for (const auto& face : BLOCK_FACES) {
                    if (GetBlockNeighbour(pos.x, pos.y, pos.z, face.side).exists) {
                        continue;
                    }

                    AddFace(
                        pos.x + face.originOffset.x,
                        pos.y + face.originOffset.y,
                        pos.z + face.originOffset.z,
                        face.normal, face.offsetU, face.offsetV,
                        vertices.data() + baseIndex
                    );

                    baseIndex += 6;
                }
            });
        }

        void RegenerateChunkData() {
            SR_TRACY_ZONE;

            if (blocksCount != size.x * size.y * size.z) {
                delete[] pBlocks;
                blocksCount = size.x * size.y * size.z;
                pBlocks = new BlockInfo[blocksCount];
            }

            SR_MATH_NS::UVector3Range chunkRange(size.x, size.y, size.z);

            std::for_each(std::execution::par_unseq, chunkRange.begin(), chunkRange.end(), [&](const auto& pos) {
                const double dx = static_cast<double>(pos.x) / noiseScale + seed;
                const double dy = static_cast<double>(pos.y) / noiseScale + seed;
                const double dz = static_cast<double>(pos.z) / noiseScale + seed;

                const float_t noise = SR_MATH_NS::SNoise(dx, dy, dz);
                GetBlockUnsafe(pos.x, pos.y, pos.z).exists = noise > 0.f;
            });
        }

        SR_FORCE_INLINE void SR_FASTCALL AddFace(
            uint32_t x, uint32_t y, uint32_t z,
            const SR_MATH_NS::FVector3& normal,
            const SR_MATH_NS::FVector3& offsetU,
            const SR_MATH_NS::FVector3& offsetV,
            SR_GRAPH_NS::Vertices::StaticMeshVertexAligned* pVertices
        ) {
            constexpr static SR_MATH_NS::FVector2 uvs[4] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
            const SR_MATH_NS::FVector3 origin(static_cast<float_t>(x), static_cast<float_t>(y), static_cast<float_t>(z));

            pVertices[0] = { origin,                     0.f, uvs[0], {}, normal };
            pVertices[1] = { origin + offsetV,           0.f, uvs[1], {}, normal };
            pVertices[2] = { origin + offsetU,           0.f, uvs[2], {}, normal };

            pVertices[3] = { origin + offsetV,           0.f, uvs[1], {}, normal };
            pVertices[4] = { origin + offsetU + offsetV, 0.f, uvs[3], {}, normal };
            pVertices[5] = { origin + offsetU,           0.f, uvs[2], {}, normal };

            /*pVertices[0] = { origin,                     0.f, uvs[0], {}, normal };
            pVertices[1] = { origin + offsetV,           0.f, uvs[1], {}, normal };
            pVertices[2] = { origin + offsetU,           0.f, uvs[2], {}, normal };
            pVertices[3] = { origin + offsetU + offsetV, 0.f, uvs[3], {}, normal };*/

            //pIndices[0] = baseIndex + 0;
            //pIndices[1] = baseIndex + 1;
            //pIndices[2] = baseIndex + 2;
            //pIndices[3] = baseIndex + 3;

            /*pVertices[0] = { origin,                     uvs[0], normal };
            pVertices[1] = { origin + offsetV,           uvs[1], normal };
            pVertices[2] = { origin + offsetU,           uvs[2], normal };
            pVertices[3] = { origin + offsetU + offsetV, uvs[3], normal };

            pIndices[0] = baseIndex + 0;
            pIndices[1] = baseIndex + 1;
            pIndices[2] = baseIndex + 2;
            pIndices[3] = baseIndex + 1;
            pIndices[4] = baseIndex + 3;
            pIndices[5] = baseIndex + 2;*/
        }

        BlockInfo& GetBlock(uint32_t x, uint32_t y, uint32_t z) {
            if (x >= size.x || y >= size.y || z >= size.z) SR_UNLIKELY_ATTRIBUTE {
                static BlockInfo emptyBlock;
                return emptyBlock;
            }
            return pBlocks[x + y * size.x + z * size.x * size.y];
        }

        SR_NODISCARD BlockInfo& SR_FASTCALL GetBlockUnsafe(uint32_t x, uint32_t y, uint32_t z) {
            return pBlocks[x + y * size.x + z * size.x * size.y];
        }

        BlockInfo& SR_FASTCALL GetBlockNeighbour(uint32_t x, uint32_t y, uint32_t z, BlockSide side) {
            return GetBlock(
                static_cast<int32_t>(x) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].x,
                static_cast<int32_t>(y) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].y,
                static_cast<int32_t>(z) + BLOCK_FACE_OFFSETS[static_cast<uint32_t>(side)].z
            );
        }

    private:
        SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertexAligned> vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;
        bool isDirty = true;

        std::mutex buffersMutex;

        BlockInfo* pBlocks = nullptr;
        uint32_t blocksCount = 0;

        uint32_t totalSides = 0;

        SR_GTYPES_NS::ProceduralMesh::Ptr pMesh;

        /// @property @onChanged(MarkDirty)
        SR_MATH_NS::UVector3 size = SR_MATH_NS::UVector3(16, 64, 16);
        /// @property @onChanged(MarkDirty)
        float_t noiseScale = 10.0f;
        /// @property @onChanged(MarkDirty)
        int64_t seed = 1;

    };
}

#include <Codegen/ChunkRendererSSBO.generated.hpp>