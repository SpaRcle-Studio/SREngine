//
// Created by Nikita on 17.11.2020.
//

#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include "Types/Texture.h"
#include <map>
#include <Loaders/TextureLoader.h>
#include <Debug.h>
#include <Render/Render.h>

inline static std::map<unsigned int, unsigned long> TexID_usages = std::map<unsigned int, unsigned long>();
inline static std::map<std::string, unsigned int> TexID_names = std::map<std::string, unsigned int>();

Framework::Graphics::Types::Texture::Texture()
    : IResource(typeid(Texture).name())
{
    if(!m_env)
        m_env = Environment::Get();
}

Framework::Graphics::Types::Texture::~Texture() {
    if (m_data)
        TextureLoader::Free(m_data);
}

bool Framework::Graphics::Types::Texture::Destroy() {
    if (IsDestroy()) {
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::Medium)
        Debug::Log("Texture::Destroy() : destroying texture...");

    /*
        Проверяем, просчитана ли текстура, если просчитана,
        регистрируем в рендере для освобождения видео-памяти, если нет, просто убираем
        юз-поинт.
        Может возникнуть такая ситуация, что текстура будет уничтожена еще до ее просчета,
        это нормально, так как она не регистрируется в рендере в прямом смысле. Т-е она там не содержится.
        Меш узнает о том, что текстура будет уничтожена, так как он сам и уничтожает материал, содержащий ее.
    */
    if (m_isCalculate)
        m_render->FreeTexture(this);

    Helper::ResourceManager::Instance().Destroy(this);

    return IResource::Destroy();
}

Framework::Graphics::Types::Texture *Framework::Graphics::Types::Texture::Load(const std::string& localPath, const Memory::TextureConfig& config) {
    const auto path = ResourceManager::Instance().GetResPath().Concat("/Textures/").Concat(localPath);

    Texture* texture = nullptr;

    if (IResource* find = ResourceManager::Instance().Find<Texture>(localPath)) {
        texture = ((Texture*)(find));

        if (texture->m_config != config || config.m_autoRemove != texture->IsEnabledAutoRemove())
            Debug::Warn("Texture::Load() : copy values do not match load values.");
    }
    else {
        if (Debug::GetLevel() >= Debug::Level::Medium)
            Debug::Log("Texture::Load : load \"" + localPath + "\" texture...");

        texture = TextureLoader::Load(path.ToString());
        texture->SetConfig(config);
        texture->m_name = localPath;

        texture->SetId(localPath);
    }

    return texture;
}

bool Framework::Graphics::Types::Texture::Calculate() {
    if (!m_data)
        return false;

    if (!m_render){
        Debug::Error("Texture::Calculate() : this texture is not register in render!");
        return false;
    }

    if (IsDestroy()) {
        Debug::Error("Texture::Calculate() : texture is destroyed!");
        return false;
    }

    if (m_isCalculate){
        Debug::Error("Texture::Calculate() : texture already calculated!");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Texture::Calculate() : calculating \"" + GetResourceId() + "\" texture...");

    // TODO: to refactoring
    m_ID = m_env->CalculateTexture(m_data,
            m_config.m_format, m_width, m_height, m_config.m_filter,
            m_config.m_compression, m_config.m_mipLevels,
            m_config.m_alpha == Helper::BoolExt::None, m_config.m_cpuUsage);

    if (m_ID < 0) { // TODO: vulkan can be return 0 as correct value
        Debug::Error("Texture::Calculate() : failed calculate texture!");
        return false;
    } else {
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("Texture::Calculate() : texture \"" + GetResourceId() + "\" has " + std::to_string(m_ID) + " id.");
        TextureLoader::Free(m_data);
        m_data = nullptr;
    }

    this->m_isCalculate = true;

    return true;
}

void Framework::Graphics::Types::Texture::OnDestroyGameObject() {
    if (IsEnabledAutoRemove() && GetCountUses() == 1)
        this->Destroy();
}

void Framework::Graphics::Types::Texture::SetRender(Framework::Graphics::Render *render) {
    this->m_render = render;
}

bool Framework::Graphics::Types::Texture::FreeVideoMemory()  {
    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Texture::FreeVideoMemory() : free \"" + std::string(GetResourceName()) + "\" texture video memory...");

    if (!m_isCalculate) {
        Debug::Error("Texture::FreeVideoMemory() : texture \"" + std::string(GetResourceName()) + "\" is not calculated!");
        return false;
    }
    else
        return Framework::Graphics::Types::Texture::m_env->FreeTexture(m_ID);
}

Texture *Texture::Load(const std::string &path) {
    return Load(path, TextureConfigs::Instance().FindOrDefault(path));
}

void Texture::SetConfig(const TextureConfig &config) {
    auto alpha = m_config.m_alpha;
    m_config = config;

    // TODO: to refactoring
    if (alpha != Helper::BoolExt::None)
        m_config.m_alpha = alpha;

    SetAutoRemoveEnabled(m_config.m_autoRemove);
}
