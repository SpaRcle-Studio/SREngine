//
// Created by Nikita on 17.11.2020.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/StringUtils.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Loaders/TextureLoader.h>
#include <Graphics/Render/RenderContext.h>

namespace SR_GTYPES_NS {
    Texture::Texture()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Texture))
    { }

    Texture::~Texture() {
        FreeTextureData();
    }

    Texture::Ptr Texture::LoadFont(Font* pFont) {
        auto&& pTexture = new Texture();

        pTexture->m_fromMemory = true;
        pTexture->m_isFont = true;

        pTexture->m_width = pFont->GetWidth();
        pTexture->m_height = pFont->GetHeight();
        pTexture->m_data = pFont->CopyData();

        pTexture->m_config.m_alpha = SR_UTILS_NS::BoolExt::True;
        pTexture->m_config.m_format = ImageFormat::RGBA8_UNORM;
        pTexture->m_config.m_filter = TextureFilter::NEAREST;
        pTexture->m_config.m_compression = TextureCompression::None;
        pTexture->m_config.m_mipLevels = 1;
        pTexture->m_config.m_cpuUsage = false;

        pTexture->SetId("FontTexture");

        return pTexture;
    }

    Texture::Ptr Texture::LoadRaw(const uint8_t* pData, uint64_t bytes, uint64_t h, uint64_t w, const Memory::TextureConfig &config) {
        Texture* texture = new Texture();

        texture->m_fromMemory = true;
        texture->m_rawMemory = true;

        texture->m_width = w;
        texture->m_height = h;

        texture->m_data = new uint8_t[bytes];
        memcpy(texture->m_data, pData, bytes);

        texture->m_config = config;

        texture->SetId("RawTexture");

        return texture;
    }

    Texture::Ptr Texture::Load(const std::string& rawPath, const std::optional<Memory::TextureConfig>& config) {
        auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        Texture::Ptr pTexture = nullptr;

        resourceManager.Execute([&]() {
            SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(resourceManager.GetResPath());

            if ((pTexture = SR_UTILS_NS::ResourceManager::Instance().Find<Texture>(path))) {
                if (config && pTexture->m_config != config.value()) {
                    SR_WARN("Texture::Load() : copy values do not match load values.");
                }

                return;
            }

            pTexture = new Texture();

            if (config) {
                pTexture->SetConfig(config.value());
            }
            else {
                pTexture->SetConfig(Memory::TextureConfig());
            }

            pTexture->SetId(path, false /** auto register */);

            if (!pTexture->Load()) {
                SR_ERROR("Texture::Load() : failed to load texture! \n\tPath: " + path.ToString());
                pTexture->DeleteResource();
                pTexture = nullptr;
                return;
            }

            /// отложенная ручная регистрация
            SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pTexture);
        });

        return pTexture;
    }

    bool Texture::Unload() {
        bool hasErrors = !IResource::Unload();

        FreeTextureData();

        m_isCalculated = false;

        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });

        return !hasErrors;
    }

    bool Texture::Load() {
        bool hasErrors = !IResource::Load();

        if (!IsCalculated()) {
            SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());
            if (!path.IsAbs()) {
                path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);
            }

            if (!TextureLoader::Load(this, path.ToString())) {
                hasErrors |= true;
            }
        }
        else {
            SRHalt("Texture already calculated!");
        }

        m_context.Do([](RenderContext* ptr) {
            ptr->SetDirty();
        });

        return !hasErrors;
    }

    bool Texture::Calculate() {
        if (m_isCalculated) {
            SR_ERROR("Texture::Calculate() : texture is already calculated!");
            return false;
        }

        if (!m_data) {
            SR_ERROR("Texture::Calculate() : data is invalid!");
            return false;
        }

        if (!SRVerifyFalse2(!(m_context = SR_THIS_THREAD->GetContext()->GetValue<RenderContextPtr>()), "Is not render context!")) {
            m_hasErrors = true;
            return false;
        }

        m_context.Do([this](RenderContext* ptr) {
            ptr->Register(this);
        });

        if (IsDestroyed()) {
            SR_ERROR("Texture::Calculate() : the texture is destroyed!");
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Texture::Calculate() : calculating \"" + std::string(GetResourceId()) + "\" texture...");
        }

        if (m_id != SR_ID_INVALID) {
            SRVerifyFalse(!m_pipeline->FreeTexture(&m_id));
        }

        EVK_PUSH_LOG_LEVEL(EvoVulkan::Tools::LogLevel::ErrorsOnly);

        SRTextureCreateInfo createInfo;
        createInfo.pData = m_data;
        createInfo.width = m_width;
        createInfo.height = m_height;
        createInfo.compression = m_config.m_compression;
        createInfo.cpuUsage = m_config.m_cpuUsage;
        createInfo.alpha = m_config.m_alpha == SR_UTILS_NS::BoolExt::None;
        createInfo.format = m_config.m_format;
        createInfo.mipLevels = m_config.m_mipLevels;
        createInfo.filter = m_config.m_filter;

        m_id = m_pipeline->AllocateTexture(createInfo);

        EVK_POP_LOG_LEVEL();

        if (m_id == SR_ID_INVALID) {
            SR_ERROR("Texture::Calculate() : failed to calculate the texture!");
            return false;
        }
        else {
            if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
                SR_LOG("Texture::Calculate() : texture \"" + std::string(GetResourceId()) + "\" has " + std::to_string(m_id) + " id.");
            }
        }

        m_isCalculated = true;

        return true;
    }

    void Texture::FreeVideoMemory() {
        /// Просто игнорируем, текстура могла быть не использована
        if (!m_isCalculated) {
            return;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Low) {
            SR_LOG("Texture::FreeVideoMemory() : free \"" + std::string(GetResourceId()) + "\" texture's video memory...");
        }

        SRAssert(m_pipeline);

        if (m_pipeline && !m_pipeline->FreeTexture(&m_id)) {
            SR_ERROR("Texture::FreeVideoMemory() : failed to free texture!");
        }

        IGraphicsResource::FreeVideoMemory();
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
            SRHalt("Texture::GetId() : the texture \"" + std::string(GetResourceId()) + "\" is destroyed!");
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
        Texture::Ptr texture = new Texture();

        if (!TextureLoader::LoadFromMemory(texture, data, config)) {
            SRHalt("Texture::LoadFromMemory() : failed to load the texture!");
            delete texture;
            return nullptr;
        }

        texture->m_fromMemory = true;

        texture->SetConfig(config);
        texture->SetId("TextureFromMemory");

        return texture;
    }

    void* Texture::GetDescriptor() {
        auto&& textureId = GetId();

        if (textureId == SR_ID_INVALID) {
            return nullptr;
        }

        return m_pipeline->GetOverlayTextureDescriptorSet(textureId, OverlayType::ImGui);
    }

    SR_UTILS_NS::Path SR_GTYPES_NS::Texture::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    uint64_t Texture::GetFileHash() const {
        if (IsFromMemory()) {
            return 0;
        }

        return IResource::GetFileHash();
    }

    void Texture::FreeTextureData() {
        if (!m_data) {
            return;
        }

        /// шрифт сам освободит свои данные
        if (!m_isFont && !m_rawMemory) {
            TextureLoader::Free(m_data);
        }
        else if (m_rawMemory) {
            delete[] m_data;
        }

        m_data = nullptr;
    }

    SR_UTILS_NS::IResource::RemoveUPResult Texture::RemoveUsePoint() {
        SRAssert2(!(IsCalculated() && GetCountUses() == 1), "Possible multi threading error!");
        return IResource::RemoveUsePoint();
    }

    void Texture::StartWatch() {
        if (IsFromMemory()) {
            return;
        }
        IResource::StartWatch();
    }
}