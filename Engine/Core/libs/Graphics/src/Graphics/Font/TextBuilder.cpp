//
// Created by Monika on 30.10.2022.
//

#include <Graphics/Font/TextBuilder.h>

namespace SR_GRAPH_NS {
    TextBuilder::TextBuilder(TextBuilder::FontPtr pFont)
        : Super()
        , m_font(pFont)
    {
        if (m_font) {
            m_font->AddUsePoint();
        }
    }

    TextBuilder::~TextBuilder() {
        Clear();

        if (m_font) {
            m_font->RemoveUsePoint();
            m_font = nullptr;
        }
    }

    bool TextBuilder::Build(StringType text) {
        Clear();

        if (!m_font) {
            return false;
        }

        m_font->SetPixelSizes(0, m_fontSize);
        m_font->SetCharSize(0, 16 * 64, 500, 500);

        /// препроцессор текста
        for (uint32_t i = 0; i < static_cast<uint32_t>(text.size()); ++i) {
            if (auto&& iterator = PreProcess(text, i); iterator != SR_ID_INVALID) {
                text.erase(text.begin() + i, text.begin() + iterator);
                continue;
            }

            //if (!Prepare(text[i])) {
            //    SR_ERROR("TextBuilder::Build() : failed to prepare symbol!")
            //    return false;
            //}
        }

        if (!ParseGlyph(text)) {
            return false;
        }

        auto&& size = GetSize();

        m_textureData = new uint8_t[size];
        memset(m_textureData, 255, size);

        for (auto&& pGlyph : m_glyphs) {
            auto&& pGlyphImage = GlyphImage::Create(pGlyph);
            pGlyphImage->InsertTo(m_textureData, m_top, m_imageWidth, m_imageHeight);
        }

        /// auto&& pImage = CreateImage(text);
///
        /// uint32_t size = m_imageWidth * m_imageHeight;
///
        /// if (size == 0) {
        ///     SR_ERROR("TextBuilder::Build() : image size is zero!");
        ///     return false;
        /// }
///
        /// m_textureData = new uint8_t[size * 4];
        /// memset(m_textureData, 255, size * 4 * sizeof(uint8_t));
///
        /// for (uint32_t i = 0, y = 0; i < size; ++y) {
        ///     for (uint32_t x = 0; x < m_imageWidth; ++x, ++i) {
        ///         m_textureData[4 * i + 0] = pImage[y][x].r;
        ///         m_textureData[4 * i + 1] = pImage[y][x].g;
        ///         m_textureData[4 * i + 2] = pImage[y][x].b;
        ///         m_textureData[4 * i + 3] = pImage[y][x].a;
        ///     }
        /// }
///
        /// for (uint32_t i = 0; i < m_imageHeight; ++i) {
        ///     delete pImage[i];
        /// }
        /// delete[] pImage;

        return true;
    }

    void TextBuilder::SetFontSize(uint32_t size) {
        m_fontSize = size;
    }

    uint32_t TextBuilder::PreProcess(const TextBuilder::StringType& text, uint32_t iterator) {
        if (!m_needParse) {
            return SR_ID_INVALID;
        }

        if (text[iterator] == '<') {
            const uint32_t pos = text.find('>', iterator);
            PreProcessImpl(text, iterator, pos);
            return pos;
        }

        return SR_ID_INVALID;
    }

    void TextBuilder::PreProcessImpl(const TextBuilder::StringType &text, uint32_t begin, uint32_t end) {

    }

    bool TextBuilder::ParseGlyph(const StringType& text) {
        std::optional<uint32_t> prevCode;

        int32_t posX = 0;
        int32_t bottom = 0;

        for (auto&& code : text) {
            if (code == ' ') {
                posX += m_space;
                prevCode = std::nullopt;
                continue;
            }

            auto&& glyph = m_font->GetGlyph(code, m_renderMode);
            if (!glyph) {
                continue;
            }

            auto&& pGlyph = std::make_shared<Glyph>(glyph, m_renderMode);

            if (m_kerning && prevCode.has_value()) {
                posX += m_font->GetKerning(prevCode.value(), code);
            }
            prevCode = code;

            pGlyph->GetMetrics().posX = posX;
            pGlyph->GetMetrics().posY = -pGlyph->GetMetrics().top;

            ////// Вычисляем самую верхнюю позицию
            m_top = SR_MIN(m_top, pGlyph->GetMetrics().posY);

            ///metrics.posX = posX + bitmap_glyph->left;
            ///metrics.posY = -bitmap_glyph->top;
            ///metrics.width = bitmap.width;
            ///metrics.height = bitmap.rows;

            ////// Вычисляем самую нижнюю позицию
            bottom = SR_MAX(bottom, pGlyph->GetMetrics().posY + pGlyph->GetMetrics().height);

            posX += m_align + pGlyph->GetWidth();

            m_glyphs.emplace_back(pGlyph);
        }

        if (m_glyphs.empty()) {
            return false;
        }

        m_imageWidth = m_glyphs.back()->GetPosX() + m_glyphs.back()->GetWidth();
        m_imageHeight = bottom - m_top;

        return m_imageHeight * m_imageWidth > 0;
    }

