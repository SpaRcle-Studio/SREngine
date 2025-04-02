

# File TextureLoader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Loaders**](dir_3c21463f64aae35806a3291732eddb38.md) **>** [**TextureLoader.h**](TextureLoader_8h.md)

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


