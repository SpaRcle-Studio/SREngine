//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_TEXTURECONFIGS_H
#define SRENGINE_TEXTURECONFIGS_H

#include <Utils/Common/Singleton.h>
#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GRAPH_NS::Memory {
    struct TextureConfig {
        TextureConfig(
            ColorFormat format,
            TextureFilter filter,
            TextureCompression compression,
            uint32_t mipLevels,
            SR_UTILS_NS::BoolExt alpha,
            bool cpuUsage
        )
            : m_format(format)
            , m_filter(filter)
            , m_compression(compression)
            , m_mipLevels(mipLevels)
            , m_alpha(alpha)
            , m_cpuUsage(cpuUsage)
        { }

        TextureConfig()
            : m_format(ColorFormat::RGBA8_UNORM)
            , m_filter(TextureFilter::LINEAR)
            , m_compression(TextureCompression::None)
            , m_mipLevels(1)
            , m_alpha(SR_UTILS_NS::BoolExt::None)
            , m_cpuUsage(false)
        { }

        ColorFormat m_format;
        TextureFilter m_filter;
        TextureCompression m_compression;
        uint32_t m_mipLevels;
        SR_UTILS_NS::BoolExt m_alpha;
        bool m_cpuUsage;

        bool operator==(const TextureConfig& lrs) const {
            return m_format == lrs.m_format
                   && m_filter == lrs.m_filter
                   && m_compression == lrs.m_compression
                   && m_mipLevels == lrs.m_mipLevels
                   && (m_alpha == lrs.m_alpha || m_alpha == SR_UTILS_NS::BoolExt::None || lrs.m_alpha == SR_UTILS_NS::BoolExt::None)
                   && m_cpuUsage == lrs.m_cpuUsage;
        }

        bool operator!=(const TextureConfig& lrs) const {
            return !(*this == lrs);
        }
    };

    class TextureConfigs : public SR_UTILS_NS::Singleton<TextureConfigs> {
        friend class SR_UTILS_NS::Singleton<TextureConfigs>;
    private:
        ~TextureConfigs() override = default;

    public:
        bool Reload();
        std::optional<TextureConfig> Find(const std::string& path);
        TextureConfig FindOrDefault(const std::string& path);

    private:
        std::atomic<bool> m_loaded = false;
        std::unordered_map<std::string, TextureConfig> m_configs;

    };
}

#endif //SRENGINE_TEXTURECONFIGS_H
