//
// Created by Monika on 30.10.2022.
//

#ifndef SRENGINE_TEXTBUILDER_H
#define SRENGINE_TEXTBUILDER_H

#include <Utils/Common/NonCopyable.h>
#include <Graphics/Font/FreeType.h>
#include <Graphics/Font/Glyph.h>

namespace SR_GTYPES_NS {
    class Font;
}

namespace SR_GRAPH_NS {
    class TextBuilder : SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using FontPtr = SR_GTYPES_NS::Font*;
        using StringType = std::u32string;
        struct Pixel {
            uint8_t r, g, b, a;
        };
    public:
        explicit TextBuilder(FontPtr pFont);
        ~TextBuilder() override;

    public:
        SR_NODISCARD uint32_t GetSize() const noexcept;
        SR_NODISCARD uint32_t GetWidth() const noexcept { return m_imageWidth; }
        SR_NODISCARD uint32_t GetHeight() const noexcept { return m_imageHeight; }
        SR_NODISCARD uint8_t* GetData() const noexcept { return m_textureData; }
        SR_NODISCARD ColorFormat GetColorFormat() const noexcept;

        bool Build(StringType text);

        void SetFontSize(uint32_t size);
        void SetKerning(bool enabled);

    private:
        void Clear();
        bool Prepare(char32_t code);

        bool ParseGlyph(const StringType& text);

        SR_NODISCARD Pixel** CreateImage(const StringType& text);
        SR_NODISCARD Pixel** CreateImage();

        uint32_t PreProcess(const StringType& text, uint32_t iterator);
        void PreProcessImpl(const StringType& text, uint32_t begin, uint32_t end);

    private:
        FT_Render_Mode m_renderMode = FT_RENDER_MODE_NORMAL;

        FontPtr m_font = nullptr;

        std::vector<Glyph::Ptr> m_glyphs;

        bool m_kerning = false;

        uint32_t m_fontSize = 32;
        uint32_t m_align = 0;
        uint32_t m_valign = -2;
        uint32_t m_space = 24;

        uint32_t m_maxGlyphHeight = 0;

        int32_t m_top = 0;

        uint32_t m_imageHeight = 0;
        uint32_t m_imageWidth = 0;
        uint8_t* m_textureData = nullptr;

        bool m_needParse = false;

    };
}

#endif //SRENGINE_TEXTBUILDER_H
