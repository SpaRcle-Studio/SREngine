

# File Glyph.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**Glyph.h**](Glyph_8h.md)

[Go to the documentation of this file](Glyph_8h.md)


```C++
//
// Created by Monika on 24.05.2023.
//

#ifndef SR_ENGINE_GLYPH_H
#define SR_ENGINE_GLYPH_H

#include <Graphics/macros.h>

#include <Utils/Common/NonCopyable.h>
#include <Graphics/Font/FreeType.h>

namespace SR_GRAPH_NS {
    struct GlyphMetrics {
        int32_t posX = 0;
        int32_t posY = 0;
        int32_t width = 0;
        int32_t height = 0;

        int32_t left = 0;
        int32_t top = 0;

        int32_t advanceX = 0;
        int32_t advanceY = 0;
    };

    class Glyph : public SR_UTILS_NS::NonCopyable {
    public:
        using Super = SR_UTILS_NS::NonCopyable;
        using Ptr = std::shared_ptr<Glyph>;

    public:
        Glyph(FT_Glyph pGlyph, FT_Render_Mode renderMode);
        ~Glyph() override;

    public:
        SR_NODISCARD int32_t GetPosX() const noexcept;
        SR_NODISCARD int32_t GetPosY() const noexcept;
        SR_NODISCARD uint32_t GetSize() const noexcept;
        SR_NODISCARD uint32_t GetWidth() const noexcept;
        SR_NODISCARD uint32_t GetHeight() const noexcept;
        SR_NODISCARD uint32_t GetPixelSize() const noexcept;
        SR_NODISCARD FT_Glyph GetGlyph() const noexcept;
        SR_NODISCARD GlyphMetrics& GetMetrics() noexcept;

    private:
        FT_Render_Mode m_renderMode;
        GlyphMetrics m_metrics = { };
        FT_Glyph m_glyph = nullptr;

    };

    class GlyphImage : public SR_UTILS_NS::NonCopyable {
    public:
        using Ptr = std::shared_ptr<GlyphImage>;

    public:
        GlyphImage() = default;
        ~GlyphImage() override;

    public:
        SR_NODISCARD static GlyphImage::Ptr Create(const Glyph::Ptr& pGlyph, bool needInit);
        SR_NODISCARD uint8_t* GetData() const { return m_data; }

        void InsertTo(uint8_t* pTarget, int32_t top, uint32_t sizeX);
        void Debug(uint8_t* pTarget, int32_t top, uint32_t sizeX);

    private:
        SR_NODISCARD bool Init();

    private:
        uint8_t* m_data = nullptr;
        Glyph::Ptr m_glyph;

    };
}

#endif //SR_ENGINE_GLYPH_H
```


