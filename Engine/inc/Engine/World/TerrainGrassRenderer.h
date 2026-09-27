//
// Created by Monika on 27.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_GRASS_RENDERER_H
#define SR_ENGINE_WORLD_TERRAIN_GRASS_RENDERER_H

#include <Engine/stdInclude.h>

#include <Graphics/Types/IRenderComponent.h>
#include <Graphics/Utils/Frustum.h>

#include <Utils/Math/Vector3.h>
#include <Utils/Math/AABB.h>

namespace SR_CORE_NS {
    /// Один инстанс травинки. Вся остальная вариативность (поворот, высота, ширина, изгиб, цвет, тип, клампы)
    /// выводится в вершинном шейдере из random, поэтому инстанс занимает всего 32 байта.
    struct TerrainGrassInstance {
        SR_MATH_NS::FVector3 position; /// корень травинки в мировых осях относительно позиции объекта чанка
        float_t rank = 0.f;            /// [0, 1), внутри ячейки инстансы отсортированы по нему (LOD плотности)
        SR_MATH_NS::FVector3 normal;   /// нормаль поверхности террейна в корне (мировая)
        float_t random = 0.f;          /// [0, 1), сид вариативности травинки
    };

    static_assert(sizeof(TerrainGrassInstance) == 32, "TerrainGrassInstance must be 32 bytes!");

    /// Количество корзин по rank. Позволяет рисовать префикс ячейки, отбрасывая "лишние" травинки вдали.
    static constexpr uint32_t SR_TERRAIN_GRASS_RANK_BUCKETS = 32;
    /// Шаг квантования LOD-уровня (в корзинах). Чем больше, тем реже пересобираются командные буферы.
    static constexpr uint32_t SR_TERRAIN_GRASS_LOD_STEP = 4;

    /// Ячейка травы (колонка в плоскости XZ). Инстансы ячейки лежат в буфере непрерывно
    /// и отсортированы по корзинам rank, поэтому любой LOD ячейки - это один непрерывный диапазон.
    struct TerrainGrassCell {
        SR_MATH_NS::AABB bounds; /// мировые границы (для выбора LOD и отсечения)
        uint32_t start = 0;      /// первый инстанс ячейки в буфере
        /// cumulative[i] - число инстансов ячейки с rank < (i + 1) / SR_TERRAIN_GRASS_RANK_BUCKETS
        std::array<uint32_t, SR_TERRAIN_GRASS_RANK_BUCKETS> cumulative = { };
    };

    /// Параметры дистанционного LOD. Одни и те же значения используются на CPU (сколько инстансов рисовать)
    /// и в шейдере (плавное исчезновение отдельных травинок), поэтому задаются в одном месте - в TerrainGrass.
    struct TerrainGrassLodParams {
        float_t fullDensityDistance = 12.f; /// до этой дистанции рисуется 100% травинок
        float_t maxDistance = 80.f;         /// после неё травы нет
        float_t falloff = 1.6f;             /// степень кривой убывания плотности
        float_t minKeep = 0.04f;            /// минимальная доля травинок перед полным исчезновением
        float_t segmentsLodDistance = 25.f; /// после этой дистанции травинка строится из lowSegments сегментов
        uint32_t segments = 5;              /// сегментов у ближней травинки (1..7)
        uint32_t lowSegments = 2;           /// сегментов у дальней травинки (1..segments)

        SR_NODISCARD float_t GetKeepFraction(float_t distance) const noexcept;
        SR_NODISCARD bool operator==(const TerrainGrassLodParams& other) const noexcept = default;
    };

    /// Рендерер травы одного чанка террейна. Добавляется на объект чанка системой TerrainGrass автоматически.
    /// Геометрии нет вообще: травинка строится в шейдере по VERTEX_INDEX (triangle strip), а инстанс-буфер
    /// статичен и перезаливается только при перегенерации травы чанка. Командные буферы пересобираются
    /// только когда меняется LOD-уровень или видимость какой-либо ячейки.
    /// @noCopyable @category(Render)
    class TerrainGrassRenderer : public SR_GTYPES_NS::IRenderComponent {
        SR_CLASS()
        using Super = SR_GTYPES_NS::IRenderComponent;
    public:
        /// Поток сцены. Данные будут залиты на GPU при ближайшей сборке командного буфера.
        void SetInstances(std::vector<TerrainGrassInstance>&& instances, std::vector<TerrainGrassCell>&& cells);
        void ClearInstances();

        /// Поток сцены. Пересчитывает LOD и видимость ячеек. Возвращает true, если набор отрисовки изменился.
        bool UpdateLod(const SR_MATH_NS::FVector3& observer, const TerrainGrassLodParams& params, const SR_GRAPH_NS::Frustum* pFrustum);

        void SetCastShadows(bool castShadows) { m_castShadows = castShadows; }

        SR_NODISCARD uint32_t GetInstancesCount() const noexcept { return m_instancesCount; }
        SR_NODISCARD uint32_t GetDrawnInstancesCount() const noexcept { return m_drawnCount; }
        SR_NODISCARD bool HasInstances() const noexcept { return m_instancesCount > 0; }

        void FreeVideoMemory() override;
        bool Bind() override;
        void Draw() override;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        void UseMaterial(SR_GTYPES_NS::Shader& shader) override;
        void UseModelMatrix(SR_GTYPES_NS::Shader& shader) override;

        SR_NODISCARD int32_t GetVirtualUBO() const override { return m_virtualUBO; }
        /// Отсечение выполняется самим рендерером по ячейкам (см. UpdateLod), AABB объекта чанка для травы не подходит.
        SR_NODISCARD SR_GRAPH_NS::FrustumCullingType GetFrustumCullingType() const noexcept override { return SR_GRAPH_NS::FrustumCullingType::None; }

        SR_NODISCARD SR_UTILS_NS::VertexLayoutDescriptionsRef GetShaderVertexLayoutDescriptions() const noexcept override;

    private:
        struct DrawRange {
            uint32_t start = 0;
            uint32_t count = 0;
            uint32_t vertexCount = 0;
        };

        /// Заливка отложенных данных на GPU. Только поток рендера, под m_mutex.
        void Calculate();
        /// Под m_mutex.
        void RebuildRanges();
        void MarkRenderDirty();

    private:
        mutable std::mutex m_mutex;

        std::vector<TerrainGrassInstance> m_pendingInstances;
        std::vector<TerrainGrassCell> m_cells;
        /// Упакованный уровень ячейки: биты 0..5 - число корзин rank, бит 7 - полная детализация травинки.
        std::vector<uint8_t> m_cellLevels;
        std::vector<DrawRange> m_ranges;
        TerrainGrassLodParams m_lodParams;
        bool m_isDataDirty = false;

        std::atomic<bool> m_castShadows = false;
        std::atomic<uint32_t> m_instancesCount = 0;
        std::atomic<uint32_t> m_drawnCount = 0;

        uint32_t m_uploadedCount = 0;

        int32_t m_VBO = SR_ID_INVALID;
        int32_t m_virtualUBO = SR_ID_INVALID;
        int32_t m_virtualDescriptor = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_GRASS_RENDERER_H
