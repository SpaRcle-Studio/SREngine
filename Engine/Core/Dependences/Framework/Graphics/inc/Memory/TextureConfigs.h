//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_TEXTURECONFIGS_H
#define SRENGINE_TEXTURECONFIGS_H

#include <Utils/Singleton.h>
#include <Environment/TextureHelper.h>

namespace Framework::Graphics::Memory {
    struct TextureConfig {
        TextureConfig(TextureFormat format,
                TextureType type,
                bool autoRemove,
                TextureFilter filter,
                TextureCompression compression,
                uint32_t mipLevels,
                Helper::BoolExt alpha,
                bool cpuUsage)
            : m_format(format)
            , m_type(type)
            , m_autoRemove(autoRemove)
            , m_filter(filter)
            , m_compression(compression)
            , m_mipLevels(mipLevels)
            , m_alpha(alpha)
            , m_cpuUsage(cpuUsage)
        { }

        TextureConfig()
            : m_format(TextureFormat::RGBA8_UNORM)
            , m_type(TextureType::Diffuse)
            , m_autoRemove(true)
            , m_filter(TextureFilter::LINEAR)
            , m_compression(TextureCompression::None)
            , m_mipLevels(1)
            , m_alpha(Helper::BoolExt::None)
            , m_cpuUsage(false)
        { }

        TextureFormat m_format;
        TextureType m_type;
        bool m_autoRemove;
        TextureFilter m_filter;
        TextureCompression m_compression;
        uint32_t m_mipLevels;
        Helper::BoolExt m_alpha;
        bool m_cpuUsage;

        bool operator==(const TextureConfig& lrs) const {
            return m_format == lrs.m_format
                   && m_type == lrs.m_type
                   && m_autoRemove == lrs.m_autoRemove
                   && m_filter == lrs.m_filter
                   && m_compression == lrs.m_compression
                   && m_mipLevels == lrs.m_mipLevels
                   && (m_alpha == lrs.m_alpha || m_alpha == Helper::BoolExt::None || lrs.m_alpha == Helper::BoolExt::None)
                   && m_cpuUsage == lrs.m_cpuUsage;
        }
    };

    class TextureConfigs : public Helper::Singleton<TextureConfigs> {
        friend class Helper::Singleton<TextureConfigs>;
    private:
        ~TextureConfigs() override = default;

    public:
        bool Reload();
        std::optional<TextureConfig> Find(const std::string& path);
        TextureConfig FindOrDefault(const std::string& path);

    private:
        std::recursive_mutex m_mutex;
        std::atomic<bool> m_loaded = false;
        std::unordered_map<std::string, TextureConfig> m_configs;

    };
}

#endif //SRENGINE_TEXTURECONFIGS_H
