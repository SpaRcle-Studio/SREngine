

# File TextureLoader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Loaders**](dir_d0a1daf921f47a1ee4283e6d14a9506b.md) **>** [**TextureLoader.h**](TextureLoader_8h.md)

[Go to the documentation of this file](TextureLoader_8h.md)


```C++
//
// Created by Nikita on 03.12.2020.
//

#ifndef SR_GRAPHICS_TEXTURE_LOADER_H
#define SR_GRAPHICS_TEXTURE_LOADER_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/Function.h>

#include <Graphics/Memory/TextureConfigs.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class TextureData : public SR_HTYPES_NS::SharedPtr<TextureData>, SR_UTILS_NS::NonCopyable {
        using Super = SR_HTYPES_NS::SharedPtr<TextureData>;
        using DeleterFn = SR_HTYPES_NS::Function<void(uint8_t*)>;
    private:
        TextureData(uint32_t width, uint32_t height, uint8_t channels, uint8_t* data, ImageLoadFormat format);

    public:
        ~TextureData() override;

    public:
        static TextureData::Ptr Load(const SR_UTILS_NS::Path& path, ImageLoadFormat format = ImageLoadFormat::RGBA);
        static TextureData::Ptr Create(uint32_t width, uint32_t height, uint8_t* pData, DeleterFn&& deleter, ImageLoadFormat format = ImageLoadFormat::RGBA);

        SR_NODISCARD bool Save(const SR_UTILS_NS::Path& path) const;

    public:
        SR_NODISCARD SR_MATH_NS::UVector2 GetSize() const { return { m_width, m_height }; }
        SR_NODISCARD uint32_t GetWidth() const { return m_width; }
        SR_NODISCARD uint32_t GetHeight() const { return m_height; }
        SR_NODISCARD uint8_t GetChannels() const { return m_channels; }
        SR_NODISCARD const uint8_t* GetData() const { return m_data; }
        SR_NODISCARD uint32_t GetNumberOfBytes() const { return (m_data) ? (m_width * m_height * m_channels) : 0; }
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const { return m_path; }
        SR_NODISCARD ImageLoadFormat GetFormat() const { return m_format; }

        void SetPath(const SR_UTILS_NS::Path& path) { m_path = path; }

    private:
        uint32_t m_width = 0;
        uint32_t m_height = 0;
        uint8_t m_channels = 0;
        uint8_t* m_data = nullptr;
        SR_UTILS_NS::Path m_path;
        ImageLoadFormat m_format = ImageLoadFormat::Unknown;
        DeleterFn m_deleter;
    };

    class TextureLoader {
        using TexturePtr = SR_GTYPES_NS::Texture*;
    public:
        TextureLoader() = delete;
        TextureLoader(const TextureLoader&) = delete;
        TextureLoader(TextureLoader&&) = delete;
        ~TextureLoader() = delete;

    public:
        static TextureData::Ptr Load(const SR_UTILS_NS::Path& path);
        static TextureData::Ptr LoadFromMemory(const std::string& data, const Memory::TextureConfig& config);

        static bool Free(unsigned char* data);

    private:
        static TextureData::Ptr LoadFromCache(const SR_UTILS_NS::Path& path);

    };
}

#endif //SR_GRAPHICS_TEXTURE_LOADER_H
```


