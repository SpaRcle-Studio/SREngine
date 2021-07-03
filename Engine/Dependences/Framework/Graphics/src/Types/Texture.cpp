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

Framework::Graphics::Types::Texture::Texture() : IResource("Texture") {
    if(!m_env)
        m_env = Environment::Get();
}

Framework::Graphics::Types::Texture::~Texture() {
    if (m_data)
        TextureLoader::Free(m_data);
}

bool Framework::Graphics::Types::Texture::Destroy() {
    if (m_isDestroy)
        return false;

    if (Debug::GetLevel() >= Debug::Level::Medium)
        Debug::Log("Texture::Destroy() : destroying texture...");

    this->m_isDestroy = true;

    /*
        Проверяем, просчитана ли текстура, если просчитана,
        регистрируем в рендере для освобождения видео-памяти, если нет, просто убираем
        юз-поинт.
        Может возникнуть такая ситуация, что текстура будет уничтожена еще до ее просчета,
        это нормально, так как она не регистрируется в рендере в прямом смысле. Т-е она там не содержится.
        Меш узнает о том, что текстура будет уничтожена, так как он сам и уничтожает материал, содержащий ее.
    */
    if (m_isCalculate) {
        m_render->FreeTexture(this);
    } else
        this->RemoveUsePoint();

    Helper::ResourceManager::Destroy(this);

    return true;
}

Framework::Graphics::Types::Texture *Framework::Graphics::Types::Texture::Load(
        const std::string& localPath,
        TextureFormat format,
        bool autoRemove,
        TextureType type,
        TextureFilter filter,
        TextureCompression compression,
        uint8_t mipLevels)
{
    std::string path = ResourceManager::GetResourcesFolder() + "/Textures/"+ localPath;

#ifdef WIN32
    path = Helper::StringUtils::MakePath(path, true);
#else
    path = StringUtils::MakePath(path, false);
#endif
    Texture* texture = nullptr;

    IResource* find = ResourceManager::Find("Texture", localPath);
    if (find) {
        //texture = ((Texture*)(find))->Copy();
        texture = ((Texture*)(find));

        if (texture->m_autoRemove != autoRemove || texture->m_type != type || texture->m_filter != filter){
            Debug::Warn("Texture::Load() : copy values do not match load values.");
        }
    } else {
        if (Debug::GetLevel() >= Debug::Level::Medium)
            Debug::Log("Texture::Load : load \""+localPath+"\" texture...");

        texture = TextureLoader::Load(path);
        texture->m_resource_id = localPath;
        texture->m_autoRemove = autoRemove;
        texture->m_type = type;
        texture->m_filter = filter;
        texture->m_format = format;
        texture->m_compression = compression;
        texture->m_mipLevels = mipLevels;
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

    if (m_isDestroy) {
        Debug::Error("Texture::Calculate() : texture is destroyed!");
        return false;
    }

    if (m_isCalculate){
        Debug::Error("Texture::Calculate() : texture already calculated!");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Texture::Calculate() : calculating \""+ m_resource_id +"\" texture...");

    m_ID = m_env->CalculateTexture(m_data, m_format, m_width, m_height, m_filter, m_compression, m_mipLevels, m_alpha);
    if (m_ID < 0) { // TODO: vulkan can be return 0 as correct value
        Debug::Error("Texture::Calculate() : failed calculate texture!");
        return false;
    } else {
        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("Texture::Calculate() : texture \""+ m_resource_id +"\" has " + std::to_string(m_ID) + " ID.");
        TextureLoader::Free(m_data);
        m_data = nullptr;
    }

    this->m_isCalculate = true;

    return true;
}

void Framework::Graphics::Types::Texture::OnDestroyGameObject() noexcept {
    if (m_autoRemove && m_countUses == 1)
        this->Destroy();
}

void Framework::Graphics::Types::Texture::SetRender(Framework::Graphics::Render *render) {
    this->m_render = render;
}

/*
Framework::Graphics::Types::Texture *Framework::Graphics::Types::Texture::Copy() {
    if (m_isDestroy) {
        Debug::Error("Texture::Copy() : texture already destroyed!");
        return nullptr;
    }

    //Texture*

    return nullptr;
}*/

