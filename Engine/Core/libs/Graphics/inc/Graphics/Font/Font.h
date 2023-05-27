//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_FONT_H
#define SRENGINE_FONT_H

#include <Utils/ResourceManager/IResource.h>
#include <Graphics/Font/FreeType.h>

namespace SR_GTYPES_NS {
    class SR_DLL_EXPORT Font : public SR_UTILS_NS::IResource {
        using Super = SR_UTILS_NS::IResource;
        using FontLibraty = FT_Library;
        using FontFace = FT_Face;
        using StringType = std::u32string;
    private:
        Font();
        ~Font() override = default;

    public:
        static void FreeTextureData(uint8_t* pData);

    public:
        static Font* Load(const SR_UTILS_NS::Path& rawPath);
        bool Init(const StringType& text, uint32_t fontSize, uint32_t align, uint32_t valign, uint32_t space, uint8_t r, uint8_t g, uint8_t b);

        SR_NODISCARD uint32_t GetWidth() const noexcept { return m_imageWidth; }
        SR_NODISCARD uint32_t GetHeight() const noexcept { return m_imageHeight; }
        SR_NODISCARD uint8_t* GetData() const noexcept { return m_textureData; }
        SR_NODISCARD FontFace GetFace() const noexcept { return m_face; }
        SR_NODISCARD bool HasColor() const noexcept { return m_hasColor; }
        SR_NODISCARD bool IsColorEmoji() const noexcept { return m_isColorEmoji; }

        SR_NODISCARD uint8_t* CopyData() const noexcept;

        SR_NODISCARD FT_Glyph GetGlyph(char32_t code, FT_Render_Mode renderMode, FT_Int32 charLoad, FT_Int32 glyphLoad) const;
        SR_NODISCARD FT_Glyph GetGlyph(char32_t code, FT_Render_Mode renderMode) const;

        SR_NODISCARD FT_Pos GetKerning(uint32_t leftCharCode, uint32_t rightCharCode) const;

        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;

        bool SetPixelSizes(uint32_t w, uint32_t h);
        bool SetCharSize(uint32_t w, uint32_t h, uint32_t wRes, uint32_t hRes);

    protected:
        bool Unload() override;
        bool Load() override;

    private:
        bool MathGlyphSizes(const StringType& text, uint32_t align, uint32_t valign, uint32_t space);
        bool InitImage(uint8_t** pImage, const StringType& text, uint32_t align, uint32_t space);

    private:
        uint8_t* m_textureData = nullptr;

        FT_Render_Mode m_renderMode = FT_RENDER_MODE_NORMAL;

        FontLibraty m_library = nullptr;
        FontFace m_face = nullptr;
        uint32_t m_fontSize = 0;

        int32_t m_glyphWidth = 0;
        uint32_t m_glyphHeight = 0;

        uint32_t m_maxGlyphHeight = 0;
        uint32_t m_maxGlyphWidth = 0;

        uint32_t m_topRow = 0;

        uint32_t m_imageHeight = 0;
        uint32_t m_imageWidth = 0;

        bool m_hasColor = false;
        bool m_isColorEmoji = false;

    };
}

#endif //SRENGINE_FONT_H
