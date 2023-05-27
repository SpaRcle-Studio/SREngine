//
// Created by Monika on 14.02.2022.
//

#include <Graphics/Font/Font.h>
#include <Graphics/Font/SDF.h>

#include <freetype/include/freetype/ftglyph.h>

namespace SR_GTYPES_NS {
    Font::Font()
        : Super(SR_COMPILE_TIME_CRC32_TYPE_NAME(Font), true /** auto remove */)
        , m_fontSize(16)
    { }

    Font* Font::Load(const SR_UTILS_NS::Path& rawPath) {
        SR_GLOBAL_LOCK

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(rawPath).RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());

        if (auto&& pResource = SR_UTILS_NS::ResourceManager::Instance().Find<Font>(path)) {
            return pResource;
        }

        auto&& pResource = new Font();

        pResource->SetId(path, false /** auto register */);

        if (!pResource->Reload()) {
            SR_ERROR("Font::Load() : failed to load font! \n\tPath: " + path.ToString());
            delete pResource;
            return nullptr;
        }

        /// отложенная ручная регистрация
        SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pResource);

        return pResource;
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

    bool Font::Unload() {
        if (m_library) {
            FT_Done_FreeType(m_library);
            m_library = nullptr;
        }

        if (m_textureData) {
            delete[] m_textureData;
            m_textureData = nullptr;
        }

        return IResource::Unload();
    }

    bool Font::Load() {
        FT_Init_FreeType(&m_library);

        SR_UTILS_NS::Path&& path = SR_UTILS_NS::Path(GetResourceId());
        if (!path.IsAbs()) {
            path = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path);
        }

        if (FT_New_Face(m_library, path.c_str(), 0, &m_face)) {
            SR_ERROR("Font::Load() : failed to load free-type font! \n\tPath: " + path.ToString());
            return false;
        }

        if (FT_Select_Charmap(m_face, FT_ENCODING_UNICODE)) {
            SR_ERROR("Font::Load() : failed to set char map!");
            return false;
        }

        m_hasColor = FT_HAS_COLOR(m_face);

        static const uint32_t tag = FT_MAKE_TAG('C', 'B', 'D', 'T');
        FT_ULong length = 0;
        FT_Load_Sfnt_Table(m_face, tag, 0, nullptr, &length);
        m_isColorEmoji = length > 0;

        return IResource::Load();
    }

    SR_UTILS_NS::Path Font::GetAssociatedPath() const {
        return SR_UTILS_NS::ResourceManager::Instance().GetResPath();
    }

    bool Font::SetPixelSizes(uint32_t w, uint32_t h) {
        if (IsColorEmoji()) {
            if (m_face->num_fixed_sizes == 0) {
                SR_ERROR("Font::SetPixelSizes() : num fixes sizes is zero!");
                return false;
            }

            int32_t best_match = 0;
            int32_t diff = std::abs(static_cast<int32_t>(h - m_face->available_sizes[0].width));
            for (int32_t i = 1; i < m_face->num_fixed_sizes; ++i) {
                int32_t ndiff = std::abs(static_cast<int32_t>(h - m_face->available_sizes[i].width));
                if (ndiff < diff) {
                    best_match = i;
                    diff = ndiff;
                }
            }

            if (FT_Select_Size(m_face, best_match)) {
                SR_ERROR("Font::SetPixelSizes() : failed to select size!");
                return false;
            }
        }
        else {
            if (FT_Set_Pixel_Sizes(m_face, w, h)) {
                SR_ERROR("Font::SetPixelSizes() : failed to set pixel sizes!");
                return false;
            }
        }

        return true;
    }

    bool Font::SetCharSize(uint32_t w, uint32_t h, uint32_t wRes, uint32_t hRes) {
        if (auto&& err = FT_Set_Char_Size(m_face, w, h, wRes, hRes)) {
            SR_ERROR("Font::SetCharSize() : failed to set char size!\n\tError: " + SRFreeTypeErrToString(err));
            return false;
        }

        return true;
    }

    FT_Pos Font::GetKerning(uint32_t leftCharCode, uint32_t rightCharCode) const {
        if (!FT_HAS_KERNING(m_face)) {
            return 0;
        }

        /// Получаем индекс левого символа
        FT_UInt leftIndex = FT_Get_Char_Index(m_face, leftCharCode);
        /// Получаем индекс правого символа
        FT_UInt rightIndex = FT_Get_Char_Index(m_face, rightCharCode);
        /// Здесь будет хранится кернинг в формате 26.6
        FT_Vector delta;
        /// Получаем кернинг для двух символов
        FT_Get_Kerning(m_face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &delta);

        return delta.x;
    }

    FT_Glyph Font::GetGlyph(char32_t code, FT_Render_Mode renderMode) const {
        if (HasColor()) {
            return GetGlyph(code, renderMode, FT_LOAD_RENDER, FT_LOAD_COLOR);
        }

        return GetGlyph(code, renderMode, FT_LOAD_RENDER, FT_LOAD_DEFAULT);
    }

    FT_Glyph Font::GetGlyph(char32_t code, FT_Render_Mode renderMode, FT_Int32 charLoad, FT_Int32 glyphLoad) const {
         FT_Glyph glyph = nullptr;

        if (FT_Load_Char(m_face, code, charLoad)) {
            SR_WARN("Font::GetGlyph() : failed to load char!");
            return nullptr;
        }

        FT_UInt glyph_index = FT_Get_Char_Index(m_face, code);

        if (FT_Load_Glyph(m_face, glyph_index, glyphLoad)) {
            SR_WARN("Font::GetGlyph() : failed to load glyph!");
            return nullptr;
        }

        if (FT_Render_Glyph(m_face->glyph, renderMode)) {
            SR_WARN("Font::GetGlyph() : failed to render glyph!");
            return nullptr;
        }

        if (FT_Get_Glyph(m_face->glyph, &glyph)) {
            SR_WARN("Font::GetGlyph() : failed to get glyph!");
            return nullptr;
        }

        return glyph;
    }
}