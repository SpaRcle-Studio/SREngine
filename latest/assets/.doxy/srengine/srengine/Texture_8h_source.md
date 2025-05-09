

# File Texture.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Texture.h**](Texture_8h.md)

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
        friend class ::SR_GRAPH_NS::TextureLoader;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    public:
        using Ptr = Texture*;

    private:
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

        void FreeVideoMemory() override;

        RemoveUPResult RemoveUsePoint() override;

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

        Memory::TextureConfig m_config = Memory::TextureConfig();

    };
}

#endif //SR_ENGINE_TEXTURE_H
```


