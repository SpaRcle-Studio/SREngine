//
// Created by Monika on 18.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H
#define SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H

#include <Engine/World/Terrain.h>
#include <Engine/World/TerrainChunkCube.h>

#include <Graphics/Memory/SSBO.h>
#include <Graphics/Types/ComputeShader.h>

#include <Utils/FileSystem/PathDataAccessor.h>
#include <Utils/Common/Vertices.h>
#include <Utils/Math/Vector4.h>

namespace SR_CORE_NS {
    struct TerrainMarchingCubesVertex {
        SR_MATH_NS::FVector3 pos;
        float pad0;
        SR_MATH_NS::FVector4 weights; /// веса материалов (почва, камень, песок, -)
    };

    struct TerrainMarchingCubesVoxel {
        float density;
        float weights[3]; /// веса материалов (почва, камень, песок)
    };

    /// Пользовательский параметр шейдера плотности: передаётся как [[const], [uniform]] vec4 с этим именем
    struct TerrainDensityParameter : public SR_UTILS_NS::Serializable {
        SR_STRUCT()
    public:
        /// @property
        SR_UTILS_NS::StringAtom name;
        /// @property
        SR_MATH_NS::FVector4 value;

        bool operator==(const TerrainDensityParameter& other) const noexcept {
            return name == other.name && value == other.value;
        }

        bool operator!=(const TerrainDensityParameter& other) const noexcept {
            return !(*this == other);
        }
    };

    class TerrainMarchingCubesChunkData : public ITerrainChunkData {
        using Super = ITerrainChunkData;
        SR_CLASS()

    public:
        void Deactivate() override;
        void SwitchPhysics(bool enable) override;
        SR_NODISCARD bool IsPhysicsEnabled() const override { return m_isPhysicsEnabled; }
        SR_NODISCARD bool IsRenderReady() const override;

        /// Коллизия строится лениво из меша ProceduralMesh при первом включении физики
        void SetCollisionSettings(bool allowed, const SR_MATH_NS::FVector3& scale, float_t simplifyRatio, float_t simplifyError, uint64_t indicesCount);

    private:
        bool BuildCollision();

    private:
        SR_MATH_NS::FVector3 m_collisionScale = SR_MATH_NS::FVector3(1.f);
        float_t m_simplifyRatio = 0.25f;
        float_t m_simplifyError = 1e-2f;
        uint64_t m_collisionIndicesCount = 0; /// индексы меша без юбок
        bool m_isCollisionAllowed = false;
        bool m_isCollisionBuilt = false;
        bool m_isPhysicsEnabled = false;

    };

    /// @noCopyable
    class TerrainChunkDataMarchingCubesGenerator : public ITerrainChunkDataGenerator {
        using Super = ITerrainChunkDataGenerator;
        SR_CLASS()
    public:
        ~TerrainChunkDataMarchingCubesGenerator() override;

    public:
        void GenerateChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer, float_t distance) override;

        SR_NODISCARD bool CanBeginChunkData() const override;
        bool BeginChunkData(Terrain& terrain, ITerrainChunk& chunk, const TerrainObserverData& observer) override;
        void UpdateChunkData(Terrain& terrain, const SR_HTYPES_NS::Function<void(ITerrainChunk&)>& onLoaded) override;
        void CancelChunkData(ITerrainChunk& chunk) override;
        void Shutdown() override;

    private:
        /// Ресурсы одной генерации. Пока задача на GPU, её буферы и дескрипторы трогать нельзя, поэтому у каждой
        /// задачи свои SSBO и свои экземпляры compute шейдеров (у экземпляра свой набор дескрипторов).
        /// У этапов marching cubes тоже разные экземпляры: дескрипторы, привязанные в записываемом буфере, не перезаписываются
        struct GenerationSlot {
            SR_GTYPES_NS::ComputeShader::Ptr pDensityShader = nullptr;
            /// Этапы MarchingCubes.srsl: 0 - вершины, 1 - индексы, 2 - очистка таблицы рёбер
            std::array<SR_GTYPES_NS::ComputeShader::Ptr, 3> marchingShaders;

            SR_GRAPH_NS::SSBOInstance::Ptr pDensitySSBO = nullptr;
            SR_GRAPH_NS::SSBOInstance::Ptr pDensityOffsetsSSBO = nullptr;
            SR_GRAPH_NS::SSBOInstance::Ptr pHashTableSSBO = nullptr;
            SR_GRAPH_NS::SSBOInstance::Ptr pVerticesSSBO = nullptr;
            SR_GRAPH_NS::SSBOInstance::Ptr pIndicesSSBO = nullptr;

            /// Чанк, для которого идёт генерация. nullptr - генерация отменена, результат выбрасывается
            ITerrainChunk::Ptr pChunk;
            /// Задача Pipeline::BeginAsyncCompute, SR_ID_INVALID - вычисления прошли синхронно
            int32_t computeTask = SR_ID_INVALID;
            bool isBusy = false;
            bool isFailed = false;
        };

