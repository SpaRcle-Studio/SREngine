//
// Created by Nikita on 17.11.2020.
//

#include <Types/Texture.h>

#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include <Loaders/TextureLoader.h>
#include <Render/Render.h>
#include <Environment/Environment.h>

namespace SR_GTYPES_NS {
    Texture::Texture()
        : IResource(typeid(Texture).name())
    { }

    Texture::~Texture() {
        if (m_data) {
            TextureLoader::Free(m_data);
            m_data = nullptr;
        }
    }

    bool Texture::Destroy() {
        if (IsDestroyed()) {
            SRAssert2(false, "Texture already destroyed!");
            return false;
        }

        if (Debug::GetLevel() >= Debug::Level::Medium)
            SR_LOG("Texture::Destroy() : destroying texture...");

        if (m_render) {
            m_render->FreeTexture(this);
        }
        else if (IsCalculated()) {
            SRAssert2(false, "Render lost!");
        }

        return IResource::Destroy();
    }

    Texture* Texture::Load(const std::string& rawPath, const Memory::TextureConfig& config) {
        SR_GLOBAL_LOCK

        Path&& path = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetTexturesPath());

        if (auto&& pResource = ResourceManager::Instance().Find<Texture>(path)) {
            if (pResource->m_config != config || config.m_autoRemove != pResource->IsEnabledAutoRemove()) {
                SR_WARN("Texture::Load() : copy values do not match load values.");
            }

            return pResource;
        }

        auto&& pTexture = new Texture();

        pTexture->SetConfig(config);
        pTexture->SetId(path, false /** auto register */);

        if (!pTexture->Load()) {
            SR_ERROR("Texture::Load() : failed to load texture! \n\tPath: " + path.ToString());
            delete pTexture;
            return nullptr;
        }

        /// отложенная ручная регистрация
        ResourceManager::Instance().RegisterResource(pTexture);

