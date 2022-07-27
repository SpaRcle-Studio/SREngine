//
// Created by Nikita on 17.11.2020.
//

#include <Types/Texture.h>

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/StringUtils.h>
#include <Loaders/TextureLoader.h>
#include <Render/Render.h>
#include <Environment/Environment.h>
#include <Render/RenderContext.h>

namespace SR_GTYPES_NS {
    Texture::Texture()
        : IResource(typeid(Texture).name(), true /** auto remove */)
    { }

    Texture::~Texture() {
        if (m_data) {
            TextureLoader::Free(m_data);
            m_data = nullptr;
        }
    }

    Texture* Texture::Load(const std::string& rawPath, const Memory::TextureConfig& config) {
        SR_GLOBAL_LOCK

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetTexturesPath());

        if (auto&& pResource = SR_UTILS_NS::ResourceManager::Instance().Find<Texture>(path)) {
            if (pResource->m_config != config) {
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
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pTexture);

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

        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });

        return !hasErrors;
    }

    bool Texture::Load() {
        SR_SCOPED_LOCK

        bool hasErrors = !IResource::Load();

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());
        if (!path.IsAbs()) {
            path = SR_UTILS_NS::ResourceManager::Instance().GetTexturesPath().Concat(path);
        }

        if (!TextureLoader::Load(this, path.ToString())) {
            hasErrors |= true;
        }

        m_isCalculated = false;

        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });

        return !hasErrors;
    }

    bool Texture::Calculate() {
        SR_SCOPED_LOCK

        if (m_isCalculated || !m_data) {
            SR_ERROR("Texture::Calculate() : data is invalid or the texture is already calculated!");
            return false;
        }

        if (!SRVerifyFalse2(!(m_context = SR_THIS_THREAD->GetContext()->GetValue<RenderContextPtr>()), "Is not render context!")) {
            m_hasErrors = true;
            return false;
        }

        m_context.Do([this](RenderContext* ptr) {
            ptr->Register(this);
            m_pipeline = ptr->GetPipeline();
        });

        if (IsDestroyed()) {
            SR_ERROR("Texture::Calculate() : the texture is destroyed!");
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::None) {
            SR_LOG("Texture::Calculate() : calculating \"" + GetResourceId() + "\" texture...");
        }

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        // TODO: to refactoring
        m_id = m_pipeline->CalculateTexture(m_data,
                m_config.m_format, m_width, m_height, m_config.m_filter,
                m_config.m_compression, m_config.m_mipLevels,
                m_config.m_alpha == SR_UTILS_NS::BoolExt::None, m_config.m_cpuUsage);

        if (m_id == SR_ID_INVALID) {
            SR_ERROR("Texture::Calculate() : failed to calculate the texture!");
            return false;
        }
        else {
            if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
                SR_LOG("Texture::Calculate() : texture \"" + GetResourceId() + "\" has " + std::to_string(m_id) + " id.");
            }

            TextureLoader::Free(m_data);

            m_data = nullptr;
        }

        m_isCalculated = true;

        return true;
    }

    void Texture::FreeVideoMemory() {
        SR_SCOPED_LOCK

        /// Просто игнорируем, текстура могла быть не использована
        if (!m_isCalculated) {
            return;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Low) {
            SR_LOG("Texture::FreeVideoMemory() : free \"" + GetResourceId() + "\" texture's video memory...");
        }

        m_isCalculated = false;

        SRAssert(m_pipeline);

        if (m_pipeline && !m_pipeline->FreeTexture(&m_id)) {
            SR_ERROR("Texture::FreeVideoMemory() : failed to free texture!");
        }
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
    }

    int32_t Texture::GetId() noexcept {
        if (m_hasErrors) {
            return SR_ID_INVALID;
        }

        if (IsDestroyed()) {
            SRHalt("Texture::GetId() : the texture \"" + GetResourceId() + "\" is destroyed!");
            return SR_ID_INVALID;
        }

        if (!m_isCalculated && !Calculate()) {
            SR_ERROR("Texture::GetId() : failed to calculate the texture!");
            m_hasErrors = true;
            return SR_ID_INVALID;
        }

        return m_id;
    }

    Texture* Texture::LoadFromMemory(const std::string& data, const Memory::TextureConfig &config) {
        Texture* texture = new Texture();

        if (!TextureLoader::LoadFromMemory(texture, data)) {
            SRHalt("Texture::LoadFromMemory() : failed to load the texture!");
            delete texture;
            return nullptr;
        }

        texture->m_fromMemory = true;

        texture->SetConfig(config);
        texture->SetId("");

        return texture;
    }

    void* Texture::GetDescriptor() {
        SR_SCOPED_LOCK

        auto&& textureId = GetId();

        if (textureId == SR_ID_INVALID) {
            return nullptr;
        }

        return m_pipeline->GetDescriptorSetFromTexture(textureId, true);
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

        SR_LOG("Texture::Reload() : reloading \"" + GetResourceId() + "\" the texture...");

        m_loadState = LoadState::Reloading;

        bool hasErrors = false;

        hasErrors |= !Unload();
        hasErrors |= !Load();

        UpdateResources();

        m_hasErrors = false;

        return !hasErrors;
    }
}