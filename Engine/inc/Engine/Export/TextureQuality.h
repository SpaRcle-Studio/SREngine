//
// Created by OpenAI Codex on 22.11.2026.
//

#ifndef SR_ENGINE_EXPORT_TEXTURE_QUALITY_H
#define SR_ENGINE_EXPORT_TEXTURE_QUALITY_H

#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_CORE_NS {
    struct TextureQualityResult {
        bool accepted = false;
        float_t colorPsnr = 0.f;
        float_t alphaPsnr = 0.f;
        float_t worstBlockRmse = 0.f;
        float_t maxAlphaError = 0.f;
        float_t blockRmseP999 = 0.f;
        float_t alphaErrorP999 = 0.f;
        float_t badBlockFraction = 0.f;
        float_t badAlphaFraction = 0.f;
    };

    class TextureQuality {
    public:
        static TextureQualityResult Measure(const SR_UTILS_NS::Vector<float_t>& reference,
            const SR_UTILS_NS::Vector<float_t>& decoded, uint32_t width, uint32_t height,
            SR_GRAPH_NS::TextureCompressionPolicy policy);
    };
}

#endif //SR_ENGINE_EXPORT_TEXTURE_QUALITY_H
