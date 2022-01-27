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
            auto format      = StringToEnumTextureFormat(texture.TryGetAttribute("Format").ToString("RGBA8_UNORM"));
            auto type        = StringToEnumTextureType(texture.TryGetAttribute("Type").ToString("Diffuse"));
            auto autoRemove  = texture.TryGetAttribute("AutoRemove").ToBool(true);
            auto filter      = StringToEnumTextureFilter(texture.TryGetAttribute("Filter").ToString("LINEAR"));
            auto compression = StringToEnumTextureCompression(texture.TryGetAttribute("Compression").ToString("None"));
            auto mipLevels   = static_cast<uint32_t>(texture.TryGetAttribute("MipLevels").ToInt(1));
            auto alpha       = StringToEnumBoolExt(texture.TryGetAttribute("Alpha").ToString("None"));

            m_configs.insert(std::make_pair(
                    texture.GetAttribute("Path").ToString(),
                    TextureConfig {
                        format,
                        type,
                        autoRemove,
                        filter,
                        compression,
                        mipLevels,
                        alpha
                    }
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

    return TextureConfig {
            TextureFormat::RGBA8_UNORM,
            TextureType::Diffuse,
            true,
            TextureFilter::LINEAR,
            TextureCompression::None,
            1,
            Helper::BoolExt::None
    };
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