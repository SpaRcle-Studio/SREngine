//
// Created by Monika on 28.11.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_SCATTER_RULES_H
#define SR_ENGINE_WORLD_TERRAIN_SCATTER_RULES_H

#include <Engine/stdInclude.h>

#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/Math/Vector3.h>

namespace SR_CORE_NS {
    /// Точка поверхности террейна, для которой правила решают, ставить ли объект.
    /// Координаты - террейна (см. Terrain::GetTerrainOrigin)
    struct TerrainScatterPoint {
        SR_MATH_NS::FVector3 position;
        /// Нормаль поверхности
        SR_MATH_NS::FVector3 normal;
        /// "Вверх" формы мира в точке: Y для плоского мира, от центра для сферы
        SR_MATH_NS::FVector3 up;
        /// dot(normal, up): 1 - горизонталь, 0 - отвесная стена
        float_t slope = 1.f;
        /// Плоский мир - координата Y, сфера - расстояние до центра
        float_t height = 0.f;
        /// Веса материалов террейна в точке (MATERIAL_WEIGHTS меша)
        std::array<float_t, 4> materialWeights = { };
    };

    /// Детерминированные хеш и шум для размещения: одинаковый результат для любого чанка и LOD
    namespace TerrainScatterNoise {
        SR_NODISCARD SR_FORCE_INLINE uint32_t Hash(uint32_t x) noexcept {
            /// lowbias32
            x ^= x >> 16;
            x *= 0x7feb352dU;
            x ^= x >> 15;
            x *= 0x846ca68bU;
            x ^= x >> 16;
            return x;
        }

        SR_NODISCARD SR_FORCE_INLINE uint32_t Hash(int32_t x, int32_t y, int32_t z, uint32_t seed) noexcept {
            uint32_t h = Hash(static_cast<uint32_t>(x) + seed * 0x9E3779B9U);
            h = Hash(h ^ static_cast<uint32_t>(y) * 0x85EBCA6BU);
            h = Hash(h ^ static_cast<uint32_t>(z) * 0xC2B2AE35U);
            return h;
        }

        /// [0, 1)
        SR_NODISCARD SR_FORCE_INLINE float_t ToFloat(uint32_t h) noexcept {
            return static_cast<float_t>(h >> 8) * (1.f / 16777216.f);
        }

        SR_NODISCARD float_t SmoothStep(float_t edge0, float_t edge1, float_t x) noexcept;
        /// 1 внутри [min, max], плавный спад на fade за границами (fade = 0 - резкая граница)
        SR_NODISCARD float_t Band(float_t x, float_t min, float_t max, float_t fade) noexcept;
        /// Value noise [0, 1] в трёх измерениях (на сфере плоская проекция вытягивает узор)
        SR_NODISCARD float_t ValueNoise(const SR_MATH_NS::FVector3& position, uint32_t seed) noexcept;
        SR_NODISCARD float_t Fbm(const SR_MATH_NS::FVector3& position, uint32_t seed, uint32_t octaves) noexcept;
    }

    /// Правило размещения: множитель вероятности появления объекта в точке.
    /// Слой перемножает результаты всех своих правил. Вызывается из фонового потока -
    /// Evaluate не должен менять состояние правила.
    /// @abstract
    class TerrainScatterRule : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<TerrainScatterRule> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TerrainScatterRule>;

    public:
        TerrainScatterRule();
        ~TerrainScatterRule() override = default;

    public:
        SR_NODISCARD bool IsEnabled() const noexcept { return m_enabled; }
        /// [0, 1]
        SR_NODISCARD virtual float_t Evaluate(const TerrainScatterPoint& point) const { return 1.f; }

    protected:
        /// @property
        bool m_enabled = true;

    };

    /// Наклон поверхности: dot(normal, up) в [min, max]
    class TerrainScatterRuleSlope : public TerrainScatterRule {
        SR_CLASS()
        using Super = TerrainScatterRule;
    public:
        SR_NODISCARD float_t Evaluate(const TerrainScatterPoint& point) const override;

    private:
        /// @property @tooltip(dot(normal, up): 1 - горизонталь, 0 - отвесная стена)
        float_t m_min = 0.85f;
        /// @property
        float_t m_max = 1.f;
        /// @property @tooltip(Ширина плавного перехода на границах)
        float_t m_fade = 0.05f;

    };

    /// Высота: плоский мир - Y, сфера - расстояние до центра (метры, в координатах террейна)
    class TerrainScatterRuleHeight : public TerrainScatterRule {
        SR_CLASS()
        using Super = TerrainScatterRule;
    public:
        SR_NODISCARD float_t Evaluate(const TerrainScatterPoint& point) const override;

    private:
        /// @property
        float_t m_min = 0.f;
        /// @property
        float_t m_max = 100000.f;
        /// @property @tooltip(Ширина плавного перехода на границах в метрах)
        float_t m_fade = 10.f;

    };

    /// Материал террейна: сумма весов разрешённых материалов в точке
    class TerrainScatterRuleMaterial : public TerrainScatterRule {
        SR_CLASS()
        using Super = TerrainScatterRule;
    public:
        SR_NODISCARD float_t Evaluate(const TerrainScatterPoint& point) const override;

    private:
        /// @property @tooltip(Индексы материалов (0..3, как в MATERIAL_WEIGHTS шейдера плотности))
        SR_UTILS_NS::Vector<uint32_t> m_materials = { 0 };
        /// @property @tooltip(Доля разрешённых материалов, начиная с которой вероятность полная)
        float_t m_threshold = 0.6f;
        /// @property @tooltip(Ширина перехода ниже порога)
        float_t m_fade = 0.2f;

    };

    /// Шум: пятна леса, поляны, россыпи. 3D value noise по координатам террейна
    class TerrainScatterRuleNoise : public TerrainScatterRule {
        SR_CLASS()
        using Super = TerrainScatterRule;
    public:
        SR_NODISCARD float_t Evaluate(const TerrainScatterPoint& point) const override;

    private:
        /// @property @tooltip(Частота шума: 1 / размер пятна в метрах)
        float_t m_frequency = 0.004f;
        /// @property @range(1, 6)
        uint32_t m_octaves = 3;
        /// @property @tooltip(Ниже порога объектов нет)
        float_t m_threshold = 0.5f;
        /// @property @tooltip(Ширина перехода выше порога)
        float_t m_fade = 0.1f;
        /// @property @tooltip(Инвертировать маску: объекты там, где у другого слоя с тем же сидом пусто)
        bool m_invert = false;
        /// @property
        int64_t m_seed = 0;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_SCATTER_RULES_H