    bool TextBuilder::Prepare(char32_t code) {
        auto&& glyph = m_font->GetGlyph(code, m_renderMode);
        if (!glyph) {
            SR_ERROR("TextBuilder::Prepare() : failed to get glyph!\n\tCode: " + std::to_string(code));
            return false;
        }

        FT_Glyph_To_Bitmap(&glyph, m_renderMode, 0, 1);
        FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
        FT_Bitmap bitmap = bitmap_glyph->bitmap;

        int32_t resize = 0;

        if (bitmap_glyph->top < 0) {
            resize = bitmap.rows + SR_ABS(bitmap_glyph->top);
        }
        else {
            resize = bitmap.rows > bitmap_glyph->top ? bitmap.rows - bitmap_glyph->top : bitmap_glyph->top - bitmap.rows;
        }

        if (m_imageHeight < bitmap.rows + resize) {
            m_imageHeight = SR_MAX(0, static_cast<int32_t>(bitmap.rows) + resize);
        }

        if (m_imageHeight > 32768) {
            SRHalt("TextBuilder::Prepare() : very big height!\n\tHeight: " + std::to_string(m_imageHeight));
            return false;
        }

        m_imageWidth += bitmap.width;

        if (m_top < bitmap.rows) {
            m_top = bitmap.rows;
        }

        if (m_maxGlyphHeight < bitmap.rows + bitmap_glyph->top) {
            m_maxGlyphHeight = bitmap.rows + bitmap_glyph->top;
        }

        if (code == ' ') {
            m_imageWidth += m_space;
        }
        else if (code == '\n') {
            m_imageHeight += m_valign + m_maxGlyphHeight;
            FT_Done_Glyph(glyph);
            return true;
        }

        m_imageWidth += m_align;

        FT_Done_Glyph(glyph);

        return true;
    }

    void TextBuilder::Clear() {
        if (m_textureData) {
            free(m_textureData);
            m_textureData = nullptr;
        }

        m_imageHeight = 0;
        m_imageWidth = 0;

        m_top = 0;

        m_maxGlyphHeight = 0;

        m_glyphs.clear();
    }

    TextBuilder::Pixel **TextBuilder::CreateImage() {
        Pixel** pImage = new Pixel*[m_imageHeight];
        for (uint32_t i = 0; i < m_imageHeight; ++i) {
            pImage[i] = new Pixel[m_imageWidth];
            memset(pImage[i], 0, m_imageWidth * sizeof(Pixel));
        }

        return pImage;
    }

    TextBuilder::Pixel** TextBuilder::CreateImage(const TextBuilder::StringType &text) {
        Pixel** pImage = new Pixel*[m_imageHeight];
        for (uint32_t i = 0; i < m_imageHeight; ++i) {
            pImage[i] = new Pixel[m_imageWidth];
            memset(pImage[i], 0, m_imageWidth * sizeof(Pixel));
        }

        int32_t posY = 0, topY = 0, maxWidth = 0, height = 0, width = 0;

        for (uint32_t charIndex = 0; charIndex < static_cast<uint32_t>(text.size()); ++charIndex) {
            auto&& glyph = m_font->GetGlyph(text[charIndex], m_renderMode);
            if (!glyph) {
                continue;
            }

            FT_Glyph_To_Bitmap(&glyph, m_renderMode, 0, 1);
            FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph) glyph;
            FT_Bitmap bitmap = bitmap_glyph->bitmap;

            posY = bitmap_glyph->top;
            posY = bitmap.rows - posY;
            topY = m_top - bitmap.rows;

            if (text[charIndex] == '\n') {
                height += static_cast<int32_t>(m_maxGlyphHeight);
                width = 0;
                FT_Done_Glyph(glyph);
                continue;
            }

            uint8_t* src = bitmap.buffer;

            for (uint32_t y = 0, j = 0; y < bitmap.rows; ++y) {
                for (uint32_t x = 0; x < bitmap.width; ++x, ++j) {
                    if ((height + posY + y + topY) > m_imageHeight) {
                        if (posY < 0) posY = abs(posY);
                    }

                    if (height + posY + y + topY >= m_imageHeight) {
                        /// TODO: японский язык вызывает краш
                        continue;
                    }

                    auto&& pRow = pImage[height + posY + y + topY];

                    if (bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                        pRow[width + x].b = *src++;
                        pRow[width + x].g = *src++;
                        pRow[width + x].r = *src++;
                        pRow[width + x].a = *src++;
                    }
                    else {
                        pRow[width + x].r = 255 - *src;
                        pRow[width + x].g = 255 - *src;
                        pRow[width + x].b = 255 - *src;
                        pRow[width + x].a = *src;
                        src++;
                    }
                }
            }

            width += bitmap.width;
            width += m_align;

            if (maxWidth < width) {
                maxWidth = width;
            }

            if (text[charIndex] == ' ') {
                width += m_space;
            }

            FT_Done_Glyph(glyph);
        }

        width = maxWidth;

        return pImage;
    }

    uint32_t TextBuilder::GetSize() const noexcept {
        return GetWidth() * GetHeight() * 4;
    }

    void TextBuilder::SetKerning(bool kerning) {
        m_kerning = kerning;
    }

    ColorFormat TextBuilder::GetColorFormat() const noexcept {
        return ColorFormat::RGBA8_UNORM;
    }
}