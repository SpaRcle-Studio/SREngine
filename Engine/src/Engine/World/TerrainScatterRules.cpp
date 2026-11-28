//
// Created by Monika on 28.11.2026.
//

#include <Engine/World/TerrainScatterRules.h>

#include <Codegen/TerrainScatterRules.generated.hpp>

namespace SR_CORE_NS {
    namespace TerrainScatterNoise {
        float_t SmoothStep(float_t edge0, float_t edge1, float_t x) noexcept {
            if (edge1 <= edge0) {
                return x >= edge1 ? 1.f : 0.f;
            }
            const float_t t = std::clamp((x - edge0) / (edge1 - edge0), 0.f, 1.f);
            return t * t * (3.f - 2.f * t);
        }

        float_t Band(float_t x, float_t min, float_t max, float_t fade) noexcept {
            fade = std::max(0.f, fade);
            const float_t lower = SmoothStep(min - fade, min, x);
            const float_t upper = 1.f - SmoothStep(max, max + fade, x);
            return lower * upper;
        }

        float_t ValueNoise(const SR_MATH_NS::FVector3& position, uint32_t seed) noexcept {
            const float_t fx = std::floor(position.x);
            const float_t fy = std::floor(position.y);
            const float_t fz = std::floor(position.z);

            const auto ix = static_cast<int32_t>(fx);
            const auto iy = static_cast<int32_t>(fy);
            const auto iz = static_cast<int32_t>(fz);

            float_t tx = position.x - fx;
            float_t ty = position.y - fy;
            float_t tz = position.z - fz;
            tx = tx * tx * (3.f - 2.f * tx);
            ty = ty * ty * (3.f - 2.f * ty);
            tz = tz * tz * (3.f - 2.f * tz);

            const auto corner = [&](int32_t x, int32_t y, int32_t z) {
                return ToFloat(Hash(ix + x, iy + y, iz + z, seed));
            };

            const float_t x00 = corner(0, 0, 0) + (corner(1, 0, 0) - corner(0, 0, 0)) * tx;
            const float_t x10 = corner(0, 1, 0) + (corner(1, 1, 0) - corner(0, 1, 0)) * tx;
            const float_t x01 = corner(0, 0, 1) + (corner(1, 0, 1) - corner(0, 0, 1)) * tx;
            const float_t x11 = corner(0, 1, 1) + (corner(1, 1, 1) - corner(0, 1, 1)) * tx;

            const float_t y0 = x00 + (x10 - x00) * ty;
            const float_t y1 = x01 + (x11 - x01) * ty;

            return y0 + (y1 - y0) * tz;
        }

        float_t Fbm(const SR_MATH_NS::FVector3& position, uint32_t seed, uint32_t octaves) noexcept {
            octaves = std::clamp<uint32_t>(octaves, 1, 6);

            SR_MATH_NS::FVector3 point = position;
            float_t sum = 0.f;
            float_t amplitude = 0.5f;
            float_t norm = 0.f;

            for (uint32_t octave = 0; octave < octaves; ++octave) {
                sum += ValueNoise(point, seed + octave * 7919U) * amplitude;
                norm += amplitude;
                point = point * 2.03f;
                amplitude *= 0.5f;
            }

            return sum / norm;
        }
    }

    TerrainScatterRule::TerrainScatterRule()
        : SR_HTYPES_NS::SharedPtr<TerrainScatterRule>(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    float_t TerrainScatterRuleSlope::Evaluate(const TerrainScatterPoint& point) const {
        return TerrainScatterNoise::Band(point.slope, m_min, m_max, m_fade);
    }

    float_t TerrainScatterRuleHeight::Evaluate(const TerrainScatterPoint& point) const {
        return TerrainScatterNoise::Band(point.height, m_min, m_max, m_fade);
    }

    float_t TerrainScatterRuleMaterial::Evaluate(const TerrainScatterPoint& point) const {
        float_t weight = 0.f;
        for (const uint32_t material : m_materials) {
            if (material < point.materialWeights.size()) {
                weight += point.materialWeights[material];
            }
        }
        return TerrainScatterNoise::SmoothStep(m_threshold - std::max(0.f, m_fade), m_threshold, weight);
    }

    float_t TerrainScatterRuleNoise::Evaluate(const TerrainScatterPoint& point) const {
        float_t value = TerrainScatterNoise::Fbm(point.position * m_frequency, static_cast<uint32_t>(m_seed), m_octaves);
        if (m_invert) {
            value = 1.f - value;
        }
        return TerrainScatterNoise::SmoothStep(m_threshold, m_threshold + std::max(0.f, m_fade), value);
    }
}
