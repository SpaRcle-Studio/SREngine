//
// Created by Monika on 26.01.2022.
//

#include <Memory/TextureConfigs.h>
#include <Debug.h>
#include <Xml.h>

using namespace Framework::Graphics::Memory;

bool Framework::Graphics::Memory::TextureConfigs::Reload() {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    Helper::Debug::Info("TextureConfigs::Reload() : reloading configs...");

    const auto path = Helper::ResourceManager::Instance().GetTexturesPath().Concat("Asset.xml");

    if (path.Exists()) {
        auto doc = Helper::Xml::Document::Load(path);
        for (const auto& texture : doc.Root().TryGetNode("Textures").TryGetNodes("Texture")) {
            const auto format      = StringToEnumTextureFormat(texture.TryGetAttribute("Format").ToString("RGBA8_UNORM"));
            const auto type        = StringToEnumTextureType(texture.TryGetAttribute("Type").ToString("Diffuse"));
            const auto autoRemove  = texture.TryGetAttribute("AutoRemove").ToBool(true);
            const auto filter      = StringToEnumTextureFilter(texture.TryGetAttribute("Filter").ToString("LINEAR"));
            const auto compression = StringToEnumTextureCompression(texture.TryGetAttribute("Compression").ToString("None"));
            const auto mipLevels   = static_cast<uint32_t>(texture.TryGetAttribute("MipLevels").ToInt(1));
            const auto alpha       = StringToEnumBoolExt(texture.TryGetAttribute("Alpha").ToString("None"));
            const auto cpuUsage    = texture.TryGetAttribute("CPUUsage").ToBool(false);

            m_configs.insert(std::make_pair(
                    texture.GetAttribute("Path").ToString(),
                    TextureConfig(
                        format,
                        type,
                        autoRemove,
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

    Helper::Debug::Error("TextureConfigs::Reload() : file not found! \n\tPath: " + path.ToString());

    return false;
}

TextureConfig Framework::Graphics::Memory::TextureConfigs::FindOrDefault(const std::string &path) {
    if (auto&& config = Find(path); config.has_value())
        return config.value();

    return TextureConfig();
}

std::optional<TextureConfig> Framework::Graphics::Memory::TextureConfigs::Find(const std::string& path) {
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (!m_loaded)
        Reload();

    if (m_configs.count(path) != 0)
        return m_configs.at(path);
    else
        return std::optional<TextureConfig>();
}