//
// Created by OpenAI Codex on 22.11.2026.
//

#include <Engine/Export/TextureQuality.h>

#include <Utils/Profile/TracyContext.h>

namespace SR_CORE_NS {
    TextureQualityResult TextureQuality::Measure(const SR_UTILS_NS::Vector<float_t>& reference,
        const SR_UTILS_NS::Vector<float_t>& decoded, uint32_t width, uint32_t height,
        SR_GRAPH_NS::TextureCompressionPolicy policy) {
        SR_TRACY_ZONE;
        TextureQualityResult result;
        if (!width || !height || reference.size() != uint64_t(width) * height * 4 || decoded.size() != reference.size()) {
            return result;
        }
        double_t colorError = 0.0;
        double_t alphaError = 0.0;
        uint64_t visiblePixels = 0;
        uint64_t visibleBlocks = 0;
        uint64_t badBlocks = 0;
        uint64_t badAlphaPixels = 0;
        uint64_t blockHistogram[1024]{};
        uint64_t alphaHistogram[1024]{};
        const bool high = policy == SR_GRAPH_NS::TextureCompressionPolicy::HighQuality;
        const bool aggressive = policy == SR_GRAPH_NS::TextureCompressionPolicy::Aggressive;
        const float_t blockLimit = high ? 0.08f : aggressive ? 0.20f : 0.13f;
        const float_t alphaLimit = high ? 0.08f : aggressive ? 0.20f : 0.12f;
        for (uint32_t blockY = 0; blockY < height; blockY += 4) {
            for (uint32_t blockX = 0; blockX < width; blockX += 4) {
                double_t blockError = 0.0;
                uint32_t blockPixels = 0;
                for (uint32_t y = blockY; y < std::min(blockY + 4, height); ++y) {
                    for (uint32_t x = blockX; x < std::min(blockX + 4, width); ++x) {
                        const uint64_t offset = (uint64_t(y) * width + x) * 4;
                        for (uint32_t channel = 0; channel < 4; ++channel) {
                            if (!std::isfinite(reference[offset + channel]) || !std::isfinite(decoded[offset + channel])) {
                                return TextureQualityResult();
                            }
                        }
                        const float_t sourceAlpha = std::round(std::clamp(reference[offset + 3], 0.f, 1.f) * 255.f) / 255.f;
                        const float_t decodedAlpha = std::clamp(decoded[offset + 3], 0.f, 1.f);
                        const float_t alphaDifference = std::abs(sourceAlpha - decodedAlpha);
                        result.maxAlphaError = std::max(result.maxAlphaError, alphaDifference);
                        // Empty canvas must not dilute errors in a small visible sprite.
                        if (std::max(sourceAlpha, decodedAlpha) <= 1.f / 255.f) {
                            continue;
                        }
                        ++alphaHistogram[std::min(1023u, static_cast<uint32_t>(std::ceil(alphaDifference * 1023.f)))];
                        badAlphaPixels += alphaDifference > alphaLimit;
                        double_t pixelError = 0.0;
                        for (uint32_t channel = 0; channel < 3; ++channel) {
                            const float_t source = std::round(std::clamp(reference[offset + channel], 0.f, 1.f) * 255.f) / 255.f;
                            const float_t reconstructed = std::clamp(decoded[offset + channel], 0.f, 1.f);
                            // Composite over black and white to include transparent edge artifacts.
                            const double_t blackDifference = source * sourceAlpha - reconstructed * decodedAlpha;
                            const double_t whiteDifference = blackDifference - sourceAlpha + decodedAlpha;
                            pixelError += (blackDifference * blackDifference + whiteDifference * whiteDifference) / 6.0;
                        }
                        blockError += pixelError;
                        alphaError += alphaDifference * alphaDifference;
                        ++blockPixels;
                    }
                }
                colorError += blockError;
                visiblePixels += blockPixels;
                if (blockPixels) {
                    const float_t rmse = static_cast<float_t>(std::sqrt(blockError / blockPixels));
                    result.worstBlockRmse = std::max(result.worstBlockRmse, rmse);
                    ++blockHistogram[std::min(1023u, static_cast<uint32_t>(std::ceil(rmse * 1023.f)))];
                    ++visibleBlocks;
                    badBlocks += rmse > blockLimit;
                }
            }
        }
        const double_t count = static_cast<double_t>(std::max(uint64_t(1), visiblePixels));
        result.colorPsnr = static_cast<float_t>(-10.0 * std::log10(std::max(1e-12, colorError / count)));
        result.alphaPsnr = static_cast<float_t>(-10.0 * std::log10(std::max(1e-12, alphaError / count)));
        uint64_t blocksSeen = 0;
        uint64_t pixelsSeen = 0;
        const uint64_t blockRank = visibleBlocks - visibleBlocks / 1000;
        const uint64_t pixelRank = visiblePixels - visiblePixels / 1000;
        for (uint32_t bin = 0; bin < 1024; ++bin) {
            if (blocksSeen < blockRank) {
                blocksSeen += blockHistogram[bin];
                result.blockRmseP999 = bin / 1023.f;
            }
            if (pixelsSeen < pixelRank) {
                pixelsSeen += alphaHistogram[bin];
                result.alphaErrorP999 = bin / 1023.f;
            }
        }
        result.badBlockFraction = static_cast<float_t>(badBlocks) / static_cast<float_t>(std::max(uint64_t(1), visibleBlocks));
        result.badAlphaFraction = static_cast<float_t>(badAlphaPixels) / static_cast<float_t>(count);
        result.accepted = result.colorPsnr >= (high ? 40.f : aggressive ? 32.f : 36.f)
            && result.alphaPsnr >= (high ? 44.f : aggressive ? 36.f : 40.f)
            && result.blockRmseP999 <= blockLimit && result.alphaErrorP999 <= alphaLimit;
        return result;
    }
}
