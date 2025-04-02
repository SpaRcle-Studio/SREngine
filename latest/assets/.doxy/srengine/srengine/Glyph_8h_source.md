

# File Glyph.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Font**](dir_193e1c173bb6bd0681658b8507d31117.md) **>** [**Glyph.h**](Glyph_8h.md)

[Go to the documentation of this file](Glyph_8h.md)


```C++
//
// Created by Monika on 24.05.2023.
//

#ifndef SR_ENGINE_GLYPH_H
#define SR_ENGINE_GLYPH_H

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


