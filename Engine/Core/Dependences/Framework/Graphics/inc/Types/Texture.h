//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <Utils/ResourceManager/IResource.h>
#include <Environment/TextureHelper.h>
#include <Memory/TextureConfigs.h>

namespace SR_GRAPH_NS {
    class Environment;
    class TextureLoader;
    class Render;
}

namespace SR_GTYPES_NS {
    class Texture : public SR_UTILS_NS::IResource {
        friend class ::SR_GRAPH_NS::TextureLoader;
    private:
        Texture();
        ~Texture() override;

    public:
        static Texture* Load(const std::string& path);
        static Texture* Load(const std::string& path, const Memory::TextureConfig& config);
        static Texture* LoadFromMemory(const std::string& data, const Memory::TextureConfig& config);
        static Texture* GetNone();
        static void FreeNoneTexture();

    public:
        void SetRender(Render* render);

        SR_NODISCARD SR_FORCE_INLINE Render* GetRender() const noexcept { return m_render; }
        SR_NODISCARD SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculated; }
        SR_NODISCARD SR_FORCE_INLINE bool HasRender() const noexcept { return GetRender(); }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetWidth() const noexcept { return m_width; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetHeight() const noexcept { return m_height; }
        SR_NODISCARD SR_FORCE_INLINE uint32_t GetChannels() const noexcept { return m_channels; }
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD int32_t FastGetId() noexcept { return m_id; }
        SR_NODISCARD void* GetDescriptor();
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_NODISCARD bool IsValid() const override;
        SR_NODISCARD uint64_t GetFileHash() const override ;

        bool FreeVideoMemory();

    protected:
        bool Unload() override;
        bool Load() override;
        bool Reload() override;

    public:
        bool Destroy() override;

    private:
        bool Calculate();
        void SetConfig(const Memory::TextureConfig& config);

    private:
        inline static Texture*     m_none         = nullptr;

        Render*                    m_render       = nullptr;
        uint8_t*                   m_data         = nullptr;

        int32_t                    m_id           = SR_ID_INVALID;
        uint32_t                   m_width        = 0;
        uint32_t                   m_height       = 0;
        uint8_t                    m_channels     = 0;

        std::atomic<bool>          m_isCalculated = false;
        std::atomic<bool>          m_hasErrors    = false;
        std::atomic<bool>          m_fromMemory   = false;

        Memory::TextureConfig      m_config       = Memory::TextureConfig();

    };
}

#endif //GAMEENGINE_TEXTURE_H
