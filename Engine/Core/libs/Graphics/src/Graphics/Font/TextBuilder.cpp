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

        /// Позиция текущего символа в формате 26.6
        int32_t posX = 0;

        int32_t bottom = 0;
        int32_t left = 0;

        for (auto&& code : text) {
            if (code == ' ') {
                posX += m_space << 6;
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

            pGlyph->GetMetrics().posX = (posX >> 6) + pGlyph->GetMetrics().left;
            pGlyph->GetMetrics().posY = -pGlyph->GetMetrics().top;

            posX += m_align << 6;
            posX += pGlyph->GetMetrics().advanceX >> 10;

            /// Вычисляем самую верхнюю позицию
            m_top = SR_MIN(m_top, pGlyph->GetMetrics().posY);
            /// Вычисляем самую левую позицию
            left = SR_MIN(left, pGlyph->GetMetrics().posX);
            /// Вычисляем самую нижнюю позицию
            bottom = SR_MAX(bottom, pGlyph->GetMetrics().posY + pGlyph->GetMetrics().height);

            m_glyphs.emplace_back(pGlyph);
        }

        for (auto&& pGlyph : m_glyphs) {
            pGlyph->GetMetrics().posY -= left;
        }

        if (m_glyphs.empty()) {
            return false;
        }

        m_imageWidth = m_glyphs.back()->GetPosX() + m_glyphs.back()->GetWidth();
        m_imageHeight = bottom - m_top;

        return m_imageHeight * m_imageWidth > 0;
    }

    void TextBuilder::Clear() {
        if (m_textureData) {
            free(m_textureData);
            m_textureData = nullptr;
        }

        m_imageHeight = 0;
        m_imageWidth = 0;

        m_top = 0;

        m_glyphs.clear();
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