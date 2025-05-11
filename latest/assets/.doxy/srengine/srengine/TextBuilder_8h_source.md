

# File TextBuilder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Font**](dir_0f9fa5c8aefacabb9ad499652a4f09bc.md) **>** [**TextBuilder.h**](TextBuilder_8h.md)

[Go to the documentation of this file](TextBuilder_8h.md)


```C++
//
// Created by Monika on 30.10.2022.
//

#ifndef SR_ENGINE_TEXTBUILDER_H
#define SR_ENGINE_TEXTBUILDER_H

#include <Utils/Common/NonCopyable.h>
#include <Graphics/Font/FreeType.h>
#include <Graphics/Font/Glyph.h>

namespace SR_GTYPES_NS {
    class Font;
}

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(FontStyle, uint32_t,
        Regular = 0,   
        Bold = 1,      
        Italic = 2,    
        BoldItalic = 3 
    );

    class TextBuilder : SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using FontPtr = SR_GTYPES_NS::Font*;
        using StringType = std::u32string;
    public:
        explicit TextBuilder(FontPtr pFont);
        ~TextBuilder() override;

    public:
        SR_NODISCARD uint32_t GetSize() const noexcept;
        SR_NODISCARD uint32_t GetWidth() const noexcept { return m_imageWidth; }
        SR_NODISCARD uint32_t GetHeight() const noexcept { return m_imageHeight; }
        SR_NODISCARD uint8_t* GetData() const noexcept { return m_textureData; }
        SR_NODISCARD ImageFormat GetColorFormat() const noexcept;
        SR_NODISCARD uint32_t GetFontSize() const noexcept { return m_fontSize; }
        SR_NODISCARD FontStyle GetFontStyle() const noexcept { return m_fontStyle; }

        SR_NODISCARD int32_t CalculateTextWidth(const char* text);

        bool Build(const char* text);
        bool Build(StringType text);

        void SetFontStyle(FontStyle style) { m_fontStyle = style; }
        void SetFontSize(uint32_t size) { m_fontSize = size; }
        void SetKerning(bool enabled);
        void SetDebug(bool enabled);

    private:
        void InitFontSize();
        void Clear();

        bool ParseGlyphs(const StringType& text);

        uint32_t PreProcess(const StringType& text, uint32_t iterator);
        void PreProcessImpl(const StringType& text, uint32_t begin, uint32_t end);

    private:
        FontStyle m_fontStyle = FontStyle::Regular;
        FT_Render_Mode m_renderMode = FT_RENDER_MODE_NORMAL;

        FontPtr m_font = nullptr;

        std::vector<Glyph::Ptr> m_glyphs;

        bool m_kerning = false;
        bool m_debug = false;

        uint32_t m_fontSize = 12;

        uint32_t m_align = 0;
        uint32_t m_valign = 110;
        uint32_t m_space = 24;

        int32_t m_top = 0;

        uint32_t m_imageHeight = 0;
        uint32_t m_imageWidth = 0;
        uint8_t* m_textureData = nullptr;

        bool m_needParse = false;

    };
}

#endif //SR_ENGINE_TEXTBUILDER_H
```


