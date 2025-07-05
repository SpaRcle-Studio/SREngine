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
			alignas(16) SR_MATH_NS::IVector2 id;
		};

        ~MarchingCubes() override {
            Finalize();
        }

        SR_NODISCARD bool ExecuteInEditMode() const override {
            return true; // Allow execution in edit mode for testing purposes
        }

        uint32_t hashVertexID(SR_MATH_NS::IVector2 id) {
            return uint32_t(id.x * 73856093 ^ id.y * 19349663) % vertexHashTableSize;
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

            m_computeShader = SR_GTYPES_NS::ComputeShader::Load(shaderPath);

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            int numVoxels = numVoxelsPerAxis * numVoxelsPerAxis * numVoxelsPerAxis;
            int maxTriangleCount = numVoxels * 5;
            int maxVertexCount = maxTriangleCount * 3;

            if (m_computeShader) {
                const uint64_t verticesSize = sizeof(uint32_t) + 12 + sizeof(Vertex) * maxVertexCount;
                verticesSSBO = m_computeShader->GetPipeline()->AllocateSSBO(verticesSize, SR_GRAPH_NS::SSBOUsage::Write);

                const uint64_t indicesSize = sizeof(uint32_t) + sizeof(uint32_t) * maxVertexCount;
                indicesSSBO = m_computeShader->GetPipeline()->AllocateSSBO(indicesSize, SR_GRAPH_NS::SSBOUsage::Write);

                hashTableSSBO = m_computeShader->GetPipeline()->AllocateSSBO(sizeof(uint32_t) * vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::Write);
                vertexKeysSSBO = m_computeShader->GetPipeline()->AllocateSSBO(sizeof(uint32_t) * vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::Write);
                vertexValuesSSBO = m_computeShader->GetPipeline()->AllocateSSBO(sizeof(uint32_t) * vertexHashTableSize, SR_GRAPH_NS::SSBOUsage::Write);

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

                const uint64_t densityDataSize = densities.size() * sizeof(DensityType);
                densitySSBO = m_computeShader->GetPipeline()->AllocateSSBO(densityDataSize, SR_GRAPH_NS::SSBOUsage::Read);

                m_computeShader->GetPipeline()->UpdateSSBO(densitySSBO, densities.data(), densityDataSize);
            }

            vertexKeys.resize(vertexHashTableSize);
            vertexValues.resize(vertexHashTableSize);

            vertexKeys.FillInt(-1);
            vertexValues.FillZero();

            Generate();
        }

        uint32_t packID(SR_MATH_NS::IVector2 id) {
            //return (uint32_t(id.x) & 0xFFFFu) | ((uint32_t(id.y) & 0xFFFFu) << 16);
            return id.x * (73856093u ^ id.y) * 19349663u; // простой хеш-функция для ID
        }

        //SR_MATH_NS::IVector2 unpackID(uint32_t packed) {
        //    return SR_MATH_NS::IVector2(int(packed & 0xFFFFu), int((packed >> 16) & 0xFFFFu));
        //}

        void Generate() {
            SR_TRACY_ZONE;

            if (!m_computeShader) {
                return;
            }

            int numVoxelsPerAxis = numPointsPerAxis - 1;
            if (numVoxelsPerAxis <= 0) {
                return;
            }

            uint32_t nullVal = 0;
            m_computeShader->GetPipeline()->UpdateSSBO(verticesSSBO, &nullVal, sizeof(uint32_t));
            m_computeShader->GetPipeline()->UpdateSSBO(indicesSSBO, &nullVal, sizeof(uint32_t));

            m_computeShader->GetPipeline()->UpdateSSBO(vertexKeysSSBO, vertexKeys.data(), sizeof(uint32_t) * vertexHashTableSize);
            m_computeShader->GetPipeline()->UpdateSSBO(vertexValuesSSBO, vertexValues.data(), sizeof(uint32_t) * vertexHashTableSize);
            m_computeShader->GetPipeline()->UpdateSSBO(hashTableSSBO, vertexKeys.data(), sizeof(uint32_t) * vertexHashTableSize);

            for (int stage = 0; stage <= 1; ++stage) {
                if (m_computeShader->BeginCompute()) {
                    m_computeShader->GetShader()->BindSSBO("vertices", verticesSSBO);
                    m_computeShader->GetShader()->BindSSBO("indices", indicesSSBO);
                    m_computeShader->GetShader()->BindSSBO("densities", densitySSBO);
                    m_computeShader->GetShader()->BindSSBO("hashTable", hashTableSSBO);
                    m_computeShader->GetShader()->BindSSBO("vertexKeys", vertexKeysSSBO);
                    m_computeShader->GetShader()->BindSSBO("vertexValues", vertexValuesSSBO);
                    m_computeShader->GetShader()->SetConstInt("vertexHashTableSize"_atom, static_cast<int>(vertexHashTableSize));
                    m_computeShader->GetShader()->SetConstInt(SR_GRAPH_NS::SHADER_COMPUTE_STAGE, stage);
                    m_computeShader->Dispatch(numVoxelsPerAxis, numVoxelsPerAxis, numVoxelsPerAxis);
                    m_computeShader->EndCompute();
                }
            }

            DebugReadSSBO();
        }

        int getOrInsertVertex(Vertex v) {
            uint32_t h = hashVertexID(v.id);
            uint32_t key = packID(v.id);

            for (uint32_t i = 0u; i < vertexHashTableSize; ++i) {
                uint32_t idx = (h + i) & (vertexHashTableSize - 1u); // быстрая альтернатива % tableSize

                uint32_t old = vertexKeys[idx];
                if (vertexKeys[idx] == 0xFFFFFFFFu) {
                    vertexKeys[idx] = key;
                }

                if (old == key) {
                    return vertexValues[idx]; // уже был
                }

                if (old == 0xFFFFFFFFu) {
                    SR_GRAPH_NS::Vertices::StaticMeshVertex newVertex;
                    newVertex.pos = v.position;
                    newVertex.norm = v.normal;
                    vertices.push_back(newVertex);

                    vertexValues[idx] = vertices.size() - 1;
                    return vertices.size() - 1;
                }

                // иначе — коллизия, продолжаем
            }

            return -1; // таблица переполнена
        }

        void ReadIndices() {
            SR_TRACY_ZONE;
            void* pData = nullptr;

            if (!m_computeShader->GetPipeline()->MapSSBO(indicesSSBO, &pData)) {
                return;
            }

            uint32_t indicesCount = *reinterpret_cast<uint32_t*>(pData);
            indices.resize(indicesCount);
            std::memcpy(indices.data(), reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t), sizeof(uint32_t) * indicesCount);

            m_computeShader->GetPipeline()->UnMapSSBO(indicesSSBO);
        }

        void ReadVertices() {
            SR_TRACY_ZONE;

            void* pData = nullptr;
            if (!m_computeShader->GetPipeline()->MapSSBO(verticesSSBO, &pData)) {
                return;
            }

            uint32_t verticesCount = *reinterpret_cast<uint32_t*>(pData);
            Vertex* pVertices = reinterpret_cast<Vertex*>(reinterpret_cast<uint8_t*>(pData) + sizeof(uint32_t) + 12);

            vertices.resize(verticesCount);

            auto&& range = std::views::iota(0, static_cast<int>(verticesCount));
            std::for_each(std::execution::par_unseq, range.begin(), range.end(), [&](int index) {
                const Vertex& vertex = pVertices[index];
                vertices[index] = SR_GRAPH_NS::Vertices::StaticMeshVertex{
                    .pos = vertex.position,
                    .norm = vertex.normal
                };
            });

            m_computeShader->GetPipeline()->UnMapSSBO(verticesSSBO);
        }

        void DebugReadSSBO() {
            SR_TRACY_ZONE;

            if (verticesSSBO == SR_ID_INVALID) {
                return;
            }

            ReadIndices();
            ReadVertices();

            if (gameObject) {
                if (auto&& pProceduralMesh = gameObject->GetComponent<SR_GTYPES_NS::ProceduralMesh>()) {
                    pProceduralMesh->SwapIndices(indices);
                    pProceduralMesh->SwapIndexedVertices(vertices);
                    //pProceduralMesh->SetVertices(vertices);
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

            if (hashTableSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&hashTableSSBO);
            }

            if (vertexKeysSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&vertexKeysSSBO);
            }

            if (vertexValuesSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&vertexValuesSSBO);
            }

            if (indicesSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&indicesSSBO);
            }

            if (verticesSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&verticesSSBO);
            }

            if (densitySSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&densitySSBO);
            }

            if (mutexSSBO != SR_ID_INVALID) {
                m_computeShader->GetPipeline()->FreeSSBO(&mutexSSBO);
            }

            m_computeShader = nullptr;
        }

    private:
        SR_HTYPES_NS::FastMemoryArray<SR_GRAPH_NS::Vertices::StaticMeshVertex> vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> indices;

        SR_HTYPES_NS::FastMemoryArray<uint32_t> vertexKeys; // для хеш-таблицы вершин
        SR_HTYPES_NS::FastMemoryArray<uint32_t> vertexValues; // для хеш-таблицы вершин

        std::vector<DensityType> densities;
        SR_GTYPES_NS::ComputeShader::Ptr m_computeShader = nullptr;
        int32_t verticesSSBO = SR_ID_INVALID;
        int32_t indicesSSBO = SR_ID_INVALID;
        int32_t densitySSBO = SR_ID_INVALID;
        int32_t vertexKeysSSBO = SR_ID_INVALID;
        int32_t vertexValuesSSBO = SR_ID_INVALID;
        int32_t hashTableSSBO = SR_ID_INVALID;
        int32_t mutexSSBO = SR_ID_INVALID;

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
        /// @property @onChanged(DebugReadSSBO)
        bool debugReadSSBO = false;

    };
}

#include <Codegen/MarchingCubes.generated.hpp>