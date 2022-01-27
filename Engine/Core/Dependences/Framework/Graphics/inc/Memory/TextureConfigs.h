//
// Created by Monika on 26.01.2022.
//

#ifndef SRENGINE_TEXTURECONFIGS_H
#define SRENGINE_TEXTURECONFIGS_H

#include <Utils/Singleton.h>
#include <atomic>
#include <optional>
#include <mutex>
#include <unordered_map>
#include <Environment/TextureHelper.h>

namespace Framework::Graphics::Memory {
    struct TextureConfig {
        TextureFormat m_format;
        TextureType m_type;
        bool m_autoRemove;
        TextureFilter m_filter;
        TextureCompression m_compression;
        uint32_t m_mipLevels;
        Helper::BoolExt m_alpha;

        bool operator==(const TextureConfig& lrs) const {
            return m_format == lrs.m_format
                   && m_type == lrs.m_type
                   && m_autoRemove == lrs.m_autoRemove
                   && m_filter == lrs.m_filter
                   && m_compression == lrs.m_compression
                   && m_mipLevels == lrs.m_mipLevels
                   && m_alpha == lrs.m_alpha;
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
