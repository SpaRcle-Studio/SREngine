//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_FONT_H
#define SRENGINE_FONT_H

#include <Utils/Common/NonCopyable.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace SR_GRAPH_NS {
    class Font : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
        using FontLibraty = FT_Library;
        using FontFace = FT_Face;
        using StringType = std::u32string;
    public:
        Font();
        ~Font() override;

    public:
        static void FreeTextureData(uint8_t* pData);

    public:
        void Load();
        bool Init(const StringType& text, uint32_t fontSize, uint32_t align, uint32_t valign, uint32_t space, uint8_t r, uint8_t g, uint8_t b);

        SR_NODISCARD uint32_t GetWidth() const noexcept { return m_imageWidth; }
        SR_NODISCARD uint32_t GetHeight() const noexcept { return m_imageHeight; }
        SR_NODISCARD uint8_t* GetData() const noexcept { return m_textureData; }

        SR_NODISCARD uint8_t* CopyData() const noexcept;

    private:
        bool MathGlyphSizes(const StringType& text, uint32_t align, uint32_t valign, uint32_t space);
        bool InitImage(uint8_t** pImage, const StringType& text, uint32_t align, uint32_t space);

    private:
        uint8_t* m_textureData = nullptr;

        FT_Render_Mode m_renderMode = FT_RENDER_MODE_NORMAL;

        FontLibraty m_library;
        FontFace m_face;
        uint32_t m_fontSize = 0;

        int32_t m_glyphWidth = 0;
        uint32_t m_glyphHeight = 0;

        uint32_t m_maxGlyphHeight = 0;
        uint32_t m_maxGlyphWidth = 0;

        uint32_t m_topRow = 0;

        uint32_t m_imageHeight = 0;
        uint32_t m_imageWidth = 0;


    };
}

#endif //SRENGINE_FONT_H
