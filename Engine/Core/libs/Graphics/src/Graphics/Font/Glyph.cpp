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

    GlyphImage::Ptr GlyphImage::Create(const Glyph::Ptr& pGlyph) {
        auto&& pGlyphImage = std::shared_ptr<GlyphImage>(new GlyphImage());

        pGlyphImage->m_glyph = pGlyph;

        if (!pGlyphImage->Init()) {
            return nullptr;
        }

        return pGlyphImage;
    }

    bool GlyphImage::Init() {
        m_data = std::shared_ptr<uint8_t[]>(new uint8_t[m_glyph->GetSize()]);

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
                    m_data[dst + 0] = 255 - pBuffer[src];
                    m_data[dst + 1] = 255 - pBuffer[src];
                    m_data[dst + 2] = 255 - pBuffer[src];
                    m_data[dst + 3] =       pBuffer[src];
                }
            }
        }

        return true;
    }

    void GlyphImage::InsertTo(uint8_t* pTarget, int32_t top, uint32_t sizeX, uint32_t sizeY) {
        const uint32_t posX = m_glyph->GetPosX();
        const uint32_t posY = m_glyph->GetPosY(); ///(sizeY - m_glyph->GetPosY()) - m_glyph->GetHeight();
        const uint32_t pixelSize = m_glyph->GetPixelSize();

        for (uint32_t x = 0; x < m_glyph->GetWidth(); ++x) {
            for (uint32_t y = 0; y < m_glyph->GetHeight(); ++y) {
                const uint32_t src = x * pixelSize + y * m_glyph->GetWidth() * pixelSize;

                if (m_data[src + (pixelSize - 1)] == 0) {
                    continue;
                }

                const int32_t dstY = posY + y - top;
                const int32_t dstX = posX + x;

                const uint32_t dst = dstX * pixelSize + dstY * sizeX * pixelSize;

                //const uint32_t dst = (x + posX) * pixelSize + (posY + y) * sizeX * pixelSize;

                memcpy(pTarget + dst, m_data.get() + src, pixelSize);
            }
        }
    }
}