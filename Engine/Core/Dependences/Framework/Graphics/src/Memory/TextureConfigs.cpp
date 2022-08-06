//
// Created by Monika on 26.01.2022.
//

#include <Memory/TextureConfigs.h>
#include <Utils/Debug.h>
#include <Utils/Xml.h>

namespace SR_GRAPH_NS::Memory {
    bool TextureConfigs::Reload() {
        SR_SCOPED_LOCK

        SR_INFO("TextureConfigs::Reload() : reloading configs...");

        const auto path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Asset.xml");

        if (path.Exists()) {
            auto doc = Helper::Xml::Document::Load(path);
            for (const auto& texture : doc.Root().TryGetNode("Textures").TryGetNodes("Texture")) {
                const auto format      = StringToEnumColorFormat(texture.TryGetAttribute("Format").ToString("RGBA8_UNORM"));
                const auto filter      = StringToEnumTextureFilter(texture.TryGetAttribute("Filter").ToString("LINEAR"));
                const auto compression = StringToEnumTextureCompression(texture.TryGetAttribute("Compression").ToString("None"));
                const auto mipLevels   = static_cast<uint32_t>(texture.TryGetAttribute("MipLevels").ToInt(1));
                const auto alpha       = SR_UTILS_NS::StringToEnumBoolExt(texture.TryGetAttribute("Alpha").ToString("None"));
                const auto cpuUsage    = texture.TryGetAttribute("CPUUsage").ToBool(false);

                m_configs.insert(std::make_pair(
                        texture.GetAttribute("Path").ToString(),
                        TextureConfig(
                            format,
                            filter,
                            compression,
                            mipLevels,
                            alpha,
                            cpuUsage)
                ));
            }

            m_loaded = true;
            return true;
        }

        SR_ERROR("TextureConfigs::Reload() : file not found! \n\tPath: " + path.ToString());

        return false;
    }

    TextureConfig TextureConfigs::FindOrDefault(const std::string &path) {
        SR_SCOPED_LOCK

        if (auto&& config = Find(path); config.has_value())
            return config.value();

        return TextureConfig();
    }

    std::optional<TextureConfig> TextureConfigs::Find(const std::string& path) {
        SR_SCOPED_LOCK

        if (!m_loaded) {
            Reload();
        }

        if (m_configs.count(path) != 0) {
            return m_configs.at(path);
        }
        else
            return std::optional<TextureConfig>();
    }
}