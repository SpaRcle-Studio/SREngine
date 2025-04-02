

# File TextureConfigs.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Memory**](dir_cc5176abae198c1d3b7945975349bd99.md) **>** [**TextureConfigs.h**](TextureConfigs_8h.md)

[Go to the documentation of this file](TextureConfigs_8h.md)


```C++
//
// Created by Monika on 26.01.2022.
//

#ifndef SR_ENGINE_TEXTURE_CONFIGS_H
#define SR_ENGINE_TEXTURE_CONFIGS_H

#include <Utils/Common/Singleton.h>

#include <Graphics/Pipeline/TextureHelper.h>

namespace SR_GRAPH_NS::Memory {
    struct TextureConfig {
        TextureConfig(
            ImageFormat format,
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
            : m_format(ImageFormat::RGBA8_UNORM)
            , m_filter(TextureFilter::LINEAR)
            , m_compression(TextureCompression::None)
            , m_mipLevels(1)
            , m_alpha(SR_UTILS_NS::BoolExt::None)
            , m_cpuUsage(false)
        { }

        ImageFormat m_format;
        TextureFilter m_filter;
        TextureCompression m_compression;
        uint32_t m_mipLevels;
        SR_UTILS_NS::BoolExt m_alpha;
        bool m_cpuUsage;

        SR_NODISCARD ImageFormat GetFormat() const noexcept { return m_format; }
        SR_NODISCARD TextureFilter GetFilter() const noexcept { return m_filter; }
        SR_NODISCARD TextureCompression GetCompression() const noexcept { return m_compression; }
        SR_NODISCARD uint32_t GetMipLevels() const noexcept { return m_mipLevels; }
        SR_NODISCARD SR_UTILS_NS::BoolExt GetAlpha() const noexcept { return m_alpha; }
        SR_NODISCARD bool GetCpuUsage() const noexcept { return m_cpuUsage; }

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

#endif //SR_ENGINE_TEXTURE_CONFIGS_H
```


