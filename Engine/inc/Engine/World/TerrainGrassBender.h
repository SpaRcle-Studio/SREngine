//
// Created by Monika on 28.09.2026.
//

#ifndef SR_ENGINE_WORLD_TERRAIN_GRASS_BENDER_H
#define SR_ENGINE_WORLD_TERRAIN_GRASS_BENDER_H

#include <Engine/stdInclude.h>

#include <Utils/ECS/Component.h>

namespace SR_CORE_NS {
    /// Объект, приминающий траву террейна (игрок, NPC, машина, камень). Трава расходится от него в стороны
    /// и после ухода объекта постепенно распрямляется (след).
    /// @category(World)
    class TerrainGrassBender : public SR_UTILS_NS::Component {
        using Super = SR_UTILS_NS::Component;
        SR_CLASS()
    public:
        void OnEnable() override;
        void OnDisable() override;
        void OnDestroy() override;

        SR_NODISCARD SR_MATH_NS::FVector3 GetBendPosition() const;
        SR_NODISCARD float_t GetRadius() const noexcept { return m_radius; }
        SR_NODISCARD float_t GetStrength() const noexcept { return m_strength; }
        SR_NODISCARD bool IsTrailEnabled() const noexcept { return m_trail; }
        SR_NODISCARD float_t GetTrailDuration() const noexcept { return m_trailDuration; }
        SR_NODISCARD float_t GetTrailLength() const noexcept { return m_trailLength; }

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }

        /// Только поток сцены.
        SR_NODISCARD static const SR_UTILS_NS::Vector<TerrainGrassBender*>& GetActiveBenders() noexcept;

    private:
        /// @property @tooltip(Радиус приминания в метрах)
        float_t m_radius = 0.5f;
        /// @property @range(0, 1)
        float_t m_strength = 1.f;
        /// @property @tooltip(Смещение точки приминания относительно объекта, например к ногам персонажа)
        SR_MATH_NS::FVector3 m_offset;
        /// @property @tooltip(Оставлять за собой след примятой травы)
        bool m_trail = true;
        /// @property @tooltip(За сколько секунд трава распрямляется после ухода объекта)
        float_t m_trailDuration = 12.f;
        /// @property @tooltip(Максимальная длина следа в метрах. Более старая часть следа исчезает сразу)
        float_t m_trailLength = 25.f;

    };
}

#endif //SR_ENGINE_WORLD_TERRAIN_GRASS_BENDER_H
