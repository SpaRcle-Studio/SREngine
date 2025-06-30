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

namespace Detail {
    struct alignas(16) Vertex {
        alignas(16) SR_MATH_NS::FVector3 position;
        alignas(16) SR_MATH_NS::FVector3 normal;
        alignas(16) SR_MATH_NS::IVector2 id;
    };

    struct alignas(16) Triangle {
        alignas(16)Vertex c;
        alignas(16)Vertex b;
        alignas(16)Vertex a;
    };
}

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    class MarchingCubes : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        ~MarchingCubes() override {
            Finalize();
        }

        SR_NODISCARD bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        using DensityType = float;

        std::vector<DensityType> GenerateCubeDensityField() {
            SR_TRACY_ZONE;

            const int sizeX = 64;
            const int sizeY = 64;
            const int sizeZ = 64;
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
            const int sizeX = 64;
            const int sizeY = 64;
            const int sizeZ = 64;
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
                const uint64_t dataSize = sizeof(uint32_t) + 12 + sizeof(Detail::Triangle) * maxVertexCount;
                SSBO = m_computeShader->GetPipeline()->AllocateSSBO(dataSize, SR_GRAPH_NS::SSBOUsage::Read);

                /// density SSBO
                //densities = GenerateSphereDensityField();
                densities = GenerateCubeDensityField();
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

            uint32_t trianglesCount = 0;
            m_computeShader->GetPipeline()->UpdateSSBO(SSBO, &trianglesCount, sizeof(uint32_t));

            if (m_computeShader->BeginCompute()) {
                m_computeShader->GetShader()->BindSSBO("triangles", SSBO);
                m_computeShader->GetShader()->BindSSBO("densities", densitySSBO);
                m_computeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                m_computeShader->EndCompute();
            }

            DebugReadSSBO();
        }

        void DebugReadSSBO() {
            SR_TRACY_ZONE;

            if (SSBO == SR_ID_INVALID) {
                return;
            }

            void* pData = nullptr;
            if (!m_computeShader->GetPipeline()->MapSSBO(SSBO, &pData)) {
                return;
            }

            uint32_t trianglesCount = *reinterpret_cast<uint32_t*>(pData);
            Detail::Triangle* triangles = reinterpret_cast<Detail::Triangle*>(reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t) + 12);

            //std::vector<Detail::Triangle> triangles;
            //int numVoxelsPerAxis = numPointsPerAxis - 1;
            //GenerateMarchingCubesCPU(numVoxelsPerAxis * 8, numVoxelsPerAxis * 8, numVoxelsPerAxis * 8, numPointsPerAxis, densities, triangles);
            //uint32_t trianglesCount = static_cast<uint32_t>(triangles.size());

            //std::vector<SR_GRAPH_NS::Vertices::StaticMeshVertex> nonIndexedVertices;
            //nonIndexedVertices.reserve(trianglesCount * 3);

            //std::unordered_map<SR_MATH_NS::IVector2, uint32_t> vertexMap;

            std::unordered_map<uint64_t, uint32_t> vertexMap;
            static SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;
            static SR_HTYPES_NS::FastMemoryArray<uint32_t> processedTriangles;

            vertices.clear();
            processedTriangles.clear();

            vertices.reserve(trianglesCount * 3);
            processedTriangles.reserve(trianglesCount);

            int triangleIndex = 0;
            SR_GRAPH_NS::Vertices::StaticMeshVertex meshVertex;

            std::hash<SR_MATH_NS::FVector3> hashFunction;

            auto&& processVertex = [&](const Detail::Vertex& vertex) {
                const uint64_t vertexPosHash = hashFunction(vertex.position);
                auto&& pIt = vertexMap.find(vertexPosHash);
                if (pIt == vertexMap.end()) {
                    meshVertex.pos = vertex.position;
                    meshVertex.norm = vertex.normal;
                    vertices.push_back(meshVertex);
                    pIt = vertexMap.emplace(vertexPosHash, triangleIndex).first;
                    processedTriangles.push_back(triangleIndex);
                    triangleIndex++;
                }
                else {
                    processedTriangles.push_back(pIt->second);
                }

                /*auto&& pIt = vertexMap.find(vertex.id);
                if (pIt == vertexMap.end()) {
                    SR_GRAPH_NS::Vertices::StaticMeshVertex meshVertex;
                    meshVertex.pos = vertex.position;
                    meshVertex.norm = vertex.normal;
                    vertices.emplace_back(meshVertex);
                    pIt = vertexMap.emplace(vertex.id, triangleIndex).first;
                    processedTriangles.emplace_back(triangleIndex);
                    triangleIndex++;
                }
                else {
                    processedTriangles.emplace_back(pIt->second);
                }*/

                //SR_GRAPH_NS::Vertices::StaticMeshVertex meshVertex;
                //meshVertex.pos = vertex.position;
                //meshVertex.norm = vertex.normal;
                //nonIndexedVertices.emplace_back(meshVertex);
            };

            for (uint32_t i = 0; i < trianglesCount; ++i) {
                const Detail::Triangle& triangle = triangles[i];

                processVertex(triangle.c);
                processVertex(triangle.b);
                processVertex(triangle.a);
            }

            if (gameObject) {
                if (auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                    //pProceduralMesh->SetVertices(nonIndexedVertices);
                    //pProceduralMesh->SetIndexedVertices(vertices.data(), static_cast<uint32_t>(vertices.size()));
                    //pProceduralMesh->SetIndices(processedTriangles.data(), static_cast<uint32_t>(processedTriangles.size()));
                    pProceduralMesh->SwapIndices(processedTriangles);
                    pProceduralMesh->SwapIndexedVertices(vertices);
                }
            }

            m_computeShader->GetPipeline()->UnMapSSBO(SSBO);
        }

        void Update(float_t dt) override {
        }

        void Finalize() {
            SR_TRACY_ZONE;

            if (SSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&SSBO);
            }

            if (densitySSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&densitySSBO);
            }

            m_computeShader = nullptr;
        }

    private:
        std::vector<DensityType> densities;
        SR_GTYPES_NS::ComputeShader::Ptr m_computeShader = nullptr;
        int32_t SSBO = SR_ID_INVALID;
        int32_t densitySSBO = SR_ID_INVALID;

        /// @property
        uint32_t numPointsPerAxis = 10;

        /// @property
        SR_UTILS_NS::Path shaderPath = "Samples/MarchingCubes/MarchingCubes.srsl";
        /// @property @onChanged(DebugReadSSBO)
        bool debugReadSSBO = false;

    };
}

#include <Codegen/MarchingCubes.generated.hpp>