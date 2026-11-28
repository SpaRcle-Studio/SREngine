//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_SCATTER_RENDERER_H
#define SR_ENGINE_WORLD_TERRAIN_SCATTER_RENDERER_H

#include <Engine/stdInclude.h>

#include <Graphics/Types/IRenderComponent.h>

#include <Utils/Types/IRawMeshHolder.h>
#include <Utils/Math/Vector4.h>

namespace SR_CORE_NS {
    /// Инстанс меша: строки аффинной матрицы 3x4 (поворот * масштаб в xyz, перенос в w).
    /// Перенос - относительно объекта рендерера. Раскладка совпадает с CUSTOM0..2 в standard-vertex.srsl
    struct TerrainScatterInstanceGPU {
        SR_MATH_NS::FVector4 row0;
        SR_MATH_NS::FVector4 row1;
        SR_MATH_NS::FVector4 row2;

        SR_NODISCARD SR_MATH_NS::FVector3 GetPosition() const noexcept { return SR_MATH_NS::FVector3(row0.w, row1.w, row2.w); }
    };

    static_assert(sizeof(TerrainScatterInstanceGPU) == 48, "TerrainScatterInstanceGPU must be 48 bytes!");

    /// Рисует одну часть меша (meshId файла модели) всеми инстансами за один draw call.
    /// Материал должен использовать шейдер с SR_STANDARD_VERTEX_INSTANCED (например Engine/Shaders/standard-instanced.srsl).
    /// Опционально упрощает геометрию (meshoptimizer) - так из одной модели получаются дальние LOD.
    /// Создаётся системой TerrainScatter на служебных объектах, в сцену не сохраняется.
    /// @noCopyable @category(Render)
    class TerrainScatterRenderer : public SR_GTYPES_NS::IRenderComponent, public SR_HTYPES_NS::IRawMeshHolder {
        SR_CLASS()
        using Super = SR_GTYPES_NS::IRenderComponent;
    public:
        /// Поток сцены. simplifyRatio - доля оставляемых индексов (1 - исходный меш)
        void SetGeometry(const SR_UTILS_NS::Path& meshPath, int32_t meshId, float_t simplifyRatio);
        /// Поток сцены. Данные будут залиты на GPU при ближайшей отрисовке
        void SetInstances(const SR_UTILS_NS::Vector<TerrainScatterInstanceGPU>& instances);
        void ClearInstances();

        SR_NODISCARD uint32_t GetInstancesCount() const noexcept { return m_instancesCount; }
        /// Досвобождает заменённые буферы инстансов
        void FreeRetired();

        void OnRawMeshChanged() override;

        void FreeVideoMemory() override;
        bool Bind() override;
        void Draw() override;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD bool IsSupportShadows() const override { return true; }

        void UseMaterial(SR_GTYPES_NS::Shader& shader) override;
        void UseModelMatrix(SR_GTYPES_NS::Shader& shader) override;

        SR_NODISCARD std::optional<int32_t> GetIBO() const override;
        SR_NODISCARD int32_t GetVirtualUBO() const override { return m_virtualUBO; }
        /// Отсечение делает TerrainScatter по чанкам, AABB объекта для набора инстансов не подходит
        SR_NODISCARD SR_GRAPH_NS::FrustumCullingType GetFrustumCullingType() const noexcept override { return SR_GRAPH_NS::FrustumCullingType::None; }

        SR_NODISCARD SR_UTILS_NS::VertexLayoutDescriptionsRef GetShaderVertexLayoutDescriptions() const noexcept override;

    private:
        /// Только поток рендера, под m_mutex
        void Calculate();
        void CalculateGeometry(SR_GRAPH_NS::Pipeline* pPipeline);
        void CalculateInstances(SR_GRAPH_NS::Pipeline* pPipeline);
        void FreeRetiredVBOs(SR_GRAPH_NS::Pipeline* pPipeline);
        void MarkRenderDirty();

    private:
        /// @property @group(Stats) @readOnly @dontSave @tooltip(Сколько экземпляров сейчас отдано рендереру (видимые этого LOD))
        uint32_t m_statInstances = 0;

        mutable std::mutex m_mutex;

        /// Копия залитых (или ожидающих заливки) инстансов: для сравнения с новым набором и перезаливки после FreeVideoMemory
        SR_UTILS_NS::Vector<TerrainScatterInstanceGPU> m_instances;
        std::atomic<uint32_t> m_instancesCount = 0;
        uint32_t m_uploadedCount = 0;
        bool m_isInstancesDirty = false;

        float_t m_simplifyRatio = 1.f;
        bool m_isGeometryDirty = true;
        uint32_t m_indicesCount = 0;

        /// Буфер инстансов нельзя удалить сразу: на него ссылаются закешированные командные буферы других кадров
        struct RetiredVBO {
            int32_t VBO = SR_ID_INVALID;
            std::bitset<SR_MAX_FRAMES_IN_FLIGHT> rebuiltFrames;
        };
        SR_UTILS_NS::Vector<RetiredVBO> m_retiredVBOs;

        int32_t m_instancesVBO = SR_ID_INVALID;
        int32_t m_geometryVBO = SR_ID_INVALID;
        int32_t m_geometryIBO = SR_ID_INVALID;
        int32_t m_virtualUBO = SR_ID_INVALID;
        int32_t m_virtualDescriptor = SR_ID_INVALID;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_SCATTER_RENDERER_H
