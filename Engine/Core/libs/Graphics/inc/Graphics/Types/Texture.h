//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <Utils/ResourceManager/IResource.h>

#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Memory/TextureConfigs.h>
#include <Graphics/Memory/IGraphicsResource.h>

namespace SR_GRAPH_NS {
    class Environment;
    class TextureLoader;
    class RenderContext;
    class Render;
}

namespace SR_GTYPES_NS {
    class Font;

    class Texture : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        friend class ::SR_GRAPH_NS::TextureLoader;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
        using PipelnePtr = Environment*;
    private:
        Texture();
        ~Texture() override;

    public:
        static Texture* Load(const std::string& path, const std::optional<Memory::TextureConfig>& config = std::nullopt);
        static Texture* LoadFromMemory(const std::string& data, const Memory::TextureConfig& config);
        static Texture* LoadFont(Font* pFont);

    public:
        SR_NODISCARD SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculated; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetWidth() const noexcept { return m_width; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetHeight() const noexcept { return m_height; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetChannels() const noexcept { return m_channels; }
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD void* GetDescriptor();
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_NODISCARD uint64_t GetFileHash() const override;

        void FreeVideoMemory() override;

    protected:
        bool Unload() override;
        bool Load() override;
        bool Reload() override;

    private:
        bool Calculate();
        void SetConfig(const Memory::TextureConfig& config);
        void FreeTextureData();

    private:
        bool                       m_isFont       = false;
        uint8_t*                   m_data         = nullptr;
        PipelnePtr                 m_pipeline     = nullptr;

        int32_t                    m_id           = SR_ID_INVALID;
        uint32_t                   m_width        = 0;
        uint32_t                   m_height       = 0;
        uint8_t                    m_channels     = 0;

        std::atomic<bool>          m_isCalculated = false;
        std::atomic<bool>          m_hasErrors    = false;
        std::atomic<bool>          m_fromMemory   = false;

        Memory::TextureConfig      m_config       = Memory::TextureConfig();

        RenderContextPtr           m_context      = { };

    };
}

#endif //GAMEENGINE_TEXTURE_H
