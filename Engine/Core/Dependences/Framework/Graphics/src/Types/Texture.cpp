//
// Created by Nikita on 17.11.2020.
//

#include <Types/Texture.h>

#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include <Loaders/TextureLoader.h>
#include <Render/Render.h>
#include <Environment/Environment.h>

SR_GRAPH_NS::Types::Texture::Texture()
    : IResource(typeid(Texture).name())
    , m_env(Environment::Get())
{ }

SR_GRAPH_NS::Types::Texture::~Texture() {
    if (m_data) {
        TextureLoader::Free(m_data);
    }
}

bool SR_GRAPH_NS::Types::Texture::Destroy() {
    if (IsDestroyed()) {
        SRAssert2(false, "Texture already destroyed!");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::Medium)
        SR_LOG("Texture::Destroy() : destroying texture...");

    m_render->FreeTexture(this);

    return IResource::Destroy();
}

SR_GRAPH_NS::Types::Texture* SR_GRAPH_NS::Types::Texture::Load(const std::string& localPath, const Memory::TextureConfig& config) {
    const auto path = ResourceManager::Instance().GetResPath().Concat("/Textures/").Concat(localPath);

    Texture* texture = nullptr;

    if (IResource* find = ResourceManager::Instance().Find<Texture>(localPath)) {
        texture = ((Texture*)(find));

        if (texture->m_config != config || config.m_autoRemove != texture->IsEnabledAutoRemove())
            SR_WARN("Texture::Load() : copy values do not match load values.");
    }
    else {
        if (Debug::GetLevel() >= Debug::Level::Medium)
            SR_LOG("Texture::Load : load \"" + localPath + "\" texture...");

        if ((texture = TextureLoader::Load(path.ToString()))) {
            texture->SetConfig(config);
            texture->m_name = localPath;

            texture->SetId(localPath);
        }
    }

    return texture;
}

bool SR_GRAPH_NS::Types::Texture::Calculate() {
    if (!m_data)
        return false;

    if (!m_render) {
        SR_ERROR("Texture::Calculate() : this texture is not register in render!");
        return false;
    }

    if (IsDestroyed()) {
        SR_ERROR("Texture::Calculate() : texture is destroyed!");
        return false;
    }

    if (m_isCalculate){
        SR_ERROR("Texture::Calculate() : texture already calculated!");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        SR_LOG("Texture::Calculate() : calculating \"" + GetResourceId() + "\" texture...");

    // TODO: to refactoring
    m_ID = m_env->CalculateTexture(m_data,
            m_config.m_format, m_width, m_height, m_config.m_filter,
            m_config.m_compression, m_config.m_mipLevels,
            m_config.m_alpha == Helper::BoolExt::None, m_config.m_cpuUsage);

    if (m_ID < 0) { // TODO: vulkan can be return 0 as correct value
        SR_ERROR("Texture::Calculate() : failed calculate texture!");
        return false;
    }
    else {
        if (Debug::GetLevel() >= Debug::Level::High)
            SR_LOG("Texture::Calculate() : texture \"" + GetResourceId() + "\" has " + std::to_string(m_ID) + " id.");

        TextureLoader::Free(m_data);

        m_data = nullptr;
    }

    m_isCalculate = true;

    return true;
}

void SR_GRAPH_NS::Types::Texture::SetRender(Framework::Graphics::Render *render) {
    m_render = render;
}

bool SR_GRAPH_NS::Types::Texture::FreeVideoMemory()  {
    if (Debug::GetLevel() >= Debug::Level::High)
        SR_LOG("Texture::FreeVideoMemory() : free \"" + std::string(GetResourceName()) + "\" texture video memory...");

    if (!m_isCalculate) {
        SR_ERROR("Texture::FreeVideoMemory() : texture \"" + std::string(GetResourceName()) + "\" is not calculated!");
        return false;
    }
    else
        return Framework::Graphics::Types::Texture::m_env->FreeTexture(m_ID);
}

SR_GTYPES_NS::Texture *SR_GTYPES_NS::Texture::Load(const std::string &path) {
    return Load(path, TextureConfigs::Instance().FindOrDefault(path));
}

void SR_GTYPES_NS::Texture::SetConfig(const TextureConfig &config) {
    auto alpha = m_config.m_alpha;
    m_config = config;

    // TODO: to refactoring
    if (alpha != Helper::BoolExt::None)
        m_config.m_alpha = alpha;

    SetAutoRemoveEnabled(m_config.m_autoRemove);
}

int32_t SR_GTYPES_NS::Texture::GetID() noexcept  {
    if (IsDestroyed()) {
        SR_ERROR("Texture::GetID() : texture \"" + GetResourceId() + "\" is destroyed!");
        return -1;
    }

    if (!m_isCalculate && !Calculate()) {
        SR_ERROR("Texture::GetID() : failed to calculating texture!");
        return -1;
    }

    return m_ID;
}

SR_GTYPES_NS::Texture *SR_GTYPES_NS::Texture::GetNone() {
    if (!m_none) {
        /// так как вписать в код данные текстуры невозможно, то она хранится в виде base64, текстура размером 1x1 елого цвета типа png
        const std::string image = "iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAABmJLR0QA/wD/AP+gvaeTAAAADUlEQVQI12N48eIFOwAINALALwGcPAAAAABJRU5ErkJggg==";

        const auto&& config = TextureConfig(
                /**.m_format = */ TextureFormat::RGBA8_UNORM,
                /**.m_type = */ TextureType::Diffuse,
                /**.m_autoRemove = */ false,
                /**.m_filter = */ TextureFilter::NEAREST,
                /**.m_compression = */ TextureCompression::None,
                /**.m_mipLevels = */ 1,
                /**.m_alpha = */ Helper::BoolExt::None,
                /**.m_cpuUsage = */ false
        );

        m_none = LoadFromMemory(SR_UTILS_NS::StringUtils::Base64Decode(image), config);
    }

    if (!m_none) {
        SR_ERROR("Texture::GetNone() : fatal internal error...");
        SR_UTILS_NS::Debug::MakeCrash();
    }

    return m_none;
}

SR_GTYPES_NS::Texture *SR_GTYPES_NS::Texture::LoadFromMemory(const std::string& data, const TextureConfig &config) {
    Texture* texture = TextureLoader::LoadFromMemory(data);

    if (!texture) {
        SRVerifyFalse2(false, "Texture::LoadFromMemory() : failed to load texture!");
        return nullptr;
    }

    texture->SetConfig(config);
    texture->m_name = "TextureFromMemory";

    texture->SetId(texture->m_name);

    return texture;
}

void SR_GTYPES_NS::Texture::FreeNoneTexture() {
    if (m_none) {
        m_none->Destroy();
        m_none = nullptr;
    }
}
