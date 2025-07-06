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
#include <Graphics/Memory/SSBO.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::Samples {
    SR_ENUM_NS_CLASS_T(MarchingCubesShape, uint32_t,
        Sphere = 0,
        Cube = 1,
        WavySphere = 2,
        PerlinNoise = 3
    );

    class MarchingCubes : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
	    struct alignas(16) Vertex {
			alignas(16) SR_MATH_NS::FVector3 position;
			alignas(16) SR_MATH_NS::FVector3 normal;
		};

        ~MarchingCubes() override {
            Finalize();
        }

        SR_NODISCARD bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        using DensityType = float;

        std::vector<DensityType> GenerateRandomDensityField() {
            SR_TRACY_ZONE;

            const int sizeX = 64;
            const int sizeY = 64;
            const int sizeZ = 64;
            const float voxelSize = 1.0f; // шаг сетки в мире
            const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра

            std::vector<DensityType> densities(sizeX * sizeY * sizeZ);

            for (int z = 0; z < sizeZ; ++z) {
                for (int y = 0; y < sizeY; ++y) {
                    for (int x = 0; x < sizeX; ++x) {
                        int index = z * sizeY * sizeX + y * sizeX + x;

                        glm::vec3 worldPos = glm::vec3(x, y, z) * voxelSize;

                        const double dx = static_cast<double>(worldPos.x) / noiseScale + seed;
                        const double dy = static_cast<double>(worldPos.y) / noiseScale + seed;
                        const double dz = static_cast<double>(worldPos.z) / noiseScale + seed;

                        // Генерация случайной плотности с использованием шума Перлина
                        float noiseValue = SR_MATH_NS::SNoise(dx, dy, dz);
                        densities[index] = noiseValue - isoLevel; // смещение по isoLevel
                    }
                }
            }

            return densities;
        }

        std::vector<DensityType> GenerateCubeDensityField() {
            SR_TRACY_ZONE;

            const int sizeX = 64;
            const int sizeY = 64;
            const int sizeZ = 64;
            const float voxelSize = 1.0f; // шаг сетки в мире
            const float isoLevel = 0.0f;  // поверхность будет на расстоянии radius от центра
            const float cubeSize = 32.0f * geometrySize;  // поверхность будет на расстоянии radius от центра

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

        std::vector<DensityType> generateWavySphereDensities() {
            SR_TRACY_ZONE;
            const int GRID_SIZE = 64; // Размер сетки
            std::vector<DensityType> density(GRID_SIZE * GRID_SIZE * GRID_SIZE);

            for (int z = 0; z < GRID_SIZE; ++z) {
                for (int y = 0; y < GRID_SIZE; ++y) {
                    for (int x = 0; x < GRID_SIZE; ++x) {
                        // Нормализуем координаты в [-1, 1]
                        float fx = (float)x / (GRID_SIZE - 1) * 2.f - 1.f;
                        float fy = (float)y / (GRID_SIZE - 1) * 2.f - 1.f;
                        float fz = (float)z / (GRID_SIZE - 1) * 2.f - 1.f;

                        // Расстояние до центра
                        float dist = std::sqrt(fx * fx + fy * fy + fz * fz);

                        // Базовая плотность — сфера радиуса 0.5
                        float base = 0.5f * geometrySize - dist;

                        // Волны в разных плоскостях
                        float waveXZ = 0.07f * std::sin(10.f * fx) * std::sin(10.f * fz);
                        float waveXY = 0.07f * std::cos(12.f * fx) * std::cos(12.f * fy);

                        // Итоговая плотность
                        float finalDensity = base + waveXZ + waveXY;

                        density[x + y * GRID_SIZE + z * GRID_SIZE * GRID_SIZE] = finalDensity;
                    }
                }
            }

            return density;
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
            float radius = 20.0f * geometrySize;

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

            pComputeShader = SR_GTYPES_NS::ComputeShader::Load(shaderPath);

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
            int maxTriangleCount = numVoxels * 5;
            int maxVertexCount = maxTriangleCount * 3;

            std::vector<float_t> densities;

            /// density SSBO
            switch (shape) {
                default:
                case MarchingCubesShape::Sphere:
                    densities = GenerateSphereDensityField();
                    break;
                case MarchingCubesShape::Cube:
                    densities = GenerateCubeDensityField();
                    break;
                case MarchingCubesShape::WavySphere:
                    densities = generateWavySphereDensities();
                    break;
                case MarchingCubesShape::PerlinNoise:
                    densities = GenerateRandomDensityField();
                    break;
            }

            pDensitySSBO = SR_GRAPH_NS::SSBOInstance::Create<float_t>(densities.size(), SR_GRAPH_NS::SSBOUsage::CPUToGPU, "densities");
            pDensitySSBO->UpdateSSBO(densities.data());

            pHashTableSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::CPUToGPU, "hashTable");
            pVerticesSSBO = SR_GRAPH_NS::SSBOInstance::Create<Vertex>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "vertices", SR_GRAPH_NS::SSBOFlags::StructuredCounter);
            pIndicesSSBO = SR_GRAPH_NS::SSBOInstance::Create<uint32_t>(maxVertexCount, SR_GRAPH_NS::SSBOUsage::GPUToCPU, "indices", SR_GRAPH_NS::SSBOFlags::Counter);

            Generate();
        }

        void Generate() {
            SR_TRACY_ZONE;

            if (!pComputeShader) {
                return;
            }

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            if (numVoxelsPerAxis <= 0) {
                return;
            }

            pHashTableSSBO->Memset(-1);

            for (int stage = 0; stage <= 1; ++stage) {
                if (pComputeShader->BeginCompute()) {
                    pDensitySSBO->Bind();
                    pHashTableSSBO->Bind();
                    pVerticesSSBO->Bind();
                    pIndicesSSBO->Bind();
                    pComputeShader->GetShader()->SetConstInt("vertexHashTableSize"_atom, static_cast<int>(vertexHashTableSize));
                    pComputeShader->GetShader()->SetConstInt(SR_GRAPH_NS::SHADER_COMPUTE_STAGE, stage);
                    pComputeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                    pComputeShader->EndCompute();
                }
            }

            GenerateMesh();
        }

        void ReadIndices() {
            SR_TRACY_ZONE;

            if (void* pData = pIndicesSSBO->MapData()) {
                const uint32_t indicesCount = pIndicesSSBO->GetCounter();
                indices.resize(indicesCount);
                std::memcpy(indices.data(), pData, sizeof(uint32_t) * indicesCount);
                pIndicesSSBO->ResetCounter();
                pIndicesSSBO->FlushCounter();
                pIndicesSSBO->UnMap();
            }
        }

        void ReadVertices() {
            SR_TRACY_ZONE;

            if (auto&& pVertices = reinterpret_cast<Vertex*>(pVerticesSSBO->MapData())) {
                const uint32_t verticesCount = pVerticesSSBO->GetCounter();
                vertices.resize(verticesCount);

                auto&& range = std::views::iota(0, static_cast<int>(verticesCount));

                std::for_each(std::execution::par_unseq, range.begin(), range.end(), [&](int index) {
                    const Vertex& vertex = pVertices[index];
                    vertices[index] = SR_GRAPH_NS::Vertices::StaticMeshVertex{
                        .pos = vertex.position,
                        .norm = vertex.normal
                    };
                });

                pVerticesSSBO->ResetCounter();
                pVerticesSSBO->FlushCounter();
                pVerticesSSBO->UnMap();
            }
        }

        void GenerateMesh() {
            SR_TRACY_ZONE;

            ReadIndices();
            ReadVertices();

            if (gameObject) {
                if (auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                    pProceduralMesh->SwapIndices(indices);
                    pProceduralMesh->SwapIndexedVertices(vertices);
                }
            }
        }

        void Update(float_t dt) override {
            if (generateEveryFrame) {
                Generate();
            }
        }

        void Finalize() {
            SR_TRACY_ZONE;

            pVerticesSSBO = nullptr;
            pIndicesSSBO = nullptr;
            pHashTableSSBO = nullptr;
            pDensitySSBO = nullptr;
            pComputeShader = nullptr;
        }

    private:
        SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;

        SR_GTYPES_NS::ComputeShader::Ptr pComputeShader = nullptr;

        SR_GRAPH_NS::SSBOInstance::Ptr pDensitySSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pHashTableSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pVerticesSSBO = nullptr;
        SR_GRAPH_NS::SSBOInstance::Ptr pIndicesSSBO = nullptr;

        /// @property @onChanged(OnEnable)
        uint32_t numPointsPerAxis = 10;

        /// @property @onChanged(OnEnable)
        uint32_t vertexHashTableSize = 65536;

        /// @property @onChanged(OnEnable)
        float_t noiseScale = 10.0f;
        /// @property @onChanged(OnEnable)
        int64_t seed = 1;
        /// @property @onChanged(OnEnable)
        float_t geometrySize = 1.f;
        /// @property
        bool generateEveryFrame = false;

        /// @property @onChanged(OnEnable)
        MarchingCubesShape shape = MarchingCubesShape::Sphere;

        /// @property
        SR_UTILS_NS::Path shaderPath = "Samples/MarchingCubes/MarchingCubes.srsl";

    };
}

#include <Codegen/MarchingCubes.generated.hpp>