        bool Init();
        SR_NODISCARD bool CreateSlotResources(GenerationSlot& slot);
        SR_NODISCARD GenerationSlot* FindFreeSlot() const;
        SR_NODISCARD bool HasBusySlots() const;
        /// Настройки, от которых зависят размеры буферов и число слотов, изменились после создания слотов
        SR_NODISCARD bool IsSlotsOutdated() const;
        SR_NODISCARD uint64_t GetMaxVertexCount() const;
        SR_NODISCARD uint64_t GetMaxIndicesCount() const;

        /// Подготовка данных чанка и запись вычислений. true - вычисления асинхронные и ещё идут
        bool DispatchSlot(Terrain& terrain, TerrainChunkCube& chunk, GenerationSlot& slot);
        /// Чтение результата с GPU и построение меша, травы, коллизии. Слот освобождается
        void FinishSlot(Terrain& terrain, GenerationSlot& slot);
        void ReleaseSlot(GenerationSlot& slot);
        void BuildChunk(Terrain& terrain, TerrainChunkCube& chunk, GenerationSlot& slot);

    private:
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_marchingCubesShader = "Engine/Shaders/MarchingCubes/MarchingCubes.srsl";
        /// @property
        /// @customArgs(pick: enabled, filter name: Shader, relative: resources)
        /// @customArg(filter value: srsl)
        SR_UTILS_NS::Path m_densityShader = "Engine/Shaders/MarchingCubes/Density.srsl";

        /// @property @group(Density)
        uint32_t m_densityCountAxis = 32;
        /// @property @group(Density)
        float_t m_noiseScale = 13.0f;
        /// @property @group(Density)
        int64_t m_seed = 0;
        /// @property @group(Density)
        float_t m_isoLevel = 1.f;
        /// @property @group(Density) @tooltip(Параметры шейдера плотности. Каждый передаётся как vec4 uniform с указанным именем. Кроме них шейдер всегда получает voxelSize (vec3, метры) и terrainUp (vec4: xyz - центр сферы, w - 1 для сферы, 0 для плоского мира))
        SR_UTILS_NS::Vector<TerrainDensityParameter> m_densityParameters;

        /// @property @group(SSBO) @tooltip(Размер таблицы рёбер. Меньше числа рёбер сетки (3 * densityCountAxis^3) не бывает)
        uint32_t m_vertexHashTableSize = 800000;
        /// @property @group(SSBO) @range(1, 32) @tooltip(Сколько чанков может генерироваться на GPU одновременно. Каждая задача держит свой набор буферов. Без поддержки асинхронных вычислений API генерация синхронная)
        uint32_t m_maxGenerationsInFlight = 16;
        /// @property @group(SSBO) @range(0.f, 100.f) @tooltip(Бюджет времени на сборку готовых чанков за кадр (чтение с GPU, нормали, юбки, трава), мс. Хотя бы один чанк собирается всегда. 0 - без ограничения)
        float_t m_finishBudgetMs = 4.f;

        /// @property
        SR_MATH_NS::FVector3 m_geometryScale = SR_MATH_NS::FVector3(1.f);
        /// @property @group(Physics) @range(0.01f, 1.f) @tooltip(Доля треугольников, остающаяся в меше коллизии)
        float_t m_collisionSimplifyRatio = 0.25f;
        /// @property @group(Physics) @range(0.f, 1.f)
        float_t m_collisionSimplifyError = 1e-2f;
        /// @property @range(0.f, 16.f) @tooltip(Глубина юбок на стыках чанков в вокселях чанка. Закрывает щели между LOD)
        float_t m_skirtDepth = 1.5f;

    private:
        bool m_isInitialized = false;

        /// Настройки, с которыми созданы слоты. Поменялись в инспекторе - слоты пересоздаются, когда все задачи завершатся
        /// (иначе диспатч по новой сетке пишет за границы старых буферов и портит соседние)
        uint32_t m_slotsDensityCountAxis = 0;
        uint32_t m_slotsHashTableSize = 0;
        uint32_t m_slotsCount = 0;
        SR_UTILS_NS::Path m_slotsMarchingCubesShader;
        SR_UTILS_NS::Path m_slotsDensityShader;

        SR_UTILS_NS::VertexDataBuffer m_vertices;
        SR_HTYPES_NS::FastMemoryArray<uint32_t> m_indices;
        SR_HTYPES_NS::FastMemoryArray<float_t> m_densityOffsets;

        SR_UTILS_NS::Vector<SR_UTILS_NS::RawPointerHolder<GenerationSlot>> m_slots;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_CHUNK_DATA_MARCHING_CUBES_GENERATOR_H
