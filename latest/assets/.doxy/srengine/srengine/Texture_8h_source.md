

# File Texture.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Texture.h**](Texture_8h.md)

[Go to the documentation of this file](Texture_8h.md)


```C++
//
// Created by Nikita on 17.11.2020.
//

#ifndef SR_ENGINE_TEXTURE_H
#define SR_ENGINE_TEXTURE_H

#include <Utils/Resources/IResource.h>
#include <Utils/Types/SafePointer.h>

#include <Graphics/Pipeline/TextureHelper.h>
#include <Graphics/Memory/TextureConfigs.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Loaders/TextureLoader.h>

namespace SR_GRAPH_NS {
    class TextureLoader;
    class RenderContext;
    class Render;
}

namespace SR_GTYPES_NS {
    class Font;

    class Texture : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        SR_CLASS()
        friend class ::SR_GRAPH_NS::TextureLoader;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Texture>;

    public:
        Texture();
        ~Texture() override;

    public:
        static Texture::Ptr Load(const SR_UTILS_NS::Path& rawPath, const std::optional<Memory::TextureConfig>& config = std::nullopt);
        static Texture::Ptr LoadRaw(const uint8_t* pData, uint64_t bytes, uint64_t h, uint64_t w, const Memory::TextureConfig& config);
        static Texture::Ptr LoadFromMemory(const std::string& data, const Memory::TextureConfig& config);

    public:
        SR_NODISCARD uint32_t GetWidth() const noexcept;
        SR_NODISCARD uint32_t GetHeight() const noexcept;
        SR_NODISCARD uint32_t GetChannels() const noexcept;
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD void* GetDescriptor();
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_NODISCARD const Memory::TextureConfig& GetTextureConfig() const noexcept { return m_config; }

        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        void FreeVMemory() override;

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        bool Calculate();
        void SetConfig(const Memory::TextureConfig& config);
        void FreeTextureData();

    private:
        TextureData::Ptr m_textureData;

        int32_t m_id = SR_ID_INVALID;

        std::atomic<bool> m_hasErrors = false;
        std::atomic<bool> m_isDirty = true;

        Memory::TextureConfig m_config = Memory::TextureConfig();

    };
}

#endif //SR_ENGINE_TEXTURE_H
```


