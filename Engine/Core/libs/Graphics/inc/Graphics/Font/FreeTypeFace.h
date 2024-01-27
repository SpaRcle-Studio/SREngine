//
// Created by Monika on 06.11.2022.
//

#ifndef SR_ENGINE_FREETYPEFACE_H
#define SR_ENGINE_FREETYPEFACE_H

#include <Graphics/Font/FreeType.h>
#include <Graphics/Font/FreeTypeDrawContext.h>

namespace SR_GRAPH_NS {
    class FreeTypeDrawContext;

    class FreeTypeFace : SR_UTILS_NS::NonCopyable {
    public:
        explicit FreeTypeFace(FT_Face face)
            : m_face(face)
        { }

        ~FreeTypeFace() override = default;

    public:
        SR_NODISCARD bool CalculateBox(uint32_t codePoint, FreeTypeDrawContext* pContext, FT_Int32 loadFlags, FT_Render_Mode renderMode) {
            if (!RenderGlyph(codePoint, loadFlags, renderMode)) {
                SR_ERROR("FreeTypeFace::CalculateBox() : failed to render glyph!");
                return false;
            }

            int32_t resize = 0;

            FT_Glyph glyph = nullptr;

            if (FT_Get_Glyph(m_face->glyph, &glyph)) {
                SR_ERROR("FreeTypeFace::CalculateBox() : failed to get glyph!");
                return false;
            }

            FT_Glyph_To_Bitmap(&glyph, renderMode, nullptr, 1);
            auto&& bitmap_glyph = (FT_BitmapGlyph)glyph;
            FT_Bitmap bitmap = bitmap_glyph->bitmap;

            if (bitmap_glyph->top < 0) {
                resize = bitmap.rows + SR_ABS(bitmap_glyph->top);
            }
            else {
                resize = bitmap.rows > bitmap_glyph->top ? bitmap.rows - bitmap_glyph->top : bitmap_glyph->top - bitmap.rows;
            }

            if (pContext->m_height < bitmap.rows + resize) {
                pContext->m_height = SR_MAX(0, static_cast<int32_t>(bitmap.rows) + resize);
            }

            if (pContext->m_height > 32768) {
                SRHalt("FreeTypeFace::CalculateBox() : very big height!\n\tHeight: " + std::to_string(pContext->m_height));
                return false;
            }

            pContext->m_width += bitmap.width;

            if (pContext->m_topRow < bitmap.rows) {
                pContext->m_topRow = bitmap.rows;
            }

            if (pContext->m_maxGlyphHeight < bitmap.rows + bitmap_glyph->top) {
                pContext->m_maxGlyphHeight = bitmap.rows + bitmap_glyph->top;
            }

            return true;
        }

        SR_NODISCARD bool DrawCodePoint(FreeTypeDrawContext* context, uint32_t codePoint, FT_Int32 loadFlags, FT_Render_Mode renderMode) {
            if (!RenderGlyph(codePoint, loadFlags, renderMode))
                return false;

            //if (codePoint == '\n') {
            //    m_imageHeight += m_maxGlyphHeight;
            //    m_imageWidth = 0;
            //    return true;
            //}

            return DrawBitmap(context, m_face->glyph);
        }

    private:
        SR_NODISCARD bool RenderGlyph(char32_t codePoint, FT_Int32 loadFlags, FT_Render_Mode renderMode) const {
            if (!m_face) {
                return false;
            }

            const uint32_t glyph_index = FT_Get_Char_Index(m_face, codePoint);

            if (FT_Load_Glyph(m_face, glyph_index, loadFlags)) {
                SR_ERROR("FreeTypeFace::RenderGlyph() : failed to load glyph!");
                return false;
            }

            if (FT_Render_Glyph(m_face->glyph, renderMode)) {
                SR_ERROR("FreeTypeFace::RenderGlyph() : failed to render glyph!");
                return false;
            }

            return true;
        }

        SR_NODISCARD static bool DrawBitmap(FreeTypeDrawContext* pContext, FT_GlyphSlot slot) {
            int32_t posY = posY = slot->bitmap.rows - slot->bitmap_top;
            int32_t topY = pContext->m_topRow - slot->bitmap.rows;

            for (uint32_t y = 0, j = 0; y < slot->bitmap.rows; ++y) {
                for (uint32_t x = 0; x < slot->bitmap.width; ++x, ++j) {
                    if ((m_tmpHeight + posY + y + topY) > m_glyphHeight) {
                        if (posY < 0) posY = abs(posY);
                    }

                    if (m_tmpHeight + posY + y + topY >= m_glyphHeight) {
                        /// TODO: японский язык вызывает краш
                        continue;
                    }

                    uint8_t *src = slot->bitmap.buffer]

                    if (slot->bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                        pRow[pContext->m_tmpWidth + x].a = *(src + (((j + 1) * 4) - 0));
                        pRow[pContext->m_tmpWidth + x].r = *(src + (((j + 1) * 4) - 1));
                        pRow[pContext->m_tmpWidth + x].g = *(src + (((j + 1) * 4) - 2));
                        pRow[pContext->m_tmpWidth + x].b = *(src + (((j + 1) * 4) - 3));
                    }
                    else {
                        const uint8_t character = src[j];
                        pRow[pContext->m_tmpWidth + x].r = 0;
                        pRow[pContext->m_tmpWidth + x].g = 0;
                        pRow[pContext->m_tmpWidth + x].b = 0;
                        pRow[pContext->m_tmpWidth + x].a = character;
                    }
                }
            }

            return true;
        }

    private:
        FT_Face m_face;

    };
}

#endif //SR_ENGINE_FREETYPEFACE_H