        return pTexture;
    }

    bool Texture::Unload() {
        SR_SCOPED_LOCK

        bool hasErrors = !IResource::Unload();

        if (m_data) {
            TextureLoader::Free(m_data);
            m_data = nullptr;
        }

        m_isCalculated = false;
        Environment::Get()->SetBuildState(false);

        return !hasErrors;
    }

    bool Texture::Load() {
        SR_SCOPED_LOCK

        bool hasErrors = !IResource::Load();

        Path&& path = Path(GetResourceId());
        if (!path.IsAbs()) {
            path = ResourceManager::Instance().GetTexturesPath().Concat(path);
        }

        if (!TextureLoader::Load(this, path.ToString())) {
            hasErrors |= true;
        }

        m_isCalculated = false;
        Environment::Get()->SetBuildState(false);

        return !hasErrors;
    }

    bool Texture::Calculate() {
        SR_SCOPED_LOCK

        if (!m_data) {
            return false;
        }

        if (!m_render) {
            SR_ERROR("Texture::Calculate() : this texture is not register in render!");
            m_hasErrors = true;
            return false;
        }

        if (IsDestroyed()) {
            SR_ERROR("Texture::Calculate() : texture is destroyed!");
            return false;
        }

        if (m_isCalculated) {
            SR_ERROR("Texture::Calculate() : texture already calculated!");
            return false;
        }

        if (Debug::GetLevel() >= Debug::Level::None)
            SR_LOG("Texture::Calculate() : calculating \"" + GetResourceId() + "\" texture...");

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!Environment::Get()->FreeTexture(&m_id));
        }

        // TODO: to refactoring
        m_id = Environment::Get()->CalculateTexture(m_data,
                m_config.m_format, m_width, m_height, m_config.m_filter,
                m_config.m_compression, m_config.m_mipLevels,
                m_config.m_alpha == SR_UTILS_NS::BoolExt::None, m_config.m_cpuUsage);

        if (m_id == SR_ID_INVALID) { // TODO: vulkan can be return 0 as correct value
            SR_ERROR("Texture::Calculate() : failed to calculate texture!");
            return false;
        }
        else {
            if (Debug::GetLevel() >= Debug::Level::High) {
                SR_LOG("Texture::Calculate() : texture \"" + GetResourceId() + "\" has " + std::to_string(m_id) + " id.");
            }

            TextureLoader::Free(m_data);

            m_data = nullptr;
        }

        m_isCalculated = true;

        return true;
    }

    void Texture::SetRender(SR_GRAPH_NS::Render *render) {
        m_render = render;
    }

    bool Texture::FreeVideoMemory()  {
        SR_SCOPED_LOCK

        if (Debug::GetLevel() >= Debug::Level::High) {
            SR_LOG("Texture::FreeVideoMemory() : free \"" + std::string(GetResourceName()) + "\" texture video memory...");
        }

        if (!m_isCalculated) {
            SR_ERROR("Texture::FreeVideoMemory() : texture \"" + std::string(GetResourceName()) + "\" is not calculated!");
            return false;
        }

        m_isCalculated = false;

        return Environment::Get()->FreeTexture(&m_id);
    }

    Texture* Texture::Load(const std::string &path) {
        return Load(path, Memory::TextureConfigs::Instance().FindOrDefault(path));
    }

    void Texture::SetConfig(const Memory::TextureConfig &config) {
        auto alpha = m_config.m_alpha;
        m_config = config;

        // TODO: to refactoring
        if (alpha != SR_UTILS_NS::BoolExt::None)
            m_config.m_alpha = alpha;

        SetAutoRemoveEnabled(m_config.m_autoRemove);
    }

    int32_t Texture::GetId() noexcept {
        if (m_hasErrors) {
            return SR_ID_INVALID;
        }

        if (IsDestroyed()) {
            SR_ERROR("Texture::GetId() : texture \"" + GetResourceId() + "\" is destroyed!");
            return SR_ID_INVALID;
        }

        if (!m_isCalculated && !Calculate()) {
            SR_ERROR("Texture::GetId() : failed to calculating texture!");
            return SR_ID_INVALID;
        }

        return m_id;
    }

    Texture* Texture::GetNone() {
        if (!m_none) {
            /// так как вписать в код данные текстуры невозможно, то она хранится в виде base64, текстура размером 1x1 белого цвета формата png
            const std::string image = "iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAABmJLR0QA/wD/AP+gvaeTAAAADUlEQVQI12N48eIFOwAINALALwGcPAAAAABJRU5ErkJggg==";

            const auto&& config = Memory::TextureConfig(
                    /**.m_format = */ TextureFormat::RGBA8_UNORM,
                    /**.m_autoRemove = */ false,
                    /**.m_filter = */ TextureFilter::NEAREST,
                    /**.m_compression = */ TextureCompression::None,
                    /**.m_mipLevels = */ 1,
                    /**.m_alpha = */ SR_UTILS_NS::BoolExt::None,
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

    Texture* Texture::LoadFromMemory(const std::string& data, const Memory::TextureConfig &config) {
        Texture* texture = new Texture();

        if (!TextureLoader::LoadFromMemory(texture, data)) {
            SRHalt("Texture::LoadFromMemory() : failed to load texture!");
            delete texture;
            return nullptr;
        }

        texture->m_fromMemory = true;

        texture->SetConfig(config);
        texture->SetId("");

        return texture;
    }

    void SR_GTYPES_NS::Texture::FreeNoneTexture() {
        if (m_none) {
            m_none->Destroy();
            m_none = nullptr;
        }
    }

    void* Texture::GetDescriptor() {
        SR_SCOPED_LOCK

        if (!IsCalculated()) {
            return nullptr;
        }

        return Environment::Get()->GetDescriptorSetFromTexture(GetId(), true);
    }

    SR_UTILS_NS::Path Framework::Graphics::Types::Texture::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetTexturesPath();
    }

    bool Texture::IsValid() const {
        return GetResourceId() != "NoID" && std::string(m_resourceName) != "Unnamed";
    }

    uint64_t Texture::GetFileHash() const {
        if (m_fromMemory) {
            return 0;
        }

        return IResource::GetFileHash();
    }

    bool Texture::Reload() {
        SR_SCOPED_LOCK

        SR_LOG("Texture::Reload() : reloading \"" + GetResourceId() + "\" texture...");

        m_loadState = LoadState::Reloading;

        bool hasErrors = false;

        hasErrors |= !Unload();
        hasErrors |= !Load();

        UpdateResources();

        return !hasErrors;
    }
}