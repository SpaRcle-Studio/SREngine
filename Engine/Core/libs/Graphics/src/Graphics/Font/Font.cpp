//
// Created by Monika on 14.02.2022.
//

#include <Graphics/Font/Font.h>
#include <Graphics/Font/SDF.h>

#include <freetype/include/freetype/ftglyph.h>

namespace SR_GRAPH_NS {
    Font::Font()
        : Super()
        , m_fontSize(16)
    {
        FT_Init_FreeType(&m_library);
    }

    Font::~Font() {
        FT_Done_FreeType(m_library);

        if (m_textureData) {
            delete[] m_textureData;
            m_textureData = nullptr;
        }
    }

    void Font::Load() {
        auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Fonts/TsunagiGothic.ttf");

        if (FT_New_Face(m_library, path.c_str(), 0, &m_face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }
    }

    bool Font::Init(const StringType &text,
            uint32_t fontSize, uint32_t align,
            uint32_t valign, uint32_t space,
            uint8_t r, uint8_t g, uint8_t b)
    {
        FT_Set_Pixel_Sizes(m_face, 0, (m_fontSize = fontSize));

        FT_Set_Char_Size(
                m_face,  /* handle to face object           */
                0,       /* char_width in 1/64th of points  */
                16*64,   /* char_height in 1/64th of points */
                900,     /* horizontal device resolution    */
                900 );   /* vertical device resolution      */

        MathGlyphSizes(text, align, valign, space);

        uint8_t** pImage = new uint8_t*[m_glyphHeight];
        for (uint32_t i = 0; i < m_glyphHeight; ++i) {
            pImage[i] = new uint8_t[m_glyphWidth];
            memset(pImage[i], 0, m_glyphWidth * sizeof(uint8_t));
        }

        InitImage(pImage, text, align, space);

        uint32_t size = m_imageWidth * m_imageHeight;
        m_textureData = new uint8_t [size * 4];
        memset(m_textureData, 255, size * 4 * sizeof(uint8_t));

        for (uint32_t i = 0, y = 0; i < size; ++y) {
            for (uint32_t x = 0; x < m_imageWidth; ++x, ++i) {
                m_textureData[4 * i + 3] = pImage[y][x];
                m_textureData[4 * i + 0] = r;
                m_textureData[4 * i + 1] = g;
                m_textureData[4 * i + 2] = b;
            }
        }

        for (uint32_t i = 0; i < m_glyphHeight; ++i) {
            delete pImage[i];
        }
        delete[] pImage;


        return false;
    }

    bool Font::MathGlyphSizes(const StringType &text, uint32_t align, uint32_t valign, uint32_t space) {
        FT_Glyph glyph;

        for (uint32_t i = 0; i < text.size(); ++i) {
            auto &&code = text[i];

            FT_Load_Char(m_face, code, FT_LOAD_RENDER);

            FT_UInt glyph_index = FT_Get_Char_Index(m_face, code);
            FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
            FT_Render_Glyph(m_face->glyph, m_renderMode);
            FT_Get_Glyph(m_face->glyph, &glyph);

            FT_Glyph_To_Bitmap(&glyph, m_renderMode, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
            FT_Bitmap bitmap = bitmap_glyph->bitmap;

            m_glyphWidth += bitmap.width;

            int32_t resize = bitmap.rows > bitmap_glyph->top ? bitmap.rows - bitmap_glyph->top : bitmap_glyph->top - bitmap.rows;

            if (m_glyphHeight < bitmap.rows + resize) {
                m_glyphHeight = bitmap.rows + resize;
            }

            if (m_topRow < bitmap.rows) {
                m_topRow = bitmap.rows;
            }

            if (m_maxGlyphHeight < bitmap.rows + bitmap_glyph->top) {
                m_maxGlyphHeight = bitmap.rows + bitmap_glyph->top;
            }

            if (code == ' ') {
                m_glyphWidth += space;
            }
            else if (code == '\n') {
                m_glyphHeight += valign + m_maxGlyphHeight;
                FT_Done_Glyph(glyph);
                continue;
            }

            m_glyphWidth += align;

            FT_Done_Glyph(glyph);
        }

        if (m_glyphHeight <= 0) {
            m_glyphHeight = m_maxGlyphHeight;
        }

        return true;
    }

    bool Font::InitImage(uint8_t** pImage, const StringType& text, uint32_t align, uint32_t space) {
        int32_t posY = 0;
        int32_t topY = 0;

        FT_Glyph glyph;

        for (uint32_t i = 0; i < text.size(); ++i) {
            auto&& code = text[i];

            FT_Load_Char(m_face, code, FT_LOAD_RENDER);
            FT_UInt glyph_index = FT_Get_Char_Index(m_face, code);

            FT_Load_Glyph(m_face, glyph_index, FT_LOAD_DEFAULT);
            FT_Render_Glyph(m_face->glyph, m_renderMode);
            FT_Get_Glyph(m_face->glyph, &glyph);

            FT_Glyph_To_Bitmap(&glyph, m_renderMode, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
            FT_Bitmap bitmap = bitmap_glyph->bitmap;

            posY = bitmap_glyph->top;
            posY = bitmap.rows - posY;
            topY = m_topRow - bitmap.rows;

            if (code == '\n') {
                m_imageHeight += m_maxGlyphHeight;
                m_imageWidth = 0;
                FT_Done_Glyph(glyph);
                continue;
            }

            for (uint32_t y = 0, j = 0; y < bitmap.rows; ++y) {
                for (uint32_t x = 0; x < bitmap.width; ++x, ++j) {
                    if ((m_imageHeight + posY + y + topY) > m_glyphHeight) {
                        if (posY < 0) posY = abs(posY);
                    }

                    if (m_imageHeight + posY + y + topY >= m_glyphHeight) {
                        /// TODO: японский язык вызывает краш
                        continue;
                    }

                    const uint8_t character = bitmap.buffer[j];
                    auto&& pRow = pImage[m_imageHeight + posY + y + topY];
                    pRow[m_imageWidth + x] = character;
                }
            }

            m_imageWidth += bitmap.width;
            m_imageWidth += align;

            if (m_maxGlyphWidth < m_imageWidth) {
                m_maxGlyphWidth = m_imageWidth;
            }

            if (code == ' ') {
                m_imageWidth += space;
            }

            FT_Done_Glyph(glyph);

        }

        m_imageWidth = m_maxGlyphWidth;
        m_imageHeight = m_glyphHeight;

        return true;
    }

    void Font::FreeTextureData(uint8_t *pData) {
        if (!pData) {
            return;
        }

        delete[] pData;
    }

    uint8_t *Font::CopyData() const noexcept {
        if (!m_textureData) {
            return nullptr;
        }

        uint32_t size = m_imageWidth * m_imageHeight;
        uint8_t* pCopy = new uint8_t [size * 4];
        memcpy(pCopy, m_textureData, size * 4 * sizeof(uint8_t));

        return pCopy;
    }
}