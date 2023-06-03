//
// Created by Monika on 24.05.2023.
//

#include <Graphics/Font/Glyph.h>

namespace SR_GRAPH_NS {
    Glyph::Glyph(FT_Glyph pGlyph, FT_Render_Mode renderMode)
        : Super()
        , m_glyph(pGlyph)
        , m_renderMode(renderMode)
    {
        FT_Glyph_To_Bitmap(&m_glyph, m_renderMode, 0, 1);
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)m_glyph;
        FT_Bitmap bitmap = bitmap_glyph->bitmap;

        m_metrics.advanceX = m_glyph->advance.x;
        m_metrics.advanceY = m_glyph->advance.y;
        m_metrics.left = bitmap_glyph->left;
        m_metrics.top = bitmap_glyph->top;
        m_metrics.width = bitmap.width;
        m_metrics.height = bitmap.rows;
    }

    Glyph::~Glyph() {
        if (m_glyph) {
            FT_Done_Glyph(m_glyph);
            m_glyph = nullptr;
        }
    }

    uint32_t Glyph::GetSize() const noexcept {
        return GetWidth() * GetHeight() * GetPixelSize();
    }

    uint32_t Glyph::GetPixelSize() const noexcept {
        return 4;
    }

    GlyphMetrics& Glyph::GetMetrics() noexcept {
        return m_metrics;
    }

    uint32_t Glyph::GetWidth() const noexcept {
        return m_metrics.width;
    }

    uint32_t Glyph::GetHeight() const noexcept {
        return m_metrics.height;
    }

    FT_Glyph Glyph::GetGlyph() const noexcept {
        return m_glyph;
    }

    int32_t Glyph::GetPosX() const noexcept {
        return m_metrics.posX;
    }

    int32_t Glyph::GetPosY() const noexcept {
        return m_metrics.posY;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    GlyphImage::Ptr GlyphImage::Create(const Glyph::Ptr& pGlyph, bool needInit) {
        auto&& pGlyphImage = std::make_shared<GlyphImage>();

        pGlyphImage->m_glyph = pGlyph;

        if (needInit && !pGlyphImage->Init()) {
            return nullptr;
        }

        return pGlyphImage;
    }


    GlyphImage::~GlyphImage() {
        SR_SAFE_DELETE_ARRAY_PTR(m_data);
    }

    bool GlyphImage::Init() {
        if (m_glyph->GetSize() == 0) {
            return false;
        }

        m_data = new uint8_t[m_glyph->GetSize()];

        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)m_glyph->GetGlyph();
        FT_Bitmap bitmap = bitmap_glyph->bitmap;

        uint8_t* pBuffer = bitmap.buffer;

        const uint32_t pixelSize = m_glyph->GetPixelSize();

        for (uint32_t x = 0; x < m_glyph->GetWidth(); ++x) {
            for (uint32_t y = 0; y < m_glyph->GetHeight(); ++y) {
                const uint32_t dst = x * pixelSize + y * m_glyph->GetWidth() * pixelSize;

                if (pixelSize == 1) {
                    const uint32_t src = x + y * bitmap.pitch;
                    m_data[dst] = 255 - pBuffer[src];
                }
                else if (bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                    m_data[dst + 0] = pBuffer[dst + 2];
                    m_data[dst + 1] = pBuffer[dst + 1];
                    m_data[dst + 2] = pBuffer[dst + 0];
                    m_data[dst + 3] = pBuffer[dst + 3];
                }
                else {
                    const uint32_t src = x + y * bitmap.pitch;
                    m_data[dst + 0] = uint8_t(255 - pBuffer[src]);
                    m_data[dst + 1] = uint8_t(255 - pBuffer[src]);
                    m_data[dst + 2] = uint8_t(255 - pBuffer[src]);
                    m_data[dst + 3] = uint8_t(      pBuffer[src]);
                }
            }
        }

        return true;
    }

    void GlyphImage::InsertTo(uint8_t* pTarget, int32_t top, uint32_t sizeX) {
        const int32_t posX = m_glyph->GetPosX();
        const int32_t posY = m_glyph->GetPosY();

        const uint32_t pixelSize = m_glyph->GetPixelSize();
        const uint32_t width = m_glyph->GetWidth();
        const uint32_t height = m_glyph->GetHeight();

        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)m_glyph->GetGlyph();
        FT_Bitmap bitmap = bitmap_glyph->bitmap;
        uint8_t* pBuffer = bitmap.buffer;

        for (uint32_t x = 0; x < width; ++x) {
            for (uint32_t y = 0; y < height; ++y) {
                uint32_t src = 0; 

                if (bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                    src = x * pixelSize + y * width * pixelSize;
                    if (pBuffer[src + (pixelSize - 1)] == 0) {
                        continue;
                    }
                }
                else {
                    src = x + y * width;
                    if (pBuffer[src] == 0) {
                        continue;
                    }
                }

                const int32_t dstY = posY + y - top;
                const int32_t dstX = posX + x;

                const int32_t dst = dstX * pixelSize + dstY * sizeX * pixelSize;

                if (dst < 0) {
                    continue;
                }

                if (bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                    *(pTarget + dst + 0) = *(pBuffer + src + 2);
                    *(pTarget + dst + 1) = *(pBuffer + src + 1);
                    *(pTarget + dst + 2) = *(pBuffer + src + 0);
                    *(pTarget + dst + 3) = *(pBuffer + src + 3);
                }
                else {
                    *(pTarget + dst + 0) = 0;
                    *(pTarget + dst + 1) = 0;
                    *(pTarget + dst + 2) = 0;

                    const float a = *(pBuffer + src) / 255.0f;

                    *(pTarget + dst + 3) = uint8_t(a * 255 + (1 - a) * *(pTarget + dst + 3));
                }
            }
        }
    }

    void GlyphImage::Debug(uint8_t* pTarget, int32_t top, uint32_t sizeX)
    {
        const int32_t posX = m_glyph->GetPosX();
        const int32_t posY = m_glyph->GetPosY();

        const uint32_t pixelSize = m_glyph->GetPixelSize();
        const uint32_t width = m_glyph->GetWidth();
        const uint32_t height = m_glyph->GetHeight();

        for (uint32_t x = 0; x < width; ++x) {
            for (uint32_t y = 0; y < height; ++y) {
                if (x != 0 && y != 0 && x + 1 != width && y + 1 != height) {
                    continue;
                }

                const int32_t dstY = posY + y - top;
                const int32_t dstX = posX + x;

                const uint32_t dst = dstX * pixelSize + dstY * sizeX * pixelSize;

                *(pTarget + dst + 0) = 255;
                *(pTarget + dst + 1) = 0;
                *(pTarget + dst + 2) = 0;
                *(pTarget + dst + 3) = 255;
            }
        }
    }
}