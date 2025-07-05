//
// Created by Monika on 28.06.2025.
//

#include <Utils/Input/KeyCodes.h>
#include <Utils/Math/Vector2.h>
#include <Utils/Math/Noise.h>
#include <Utils/Math/VectorRanges.h>

#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/Types/ComputeShader.h>
#include <Graphics/Render/RenderContext.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    class MarchingCubesOptimized : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
		struct alignas(16) Vertex {
			alignas(16) SR_MATH_NS::FVector3 position;
			alignas(16) SR_MATH_NS::FVector3 normal;
		};

        ~MarchingCubesOptimized() override {
            Finalize();
        }

        SR_NODISCARD bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        using DensityType = float;

        std::vector<DensityType> GenerateCubeDensityField() {
            SR_TRACY_ZONE;

            const int sizeX = densityCountAxis;
            const int sizeY = densityCountAxis;
            const int sizeZ = densityCountAxis;
            const float voxelSize = 1.0f; // шаг сетки в мире
            const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра
            const float cubeSize = 32.0f;  // поверхность будет на расстоянии radius от центра

            std::vector<DensityType> densities(sizeX * sizeY * sizeZ);

            // Центр куба
            glm::vec3 center = glm::vec3(sizeX, sizeY, sizeZ) * 0.5f * voxelSize;
            glm::vec3 halfExtents = glm::vec3(cubeSize * 0.5f);

            for (int z = 0; z < sizeZ; ++z) {
                for (int y = 0; y < sizeY; ++y) {
                    for (int x = 0; x < sizeX; ++x) {
                        int index = z * sizeY * sizeX + y * sizeX + x;

                        glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;
                        glm::vec3 d = glm::abs(worldPos - center) - halfExtents;

                        // SDF куба: max(max(d.x, d.y), d.z)
                        float outside = glm::max(glm::max(d.x, d.y), d.z);
                        float sdf = -outside; // < 0 — снаружи, > 0 — внутри

                        densities[index] = sdf;
                    }
                }
            }

            return densities;
        }

        std::vector<DensityType> GenerateSphereDensityField() {
            SR_TRACY_ZONE;

            /// Параметры сетки
            const int sizeX = densityCountAxis;
            const int sizeY = densityCountAxis;
            const int sizeZ = densityCountAxis;
            const float voxelSize = 1.0f; // шаг сетки в мире
            const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра

            /// Центр и радиус сферы
            glm::vec3 center = glm::vec3(sizeX, sizeY, sizeZ) * 0.5f * voxelSize;
            float radius = 20.0f;

            std::vector<DensityType> densities(sizeX * sizeY * sizeZ);

            for (int z = 0; z < sizeZ; ++z) {
                for (int y = 0; y < sizeY; ++y) {
                    for (int x = 0; x < sizeX; ++x) {
                        int index = z * sizeY * sizeX + y * sizeX + x;

                        // Мировая позиция текущего вокселя
                        glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;

                        // SDF сферы: (расстояние от центра - радиус)
                        float d = radius - glm::distance(worldPos, center);

                        densities[index] = d;
                    }
                }
            }

            return densities;
        }

        void OnDisable() override {
            Finalize();
        }

        void OnEnable() override {
            SR_TRACY_ZONE;

            Finalize();

            m_computeShader = SR_GTYPES_NS::ComputeShader::Load(shaderPath);

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
            int maxTriangleCount = numVoxels * 5;
            int maxVertexCount = maxTriangleCount * 3;

            if (m_computeShader) {
                vertexCacheSSBO = m_computeShader->GetPipeline()->AllocateSSBO(3 * densityCountAxis * densityCountAxis * densityCountAxis * sizeof(uint32_t), SR_GRAPH_NS::SSBOUsage::ReadWrite);

                verticesSSBO = m_computeShader->GetPipeline()->AllocateSSBO(maxVertexCount * sizeof(Vertex) + sizeof(uint32_t) * 4, SR_GRAPH_NS::SSBOUsage::Read);
                indicesSSBO = m_computeShader->GetPipeline()->AllocateSSBO(maxTriangleCount * sizeof(uint32_t) + sizeof(uint32_t), SR_GRAPH_NS::SSBOUsage::Read);

                /// density SSBO
                densities = GenerateSphereDensityField();
                //densities = GenerateCubeDensityField();
                const uint64_t densityDataSize = densities.size() * sizeof(DensityType);
                densitySSBO = m_computeShader->GetPipeline()->AllocateSSBO(densityDataSize, SR_GRAPH_NS::SSBOUsage::Write);

                m_computeShader->GetPipeline()->UpdateSSBO(densitySSBO, densities.data(), densityDataSize);
            }

            Generate();
        }

        void Generate() {
            SR_TRACY_ZONE;

            if (!m_computeShader) {
                return;
            }

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            if (numVoxelsPerAxis <= 0) {
                return;
            }

            uint32_t nullValue = 0;
            m_computeShader->GetPipeline()->UpdateSSBO(verticesSSBO, &nullValue, sizeof(uint32_t));
            m_computeShader->GetPipeline()->UpdateSSBO(indicesSSBO, &nullValue, sizeof(uint32_t));

            if (m_computeShader->BeginCompute()) {
                m_computeShader->GetShader()->BindSSBO("densities", densitySSBO);
                m_computeShader->GetShader()->BindSSBO("vertices", verticesSSBO);
                m_computeShader->GetShader()->BindSSBO("indices", indicesSSBO);

                //int threadsPerGroup = 8;
                //int groups = (numPointsPerAxis + threadsPerGroup - 1) / threadsPerGroup;
                //m_computeShader->Dispatch(groups, groups, groups);

                m_computeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                //m_computeShader->Dispatch(groups * 8, groups * 8, groups * 8);
                m_computeShader->EndCompute();
            }

            DebugReadSSBO();
        }

        void DebugReadSSBO() {
            SR_TRACY_ZONE;

            if (vertexCacheSSBO == SR_ID_INVALID || !gameObject) {
                return;
            }

            auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>();
            if (!pProceduralMesh) {
                return;
            }

            void* pData = nullptr;

            if (m_computeShader->GetPipeline()->MapSSBO(indicesSSBO, &pData)) {
                uint32_t indicesCount = *reinterpret_cast<uint32_t *>(pData);

                SR_LOG("MarchingCubes::DebugReadSSBO() : indicesCount = {}", indicesCount);

                indices.resize(indicesCount);
                memcpy(indices.data(), reinterpret_cast<uint8_t *>(pData) + sizeof(uint32_t), indicesCount * sizeof(uint32_t));
                pProceduralMesh->SwapIndices(indices);

                m_computeShader->GetPipeline()->UnMapSSBO(indicesSSBO);
            }

            if (m_computeShader->GetPipeline()->MapSSBO(verticesSSBO, &pData)) {
                uint32_t uniqueVerticesCount = *reinterpret_cast<uint32_t*>(pData);
                SR_LOG("MarchingCubes::DebugReadSSBO() : uniqueVerticesCount = {}", uniqueVerticesCount);

                vertices.resize(uniqueVerticesCount);
                for (uint32_t i = 0; i < uniqueVerticesCount; ++i) {
                    auto& vertex = vertices[i];
                    auto& detailVertex = reinterpret_cast<Vertex*>(reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t) * 4)[i];
                    vertex.pos = detailVertex.position;
                    vertex.norm = detailVertex.normal;
                }

                pProceduralMesh->SwapIndexedVertices(vertices);
                m_computeShader->GetPipeline()->UnMapSSBO(verticesSSBO);
            }

            //uint32_t trianglesCount = *reinterpret_cast<uint32_t*>(pData);
            //Detail::Triangle* triangles = reinterpret_cast<Detail::Triangle*>(reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t) + 12);

            //m_computeShader->GetPipeline()->UnMapSSBO(SSBO);
        }

        void Update(float_t dt) override {
        }

        void Finalize() {
            SR_TRACY_ZONE;

            if (densitySSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&densitySSBO);
            }

            if (verticesSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&verticesSSBO);
            }

            if (indicesSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&indicesSSBO);
            }

            m_computeShader = nullptr;
        }

    private:
        std::vector<DensityType> densities;
        SR_GTYPES_NS::ComputeShader::Ptr m_computeShader = nullptr;
        int32_t verticesSSBO = SR_ID_INVALID;
        int32_t indicesSSBO = SR_ID_INVALID;
        int32_t densitySSBO = SR_ID_INVALID;
        int32_t vertexCacheSSBO = SR_ID_INVALID;

        SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;
        SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;

        /// @property
        uint32_t numPointsPerAxis = 10;
        /// @property
        uint32_t densityCountAxis = 64;

        /// @property
        SR_UTILS_NS::Path shaderPath = "Samples/MarchingCubes/MarchingCubesOptimized.srsl";
        /// @property @onChanged(DebugReadSSBO)
        bool debugReadSSBO = false;

    };
}

#include <Codegen/MarchingCubesOptimized.generated.hpp>